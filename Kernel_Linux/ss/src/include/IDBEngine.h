/*****************************************************************************
 * 模块名      : mysql数据库引擎接口
 * 文件名      : IDBEngine.h
 * 相关文件    : 
 * 文件实现功能: mysql数据库引擎接口
 * 作者        : 庄雪锋
 * 版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
 * -----------------------------------------------------------------------------
 *  修改记录:
 *  日  期      版本        修改人      修改内容
 *  2011/06/30  0.1         庄雪锋      创建
 *  ******************************************************************************/
#ifndef	__IDBENGINE_H__
#define	__IDBENGINE_H__
#include "GameSys.h"
#include "IOsApi.h"

// 数据库请求返回值定义
enum
{
	DBRET_ERROR_UNKNOWN		= -9999,// 未知错误(引擎返回)
 	DBRET_ERROR_LOGIC		= -1,	// <=该值的为逻辑错误(数据库返回)，具体由DB定义
 	DBRET_ERROR_LOCK		= 0,	// 表死锁
 	DBRET_OK			= 1,	// 成功
};

// 异常报警定义
enum
{
	DBWARN_DISCONNECTED = 0,	// 数据库连接断开
	DBWARN_CONNECTED,		// 数据库连接恢复正常
	DBWARN_RETRY_MAXSIZE,		// 重试队列达到最大长度
	DBWARN_REDUCE_STRATEGY,		// 请求对列执行抛包策略
	DBWARN_CACHE_STRATEGY,		// 请求对列执行本地缓存策略
};

// 异步队列状态信息
struct ASYNLISTSTATE
{
	s32 	nRequestType;			// 请求类型
	s32	nRequestObjectNum;		// 请求包数量
	s32	nRetryObjectNum;		// 重试包数量

	ASYNLISTSTATE()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 数据库请求返回回调接口
struct IDBRetSink
{
  virtual ~IDBRetSink() {}
	// 数据库请求返回回调函数
	// nReturn: 参考上面数据库请求返回值定义
	// pOutData: 输出数据缓冲区指针
	// nOutLen: 输出数据缓冲区长度
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen) = 0;
};

// 异常报警回调接口
struct IDBWarningSink
{
  virtual ~IDBWarningSink() {}
	// 异常报警回调函数
	// nReturn: 参考上面异常报警定义
	// szDesc:  报警信息描述
	virtual void OnWarning(s32 nReturn, LPSTR szDesc) = 0;
};

// 通用数据库引擎接口
struct IDBEngine
{
  virtual ~IDBEngine() {}
	// 销毁通用数据库引擎
	virtual void Release(void) = 0;

	// 数据库请求返回处理
	virtual void OnReturn(void) = 0;

	// 请求数据库
	// nIndex: 请求流水号, 唯一对应每个请求
	// nRequestID: 请求ID
	// qwUserID: 发出本情求的用户ID, 用于取模进行负载均衡
	// pInData: 输入数据缓冲区
	// nInDataLen: 输入数据缓冲区长度
	// pRet: 请求返回回调接口
	virtual BOOL Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBRetSink *pRet) = 0;

	// 获取某种请求类型的异步队列状态信息
	// nRequestType为-1表示获取所有请求类型的异步队列状态信息
	// nNum: 返回队列个数
	// pStateBuf: 数据缓冲区指针, 用于存放返回数据
	// nBufLen: 数据缓冲区长度
	virtual BOOL GetAsynListState(s32 nRequestType, s32 &nNum,
		ASYNLISTSTATE *pStateBuf, s32 nBufLen) = 0;

	// 动态更新配置信息(目标数据库和异步队列各种策略)
	// virtual BOOL UpdateConfig(void) = 0;
};

// 创建通用数据库引擎(输出函数)
extern "C" BOOL CreateDBEngine(IDBEngine **ppDBEngine, IDBWarningSink *pWarningSink,
	LPSTR szKey, LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file);

typedef BOOL (*ProcCreateDBEngine)(IDBEngine **ppDBEngine, IDBWarningSink *pWarningSink,
	LPSTR szKey, LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file);

// 数据库引擎创建辅助类
class CDBEngineCreateHelper 
{
public:
	CDBEngineCreateHelper() : m_pDBEngine(NULL)
	{

	}

	~CDBEngineCreateHelper() 
	{
		this->Close(); 
	}

	// 创建通用数据库引擎
	BOOL Create(IDBWarningSink *pWarningSink, char *szKey, const char *szDBEngineName,
		LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file) 
	{
		if(this->m_DynamicLoader.LoadLibrary(szDBEngineName) == FALSE) 
		{
			return FALSE;
		}

		ProcCreateDBEngine proc = NULL;
		proc = (ProcCreateDBEngine)(this->m_DynamicLoader.GetProcAddress("CreateDBEngine"));
		if(proc == NULL)
			return FALSE;

		return proc(&(this->m_pDBEngine), pWarningSink, szKey, szDBEngineScp, szDBRequestScp, log_file);
	}

	void Close() 
	{
		if(this->m_pDBEngine) 
		{
			this->m_pDBEngine->Release();
			this->m_pDBEngine = NULL;
		}
		this->m_DynamicLoader.FreeLibrary();
	}

public:
	IDBEngine	*m_pDBEngine;			// 通用数据库引擎指针

private:
	CDynamicLoader m_DynamicLoader;
};

#endif // __IDBENGINE_H__
