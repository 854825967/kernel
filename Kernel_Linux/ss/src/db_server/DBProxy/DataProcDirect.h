#ifndef __DATAPROCDIRECT_H__
#define __DATAPROCDIRECT_H__
#include "DataProc.h"
#include "IDBEngine.h"

// 数据处理类 - 直通数据
class CDataProcDirect : public CDataProc, public IDBRetSink
{
public:
	// 请求处理
	virtual BOOL Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
		LPVOID dwServerID);

	// 数据库请求返回回调函数
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen);

private:
	map<s32, IDBProxyRetSink*>	m_RequestMap;	// 请求映射表
};

#endif // __DATAPROCDIRECT_H__

