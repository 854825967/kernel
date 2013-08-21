#include "Header.h"
#include "DataProcDirect.h"
#include "IDBEngine.h"

// 请求处理
BOOL CDataProcDirect::Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
							  LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
							  LPVOID dwServerID)
{
	// 如果已经存在该请求, 则不处理
	if (m_RequestMap.find(nIndex) != m_RequestMap.end())
	{
		return FALSE;
	}

	if (FALSE == g_pDBEngine->Request(nIndex, nRequestID, qwUserID, pInData, nInDataLen, this))
	{
		return FALSE;
	}

	m_RequestMap[nIndex] = pRet;

	return TRUE;
}

// 数据库请求返回回调函数
void CDataProcDirect::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
							s32 nReturn, LPSTR pOutData, s32 nOutLen)
{
	// 如果没有找到该请求, 则不处理
	map<s32, IDBProxyRetSink*>::iterator it = m_RequestMap.find(nIndex);
	if (it == m_RequestMap.end())
	{
		return;
	}

	IDBProxyRetSink *pSink = (*it).second;
	m_RequestMap.erase(nIndex);

	pSink->OnRet(nIndex, qwUserID, nRequestID, pInData, nInLen, nReturn, pOutData, nOutLen);
}


