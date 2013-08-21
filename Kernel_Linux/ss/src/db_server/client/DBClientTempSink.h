//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7062 $
// $Author: than $
// $Date: 2012-04-28 11:08:42 +0800 (鍛ㄥ叚, 2012-04-28) $
//
// Define class CDBClientTempSink.
//

#ifndef __DB__CLIENT__TEMP__SINK
#define __DB__CLIENT__TEMP__SINK

#include "IDBClient.h"

class CDBClientTempSink : public IDBClientSink {
 public:
  CDBClientTempSink();
  virtual ~CDBClientTempSink();

  // 前置机回调
  // nIndex: 请求流水号
  // nRetCode: 取值于 EN_VESTIBULE_RET
  virtual void OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID,
         LPSTR pOutData, s32 nOutDataLen, LPSTR pInData = NULL, s32 nInDataLen = 0);
};

extern CDBClientTempSink g_DBClientTempSink;

#endif  // __DB__CLIENT__TEMP__SINK

