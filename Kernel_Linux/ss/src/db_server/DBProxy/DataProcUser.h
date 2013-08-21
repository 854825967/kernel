#ifndef __DATAPROCUSER_H__
#define __DATAPROCUSER_H__
#include "DataProc.h"
#include "IDBEngine.h"

class CUserData;

// 数据处理类 - 用户
class CDataProcUser : public CDataProc, public IDBRetSink
{
public:
	// 构造函数
	CDataProcUser();
	// 析构函数
	~CDataProcUser();

	// 请求处理
	virtual BOOL Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet, LPVOID dwServerID);

	// 数据库请求返回回调函数
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen);

	// 查找用户
	CUserData* FindUser(s64 qwUserID);

	// 删除用户
	void DelUser(s64 qwUserID, CUserData *pUserData);

	void KickUser(s64 qwUserID);

private:
	map<s32, IDBProxyRetSink*>		m_RequestMap;	// 请求映射表
	map<s64, CUserData*>			m_UserMap;		// 用户映射表
};

#endif // __DATAPROCUSER_H__

