//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 3934 $
// $Author: than $
// $Date: 2012-01-14 20:13:10 +0800 (鍛ㄥ叚, 2012-01-14) $
//
// Define class CVestibuleMgr.
//

#ifndef __DB__CLIENT__MGR__H
#define __DB__CLIENT__MGR__H

#include <map>

#include "IDBClient.h"

class CVestibuleMgr : public IVestibuleMgr {
 public:
  CVestibuleMgr();
  virtual ~CVestibuleMgr();

  // 释放
  virtual void Release();

  // 启动前置机
  virtual IVestibule* Start(u32 dwDBServerID, LPCSTR lpszServerIP, u16 wServerPort,
         IDBClientWarningSink *pVestibuleWarningSink, LPCSTR lpszAppName, u8 lType,
         u32 dwAppID, BOOL bReConnect);

  // 停止前置机
  virtual void Stop(u32 dwDBServerID);

  // 获取所有前置机
  virtual std::map<u32, IVestibule*>& GetAllVestibule() {
    return m_mapVestibure;
  }

 private:
  // 前置机列表
  std::map<u32, IVestibule *> m_mapVestibure;
};

#endif  // __DB__CLIENT__MGR__H

