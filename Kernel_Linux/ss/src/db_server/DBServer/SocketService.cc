#include "Header.h"
#include "SocketService.h"
#include "ILog.h"
#include "ServerClientSink.h"
#include "IDBClient.h"
#include "ServerService.h"

CSocketService::CSocketService(LPCSTR lpszIP, u16 wPort, const std::string &name) 
: TCPServer(InetAddress(lpszIP, wPort), name)
{
}

CSocketService::~CSocketService(void)
{

}

BOOL CSocketService::Create()
{
	return TRUE;
}

// 能否停止
BOOL CSocketService::CanStop(void)
{
	if (m_ColloquyList.size() > 0)
	{
		return FALSE;
	}
	return TRUE;
}

void CSocketService::OnStop() {
	g_ServerService.CloseService();
}

// 创建接受连接(接受线程)
ConnectionTask *CSocketService::OnConnectionEstablished()
{
	CServerClientSink *pColloquy = new CServerClientSink(this);
	if (NULL == pColloquy)
	{
		printf("CSocketService::OnConnectionEstablished失败, New失败!\n");
		return NULL;
	}

	return pColloquy;
}

// 添加用户处理回调函数
void CSocketService::OnAddUser(LPVOID dwServerID, s64 qwUserID, s32 lActorID)
{
	CServerClientSink *pColloquy = (CServerClientSink*)dwServerID;
	list<CServerClientSink*>::iterator it = m_ColloquyList.begin();
	for (; it != m_ColloquyList.end(); ++it)
	{
		if (pColloquy == (*it))
		{
			pColloquy->AddUser(qwUserID, lActorID);
			return;
		}
	}
	g_pServerLog->TraceLn("CSocketService::OnAddUser失败, 没有找到会话对象!");
	return;
}

// 删除用户处理回调函数
void CSocketService::OnDelUser(LPVOID dwServerID, s64 qwUserID)
{
	CServerClientSink *pColloquy = (CServerClientSink*)dwServerID;
	list<CServerClientSink*>::iterator it = m_ColloquyList.begin();
	for (; it != m_ColloquyList.end(); ++it)
	{
		if (pColloquy == (*it))
		{
			pColloquy->DelUser(qwUserID);
			return;
		}
	}
	// g_pServerLog->TraceLn("CSocketService::OnAddUser失败, 没有找到会话对象!");
	return;
}

// 删除会话
void CSocketService::DelColloquy(CServerClientSink *pColloquy)
{
	list<CServerClientSink*>::iterator it = m_ColloquyList.begin();
	for (; it != m_ColloquyList.end(); ++it)
	{
		if (pColloquy == (*it))
		{
			m_ColloquyList.erase(it);
			return;
		}
	}
	g_pServerLog->TraceLn("CSocketService::DelColloquy失败, 没有找到会话对象!");
	return;
}

// 获取会话数量
u32 CSocketService::GetColloquyNum()
{
	return m_ColloquyList.size();
}

// 添加会话
void CSocketService::AddColloquy(CServerClientSink *pColloquy)
{
	m_ColloquyList.push_back(pColloquy);
	return;
}



