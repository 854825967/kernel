#ifndef __DATAPROC_H__
#define __DATAPROC_H__
#include "GameSys.h"
#include "IDBProxy.h"

struct IDBEngine;

// 数据处理基类
class CDataProc
{
public:
  virtual ~CDataProc() {}
	// 请求处理
	virtual BOOL Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet, LPVOID dwServerID);

};

#endif // __DATAPROC_H__

