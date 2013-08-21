//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 9965 $
// $Author: xfzhuang $
// $Date: 2012-08-31 19:25:45 +0800 (鍛ㄤ簲, 2012-08-31) $
//
// Define class CGateWayServiceMgr.
//

#ifndef __CGATEWAY__SERVICE__H
#define __CGATEWAY__SERVICE__H

#include "ConnectStateSink.h"
#include "DBServerConfigMgr.h"
#include "GameClientMgr.h"
#include "ICenterClient.h"
#include "IDBClient.h"
#include "IServerKernel.h"
#include "ITimeAxis.h"
#include "ServerConfigure.h"
#include "core/tcp_server.h"

#define TIMER_WRITE_ON_LINE_NUM		1
#define TIMER_INTERVAL_VALUE		1000

class CClientUser;
class CGameClientConn;
class CConnectSinkManager;
class CConnectSinkPool;
class ILog;

class CGateWayServiceMgr
       : public IAppServer,
         public core::TCPServer,
         public IDBClientWarningSink,
         public ITimerHandler {
 public:
  CGateWayServiceMgr(/*const InetAddress &address, */const char *ip, WORD port, const std::string &name);
  virtual ~CGateWayServiceMgr(void);

  // Initialize and start center client.
  bool Initialize(s32 nGateWayID, const InetAddress &center_address,
         s32 nMaxConnectNum, const ServerConfigure &configure);

  virtual void OnStop();

  virtual ConnectionTask *OnConnectionEstablished();

  // 获取内核指针
  virtual IServerKernel *GetServerKernel() { return  m_ServerKernelCreateHelper.server_kernel_; }

  // 获取时间轴指针
  virtual ITimerAxis *GetTimerAxis() { return m_pTimerAxis; }

  // 获取网关服日志系统
  virtual ILog*	GetServerLog() { return m_pServerLog; }

  // 事件引擎
  virtual IEventEngine *GetEventEngine() { return m_pEventEngine; }

  // 中心服客户端
  virtual ICenterClient *GetCenterClient() { return m_CenterClientHelper.center_client_; }

  // 数据库前端
  virtual IVestibule *GetVestibule(u64 qwUserID);

  // 全局客户端连接管理器
  CConnectSinkManager* GetConnectSinkMgr() { return m_pConnectSinkManager; }

  // 全局客户端用户管理器
  CConnectSinkPool *GetConnectSinkPool() { return m_pConnectSinkPool; }

  // TimerHandler 接口实现
  virtual void OnTimer(u32 dwEventID);

  // 获取应用服务器信息
  // nLen为szName缓冲区的大小
  // nType参考 DCenterServerMsg.h 的定义
  virtual BOOL GetInfo(LPSTR szName, s32 nLen, u32 &nID, u8 &nType, u16 &wPort);

  // 应用服务器登录处理
  // bResult, TRUE表示登录成功; FALSE表示登录失败
  // szDesc, 登录失败时的描述信息
  virtual void OnServerLogin(BOOL bResult, LPCSTR szDesc);

  // 应用服务器退出处理
  virtual void OnServerLogout(void);

  // 发给某个角色数据的处理
  virtual void OnSendDataToActor(s32 lActorID, LPSTR buf, s32 nLen);

  // 发给某个房间数据的处理
  virtual void OnSendDataToRoom(s32 lMapID, LPSTR buf, s32 nLen);

  // 全服务器广播数据的处理
  virtual void OnBroadcastData(LPSTR buf, s32 nLen);

  // 有服务器登入和登出
  virtual void OnAppInfo(LPSTR buf, s32 nLen);

  virtual void OnSendDataToSociety(LPSTR buf, s32 nLen) {};

  // 前置机报警回调函数
  // nErrorCode: 取值于上面报警定义
  // szDesc: 报警信息描述
  virtual void OnVestibuleWarning(s32 nErrorCode, const char *szDesc);

  // 查找大厅
  virtual BOOL FindLobbyServer(s64 qwUserID, SServerKey &Key);

  void SetServerLog(ILog *log) { this->m_pServerLog = log; }

  CGameClientConn * FindGameConn(LPCSTR lpServerIP, u16 wPort);

  LPCSTR GetServerIP() { return m_szIp; }

  u16 GetServerPort() { return m_wPort; }

  // 获取网关ID
  u32 GetGateWayID() { return m_nGateWayID; }

 private:
  CServerKernelCreateHelper m_ServerKernelCreateHelper;
  CCenterClientHelper m_CenterClientHelper;
  CVestibuleMgrHelper m_VestibuleMgrHelper;
  DBServerConfigMgr m_DBServerConfigMgr;
  CGameClientMgr m_GameClientMgr;
  CConnectStateSink m_ConnectStateSink;
  ILog *m_pServerLog;
  ITimerAxis *m_pTimerAxis;
  IEventEngine *m_pEventEngine;
  CConnectSinkManager *m_pConnectSinkManager;
  CConnectSinkPool *m_pConnectSinkPool;
  char m_szIp[33];
  u16 m_wPort;
  s32 m_nMaxConnectNum;
  u32 m_nGateWayID;
  BOOL m_bStartTimer;
};

extern CGateWayServiceMgr *g_GateWayServiceMgr;

#endif  // __CGATEWAY__SERVICE__H

