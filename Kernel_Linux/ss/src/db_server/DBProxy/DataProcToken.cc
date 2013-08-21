#include "Header.h"
#include "DataProcToken.h"
#include "UserToken.h"
#include "IDBEngine.h"
#include "IDBStruct.h"
#include "IDBClient.h"
#include "DataProcUser.h"

// 构造函数
CDataProcToken::CDataProcToken(CDataProcUser *pProcUser)
{
	m_pProcUser = pProcUser;
}

// 析构函数
CDataProcToken::~CDataProcToken()
{
	map<s64, CUserToken*>::iterator it = m_TokenMap.begin();
	while (it != m_TokenMap.end())
	{
		CUserToken *pUserToken = (*it).second;
		delete pUserToken;
		it = m_TokenMap.begin();

		//g_pTrace->TraceErrorLn("CDataProcToken::~CDataProcToken, 主动释放!");
		//g_pTrace->TraceLn("CDataProcToken::~CDataProcToken, 主动释放!");
	}

	m_TokenMap.clear();
}

// 请求处理
BOOL CDataProcToken::Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
							 LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
							 LPVOID dwServerID)
{
	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	// 跳转开始
	if (REQ_VESTIB_LOGIN_USER_JUMP_START == nRequestID)
	{
		// 如果缓存数据中存在该令牌了, 则不处理
		map<s64, CUserToken*>::iterator it = m_TokenMap.find(qwUserID);
		if (it != m_TokenMap.end())
		{
			g_pTrace->TraceErrorLn("CDataProcToken::Request失败, 令牌重复, UserID=%d!", qwUserID);
			return FALSE;
		}

		if (nInDataLen != sizeof(SLoginUserJumpStart_Set))
		{
			g_pTrace->TraceLn("CDataProcToken::Request失败, %d!=sizeof(SLoginUserJumpStart_Set)!", nInDataLen);
			return FALSE;
		}

		// 如果是登录后即将进入场景服时, 则要判断是否重复登录
		SLoginUserJumpStart_Set *pSet = (SLoginUserJumpStart_Set*)pInData;
		if (LOGIN_USER_JUMP_TYPE_FIRST_LOGIN == pSet->lJumpType)
		{
			if (m_pProcUser->FindUser(pSet->qwUserID) != NULL)
			{
				nOutLen = 0;
				pRet->OnRet(nIndex, qwUserID, nRequestID, pInData, nInDataLen,
					VESTIBULE_RET_REQ_REPEATLY_LOGIN, pOutData, nOutLen);
				g_pTrace->TraceLn("CDataProcToken::Request失败, 重复登录角色, UserID=%ld!", pSet->qwUserID);
				return TRUE;
			}
		}

		CUserToken *pUserToken = new CUserToken(qwUserID, this);
		if (NULL == pUserToken)
		{
			g_pTrace->TraceLn("CDataProcToken::Request失败, New失败!");
			return FALSE;
		}

		if (FALSE == pUserToken->Create(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			g_pTrace->TraceLn("CDataProcToken::Request失败, Create失败!");
			delete pUserToken;
			return FALSE;
		}

		m_TokenMap[qwUserID] = pUserToken;
	}
	// 跳转完成
	else if (REQ_VESTIB_LOGIN_USER_JUMP_FINISH == nRequestID)
	{
		// 如果缓存数据中不存在该令牌了, 则不处理
		map<s64, CUserToken*>::iterator it = m_TokenMap.find(qwUserID);
		if (it == m_TokenMap.end())
		{
			//g_pTrace->TraceErrorLn("CDataProcToken::Request失败, 不存在令牌或者令牌失效, UserID=%ld!", qwUserID);
			return FALSE;
		}

		CUserToken *pUserToken = (*it).second;
		if (FALSE == pUserToken->Check(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			return FALSE;
		}
	}
	// 踢人
	else if (REQ_VESTIB_KICK_USER == nRequestID)
	{
		//先看玩家的数据是否可以保存DB
		if (NULL != m_pProcUser)
		{
			m_pProcUser->KickUser(qwUserID);
		}

		// 如果缓存数据中不存在该令牌了, 则不处理
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
		//g_pTrace->TraceErrorLn("CDataProcToken::Request失败, RequestID=%d!", nRequestID);
		return FALSE;
	}

	pRet->OnRet(nIndex, qwUserID, nRequestID, pInData, nInDataLen, DBRET_OK, pOutData, nOutLen);

	return TRUE;
}

// 删除令牌
void CDataProcToken::DelToken(s64 qwUserID, CUserToken *pUserToken)
{
	map<s64, CUserToken*>::iterator it = m_TokenMap.find(qwUserID);
	if (it == m_TokenMap.end())
	{
		//g_pTrace->TraceLn("CDataProcToken::DelToken失败, 没有找到用户%ld!", qwUserID);
		return;
	}

	if (pUserToken != (*it).second)
	{
		//g_pTrace->TraceLn("CDataProcToken::DelToken失败, 用户指针不对!");
		return;
	}
	m_TokenMap.erase(qwUserID);
}


