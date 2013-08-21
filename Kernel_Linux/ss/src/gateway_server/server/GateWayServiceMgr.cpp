//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 10012 $
// $Author: xfzhuang $
// $Date: 2012-09-04 22:31:06 +0800 (鍛ㄤ簩, 2012-09-04) $
//
// Define class CGateWayServiceMgr.
//

#include "GateWayServiceMgr.h"

#include <list>
#include <map>

#include "DCenterServerMsg.h"
#include "ClientIDGenerator.h"
#include "ConnectSinkMgr.h"
#include "Header.h"
#include "ILog.h"
#include "IEventEngine.h"

CGateWayServiceMgr *g_GateWayServiceMgr = NULL;

CGateWayServiceMgr::CGateWayServiceMgr(/*const core::InetAddress &address,*/
    const char *ip, WORD port, const std::string &name)
    : TCPServer(core::InetAddress(port), name), m_wPort(port) {
  strncpy(this->m_szIp, ip, sizeof(this->m_szIp));
}

CGateWayServiceMgr::~CGateWayServiceMgr(void) {
  this->m_ServerKernelCreateHelper.Close();
}

// Initialize and start center client.
bool CGateWayServiceMgr::Initialize(s32 nGateWayID, const core::InetAddress &center_address,
       s32 nMaxConnectNum, const ServerConfigure &configure) {
  if(this->m_ServerKernelCreateHelper.Create() == FALSE) {
    printf("[ERROR] %s:%d (%s) 创建服务器引擎失败!\n",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  char id[10];
  snprintf(id, sizeof(id), "_%d", nGateWayID);

  IServerKernel *kernel = this->GetServerKernel();
  if(kernel && kernel->Initialize(configure.GetCoreDir(),
         configure.GetCoreLog() + id, configure.CheckDeamon())) {
    if(kernel->CreateLog(&this->m_pServerLog, configure.GetLogicLog() + id) == FALSE) {
      printf("[ERROR] %s:%d (%s) CreateLog error!!\n",
             __FILE__, __LINE__, __FUNCTION__);
      return false;
    }

    const core::InetAddress *local_address = this->GetLocalAddress();
    char center_ip[17];
    u16 center_port = 0;
    center_address.GetAddressInfo(center_ip, sizeof(center_ip), center_port);

    // local_address->GetAddressInfo(this->m_szIp, 17, this->m_wPort);

    // 初始化相关成员变量
    m_nGateWayID = nGateWayID;
    m_nMaxConnectNum = nMaxConnectNum;
    ClientIDGenerator::getInstance()->SetGatewayID(nGateWayID);

    // 读取DB前端配置
    s32 nErrLine = 0;
    if(!m_DBServerConfigMgr.Load(configure.GetDBServerIni().c_str(), nErrLine)) {
      this->m_pServerLog->TraceErrorLn("读取%s的错误，行号为%d!", configure.GetDBServerIni().c_str());
      return false;
    }

    // 创建全局客户端连接管理器
    m_pConnectSinkManager = new CConnectSinkManager();
    if(NULL == m_pConnectSinkManager) {
      this->m_pServerLog->TraceErrorLn("CLoginServiceMgr::Start失败, 创建全局客户端连接管理器!");
      return false;
    }

    // 创建全局客户端用户管理器
    m_pConnectSinkPool = new CConnectSinkPool();
    if(NULL == m_pConnectSinkPool) {
      this->m_pServerLog->TraceErrorLn("CLoginServiceMgr::Start失败, 创建全局客户端用户管理器!");
      return false;
    }

    if(kernel->CreateEventEngine(&this->m_pEventEngine) == false) {
      this->m_pServerLog->TraceErrorLn("[ERROR] %s:%d (%s) 创建事件引擎失败!",
             __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
    if(kernel->CreateTimerAxis(&this->m_pTimerAxis) == false) {
      this->m_pServerLog->TraceErrorLn("[ERROR] %s:%d (%s) 创建时间轴失败!",
             __FILE__, __LINE__, __FUNCTION__);
      return false;
    }

    SVestibCreateParam stCreateParam;
    stCreateParam.pServerKernel =  GetServerKernel();
    stCreateParam.pTrace= m_pServerLog;
    stCreateParam.pTimeAxis = m_pTimerAxis;
    strncpy(stCreateParam.lpszAppName, "网关服务器", sizeof(stCreateParam.lpszAppName));
    stCreateParam.lType= CENTER_ST_GATEWAY;
    stCreateParam.dwAppID = nGateWayID; // 登录服务器为1000

    if (FALSE == m_VestibuleMgrHelper.Create(this, stCreateParam,
           configure.GetDBClientSo().c_str())) {
      this->m_pServerLog->TraceErrorLn("CLoginServiceMgr::Start失败, 创建DB前置机管理器接口失败!");
      return false;
    }

    std::list<SDBServerConfig>& listDBConfig = m_DBServerConfigMgr.GetAllDBConfig();
    for(std::list<SDBServerConfig>::iterator Iter = listDBConfig.begin();
           Iter != listDBConfig.end(); ++Iter)
    {
      // 创建前置机
      IVestibule* pVestibule = m_VestibuleMgrHelper.m_pVestibuleMgr->Start(Iter->dwDBServerID,
             Iter->szDBServerIP, Iter->dwDBServerPort, this, stCreateParam.lpszAppName,
             stCreateParam.lType, stCreateParam.dwAppID, TRUE);
      if( NULL == pVestibule ) {
        this->m_pServerLog->TraceErrorLn("CLoginServiceMgr::Start失败, 创建DB前置机接口失败!");
        return false;
      }
    }

    // 创建中心服客户端
    if(!m_CenterClientHelper.Create(this, m_pTimerAxis, m_pServerLog,
           GetServerKernel(), center_ip, center_port, configure.GetCenterClientSo().c_str())) {
      this->m_pServerLog->TraceErrorLn("加载大厅服插件失败! 中心服 IP = %s 端口= %d", center_ip, center_port);
      return false;
    }

    ITimerAxis* pTime = GetTimerAxis();
    if(pTime) {
      pTime->SetTimer(TIMER_WRITE_ON_LINE_NUM, TIMER_INTERVAL_VALUE, this);
      m_bStartTimer = TRUE;
    }

    return true;
  }

  return false;
}


void CGateWayServiceMgr::OnStop() {
  m_CenterClientHelper.Close();
  // 销毁客户端连接管理器
  if(NULL != m_pConnectSinkManager) {
    m_pConnectSinkManager->Restore();
    delete m_pConnectSinkManager;
    m_pConnectSinkManager = NULL;
  }
  //销毁客户端用户管理器
  if(NULL != m_pConnectSinkPool) {
    delete m_pConnectSinkPool;
    m_pConnectSinkPool = NULL;
  }

  m_GameClientMgr.Close();

  // 关闭前端客户端
  m_VestibuleMgrHelper.Close();

  if(m_bStartTimer)
  {
    ITimerAxis* pTime = GetTimerAxis();
    if(pTime) {
      pTime->KillTimer(TIMER_WRITE_ON_LINE_NUM,this);
      m_bStartTimer = FALSE;
    } else {
      m_pServerLog->TraceLn("网关服定时器可能没有关闭.");
    }
  }

  if(m_pTimerAxis != NULL) {
    m_pTimerAxis->Release();
    m_pTimerAxis = NULL;	
  }

  if(m_pEventEngine != NULL) {
    this->m_pEventEngine->Release();
    this->m_pEventEngine = NULL;
  }

  if(NULL != m_pServerLog) {
    // 关闭日志系统
    m_pServerLog->Release();
    m_pServerLog = NULL;
  }
}

ConnectionTask *CGateWayServiceMgr::OnConnectionEstablished() {
  if(this->m_pConnectSinkManager->GetConnectNum() >= (u32)this->m_nMaxConnectNum) {
    m_pServerLog->Logger(Info, "%s:%d (%s) 网关服务器已达到人数上限!",
           __FILE__, __LINE__, __FUNCTION__);
    return NULL;
  } else {
    return this->m_ConnectStateSink.OnAccept();
  }
}

BOOL CGateWayServiceMgr::GetInfo(LPSTR szName, s32 nLen, u32 &nID,  u8 &nType, u16 &wPort) {
  if (szName)
  {
    // strncpy(szName, "网关服务器", nLen);
    strncpy(szName, m_szIp, nLen);
  } else {
    return FALSE;
  }

  nType = CENTER_ST_GATEWAY;
  wPort = m_wPort;
  nID = m_nGateWayID;  //登陆服ID 约定为 0

  return TRUE;
}

void CGateWayServiceMgr::OnServerLogin(BOOL bResult, LPCSTR szDesc)
{
  if (bResult) {
    m_pServerLog->TraceLn("登录中心服成功!");
  } else {
    m_pServerLog->TraceErrorLn("登录中心服失败, Desc=%s!", szDesc);
  }
}

void CGateWayServiceMgr::OnServerLogout() {
  m_pServerLog->TraceErrorLn("与中心服断开连接!");
}

void CGateWayServiceMgr::OnSendDataToActor(s32 lActorID, LPSTR buf, s32 nLen) {
  return;
}

// 发给某个房间数据的处理
void CGateWayServiceMgr::OnSendDataToRoom(s32 lMapID, LPSTR buf, s32 nLen) {
  return;
}

// 全服务器广播数据的处理
void CGateWayServiceMgr::OnBroadcastData(LPSTR buf, s32 nLen) {
  return;
}

void CGateWayServiceMgr::OnAppInfo(LPSTR buf, s32 nLen) {
  if(NULL == buf || nLen != sizeof(SServerLoginInfo)) {
    m_pServerLog->TraceErrorLn("CCenterClient::OnOnlineActorNum失败, 接收到非法数据!");
    return;
  }

  SServerLoginInfo *pInfo = (SServerLoginInfo*)buf; 

  // 非游戏服务器直接返回
  if(pInfo->nType != CENTER_ST_ROOM && pInfo->nType != CENTER_ST_LOBBY) {
    return;
  }
  if(FALSE == pInfo->bLoginBlg) {
    // 根据 游戏服ID 查找 游戏服连接指针
    CGameClientConn * pGameClientConn = m_GameClientMgr.FindGameConnByGameID(pInfo->ServerID);
    if(NULL != pGameClientConn) {
      // 删除游戏服链接指针，否则玩家再次需要登录此游戏服时，由于m_bIsRun变量为False，进入不了游戏
      m_GameClientMgr.DelGameConn(pGameClientConn);
    }
    return;
  }
  m_GameClientMgr.CreateGameConn(pInfo->ServerID,pInfo->szIP,pInfo->wPort);
  return;
}

void CGateWayServiceMgr::OnVestibuleWarning(s32 nErrorCode, const char *szDesc) {
  if (VESTIBULE_WARN_CONNECTED == nErrorCode) {
    m_pServerLog->TraceLn("%s", szDesc);
  } else {
    m_pServerLog->TraceErrorLn("前置机报警, nErrorCode[%d], szDesc[%s]", nErrorCode, szDesc);
  }
}

BOOL CGateWayServiceMgr::FindLobbyServer(s64 qwUserID, SServerKey &Key) {
  CGameClientConn* pLobbyClientConn = m_GameClientMgr.FindLobbyConn(qwUserID);
  if(NULL == pLobbyClientConn) {
    return FALSE;
  }
  Key.nType = pLobbyClientConn->GetServerType();
  strcpy(Key.szIP, pLobbyClientConn->GetServerIP());
  Key.wPort = pLobbyClientConn->GetPort();
  return TRUE;
}

CGameClientConn * CGateWayServiceMgr::FindGameConn(LPCSTR lpServerIP, u16 wPort){
  return m_GameClientMgr.FindGameConnByServerInfo(lpServerIP,wPort);
}

void CGateWayServiceMgr::OnTimer(DWORD dwEventID) {
  // 定时记录在线人数
  int nOnlineNum = m_pConnectSinkManager->GetConnectNum();
  //OutOnlineNumInfoLog("%d",nOnlineNum);
}

IVestibule* CGateWayServiceMgr::GetVestibule(u64 qwUserID) {
  // TODO by zipher for DBServer
  std::map<u32, IVestibule*>& mapVestibule = m_VestibuleMgrHelper.m_pVestibuleMgr->GetAllVestibule();
  if(mapVestibule.empty()) {
    return NULL;
  }
  u32 nMaxDBNum = mapVestibule.size();
   u32 nOffset = (qwUserID + nMaxDBNum - 1) % nMaxDBNum;
  std::map<u32, IVestibule*>::iterator Iter = mapVestibule.begin();
  for(size_t i = 0; i < nOffset; ++i) {
    Iter++;
    if(Iter == mapVestibule.end()) {
      return NULL;
    }
  }
  return Iter->second;
}
