#include "Header.h"
#include "DBProxy.h"
#include "IDBStruct.h"
#include "IDBClient.h"

// 构造函数
CDBProxy::CDBProxy() : m_DataProcToken(&m_DataProcUser)
{

}

// 析构函数
CDBProxy::~CDBProxy()
{

}

// 创建数据库代理
BOOL CDBProxy::Create(LPSTR szKey, const char *szDBEngineName,
	LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	if (FALSE == CheckData())
	{
		return FALSE;
	}

	// 创建数据库引擎
	if (FALSE == m_DBEngineHelper.Create(this, szKey, szDBEngineName, szDBEngineScp, szDBRequestScp, log_file))
	{
		g_pTrace->TraceErrorLn("CDBProxy::Create失败, 创建数据库引擎失败!");
		return FALSE;
	} 

	// 挂接数据库事件
	//g_pLogicThread->AttachEvent(m_DBEngineHelper.m_pDBEngine->GetOnReturnEvent(), this);

	g_pDBEngine = m_DBEngineHelper.m_pDBEngine;

	// 创建50ms超时定时器
	g_pTimeAxis->SetTimer(0, 50, this, INFINITY_CALL, "CDBProxy::Create");

	return TRUE;
}

// 销毁数据库代理
void CDBProxy::Release(void)
{
	if (m_DBEngineHelper.m_pDBEngine != NULL)
	{
		// 取消挂接数据库事件
		//g_pLogicThread->DetachEvent(m_DBEngineHelper.m_pDBEngine->GetOnReturnEvent());
	}
	else
	{
		//g_pTrace->TraceLn("CDBProxy::~CDBProxy失败, 析构非法!");
	}
	g_pTimeAxis->KillTimer(0, this);
	m_DBEngineHelper.Close(); 
	delete this;
}

// 异常报警回调函数
void CDBProxy::OnWarning(s32 nReturn, LPSTR szDesc)
{
	g_pTrace->TraceErrorLn(szDesc);
}

// 请求数据库
BOOL CDBProxy::Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
					   LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
					   LPVOID dwServerID)
{
	CDataProc *pDataProc = GetDataProc(nRequestID, pInData, nInDataLen);
	if (NULL == pDataProc)
	{
		g_pTrace->TraceErrorLn("CDBProxy::Request失败, 找不到数据处理对象, RequestID=%d!", nRequestID);
		return FALSE;
	}

	if (FALSE == pDataProc->Request(nIndex, nRequestID, qwUserID, pInData, nInDataLen,
		pRet, dwServerID))
	{
		g_pTrace->TraceErrorLn("CDBProxy::Request失败, 请求失败, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

//关闭服务器，用于处理缓存数据的保存
void CDBProxy::CloseServer(LPVOID dwServerID)
{
	m_DataProcSaveDB.CloseServer(dwServerID);
}

// 事件回调接口
void CDBProxy::OnEvent(void)
{
	if (m_DBEngineHelper.m_pDBEngine != NULL)
	{
		m_DBEngineHelper.m_pDBEngine->OnReturn();
	}
}

// 定时器回调
void CDBProxy::OnTimer(u32 dwTimerID)
{
	OnEvent();
}

// 检测数据
BOOL CDBProxy::CheckData(void)
{
	/*
	if ((sizeof(SActorLogin_Get) - sizeof(s32))
		!= (sizeof(SActorUpdate_Set) - sizeof(s32) - sizeof(s32)))
	{
		g_pTrace->TraceErrorLn("CDBProxy::CheckData失败, SActorLogin_Get和SActorUpdate_Set不匹配!");
			return FALSE;
	}

	if ((sizeof(SInteractLoad_Get) - sizeof(s32))
		!= (sizeof(SInteractSave_Set) - sizeof(BYTE) * 2 - sizeof(s32)))
	{
		g_pTrace->TraceErrorLn("CDBProxy::CheckData失败, SInteractLoad_Get和SInteractSave_Set不匹配!");
			return FALSE;
	}
	*/

	return TRUE;
}

// 返回数据处理类
CDataProc* CDBProxy::GetDataProc(s32 nRequestID, LPSTR pInData, s32 nInDataLen)
{
	switch (nRequestID)
	{
	case REQUESTID_INTERACT_LOAD:
		{
			if (NULL == pInData || nInDataLen != sizeof(SInteractLoad_Set))
			{
				//g_pTrace_2->TraceLn("CDBProxy::GetDataProc, %d != sizeof(SInteractLoad_Set)!", nInDataLen);
				return NULL;
			}

			SInteractLoad_Set *pILoad_Set = (SInteractLoad_Set *) pInData;
			if (0 == pILoad_Set->lTypeID && 0 == pILoad_Set->lServerID && pILoad_Set->lOwnerID > 0)
			{
				return &m_DataProcUser;
			}
			else
			{
				return &m_DataProcSaveDB;
			}
		}
		break;

	case REQUESTID_INTERACT_SAVE:
		{
			if (NULL == pInData || nInDataLen != sizeof(SInteractSave_Set))
			{
				//g_pTrace_2->TraceLn("CDBProxy::GetDataProc, %d != sizeof(SInteractSave_Set)!", nInDataLen);
				return NULL;
			}

			SInteractSave_Set *pISave_Set = (SInteractSave_Set *) pInData;
			if (0 == pISave_Set->lTypeID && 0 == pISave_Set->lServerID && pISave_Set->lOwnerID > 0)
			{
				return &m_DataProcUser;
			}
			else
			{
				return &m_DataProcSaveDB;
			}
		}
		break;

		// 用户数据
	case REQUESTID_ACTOR_LOGIN:
	case REQUESTID_ACTOR_UPDATE:
	case REQUESTID_GOODS_GET:
	case REQUESTID_GOODS_UPDATE:
	case REQUESTID_ACTOR_LOGOUT:
	case REQ_VESTIB_USERDEFINED_LOAD:
	case REQ_VESTIB_USERDEFINED_SAVE:
	case REQ_VESTIB_USER_SAVE_OK:
		return &m_DataProcUser;

		// 令牌数据
	case REQ_VESTIB_LOGIN_USER_JUMP_START:
	case REQ_VESTIB_LOGIN_USER_JUMP_FINISH:
	case REQ_VESTIB_KICK_USER:
		return &m_DataProcToken;

		//	// 直通数据
	default:
		return &m_DataProcDirect;
	}

	return NULL;
}

// 创建数据库代理(输出函数)
extern "C" DLL_EXPORT BOOL CreateDBProxy(u32 dwSaveTimes,IDBProxy **ppDBProxy, LPSTR szKey, 
	ILog *pTrace, ITimerAxis *pTimeAxis, IDBProxyUserSink *pUserSink,LPCSTR szDBEngineName,
	LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	if ( NULL == pUserSink)
	{		 
		return FALSE;
	} 

	// 乘以1000为 毫秒单位
	g_dwSaveTimes = dwSaveTimes *1000;
	CDBProxy *pNewDBProxy = new CDBProxy;
	if (NULL == pNewDBProxy)
	{
		pTrace->TraceErrorLn("给数据库代理分配内存失败!");
		return FALSE;
	}
	g_pTrace = pTrace;
	//g_pLogicThread = pLogicThread;
	g_pTimeAxis = pTimeAxis;
	g_pUserSink = pUserSink;

	if (FALSE == pNewDBProxy->Create(szKey, szDBEngineName, szDBEngineScp, szDBRequestScp, log_file))
	{
		delete pNewDBProxy;
		pNewDBProxy = NULL;
		g_pTrace->TraceErrorLn("数据库代理创建失败!");
		return FALSE;
	}

	*ppDBProxy = static_cast<IDBProxy *>(pNewDBProxy);

	return TRUE;
}

