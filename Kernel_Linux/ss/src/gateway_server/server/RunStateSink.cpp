//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7062 $
// $Author: than $
// $Date: 2012-04-28 11:08:42 +0800 (鍛ㄥ叚, 2012-04-28) $
//
// Define class CRunStateSink.
//

#include "RunStateSink.h"

#include "ConnectSinkMgr.h"
#include "GateWayServiceMgr.h"
#include "ClientIDGenerator.h"
#include "DCenterServerMsg.h"
#include "DMsgLoginFomat.h"
#include "IDataArchive.h"
#include "IDBStruct.h"
#include "ILog.h"
#include "RandClientStr.h"
#include "VestibuleRunSink.h"
#include "VestibuleLoginSink.h"

CRunStateSink::CRunStateSink() : m_dwEnterCode(0), m_byConnectState(enConnState_Login) {
  Clean(FALSE);
  m_pSceneClientConn = NULL;
}

CRunStateSink::~CRunStateSink() {}

void CRunStateSink::OnRecieve(const char *message, int size) {
  if(this->m_byConnectState == enConnState_Login) {
    if(message == NULL || (size_t)size < sizeof(CS_SELECTACTOR_HEAD)) {
      return ;
    }

    CS_SELECTACTOR_MAC_HEAD *msg = (CS_SELECTACTOR_MAC_HEAD *)message;
    if(msg->m_wKeyRoot != CMD_ROOT_SELECTACTOR) {
       return ;
    }

    switch(msg->m_wKeyMain) {
      case ROOTSELECTACTOR_CS_MAIN_MAC: {
        this->InterpretMac(message, (s32)size);
        break;
      }

      default: {
        g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("CRunStateSink::OnRecv(), KeyMain: %d",
               msg->m_wKeyMain);
        break;
      }
    }
  } else if(this->m_byConnectState == enConnState_Running) {
    if(NULL == message || size < 0 || (size_t)size < sizeof(WORD)) {
      return;
    }

    CDataArchive data(m_BuffData,sizeof(m_BuffData)); 
    BYTE byG2MCode = GATEWAY_OR_SCENE_ACTOR_DATA;
    data.Write(&byG2MCode,sizeof(BYTE));
    data.Write(&m_ClientID,sizeof(ClientID));
    data.Write(message, size);

    // 将消息发送到场景服务器
    m_pSceneClientConn->SendData(m_BuffData, data.GetBufferOffset());
  }
}

void CRunStateSink::OnCloseConnection(bool force) {
  g_GateWayServiceMgr->GetServerLog()->TraceLn("CRunStateSink::OnCloseConnection()");
  g_GateWayServiceMgr->GetConnectSinkMgr()->UpdateConnectSink(m_dwConnectIndex, NULL);

  ICenterClient *pCenterClient = g_GateWayServiceMgr->GetCenterClient();
  if(pCenterClient != NULL) {
    pCenterClient->ActorLogout(m_qwUserDBID,m_nActorDBID,1,0);
    g_GateWayServiceMgr->GetServerLog()->TraceLn("网关服玩家数量更新至 %d",
           (g_GateWayServiceMgr->GetConnectSinkMgr())->GetConnectNum());
  }

  // 直接关闭客户端 网关向 场景服务器 发送下线通知
  if(m_pSceneClientConn != NULL) {
    SUSER_LOGOUT userlogout;
    userlogout.m_wKeyRoot = GATEWAY_OR_SCENE_USER_LOGOUT;
    userlogout.lIdenID = m_ClientID;
    userlogout.qwUserDBID = m_qwUserDBID;
    userlogout.nActorDBID = m_nActorDBID;
    m_pSceneClientConn->SendData((LPCSTR)&userlogout,sizeof(userlogout));
  }
  Clean(FALSE);
}

u8 CRunStateSink::GetConnectSinkState(void) {
  return this->m_byConnectState;
}

u32 CRunStateSink::GetGameID(void) {
  return 0;
}

BOOL CRunStateSink::StartConnectSink(u32 dwConnectIndex) {
  if(IsHaveUsed() || this->m_byConnectState != enConnState_Login) {
    // g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("CRunStateSink::StartConnectSink(), " / 
    //        "IsHaveUsed(), dwConnectIndex: %d", dwSocketID, dwConnectIndex);
    return FALSE;
  }

  m_dwConnectIndex = dwConnectIndex;
  m_bIsHaveUsed = TRUE;
  g_GateWayServiceMgr->GetConnectSinkMgr()->UpdateConnectSink(m_dwConnectIndex, this);

  return TRUE;
}

void CRunStateSink::OnConnectionOK() {
  // 随机进入码
  this->m_dwEnterCode = rand() % 100;

  SC_SELECTACTOR_ENTERCODE code(this->m_dwEnterCode);
  this->Send((const char *)(&code), sizeof(SC_SELECTACTOR_ENTERCODE));

  this->m_nState = 1;
}

BOOL CRunStateSink::Clean(BOOL bSink) {
  if(TRUE == bSink) {
    g_GateWayServiceMgr->GetConnectSinkMgr()->UpdateConnectSink(m_dwConnectIndex, NULL);
  }

  memset(m_BuffData,0,sizeof(m_BuffData));

  m_bIsHaveUsed = FALSE;
  m_wClientPort = 0;
  memset(m_szClientIP, 0, sizeof(m_szClientIP));

  m_dwConnectIndex = 0;
  m_qwUserDBID = 0;
  m_nActorDBID = 0;
  m_nTurnSType = 0;
  m_nLogoutType = 0;
  m_nState = 0;
  m_ClientID  = 0;
  m_bIsNextMap = FALSE;
  memset(m_bRandC16, 0, sizeof(m_bRandC16));
  memset(m_szIP, 0, sizeof(m_szIP));
  m_wPort = 0;
  memset(m_ValidationCode, 0, sizeof(m_ValidationCode));
  memset(m_szUserIpAddress, 0, sizeof(m_szUserIpAddress));
  memset(m_szUserSerialNO, 0, sizeof(m_szUserSerialNO));
  m_pSceneClientConn = NULL;
  m_byConnectState = enConnState_Login;
  m_bJumpFlag = 0;
  // ResetConnection();

  return TRUE;
}

void CRunStateSink::OnMessage(u32 dwMessage, LPCSTR pData, s32 nDataLen) {
  switch(dwMessage) {
    case enConnSink_UserLogin_V: {
      SUSER_LOGIN_V *pUserLogin_V = (SUSER_LOGIN_V *) pData;
      m_ClientID = ClientIDGenerator::getInstance()->Generate(m_dwConnectIndex);
      pUserLogin_V->m_wKeyRoot = GATEWAY_OR_SCENE_ACTOR_LOGIN;
      pUserLogin_V->lIdenID =m_ClientID;
      m_qwUserDBID = pUserLogin_V->qwUserDBID;
      m_nActorDBID = pUserLogin_V->nActorDBID;
      m_nTurnSType = pUserLogin_V->nTurnSType;
      memcpy(m_szUserIpAddress, pUserLogin_V->ipAddress, sizeof(m_szUserIpAddress));  
      memcpy(m_szUserSerialNO, pUserLogin_V->szSerialNO, sizeof(m_szUserSerialNO));  
      memcpy(m_bRandC16, pUserLogin_V->RandMac16, sizeof(m_bRandC16));  

      SServerKey Key;
      // 根据账号ID负载均衡至每个大厅服务器
      if(FALSE == g_GateWayServiceMgr->FindLobbyServer(m_qwUserDBID, Key)) {
        SC_ERRORCODE_MSGFORMAT ErrorMsg(ERROR_CODE_GAMESERVERBUSY);
        strncpy(ErrorMsg.m_szErrorDesc, "大厅服务器未开启，请稍后再试，或者联系GM",
               sizeof(ErrorMsg.m_szErrorDesc));
        KickUser(ErrorMsg);
        return;
      }

      // 向大厅服务器发送数据
      m_pSceneClientConn  = g_GateWayServiceMgr->FindGameConn(Key.szIP,Key.wPort);
      if(m_pSceneClientConn == NULL) {
        SC_ERRORCODE_MSGFORMAT ErrorMsg(ERROR_CODE_GAMESERVERBUSY);
        strncpy(ErrorMsg.m_szErrorDesc, "大厅服务器未启动完毕，请稍后再试，或者联系GM", 
               sizeof(ErrorMsg.m_szErrorDesc));
        KickUser(ErrorMsg);
        return;
      }

      g_GateWayServiceMgr->GetServerLog()->TraceLn("发送玩家数据到大厅服登录 SceneID = %d , qwUserDBID = %ld, ActorID = %d",
             m_pSceneClientConn->GetGameID(), m_qwUserDBID, m_nActorDBID);
      m_pSceneClientConn->SendData(pData,nDataLen);

      ICenterClient *pCenterClient  = g_GateWayServiceMgr->GetCenterClient();
      if (pCenterClient != NULL) {
        pCenterClient->ActorLogin(m_qwUserDBID,m_nActorDBID,"",0,0);

        g_GateWayServiceMgr->GetServerLog()->TraceLn("网关服玩家数量更新至 %d",
               (g_GateWayServiceMgr->GetConnectSinkMgr())->GetConnectNum());
      }

      m_nState = 1;
      break;
    }

    case enConnSink_NextZone: {
      SChangeZone* pChangeZone = (SChangeZone *)pData;


      // 如果是切换场景服，则向前端请求跳转完成
      SLoginUserJumpFinish_Set JumpFinishSet;
      JumpFinishSet.qwUserID = m_qwUserDBID;
      memcpy(JumpFinishSet.szRand, m_bRandC16, sizeof(m_bRandC16));
      memcpy(JumpFinishSet.ValidationCode, pChangeZone->ValidationCode, sizeof(pChangeZone->ValidationCode));
      g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("网关服跳转服务器令牌: (%d, %d, %d, %d)",
             (JumpFinishSet.ValidationCode)[0], (JumpFinishSet.ValidationCode)[1],
             (JumpFinishSet.ValidationCode)[2], (JumpFinishSet.ValidationCode)[3]);
      IVestibule *pVestibule = g_GateWayServiceMgr->GetVestibule(m_qwUserDBID);
      BOOL bRet = pVestibule->Request(m_dwConnectIndex, REQ_VESTIB_LOGIN_USER_JUMP_FINISH, 
             m_qwUserDBID, (char *) &JumpFinishSet, 
             sizeof(JumpFinishSet), &g_VestibuleRunSink);

      if (FALSE == bRet) {
        g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("向前端发送帐号验证请求失败, UserDBID: %ld", m_qwUserDBID);

        SC_ERRORCODE_MSGFORMAT ErrorMsg(ERROR_CODE_GAMESERVERBUSY);
        strncpy(ErrorMsg.m_szErrorDesc, "服务器出错，请稍后再试，或者联系GM", 
               sizeof(ErrorMsg.m_szErrorDesc));

        KickUser(ErrorMsg);
        return;
      }

      // 向场景服务器发送数据
      m_pSceneClientConn = g_GateWayServiceMgr->FindGameConn(pChangeZone->szIP,pChangeZone->wPort);
      if(m_pSceneClientConn == NULL) {
        SC_ERRORCODE_MSGFORMAT ErrorMsg(ERROR_CODE_GAMESERVERBUSY);
        strncpy(ErrorMsg.m_szErrorDesc, "目标服务器未启动完毕，请稍后再试，或者联系GM", 
               sizeof(ErrorMsg.m_szErrorDesc));
        g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("FindGameConn get a NULL!!");
        KickUser(ErrorMsg);
        return;
      }

      m_nTurnSType = LOGIN_USER_JUMP_TYPE_CHANGE_SCENE;

      // 发送数据到场景服务器 帐号进行登陆喽
      SUSER_LOGIN_V UserLogin_V;
      UserLogin_V.lIdenID = m_ClientID;
      UserLogin_V.m_wKeyRoot = GATEWAY_OR_SCENE_ACTOR_LOGIN;
      UserLogin_V.qwUserDBID = m_qwUserDBID;
      UserLogin_V.nActorDBID = m_nActorDBID;
      UserLogin_V.nTurnSType = m_nTurnSType;
      UserLogin_V.nLobbyServerID = pChangeZone->nLobbyServerID;

      memcpy(UserLogin_V.RandMac16, m_bRandC16, sizeof(m_bRandC16));  
      m_pSceneClientConn->SendData((LPCSTR)&UserLogin_V,sizeof(UserLogin_V));

      g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("玩家UserDBID: %ld跳转场景服务器成功！", m_qwUserDBID); 
      break;
    }

    case enConnSink_AgainSelectSceneSvr: {
      break;
    }

    default:
      break;
  }
}

void CRunStateSink::SendData(LPCSTR pData, s32 nDataLen) {
  this->Send(pData, nDataLen);
}

void CRunStateSink::OnTimer(DWORD dwTimerID) {}

BOOL CRunStateSink::CloseConnects(CLOSE_CONN enReason) {
  this->CloseConnection();
  return TRUE;
}

void CRunStateSink::OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID,
       s32 nRequestID, LPSTR pOutData, s32 nOutDataLen, 
       LPSTR pInData, s32 nInDataLen) {
  if(this->m_byConnectState != enConnState_Login)
    return ;

  switch(nRequestID) {
    case REQ_VESTIB_LOGIN_USER_JUMP_FINISH: {
      if(this->m_nState != 2) {
        g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
               "CRunStateSink::OnRet(), nRequestID: %d, UserDBID: %ld, State: %d, nIndex: %d", 
		nRequestID, m_qwUserDBID, m_nState, nIndex);
        return ;
      }
      SLoginUserJumpFinish_Get *pJumpFinishGet = (SLoginUserJumpFinish_Get *) pOutData;
      if(VESTIBULE_RET_RECV_RESULT != nRetCode || NULL == pJumpFinishGet || 
             sizeof(SLoginUserJumpFinish_Get) != nOutDataLen || 1 != pJumpFinishGet->lReturn) {
        SC_ERRORCODE_MSGFORMAT ErrorMsg(ERROR_CODE_GAMESERVERBUSY);
        if (VESTIBULE_RET_REQ_REPEATLY_LOGIN == nRetCode) {
          strncpy(ErrorMsg.m_szErrorDesc, "您的帐号已经登录游戏,请重新登陆!", 
                 sizeof(ErrorMsg.m_szErrorDesc));
        }
        else {
          strncpy(ErrorMsg.m_szErrorDesc, "您的帐号身份验证失败，请重新登录，或者联系GM!", 
                 sizeof(ErrorMsg.m_szErrorDesc));
        if (NULL == pOutData) {
          g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
                 "CRunStateSink::OnRet(), nRequestID: %d, UserDBID: %ld, nRetCode: %d, pOutData == NULL", 
                 nRequestID, m_qwUserDBID, nRetCode);
        }
        else {
          g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
                 "CRunStateSink::OnRet(), nRequestID: %d, UserDBID: %ld, nRetCode: %d, nLen: %d, %s", 
                 nRequestID, m_qwUserDBID, nRetCode, nOutDataLen, pOutData);
		      }
        }

        KickUser(ErrorMsg);
        return;
      }

      m_nState = 3;
      TurnToRunState(pJumpFinishGet->lJumpType);
    }
  }
}

void CRunStateSink::InterpretMac(LPCSTR pBuf, s32 nLen) {
  if(this->m_nState != 1 || pBuf == NULL || nLen != sizeof(CS_SELECTACTOR_MAC_HEAD)) {
    g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("CRunStateSink::InterpretMac(), m_nState: %d, nLen: %d",
           m_nState, nLen);
    return ;
  }

  CS_SELECTACTOR_MAC_HEAD *pHead = (CS_SELECTACTOR_MAC_HEAD *)(pBuf);
  m_qwUserDBID = pHead->m_qwUserID;
  m_nActorDBID = pHead->m_dwActorID;

#ifdef _LOGIC_DEBUG
  g_GateWayServiceMgr->GetServerLog()->TraceLn("CRunStateSink::InterpretMac UserID=%ld", m_qwUserDBID);
#endif

  memcpy(m_szUserSerialNO,pHead->szSerialNO,sizeof(m_szUserSerialNO));
  m_szUserSerialNO[19] ='\0';

  SRAND_BUF RandBuf;
  memcpy(RandBuf.RandBuf, pHead->m_MACBuf, sizeof(RandBuf.RandBuf));

  CRandClientStr RandMAC;
  SLoginUserJumpFinish_Set JumpFinishSet;
  JumpFinishSet.qwUserID = m_qwUserDBID;
  memcpy(JumpFinishSet.ValidationCode, pHead->RandChar16_V, sizeof(JumpFinishSet.ValidationCode));
  memcpy(JumpFinishSet.szRand, pHead->szRand, sizeof(JumpFinishSet.szRand));

  IVestibule *pVestibule = g_GateWayServiceMgr->GetVestibule(m_qwUserDBID);
  BOOL bRet = pVestibule->Request(m_dwConnectIndex, REQ_VESTIB_LOGIN_USER_JUMP_FINISH, 
         m_qwUserDBID, (char *) &JumpFinishSet, sizeof(JumpFinishSet), &g_VestibuleLoginSink);

  if(FALSE == bRet) {
    g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("向前端发送帐号验证请求失败, UserDBID: %ld", m_qwUserDBID);
    return;
  }

  m_nState = 2;
}

void CRunStateSink::TurnToRunState(s32 nTurnSType) {
  if(this->m_byConnectState == enConnState_Login) {
    SUSER_LOGIN_V UserLoginV;
    UserLoginV.qwUserDBID = m_qwUserDBID;
    UserLoginV.nActorDBID = m_nActorDBID;
    UserLoginV.nTurnSType = nTurnSType;

    WORD wPort=0;

    this->GetPeerAddress().GetAddressInfo(UserLoginV.ipAddress,
           sizeof(UserLoginV.ipAddress), wPort);

    strncpy(UserLoginV.szSerialNO, m_szUserSerialNO, sizeof(UserLoginV.szSerialNO));

    memcpy(UserLoginV.RandMac16, m_bRandC16, sizeof(UserLoginV.RandMac16));

    this->OnMessage(enConnSink_UserLogin_V, (LPCSTR)(&UserLoginV), sizeof(UserLoginV));

    this->m_byConnectState = enConnState_Running;
  }
}


