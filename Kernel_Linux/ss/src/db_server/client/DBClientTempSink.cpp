//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7062 $
// $Author: than $
// $Date: 2012-04-28 11:08:42 +0800 (鍛ㄥ叚, 2012-04-28) $
//
// Define class CDBClientTempSink.
//

#include "DBClientTempSink.h"

CDBClientTempSink g_DBClientTempSink;

CDBClientTempSink::CDBClientTempSink() {}

CDBClientTempSink::~CDBClientTempSink() {}

void CDBClientTempSink::OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID,
       LPSTR pOutData, s32 nOutDataLen, LPSTR pInData , s32 nInDataLen) {}

