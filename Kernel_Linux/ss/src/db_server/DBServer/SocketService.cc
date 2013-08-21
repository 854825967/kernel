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

// �ܷ�ֹͣ
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

// ������������(�����߳�)
ConnectionTask *CSocketService::OnConnectionEstablished()
{
	CServerClientSink *pColloquy = new CServerClientSink(this);
	if (NULL == pColloquy)
	{
		printf("CSocketService::OnConnectionEstablishedʧ��, Newʧ��!\n");
		return NULL;
	}

	return pColloquy;
}

// ����û�����ص�����
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
	g_pServerLog->TraceLn("CSocketService::OnAddUserʧ��, û���ҵ��Ự����!");
	return;
}

// ɾ���û�����ص�����
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
	// g_pServerLog->TraceLn("CSocketService::OnAddUserʧ��, û���ҵ��Ự����!");
	return;
}

// ɾ���Ự
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
	g_pServerLog->TraceLn("CSocketService::DelColloquyʧ��, û���ҵ��Ự����!");
	return;
}

// ��ȡ�Ự����
u32 CSocketService::GetColloquyNum()
{
	return m_ColloquyList.size();
}

// ��ӻỰ
void CSocketService::AddColloquy(CServerClientSink *pColloquy)
{
	m_ColloquyList.push_back(pColloquy);
	return;
}



