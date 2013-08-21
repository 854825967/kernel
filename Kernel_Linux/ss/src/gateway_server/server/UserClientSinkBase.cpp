//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 4417 $
// $Author: than $
// $Date: 2012-02-04 17:38:27 +0800 (鍛ㄥ叚, 2012-02-04) $
//
// Define class CUserClientSinkBase.
//

#include "UserClientSinkBase.h"
#include "GateWayServiceMgr.h"

CUserClientSinkBase::CUserClientSinkBase()
       : m_bIsHaveUsed(FALSE), m_wClientPort(0) {}

CUserClientSinkBase::~CUserClientSinkBase() {}

BOOL CUserClientSinkBase::KickUser(SC_ERRORCODE_MSGFORMAT &ErrorMsg) {
  this->Send((const char *)(&ErrorMsg), sizeof(SC_ERRORCODE_MSGFORMAT));
  this->CloseConnection();
  return TRUE;
}

BOOL CUserClientSinkBase::GetClientInfo(LPSTR szIP, u16 &wPort) {
  if(szIP == NULL) return FALSE;

  if(strlen(this->m_szClientIP) == 0 || m_wClientPort == 0) {
    std::string ip;
    this->GetPeerAddress().GetAddressInfo(ip, this->m_wClientPort);
    strncpy(this->m_szClientIP, ip.c_str(), sizeof(this->m_szClientIP));
  }

  strncpy(szIP, this->m_szClientIP, sizeof(this->m_szClientIP));
  wPort = this->m_wClientPort;

  return TRUE;
}

void CUserClientSinkBase::GetErrorDesc(SC_ERRORCODE_MSGFORMAT &ErrorMsg, s32 nRetCode) {
  switch(nRetCode) {
    case VESTIBULE_RET_REQ_REPEATLY_LOGIN:
      strncpy(ErrorMsg.m_szErrorDesc, "您的账号已经登录游戏！",
             sizeof(ErrorMsg.m_szErrorDesc));
      break;

    default:
      snprintf(ErrorMsg.m_szErrorDesc, sizeof(ErrorMsg.m_szErrorDesc), 
             "进入游戏世界出错，错误码：%d，请稍后再试，或者联系GM", nRetCode);
  }
}

