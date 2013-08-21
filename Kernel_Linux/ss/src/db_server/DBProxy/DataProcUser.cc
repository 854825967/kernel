#include "Header.h"
#include "DataProcUser.h"
#include "UserData.h"
#include "IDBClient.h"

// ���캯��
CDataProcUser::CDataProcUser()
{
}

// ��������
CDataProcUser::~CDataProcUser()
{
	map<s64, CUserData*>::iterator it = m_UserMap.begin();
	while (it != m_UserMap.end())
	{
		CUserData *pUserData = (*it).second;
		delete pUserData;
		it = m_UserMap.begin();
		//g_pTrace->TraceErrorLn("CDataProcUser::~CDataProcUser, �����ͷ�!");
	}

	m_UserMap.clear();
}

// ������
BOOL CDataProcUser::Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
							LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
							LPVOID dwServerID)
{
	// ����Ѿ����ڸ�����, �򲻴���
	if (m_RequestMap.find(nIndex) != m_RequestMap.end())
	{
		g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, �����ظ�, RequestID=%d!", nRequestID);
		return FALSE;
	}

	CUserData *pUserData = NULL;

	// ������������в����ڸ��û�, ����Ӹ��û�
	map<s64, CUserData*>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		if (nRequestID != REQUESTID_ACTOR_LOGIN || nInDataLen != sizeof(SActorLogin_Set))
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, ����Ƿ�, RequestID=%d!", nRequestID);
			return FALSE;
		}

		SActorLogin_Set *pSet = (SActorLogin_Set*)pInData;

		pUserData = new CUserData(pSet->qwUserID, pSet->lActorID, dwServerID, this);
		if (NULL == pUserData)
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, Newʧ��!");
			return FALSE;
		}

		m_UserMap[qwUserID] = pUserData;

		g_pUserSink->OnAddUser(dwServerID, pSet->qwUserID, pSet->lActorID);
	}
	else
	{
		pUserData = (*it).second;

		// ���Ҫ�л�������
		if (REQUESTID_ACTOR_LOGIN == nRequestID && nInDataLen == sizeof(SActorLogin_Set))
		{
			SActorLogin_Set *pSet = (SActorLogin_Set*)pInData;
			g_pUserSink->OnDelUser(pUserData->GetServerID(), qwUserID);
			g_pUserSink->OnAddUser(dwServerID, pSet->qwUserID, pSet->lActorID);
			pUserData->SetServerID(dwServerID);
		}
	}

	// ����û����ڴ���, �򲻴���
	if (TRUE == pUserData->IsSaving())
	{
		g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, �û�%ld���ڴ���...!", qwUserID);
		return FALSE;
	}

	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	switch (nRequestID)
	{
		// ��DB����
	case REQUESTID_ACTOR_LOGIN:
	case REQUESTID_GOODS_GET:
	case REQUESTID_INTERACT_LOAD:
		// ����ӻ�����ȡ����ʧ��, ������ݿ���ȡ
		if (FALSE == pUserData->Load(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			if (FALSE == g_pDBEngine->Request(nIndex, nRequestID, qwUserID, pInData, nInDataLen, this))
			{
				g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, DBEngine����ʧ��, RequestID=%d!", nRequestID);
				return FALSE;
			}
			m_RequestMap[nIndex] = pRet;
			return TRUE;
		}

		break;

		// ����DB����
	case REQ_VESTIB_USERDEFINED_LOAD:
		// ����ӻ�����ȡ����ʧ��
		if (FALSE == pUserData->Load(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, UserData����ʧ��, RequestID=%d!", nRequestID);
			return FALSE;
		}
		break;

		// д����
	case REQUESTID_ACTOR_UPDATE:
	case REQUESTID_GOODS_UPDATE:
	case REQUESTID_INTERACT_SAVE:
	case REQUESTID_ACTOR_LOGOUT:
	case REQ_VESTIB_USERDEFINED_SAVE:
	case REQ_VESTIB_USER_SAVE_OK:
		if (FALSE == pUserData->Save(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, UserData����ʧ��, RequestID=%d!", nRequestID);
			return FALSE;
		}

		break;

	default:
		g_pTrace->TraceErrorLn("CDataProcUser::Requestʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	pRet->OnRet(nIndex, qwUserID, nRequestID, pInData, nInDataLen, DBRET_OK, pOutData, nOutLen);

	return TRUE;
}

// ���ݿ����󷵻ػص�����
void CDataProcUser::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
						  s32 nReturn, LPSTR pOutData, s32 nOutLen)
{
	// ���û���ҵ�������, �򲻴���
	map<s32, IDBProxyRetSink*>::iterator it = m_RequestMap.find(nIndex);
	if (it == m_RequestMap.end())
	{
		//g_pTrace->TraceErrorLn("CDataProcUser::OnRetʧ��, û���ҵ�����, RequestID=%d!", nRequestID);
		return;
	}

	IDBProxyRetSink *pSink = m_RequestMap[nIndex];
	m_RequestMap.erase(nIndex);

	map<s64, CUserData*>::iterator itUser = m_UserMap.find(qwUserID);
	if (itUser == m_UserMap.end())
	{
		//g_pTrace->TraceErrorLn("CDataProcUser::OnRetʧ��, û���ҵ��û�, UserID=%ld!", qwUserID);
		return;
	}

	pSink->OnRet(nIndex, qwUserID, nRequestID, pInData, nInLen, nReturn, pOutData, nOutLen);
}

// �����û�
CUserData* CDataProcUser::FindUser(s64 qwUserID)
{
	map<s64, CUserData*>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		return NULL;
	}
	return (*it).second;
}

// ɾ���û�
void CDataProcUser::DelUser(s64 qwUserID, CUserData *pUserData)
{
	map<s64, CUserData*>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		//g_pTrace->TraceLn("CDataProcUser::DelUserʧ��, û���ҵ��û�%ld!", qwUserID);
		return;
	}

	if (pUserData != (*it).second)
	{
		//g_pTrace->TraceLn("CDataProcUser::DelUserʧ��, �û�ָ�벻��!");
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
		//ǿ�Ʊ�����ҵ����ݣ����������
		pUserData->KickUser();
	}
}

