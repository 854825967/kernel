#ifndef _SOCKETSERVICE_H__
#define _SOCKETSERVICE_H__
#include "core/tcp_server.h"
#include "IDBProxy.h"
using namespace core;

class CServerClientSink;

class CSocketService : public IDBProxyUserSink, public TCPServer
{
public:
	// 构造函数
	CSocketService(LPCSTR lpszIP, u16 wPort, const std::string &name);

	// 析构函数
	~CSocketService(void);

	// 创建Socket服务
	BOOL Create();

	// 能否停止
	BOOL CanStop(void);

	virtual void OnStop();

	// ServerScoket 有客户端连接上进行回调,
	// 创建ServerClientSink
	virtual ConnectionTask *OnConnectionEstablished();

	// 添加用户处理回调函数
	virtual void OnAddUser(LPVOID dwServerID, s64 qwUserID, s32 lActorID);

	// 删除用户处理回调函数
	virtual void OnDelUser(LPVOID dwServerID, s64 qwUserID);

	// 删除会话
	void DelColloquy(CServerClientSink *pColloquy);

	// 获取会话数量
	u32 GetColloquyNum();

	// 添加会话
	void AddColloquy(CServerClientSink *pColloquy);

private:
	list<CServerClientSink*>	m_ColloquyList;		// 会话列表
};

#endif //_SOCKETSERVICE_H__

