#ifndef __IDBPROXY_H__
#define __IDBPROXY_H__
#include "GameSys.h"
#include "IOsApi.h"

struct ILog;
struct ITimerAxis;

// 数据库代理请求返回回调接口
struct IDBProxyRetSink
{
  virtual ~IDBProxyRetSink() {}
	// 数据库代理请求返回回调函数
	// nReturn: 参考 IDBEngine.h 里面数据库请求返回值定义
	// pOutData: 输出数据缓冲区指针
	// nOutLen: 输出数据缓冲区长度
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen) = 0;

};

// 数据库代理用户处理回调
struct IDBProxyUserSink
{
  virtual ~IDBProxyUserSink() {}
	// 添加用户处理回调函数
	virtual void OnAddUser(LPVOID dwServerID, s64 qwUserID, s32 lActorID) = 0;
	// 删除用户处理回调函数
	virtual void OnDelUser(LPVOID dwServerID, s64 qwUserID) = 0;

};

// 数据库代理接口
struct IDBProxy
{
  virtual ~IDBProxy() {}
	// 销毁数据库代理
	virtual void Release(void) = 0;

	// 请求数据库
	// nIndex: 请求流水号, 唯一对应每个请求
	// nRequestID: 请求ID
	// qwUserID: 发出本请求的用户ID, 用于取模进行负载均衡
	// pInData: 输入数据缓冲区
	// nInDataLen: 输入数据缓冲区长度
	// pRet: 请求返回回调接口
	virtual BOOL Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet, LPVOID dwServerID) = 0;

	//关闭服务器，用于处理缓存数据的保存
	virtual void CloseServer(LPVOID dwServerID) = 0;
};

#ifdef _MSC_VER

#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif

#ifndef DLL_IMPORT
#define DLL_IMPORT __cdecl
#endif

#else

#ifndef DLL_EXPORT
#define DLL_EXPORT
#endif

#ifndef DLL_IMPORT
#define DLL_IMPORT
#endif

#endif

#ifdef _MSC_VER

#define DBPROXY_DLL_NAME "DBProxy.dll"

#else

#define DBPROXY_DLL_NAME "libDBProxy.so"

#endif

// 创建数据库代理(输出函数)
extern "C" DLL_EXPORT BOOL CreateDBProxy(u32 dwSaveTimes,IDBProxy **ppDBProxy, LPSTR szKey,
	ILog *pTrace, ITimerAxis *pTimeAxis, IDBProxyUserSink *pUserSink, LPCSTR szDBEngineName,
	LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file);
typedef BOOL (DLL_IMPORT *ProcCreateDBProxy)(u32 dwSaveTimes,IDBProxy **ppDBProxy, LPSTR szKey,
	ILog *pTrace, ITimerAxis *pTimeAxis, IDBProxyUserSink *pUserSink, LPCSTR szDBEngineName,
	LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file);

// 数据库代理创建辅助类
class CDBProxyCreateHelper
{
public:
	// 构造函数
	CDBProxyCreateHelper()
	{
		m_pDBProxy = NULL;
	}

	// 析构函数
	~CDBProxyCreateHelper()
	{
		Close();
	}

	// 创建通用数据库引擎
	BOOL Create(u32 dwSaveTimes, LPSTR szKey, 
		ILog *pTrace,
		ITimerAxis *pTimeAxis, 
		IDBProxyUserSink *pUserSink, 
		LPCSTR pDBProxyName, LPCSTR szDBEngineName,
		LPCSTR szDBEngineScp, LPCSTR szDBRequestScp,
    const char *log_file)
	{
		if( !m_DynamicLoader.LoadLibrary(pDBProxyName) )
		{
			return FALSE;
		}

		ProcCreateDBProxy pProc = NULL;
		pProc = (ProcCreateDBProxy)(m_DynamicLoader.GetProcAddress("CreateDBProxy"));
		if (NULL == pProc)
		{
			return FALSE;
		}

		if (FALSE == pProc(dwSaveTimes,&m_pDBProxy, szKey, pTrace, pTimeAxis,
			pUserSink, szDBEngineName, szDBEngineScp, szDBRequestScp, log_file))
		{
			return FALSE;
		}

		return TRUE;
	}

	// 释放数据库代理
	void Close(void)
	{
		if (m_pDBProxy != NULL)
		{
			m_pDBProxy->Release();
			m_pDBProxy = NULL;
		}

		m_DynamicLoader.FreeLibrary();
	}

public:
	IDBProxy*		m_pDBProxy;			// 数据库代理指针
private:
	CDynamicLoader	m_DynamicLoader;	// 动态库加载
};

#endif // __IDBPROXY_H__

