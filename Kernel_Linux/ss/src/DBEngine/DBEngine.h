#ifndef	__DBENGINE_H__
#define	__DBENGINE_H__
#include "GameSys.h"
#include "IDBEngine.h"
#include "base/mutex.h"
using namespace core;

class CAsynObject;
class CAsynObjectList;
class CDBMemTextFile;
struct IDBWarningSink;

// 性能评测宏
enum
{
	PT_REQUEST,			// 请求
	PT_REQUESTCAST,		// 请求耗时
	PT_ONRETCASTSTART,	// 回调耗时开始
	PT_ONRETCASTEND,	// 回调耗时结束
	PT_PRINTLOG,		// 打印统计结果
};

// 数据库引擎性能评测信息
struct DBENGINEPTINFO
{
	u32	dwRequestNum;	// 请求次数
	s64	requestTime;	// 请求总时间
	u32	dwCallNum;		// 回调次数
	s64	callTime;		// 回调总时间
	s64	callTempTime;	// 回调临时计时变量

	DBENGINEPTINFO()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 通用数据库引擎类
class CDBEngine : public IDBEngine
{
public:
	// 构造函数
	CDBEngine();

	// 析构函数
	~CDBEngine();

	// 创建通用数据库引擎
	BOOL Create(IDBWarningSink *pWarningSink, LPSTR szKey, LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file);

	// 销毁通用数据库引擎
	virtual void Release(void);

	// 数据库请求返回处理
	virtual void OnReturn(void);

	// 请求数据库
	virtual BOOL Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBRetSink *pRet);

	// 获取某种请求类型的异步队列状态信息
	virtual BOOL GetAsynListState(s32 nRequestType, s32 &nNum,
		ASYNLISTSTATE *pStateBuf, s32 nBufLen);

	// 动态更新配置信息(目标数据库和异步队列各种策略)
	// virtual BOOL UpdateConfig(void);

	// 添加一个要返回的对象
	void AddReturnObject(CAsynObject &ReturnObject);

	// 异常报警处理
	void OnWarning(s32 nReturn, LPSTR szDesc);

	// 输出信息日志
	void PrintInfoLog(LPCSTR lpszFormat, ...);

	// 性能评测函数
	void PerformanceTest(u32 key, s32 flag, s64 value);

private:
	// 创建异步队列
	BOOL CreateAsynObjectList(LPSTR szKey, s32 &nErrLine, LPCSTR szDBEngineScp);

	// 销毁异步队列
	void CloseAsynObjectList(void);

	// 过滤字符串左面的空格和tab键
	LPSTR TrimL(LPSTR szStr);

	// 查找文件中以某个字符串开始的行
	BOOL FindStrInFile(CDBMemTextFile *pFileObj, LPCSTR szStr, s32 &nCurLine, LPSTR szBuf);

private:
	list<CAsynObjectList*>	m_AsynObjectListList;	// 异步对象队列列表
	IDBWarningSink*			m_pWarningSink;			// 异常报警接口指针
	Mutex					m_WarningLock;			// 异常报警接口访问锁
	list<CAsynObject>		m_ReturnList;			// 数据库请求已返回的对象列表
	list<CAsynObject>		m_ReturnList2;			// 数据库请求已返回的对象列表2
	list<CAsynObject>*		m_pCurReturnList;		// 当前数据库请求已返回的对象列表
	list<CAsynObject>*		m_pCurReturnList2;		// 当前数据库请求已返回的对象列表2
	Mutex					m_ReturnLock;			// 数据库请求已返回的对象列表访问锁
	char					m_szKey[128];			// 用于解密字符串的Key
	Mutex					m_LogLock;				// 日志锁
	Mutex					m_TestLock;				// 数据库引擎性能测试锁
	map<u32, DBENGINEPTINFO>	m_dbTest;			// 数据库引擎性能测试
  std::string m_log_file_;

};

#endif // __DBENGINE_H__
