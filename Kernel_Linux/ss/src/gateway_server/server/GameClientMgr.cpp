#include "GateWayServiceMgr.h"

#include "DCenterServerMsg.h"
#include "GameClientMgr.h"
#include "ILog.h"

CGameClientMgr::CGameClientMgr(void)
{
	m_RoomConnMap.clear();
	m_LobbyConnMap.clear();
	m_vectLobbyServerID.clear();
}

CGameClientMgr::~CGameClientMgr(void)
{

}

void CGameClientMgr::Close()
{
	GAMECONNMAP::iterator itLobby =  m_LobbyConnMap.begin();
	for (; itLobby != m_LobbyConnMap.end(); itLobby++)
	{
		CGameClientConn *pCGameClientConn  = (CGameClientConn *)(*itLobby).second;
		if (pCGameClientConn == NULL)
		{
			continue;
		}  
		pCGameClientConn->Release();
		pCGameClientConn = NULL;
	}
	m_LobbyConnMap.clear();
	m_vectLobbyServerID.clear();

	GAMECONNMAP::iterator itRoom =  m_RoomConnMap.begin();
	for (; itRoom != m_RoomConnMap.end(); itRoom++)
	{
		CGameClientConn *pCGameClientConn  = (CGameClientConn *)(*itRoom).second;
		if (pCGameClientConn == NULL)
		{
			continue;
		}  
		pCGameClientConn->Release();
		pCGameClientConn = NULL;
	}
	m_RoomConnMap.clear();
	
	return;
}

// 登陆游戏服
BOOL CGameClientMgr::CreateGameConn(u32 dwGameID, LPCSTR lpGameIP, u16 wPort)
{
	CGameClientConn *pGameClientConn = new CGameClientConn(InetAddress(lpGameIP, wPort), "CGameClientConn");
	if(pGameClientConn == NULL)
	{
		g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("New CGameClientConn 内存不足!");
		return FALSE;
	}

	if(!pGameClientConn->Create(this, dwGameID))
	{
		if( NULL != pGameClientConn )
		{
			pGameClientConn->Release();
			pGameClientConn = NULL;
		}
		return FALSE;			
	}

	return TRUE;
}

// 登陆游戏服
BOOL CGameClientMgr::AddGameConn(CGameClientConn *pGameConn)
{
	if (pGameConn == NULL)
	{
		return FALSE;
	}

	u32 dwGameID = pGameConn->GetGameID();
	if( pGameConn->GetServerType() == CENTER_ST_LOBBY )
	{
		GAMECONNMAP::iterator it =  m_LobbyConnMap.find(dwGameID);
		if (it != m_LobbyConnMap.end())
		{
			return FALSE;
		}

		m_LobbyConnMap[dwGameID] = pGameConn;
		m_vectLobbyServerID.push_back(dwGameID);
	}
	else if( pGameConn->GetServerType() == CENTER_ST_ROOM )
	{
		GAMECONNMAP::iterator it =  m_RoomConnMap.find(dwGameID);
		if (it != m_RoomConnMap.end())
		{
			return FALSE;
		}

		m_RoomConnMap[dwGameID] = pGameConn;
	}
	return TRUE;
}

// 删除一个连接
BOOL CGameClientMgr::DelGameConn(CGameClientConn *pGameConn)
{
	if (pGameConn == NULL)
	{
		return FALSE;
	}

	u32 dwGameID = pGameConn->GetGameID();
	if( pGameConn->GetServerType() == CENTER_ST_LOBBY )
	{
		GAMECONNMAP::iterator it =  m_LobbyConnMap.find(dwGameID);
		if (it != m_LobbyConnMap.end())
		{
			m_LobbyConnMap.erase(it);
			for(std::vector<u32>::iterator it = m_vectLobbyServerID.begin();
					it != m_vectLobbyServerID.end(); ++it)
			{
				if( *it == dwGameID )
				{
					m_vectLobbyServerID.erase(it);
					break;
				}
			}
		}
	}
	else if( pGameConn->GetServerType() == CENTER_ST_ROOM )
	{
		GAMECONNMAP::iterator it =  m_RoomConnMap.find(dwGameID);
		if (it != m_RoomConnMap.end())
		{
			m_RoomConnMap.erase(it);
		}
	}

	// pGameConn->Release();
	// pGameConn = NULL; 
	pGameConn->CloseConnection();
	return TRUE;
}

CGameClientConn * CGameClientMgr::FindGameConnByGameID(u32 dwGameID)
{ 
/*
	if (dwGameID == -1)
	{
		return FALSE;
	}
*/

	GAMECONNMAP::iterator itRoom =  m_RoomConnMap.find(dwGameID);
	if (itRoom != m_RoomConnMap.end())
	{
		return (*itRoom).second;
	}

	GAMECONNMAP::iterator itLobby =  m_LobbyConnMap.find(dwGameID);
	if (itLobby != m_LobbyConnMap.end())
	{
		return (*itLobby).second;
	}
	return NULL;
}

CGameClientConn * CGameClientMgr::FindGameConnByServerInfo(LPCSTR lpServerIP, u16 wPort)
{
	GAMECONNMAP::iterator itLobby =  m_LobbyConnMap.begin();
	for (; itLobby != m_LobbyConnMap.end(); itLobby++)
	{
		CGameClientConn *pCGameClientConn  = (CGameClientConn *)(*itLobby).second;
		if (pCGameClientConn == NULL)
		{
			continue;
		} 

		if(strncmp(pCGameClientConn->GetServerIP(), lpServerIP, sizeof(lpServerIP))== 0 && 
				wPort == pCGameClientConn->GetPort())
		{
			return pCGameClientConn;
		}
	}

	GAMECONNMAP::iterator itRoom =  m_RoomConnMap.begin();
	for (; itRoom != m_RoomConnMap.end(); itRoom++)
	{
		CGameClientConn *pCGameClientConn  = (CGameClientConn *)(*itRoom).second;
		if (pCGameClientConn == NULL)
		{
			continue;
		} 

		if(strncmp(pCGameClientConn->GetServerIP(), lpServerIP, sizeof(lpServerIP))== 0 && 
				wPort == pCGameClientConn->GetPort())
		{
			return pCGameClientConn;
		}
	}

	return NULL;
}

// 根据账号ID负载均衡至每个大厅服务器
CGameClientConn* CGameClientMgr::FindLobbyConn(s64 qwUserID)
{
	u32 nMaxLobbyNum = m_LobbyConnMap.size();
	// 没有可登录的大厅服
	if( 0 == nMaxLobbyNum )
	{
		return NULL;
	}
	// 取模来负载均衡
	u32 nServerIdx = qwUserID % nMaxLobbyNum;
	if( nServerIdx >= nMaxLobbyNum )
	{
		return NULL;
	}
	u32 dwGameID = m_vectLobbyServerID[nServerIdx];
	return FindGameConnByGameID(dwGameID);
}

// 发送消息到游戏服
BOOL CGameClientMgr::SendMsgToGame(u32 dwGameID, LPCSTR lpData, s32 nLen)
{
	CGameClientConn *pGameClientConn  = FindGameConnByGameID(dwGameID);
	if (pGameClientConn == NULL)
	{
		return FALSE;
	}

	return pGameClientConn->SendData(lpData,nLen);
}
