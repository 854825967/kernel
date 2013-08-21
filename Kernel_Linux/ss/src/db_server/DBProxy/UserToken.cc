#include "Header.h"
#include "UserToken.h"
#include "IDBEngine.h"
#include "IDBStruct.h"
#include "IDBClient.h"
#include "stdlib.h"

// 构造函数
CUserToken::CUserToken(s64 qwUserID, CDataProcToken *pDataProcToken)
{
	m_qwUserID = qwUserID;
	m_pDataProcToken = pDataProcToken;

	memset(m_dwToken, 0, sizeof(m_dwToken));
	m_dwTokenOK = FALSE;
	memset(m_szFlag, 0, sizeof(m_szFlag));
	//m_lJumpType = LOGIN_USER_JUMP_TYPE_NULL;
}

// 析构函数
CUserToken::~CUserToken()
{
	g_pTimeAxis->KillTimer(0, this);
	m_pDataProcToken->DelToken(m_qwUserID, this);
}

// 定时器回调
void CUserToken::OnTimer(u32 dwTimerID)
{
	g_pTrace->TraceLn("令牌超时, UserId=%ld!", m_qwUserID);

	delete this;
}

// 生成令牌
BOOL CUserToken::Create(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
						LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_dwTokenOK)
	{
		g_pTrace->TraceLn("CUserToken::Create失败, 令牌创建重复, UserID=%ld!", m_qwUserID);
		return FALSE;
	}

	// 跳转开始
	if (REQ_VESTIB_LOGIN_USER_JUMP_START == nRequestID)
	{
		if (nInDataLen != sizeof(SLoginUserJumpStart_Set))
		{
			g_pTrace->TraceLn("CUserToken::Create失败, %d!=sizeof(SLoginUserJumpStart_Set)!", nInDataLen);
			return FALSE;
		}

		SLoginUserJumpStart_Set *pSet = (SLoginUserJumpStart_Set*)pInData;
		if (pSet->qwUserID != m_qwUserID)
		{
			g_pTrace->TraceLn("CUserToken::Create失败, 数据非法!");
			return FALSE;
		}

		// 保存客户端标示
		memcpy(m_szFlag, pSet->szRand, sizeof(m_szFlag));
		// 保存跳转类型
		m_lJumpType = pSet->lJumpType;

		// 生成令牌
		m_dwToken[0] = rand();
		m_dwToken[1] = rand();
		m_dwToken[2] = rand();
		m_dwToken[3] = rand();
		m_dwTokenOK = TRUE;

		SLoginUserJumpStart_Get *pGet = (SLoginUserJumpStart_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		memcpy(pGet->ValidationCode, m_dwToken, sizeof(pGet->ValidationCode));
		nOutDataLen = sizeof(SLoginUserJumpStart_Get);

		// 创建100S超时定时器
		g_pTimeAxis->SetTimer(0, 100000, this, INFINITY_CALL, "CUserToken::Create");
	}
	else
	{
		g_pTrace->TraceLn("CUserToken::Create失败, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

// 验证令牌
BOOL CUserToken::Check(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
					   LPSTR pOutData, s32 &nOutDataLen)
{
	if (FALSE == m_dwTokenOK)
	{
		g_pTrace->TraceLn("CUserToken::Check失败, 令牌没有创建, UserID=%ld!", m_qwUserID);
		return FALSE;
	}

	// 跳转完成
	if (REQ_VESTIB_LOGIN_USER_JUMP_FINISH == nRequestID)
	{
		if (nInDataLen != sizeof(SLoginUserJumpFinish_Set))
		{
			g_pTrace->TraceLn("CUserToken::Check失败, %d!=sizeof(SLoginUserJumpFinish_Set)!", nInDataLen);
			return FALSE;
		}

		SLoginUserJumpFinish_Set *pSet = (SLoginUserJumpFinish_Set*)pInData;
		if (pSet->qwUserID != m_qwUserID)
		{
			g_pTrace->TraceLn("CUserToken::Check失败, 数据非法!");
			return FALSE;
		}

		SLoginUserJumpFinish_Get *pGet = (SLoginUserJumpFinish_Get*)pOutData;
		pGet->lJumpType = m_lJumpType;
		nOutDataLen = sizeof(SLoginUserJumpFinish_Get);

		// 比较客户端标示以及令牌
		if (0 == memcmp(m_szFlag, pSet->szRand, sizeof(m_szFlag))
			&& 0 == memcmp(m_dwToken, pSet->ValidationCode, sizeof(m_dwToken)))
		{
			pGet->lReturn = DBRET_OK;
		}
		else
		{
			g_pTrace->TraceLn("CUserToken::Check失败, 客户端标示以及令牌!");
			delete this;
			return FALSE;
		}

		delete this;
	}
	else
	{
		g_pTrace->TraceLn("CUserToken::Check失败, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

// 踢人
BOOL CUserToken::KickUser(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
						  LPSTR pOutData, s32 &nOutDataLen)
{
	if (FALSE == m_dwTokenOK)
	{
		g_pTrace->TraceLn("CUserToken::KickUser失败, 令牌没有创建, UserID=%ld!", m_qwUserID);
		return FALSE;
	}

	// 踢人
	// 	if (REQ_VESTIB_KICK_USER == nRequestID)
	// 	{
	// 		delete this;
	// 	}
	// 	else
	// 	{
	// 		g_pTrace->TraceLn("CUserToken::KickUser失败, RequestID=%d!", nRequestID);
	// 		return FALSE;
	// 	}

	return TRUE;
}

