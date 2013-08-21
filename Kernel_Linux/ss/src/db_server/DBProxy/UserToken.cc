#include "Header.h"
#include "UserToken.h"
#include "IDBEngine.h"
#include "IDBStruct.h"
#include "IDBClient.h"
#include "stdlib.h"

// ���캯��
CUserToken::CUserToken(s64 qwUserID, CDataProcToken *pDataProcToken)
{
	m_qwUserID = qwUserID;
	m_pDataProcToken = pDataProcToken;

	memset(m_dwToken, 0, sizeof(m_dwToken));
	m_dwTokenOK = FALSE;
	memset(m_szFlag, 0, sizeof(m_szFlag));
	//m_lJumpType = LOGIN_USER_JUMP_TYPE_NULL;
}

// ��������
CUserToken::~CUserToken()
{
	g_pTimeAxis->KillTimer(0, this);
	m_pDataProcToken->DelToken(m_qwUserID, this);
}

// ��ʱ���ص�
void CUserToken::OnTimer(u32 dwTimerID)
{
	g_pTrace->TraceLn("���Ƴ�ʱ, UserId=%ld!", m_qwUserID);

	delete this;
}

// ��������
BOOL CUserToken::Create(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
						LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_dwTokenOK)
	{
		g_pTrace->TraceLn("CUserToken::Createʧ��, ���ƴ����ظ�, UserID=%ld!", m_qwUserID);
		return FALSE;
	}

	// ��ת��ʼ
	if (REQ_VESTIB_LOGIN_USER_JUMP_START == nRequestID)
	{
		if (nInDataLen != sizeof(SLoginUserJumpStart_Set))
		{
			g_pTrace->TraceLn("CUserToken::Createʧ��, %d!=sizeof(SLoginUserJumpStart_Set)!", nInDataLen);
			return FALSE;
		}

		SLoginUserJumpStart_Set *pSet = (SLoginUserJumpStart_Set*)pInData;
		if (pSet->qwUserID != m_qwUserID)
		{
			g_pTrace->TraceLn("CUserToken::Createʧ��, ���ݷǷ�!");
			return FALSE;
		}

		// ����ͻ��˱�ʾ
		memcpy(m_szFlag, pSet->szRand, sizeof(m_szFlag));
		// ������ת����
		m_lJumpType = pSet->lJumpType;

		// ��������
		m_dwToken[0] = rand();
		m_dwToken[1] = rand();
		m_dwToken[2] = rand();
		m_dwToken[3] = rand();
		m_dwTokenOK = TRUE;

		SLoginUserJumpStart_Get *pGet = (SLoginUserJumpStart_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		memcpy(pGet->ValidationCode, m_dwToken, sizeof(pGet->ValidationCode));
		nOutDataLen = sizeof(SLoginUserJumpStart_Get);

		// ����100S��ʱ��ʱ��
		g_pTimeAxis->SetTimer(0, 100000, this, INFINITY_CALL, "CUserToken::Create");
	}
	else
	{
		g_pTrace->TraceLn("CUserToken::Createʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

// ��֤����
BOOL CUserToken::Check(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
					   LPSTR pOutData, s32 &nOutDataLen)
{
	if (FALSE == m_dwTokenOK)
	{
		g_pTrace->TraceLn("CUserToken::Checkʧ��, ����û�д���, UserID=%ld!", m_qwUserID);
		return FALSE;
	}

	// ��ת���
	if (REQ_VESTIB_LOGIN_USER_JUMP_FINISH == nRequestID)
	{
		if (nInDataLen != sizeof(SLoginUserJumpFinish_Set))
		{
			g_pTrace->TraceLn("CUserToken::Checkʧ��, %d!=sizeof(SLoginUserJumpFinish_Set)!", nInDataLen);
			return FALSE;
		}

		SLoginUserJumpFinish_Set *pSet = (SLoginUserJumpFinish_Set*)pInData;
		if (pSet->qwUserID != m_qwUserID)
		{
			g_pTrace->TraceLn("CUserToken::Checkʧ��, ���ݷǷ�!");
			return FALSE;
		}

		SLoginUserJumpFinish_Get *pGet = (SLoginUserJumpFinish_Get*)pOutData;
		pGet->lJumpType = m_lJumpType;
		nOutDataLen = sizeof(SLoginUserJumpFinish_Get);

		// �ȽϿͻ��˱�ʾ�Լ�����
		if (0 == memcmp(m_szFlag, pSet->szRand, sizeof(m_szFlag))
			&& 0 == memcmp(m_dwToken, pSet->ValidationCode, sizeof(m_dwToken)))
		{
			pGet->lReturn = DBRET_OK;
		}
		else
		{
			g_pTrace->TraceLn("CUserToken::Checkʧ��, �ͻ��˱�ʾ�Լ�����!");
			delete this;
			return FALSE;
		}

		delete this;
	}
	else
	{
		g_pTrace->TraceLn("CUserToken::Checkʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

// ����
BOOL CUserToken::KickUser(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
						  LPSTR pOutData, s32 &nOutDataLen)
{
	if (FALSE == m_dwTokenOK)
	{
		g_pTrace->TraceLn("CUserToken::KickUserʧ��, ����û�д���, UserID=%ld!", m_qwUserID);
		return FALSE;
	}

	// ����
	// 	if (REQ_VESTIB_KICK_USER == nRequestID)
	// 	{
	// 		delete this;
	// 	}
	// 	else
	// 	{
	// 		g_pTrace->TraceLn("CUserToken::KickUserʧ��, RequestID=%d!", nRequestID);
	// 		return FALSE;
	// 	}

	return TRUE;
}

