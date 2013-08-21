#ifndef __DBPROXY_H__
#define __DBPROXY_H__
#include "IDBProxy.h"
#include "IDBEngine.h"
#include "DataProcDirect.h"
#include "DataProcUser.h"
#include "DataProcToken.h"
#include "DataProcSaveDB.h"
#include "ITimeAxis.h"

class CDataProc;

// 数据库代理类
class CDBProxy : public IDBProxy, public IDBWarningSink, public ITimerHandler
{
public:
	// 构造函数
	CDBProxy();

	// 析构函数
	~CDBProxy();

	// 创建数据库代理
	BOOL Create(LPSTR szKey, const char *szDBEngineName,
		LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file);

	// 销毁数据库代理
	virtual void Release(void);

	// 异常报警回调函数
	virtual void OnWarning(s32 nReturn, LPSTR szDesc);

	// 请求数据库
	virtual BOOL Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet, LPVOID dwServerID);

	//关闭服务器，用于处理缓存数据的保存
	virtual void CloseServer(LPVOID dwServerID);

	// 事件回调接口
	virtual void OnEvent(void);

	// 定时器回调
	virtual void OnTimer(u32 dwTimerID);

private:
	// 检测数据
	BOOL CheckData(void);

	// 返回数据处理类
	CDataProc* GetDataProc(s32 nRequestID, LPSTR pInData, s32 nInDataLen);

private:
	CDBEngineCreateHelper	m_DBEngineHelper;	// 数据库引擎辅助对象
	CDataProcDirect		m_DataProcDirect;		// 数据处理对象 - 直通
	CDataProcUser		m_DataProcUser;			// 数据处理对象 - 用户
	CDataProcToken		m_DataProcToken;		// 数据处理对象 - 令牌
	CDataProcSaveDB		m_DataProcSaveDB;		// 数据处理对象 - 缓存数据
};

#endif //__DBPROXY_H__

