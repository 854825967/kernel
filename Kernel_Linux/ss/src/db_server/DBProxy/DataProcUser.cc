#include "Header.h"
#include "DataProcUser.h"
#include "UserData.h"
#include "IDBClient.h"

// 构造函数
CDataProcUser::CDataProcUser()
{
}

// 析构函数
CDataProcUser::~CDataProcUser()
{
	map<s64, CUserData*>::iterator it = m_UserMap.begin();
	while (it != m_UserMap.end())
	{
		CUserData *pUserData = (*it).second;
		delete pUserData;
		it = m_UserMap.begin();
		//g_pTrace->TraceErrorLn("CDataProcUser::~CDataProcUser, 主动释放!");
	}

	m_UserMap.clear();
}

// 请求处理
BOOL CDataProcUser::Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
							LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
							LPVOID dwServerID)
{
	// 如果已经存在该请求, 则不处理
	if (m_RequestMap.find(nIndex) != m_RequestMap.end())
	{
		g_pTrace->TraceErrorLn("CDataProcUser::Request失败, 请求重复, RequestID=%d!", nRequestID);
		return FALSE;
	}

	CUserData *pUserData = NULL;

	// 如果缓存数据中不存在该用户, 则添加该用户
	map<s64, CUserData*>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		if (nRequestID != REQUESTID_ACTOR_LOGIN || nInDataLen != sizeof(SActorLogin_Set))
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Request失败, 请求非法, RequestID=%d!", nRequestID);
			return FALSE;
		}

		SActorLogin_Set *pSet = (SActorLogin_Set*)pInData;

		pUserData = new CUserData(pSet->qwUserID, pSet->lActorID, dwServerID, this);
		if (NULL == pUserData)
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Request失败, New失败!");
			return FALSE;
		}

		m_UserMap[qwUserID] = pUserData;

		g_pUserSink->OnAddUser(dwServerID, pSet->qwUserID, pSet->lActorID);
	}
	else
	{
		pUserData = (*it).second;

		// 玩家要切换场景服
		if (REQUESTID_ACTOR_LOGIN == nRequestID && nInDataLen == sizeof(SActorLogin_Set))
		{
			SActorLogin_Set *pSet = (SActorLogin_Set*)pInData;
			g_pUserSink->OnDelUser(pUserData->GetServerID(), qwUserID);
			g_pUserSink->OnAddUser(dwServerID, pSet->qwUserID, pSet->lActorID);
			pUserData->SetServerID(dwServerID);
		}
	}

	// 如果用户正在存盘, 则不处理
	if (TRUE == pUserData->IsSaving())
	{
		g_pTrace->TraceErrorLn("CDataProcUser::Request失败, 用户%ld正在存盘...!", qwUserID);
		return FALSE;
	}

	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	switch (nRequestID)
	{
		// 读DB数据
	case REQUESTID_ACTOR_LOGIN:
	case REQUESTID_GOODS_GET:
	case REQUESTID_INTERACT_LOAD:
		// 如果从缓存中取数据失败, 则从数据库中取
		if (FALSE == pUserData->Load(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			if (FALSE == g_pDBEngine->Request(nIndex, nRequestID, qwUserID, pInData, nInDataLen, this))
			{
				g_pTrace->TraceErrorLn("CDataProcUser::Request失败, DBEngine请求失败, RequestID=%d!", nRequestID);
				return FALSE;
			}
			m_RequestMap[nIndex] = pRet;
			return TRUE;
		}

		break;

		// 读非DB数据
	case REQ_VESTIB_USERDEFINED_LOAD:
		// 如果从缓存中取数据失败
		if (FALSE == pUserData->Load(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Request失败, UserData加载失败, RequestID=%d!", nRequestID);
			return FALSE;
		}
		break;

		// 写数据
	case REQUESTID_ACTOR_UPDATE:
	case REQUESTID_GOODS_UPDATE:
	case REQUESTID_INTERACT_SAVE:
	case REQUESTID_ACTOR_LOGOUT:
	case REQ_VESTIB_USERDEFINED_SAVE:
	case REQ_VESTIB_USER_SAVE_OK:
		if (FALSE == pUserData->Save(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Request失败, UserData保存失败, RequestID=%d!", nRequestID);
			return FALSE;
		}

		break;

	default:
		g_pTrace->TraceErrorLn("CDataProcUser::Request失败, RequestID=%d!", nRequestID);
		return FALSE;
	}

	pRet->OnRet(nIndex, qwUserID, nRequestID, pInData, nInDataLen, DBRET_OK, pOutData, nOutLen);

	return TRUE;
}

// 数据库请求返回回调函数
void CDataProcUser::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
						  s32 nReturn, LPSTR pOutData, s32 nOutLen)
{
	// 如果没有找到该请求, 则不处理
	map<s32, IDBProxyRetSink*>::iterator it = m_RequestMap.find(nIndex);
	if (it == m_RequestMap.end())
	{
		//g_pTrace->TraceErrorLn("CDataProcUser::OnRet失败, 没有找到请求, RequestID=%d!", nRequestID);
		return;
	}

	IDBProxyRetSink *pSink = m_RequestMap[nIndex];
	m_RequestMap.erase(nIndex);

	map<s64, CUserData*>::iterator itUser = m_UserMap.find(qwUserID);
	if (itUser == m_UserMap.end())
	{
		//g_pTrace->TraceErrorLn("CDataProcUser::OnRet失败, 没有找到用户, UserID=%ld!", qwUserID);
		return;
	}

	pSink->OnRet(nIndex, qwUserID, nRequestID, pInData, nInLen, nReturn, pOutData, nOutLen);
}

// 查找用户
CUserData* CDataProcUser::FindUser(s64 qwUserID)
{
	map<s64, CUserData*>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		return NULL;
	}
	return (*it).second;
}

// 删除用户
void CDataProcUser::DelUser(s64 qwUserID, CUserData *pUserData)
{
	map<s64, CUserData*>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		//g_pTrace->TraceLn("CDataProcUser::DelUser失败, 没有找到用户%ld!", qwUserID);
		return;
	}

	if (pUserData != (*it).second)
	{
		//g_pTrace->TraceLn("CDataProcUser::DelUser失败, 用户指针不对!");
		return;
	}

	m_UserMap.erase(qwUserID);

	g_pUserSink->OnDelUser(pUserData->GetServerID(), qwUserID);
}

void CDataProcUser::KickUser(s64 qwUserID)
{
	map<s64, CUserData*>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		return;
	}

	CUserData *pUserData = (*it).second;
	if (NULL != pUserData && TRUE == pUserData->IsDataSaveOK())
	{
		//强制保存玩家的数据，让玩家下线
		pUserData->KickUser();
	}
}

