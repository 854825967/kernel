//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 6049 $
// $Author: than $
// $Date: 2012-03-16 21:58:07 +0800 (鍛ㄤ簲, 2012-03-16) $
//
// Define class CVestibuleMgr.
//

#include "DBClientMgr.h"

#include <map>

#include "DBClient.h"
#include "Header.h"
#include "ILog.h"
#include "core/inet_address.h"

CVestibuleMgr::CVestibuleMgr() {}

CVestibuleMgr::~CVestibuleMgr() {}

// 释放
void CVestibuleMgr::Release() {
  for(std::map<u32, IVestibule*>::iterator Iter = m_mapVestibure.begin();
         Iter != m_mapVestibure.end(); ++Iter) {
    IVestibule* pVestibule = Iter->second;
    if( NULL != pVestibule ) {
      pVestibule->Release();
    }
  }
  m_mapVestibure.clear();
  delete this;
  return;
}

// 启动前置机
IVestibule* CVestibuleMgr::Start(u32 dwDBServerID, LPCSTR lpszServerIP,
       u16 wServerPort, IDBClientWarningSink *pVestibuleWarningSink,
       LPCSTR lpszAppName, u8 lType, u32 dwAppID, BOOL bReConnect) {
  if( m_mapVestibure.find(dwDBServerID) != m_mapVestibure.end() ) {
    return NULL;
  }

  if(lpszServerIP == NULL || pVestibuleWarningSink == NULL || lpszAppName == NULL) {
    return NULL;
  }

  core::InetAddress address(lpszServerIP, wServerPort);
  CVestibule* pVestibule = new CVestibule(address, lpszAppName);
  if( NULL == pVestibule ) {
    return NULL;
  }

  BOOL bRet = pVestibule->Create(pVestibuleWarningSink, lType, dwAppID, bReConnect);
  if(!bRet) {
    delete pVestibule;
    return NULL;
  }

  m_mapVestibure[dwDBServerID] = pVestibule;

  return (IVestibule*)pVestibule;
}

// 停止前置机
void CVestibuleMgr::Stop(u32 dwDBServerID) {
  std::map<u32, IVestibule*>::iterator Iter = m_mapVestibure.find(dwDBServerID);
  if(Iter == m_mapVestibure.end()) {
	return;
  }

  IVestibule* pVestibule = Iter->second;
  if(NULL == pVestibule) {
	return;
  }

  pVestibule->Release();
  return;
}

// 创建前置机管理
extern "C" BOOL CreateVestibuleMgr(ILog *pTrace, IServerKernel *pServerKernel,
       ITimerAxis *pTimeAxis, IVestibuleMgr **ppVestibuleMgr) {
  if (NULL == pTrace || NULL == pServerKernel || NULL == pTimeAxis) {
    return FALSE;
  } 

  g_pTrace = pTrace;
  g_pServerKernel = pServerKernel;
  g_pTimerAxis = pTimeAxis;

  CVestibuleMgr *pVestibuleMgr = new CVestibuleMgr;
  if (NULL == pVestibuleMgr) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 前置机管理模块New失败!",
           __FILE__, __LINE__, __FUNCTION__);
    return FALSE;
  }

  *ppVestibuleMgr = static_cast<IVestibuleMgr*>(pVestibuleMgr);

  return TRUE;
}

