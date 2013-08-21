#include "Header.h"
#include "DataProcToken.h"
#include "UserToken.h"
#include "IDBEngine.h"
#include "IDBStruct.h"
#include "IDBClient.h"
#include "DataProcUser.h"

// ���캯��
CDataProcToken::CDataProcToken(CDataProcUser *pProcUser)
{
	m_pProcUser = pProcUser;
}

// ��������
CDataProcToken::~CDataProcToken()
{
	map<s64, CUserToken*>::iterator it = m_TokenMap.begin();
	while (it != m_TokenMap.end())
	{
		CUserToken *pUserToken = (*it).second;
		delete pUserToken;
		it = m_TokenMap.begin();

		//g_pTrace->TraceErrorLn("CDataProcToken::~CDataProcToken, �����ͷ�!");
		//g_pTrace->TraceLn("CDataProcToken::~CDataProcToken, �����ͷ�!");
	}

	m_TokenMap.clear();
}

// ������
BOOL CDataProcToken::Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
							 LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
							 LPVOID dwServerID)
{
	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	// ��ת��ʼ
	if (REQ_VESTIB_LOGIN_USER_JUMP_START == nRequestID)
	{
		// ������������д��ڸ�������, �򲻴���
		map<s64, CUserToken*>::iterator it = m_TokenMap.find(qwUserID);
		if (it != m_TokenMap.end())
		{
			g_pTrace->TraceErrorLn("CDataProcToken::Requestʧ��, �����ظ�, UserID=%d!", qwUserID);
			return FALSE;
		}

		if (nInDataLen != sizeof(SLoginUserJumpStart_Set))
		{
			g_pTrace->TraceLn("CDataProcToken::Requestʧ��, %d!=sizeof(SLoginUserJumpStart_Set)!", nInDataLen);
			return FALSE;
		}

		// ����ǵ�¼�󼴽����볡����ʱ, ��Ҫ�ж��Ƿ��ظ���¼
		SLoginUserJumpStart_Set *pSet = (SLoginUserJumpStart_Set*)pInData;
		if (LOGIN_USER_JUMP_TYPE_FIRST_LOGIN == pSet->lJumpType)
		{
			if (m_pProcUser->FindUser(pSet->qwUserID) != NULL)
			{
				nOutLen = 0;
				pRet->OnRet(nIndex, qwUserID, nRequestID, pInData, nInDataLen,
					VESTIBULE_RET_REQ_REPEATLY_LOGIN, pOutData, nOutLen);
				g_pTrace->TraceLn("CDataProcToken::Requestʧ��, �ظ���¼��ɫ, UserID=%ld!", pSet->qwUserID);
				return TRUE;
			}
		}

		CUserToken *pUserToken = new CUserToken(qwUserID, this);
		if (NULL == pUserToken)
		{
			g_pTrace->TraceLn("CDataProcToken::Requestʧ��, Newʧ��!");
			return FALSE;
		}

		if (FALSE == pUserToken->Create(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			g_pTrace->TraceLn("CDataProcToken::Requestʧ��, Createʧ��!");
			delete pUserToken;
			return FALSE;
		}

		m_TokenMap[qwUserID] = pUserToken;
	}
	// ��ת���
	else if (REQ_VESTIB_LOGIN_USER_JUMP_FINISH == nRequestID)
	{
		// ������������в����ڸ�������, �򲻴���
		map<s64, CUserToken*>::iterator it = m_TokenMap.find(qwUserID);
		if (it == m_TokenMap.end())
		{
			//g_pTrace->TraceErrorLn("CDataProcToken::Requestʧ��, ���������ƻ�������ʧЧ, UserID=%ld!", qwUserID);
			return FALSE;
		}

		CUserToken *pUserToken = (*it).second;
		if (FALSE == pUserToken->Check(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			return FALSE;
		}
	}
	// ����
	else if (REQ_VESTIB_KICK_USER == nRequestID)
	{
		//�ȿ���ҵ������Ƿ���Ա���DB
		if (NULL != m_pProcUser)
		{
			m_pProcUser->KickUser(qwUserID);
		}

		// ������������в����ڸ�������, �򲻴���
		map<s64, CUserToken*>::iterator it = m_TokenMap.find(qwUserID);
		if (it != m_TokenMap.end())
		{
			CUserToken *pUserToken = (*it).second;
			if (FALSE == pUserToken->KickUser(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
			{
				return FALSE;
			}
		}
	}
	else
	{
		//g_pTrace->TraceErrorLn("CDataProcToken::Requestʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	pRet->OnRet(nIndex, qwUserID, nRequestID, pInData, nInDataLen, DBRET_OK, pOutData, nOutLen);

	return TRUE;
}

// ɾ������
void CDataProcToken::DelToken(s64 qwUserID, CUserToken *pUserToken)
{
	map<s64, CUserToken*>::iterator it = m_TokenMap.find(qwUserID);
	if (it == m_TokenMap.end())
	{
		//g_pTrace->TraceLn("CDataProcToken::DelTokenʧ��, û���ҵ��û�%ld!", qwUserID);
		return;
	}

	if (pUserToken != (*it).second)
	{
		//g_pTrace->TraceLn("CDataProcToken::DelTokenʧ��, �û�ָ�벻��!");
		return;
	}
	m_TokenMap.erase(qwUserID);
}


