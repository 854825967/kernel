#ifndef _SERVERCLIENTSINK_H__
#define _SERVERCLIENTSINK_H__
#include "ITimeAxis.h"
#include "IDBProxy.h"
#include "core/connection_task.h"
using namespace core;

class CSocketService;

class CServerClientSink : public ConnectionTask,
	public ITimerHandler, 
	public IDBProxyRetSink
{ 
public:
	// 构造函数
	CServerClientSink(CSocketService *pVestibule);

	// 析构函数
	~CServerClientSink();

	// 接收数据处理
	virtual void OnRecieve(LPCSTR Buf, s32 nLen);

	// 连接成功处理
	virtual void OnConnectionOK();

	// 关闭连接处理
	virtual void OnCloseConnection(bool force);

	// 数据库代理请求返回回调函数
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen);

	// 定时器回调
	virtual void OnTimer(u32 dwTimerID);

	// 添加用户处理函数
	void AddUser(s64 qwUserID, s32 lActorID);

	// 删除用户处理函数
	void DelUser(s64 qwUserID);

	//开启
	void Start(void);

private:
	// 数据库请求处理
	void RequestDB(LPCSTR pBuf, s32 nLen);

private:
	CSocketService*	m_pVestibule;		// 前置机指针
	s8				m_szIP[16];			// 应用服IP
	u16				m_wPort;			// 应用服端口
	BOOL			m_bClosed;			// 关闭标志
	map<s64, s32>	m_UserMap;			// 用户列表
	map<s32, s32>	m_RequestMap;		// 请求表
	vector<s32>		m_PTTest;			// 性能统计
	s32				m_PTTime;			// 统计时间
	static s32		s_lIndex;			// 请求序列号
	BOOL			m_bKeepAlive;		// 为TRUE表示收到了客户端的心跳包
};

#endif //_SERVERCLIENTSINK_H__

