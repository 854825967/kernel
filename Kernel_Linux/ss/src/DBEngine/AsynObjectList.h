#ifndef	__ASYNOBJECTLIST_H__
#define	__ASYNOBJECTLIST_H__
#include "GameSys.h"
#include "base/mutex.h"
#include "base_loop.h"
#include "loop_thread.h"
using namespace core;

class CDBADO;
class CAsynObject;

// 异步对象队列信息
struct ASYNLISTINFO
{
	s32		nDriverType;							// 数据库驱动类型
	char	szServerName[MAX_CONNECTSTRING_LEN];	// 数据库服务器名
	s32		nServerPort;			// 数据库服务器端口
	char	szDBName[MAX_CONNECTSTRING_LEN];		// 数据库名
	char	szUserName[MAX_CONNECTSTRING_LEN];		// 用户名
	char	szPassword[MAX_CONNECTSTRING_LEN];		// 密码
	s32		nType;				// 请求类型
	s32		nRetryWeightness;	// 重试重要度
	s32		nRetryInternal;		// 重试间隔
	s32		nRetryNumber;		// 重试次数
	s32		nRetryMaxSize;		// 重试队列最大长度
	s32		nReduceSize;		// 触发抛包的队列大小
	s32		nReduceWeightness;	// 抛包重要度
	s32		nCacheSize;			// 触发缓存的队列大小

	ASYNLISTINFO()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 异步对象队列类
class CAsynObjectList : public BaseLoop
{
public:
	// 构造函数
	CAsynObjectList();

	// 析构函数
	~CAsynObjectList();

	// 创建异步对象队列
	BOOL Create(s32 nID, ASYNLISTINFO &AsynListInfo);

	// 释放异步对象队列
	void Close(void);

	// 队列主处理
	void Process(void);

	// 添加一个请求对象到队列
	void AddRequestObject(CAsynObject &AsynObject);

	// 动态更新配置信息
	BOOL UpdateConfig(ASYNLISTINFO &AsynListInfo);

	// 异常报警处理
	void OnWarning(int nReturn);

	// 获取处理请求的类型
	s32 GetRequestType(void);

	// 获取CDBADO指针
	CDBADO* GetDBADO(void);

	// 获取请求包数量
	s32 GetRequestObjNum(void);

	// 获取重试包数量
	s32 GetRetryObjNum(void);

	virtual void Loop();

private:
	// 注册对象在重试队列的信息
	void RegisterRetry(s64 qwUserID);
	// 注销对象在重试队列的信息
	void DeregisterRetry(s64 qwUserID);
	// 执行抛包策略
	void ReduceStrategy(void);
	// 抛包日志
	void ReduceLog(CAsynObject &AsynObject, LPCSTR szReason);
	// 本地缓存策略
	void CacheStrategy(void);

private:
	ASYNLISTINFO		m_AsynListInfo;		// 异步队列信息

	s32					m_nID;				// 序号
	u32					m_dwThread;			// 线程ID
	CDBADO				m_DBADO;			// CDBADO对象

	list<CAsynObject>	m_RequestList;		// 请求对象列表
	s32					m_nRequestListSize;	// 请求对象列表大小
	Mutex				m_RequestLock;		// 请求对象列表访问锁

	list<CAsynObject>	m_RetryList;		// 重试对象列表
	s32					m_nRetryListSize;	// 重试对象列表大小
	map<s64, s32>		m_RetryRegHash;		// 重试队列注册表
	s32					m_nNoRetryNum;		// 未处理重试队列计数
	s32					m_nCurObjRetryNum;	// 当前对象已重试次数

	Mutex				m_LogLock;			// 日志锁

	LoopThread*			m_pThread;			// 数据库线程指针

#ifdef PERFORMANCE_TEST
  static u64 count;
#endif
};

#endif // __ASYNOBJECTLIST_H__
