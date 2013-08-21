#ifndef __DATAPROCTOKEN_H__
#define __DATAPROCTOKEN_H__
#include "DataProc.h"

class CDataProcUser;
class CUserToken;

// 数据处理类 - 令牌
class CDataProcToken : public CDataProc
{
public:
	// 构造函数
	CDataProcToken(CDataProcUser *pProcUser);
	// 析构函数
	~CDataProcToken();

	// 请求处理
	virtual BOOL Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet, LPVOID dwServerID);

	// 删除令牌
	void DelToken(s64 qwUserID, CUserToken *pUserToken);

private:
	map<s64, CUserToken*>			m_TokenMap;		// 令牌映射表
	CDataProcUser*					m_pProcUser;	// 用户处理对象
};

#endif // __DATAPROCTOKEN_H__

