#include "Header.h"
#include "DBProxy.h"
#include "IDBStruct.h"
#include "IDBClient.h"

// ���캯��
CDBProxy::CDBProxy() : m_DataProcToken(&m_DataProcUser)
{

}

// ��������
CDBProxy::~CDBProxy()
{

}

// �������ݿ����
BOOL CDBProxy::Create(LPSTR szKey, const char *szDBEngineName,
	LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	if (FALSE == CheckData())
	{
		return FALSE;
	}

	// �������ݿ�����
	if (FALSE == m_DBEngineHelper.Create(this, szKey, szDBEngineName, szDBEngineScp, szDBRequestScp, log_file))
	{
		g_pTrace->TraceErrorLn("CDBProxy::Createʧ��, �������ݿ�����ʧ��!");
		return FALSE;
	} 

	// �ҽ����ݿ��¼�
	//g_pLogicThread->AttachEvent(m_DBEngineHelper.m_pDBEngine->GetOnReturnEvent(), this);

	g_pDBEngine = m_DBEngineHelper.m_pDBEngine;

	// ����50ms��ʱ��ʱ��
	g_pTimeAxis->SetTimer(0, 50, this, INFINITY_CALL, "CDBProxy::Create");

	return TRUE;
}

// �������ݿ����
void CDBProxy::Release(void)
{
	if (m_DBEngineHelper.m_pDBEngine != NULL)
	{
		// ȡ���ҽ����ݿ��¼�
		//g_pLogicThread->DetachEvent(m_DBEngineHelper.m_pDBEngine->GetOnReturnEvent());
	}
	else
	{
		//g_pTrace->TraceLn("CDBProxy::~CDBProxyʧ��, �����Ƿ�!");
	}
	g_pTimeAxis->KillTimer(0, this);
	m_DBEngineHelper.Close(); 
	delete this;
}

// �쳣�����ص�����
void CDBProxy::OnWarning(s32 nReturn, LPSTR szDesc)
{
	g_pTrace->TraceErrorLn(szDesc);
}

// �������ݿ�
BOOL CDBProxy::Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
					   LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet,
					   LPVOID dwServerID)
{
	CDataProc *pDataProc = GetDataProc(nRequestID, pInData, nInDataLen);
	if (NULL == pDataProc)
	{
		g_pTrace->TraceErrorLn("CDBProxy::Requestʧ��, �Ҳ������ݴ������, RequestID=%d!", nRequestID);
		return FALSE;
	}

	if (FALSE == pDataProc->Request(nIndex, nRequestID, qwUserID, pInData, nInDataLen,
		pRet, dwServerID))
	{
		g_pTrace->TraceErrorLn("CDBProxy::Requestʧ��, ����ʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

//�رշ����������ڴ��������ݵı���
void CDBProxy::CloseServer(LPVOID dwServerID)
{
	m_DataProcSaveDB.CloseServer(dwServerID);
}

// �¼��ص��ӿ�
void CDBProxy::OnEvent(void)
{
	if (m_DBEngineHelper.m_pDBEngine != NULL)
	{
		m_DBEngineHelper.m_pDBEngine->OnReturn();
	}
}

// ��ʱ���ص�
void CDBProxy::OnTimer(u32 dwTimerID)
{
	OnEvent();
}

// �������
BOOL CDBProxy::CheckData(void)
{
	/*
	if ((sizeof(SActorLogin_Get) - sizeof(s32))
		!= (sizeof(SActorUpdate_Set) - sizeof(s32) - sizeof(s32)))
	{
		g_pTrace->TraceErrorLn("CDBProxy::CheckDataʧ��, SActorLogin_Get��SActorUpdate_Set��ƥ��!");
			return FALSE;
	}

	if ((sizeof(SInteractLoad_Get) - sizeof(s32))
		!= (sizeof(SInteractSave_Set) - sizeof(BYTE) * 2 - sizeof(s32)))
	{
		g_pTrace->TraceErrorLn("CDBProxy::CheckDataʧ��, SInteractLoad_Get��SInteractSave_Set��ƥ��!");
			return FALSE;
	}
	*/

	return TRUE;
}

// �������ݴ�����
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

		// �û�����
	case REQUESTID_ACTOR_LOGIN:
	case REQUESTID_ACTOR_UPDATE:
	case REQUESTID_GOODS_GET:
	case REQUESTID_GOODS_UPDATE:
	case REQUESTID_ACTOR_LOGOUT:
	case REQ_VESTIB_USERDEFINED_LOAD:
	case REQ_VESTIB_USERDEFINED_SAVE:
	case REQ_VESTIB_USER_SAVE_OK:
		return &m_DataProcUser;

		// ��������
	case REQ_VESTIB_LOGIN_USER_JUMP_START:
	case REQ_VESTIB_LOGIN_USER_JUMP_FINISH:
	case REQ_VESTIB_KICK_USER:
		return &m_DataProcToken;

		//	// ֱͨ����
	default:
		return &m_DataProcDirect;
	}

	return NULL;
}

// �������ݿ����(�������)
extern "C" DLL_EXPORT BOOL CreateDBProxy(u32 dwSaveTimes,IDBProxy **ppDBProxy, LPSTR szKey, 
	ILog *pTrace, ITimerAxis *pTimeAxis, IDBProxyUserSink *pUserSink,LPCSTR szDBEngineName,
	LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	if ( NULL == pUserSink)
	{		 
		return FALSE;
	} 

	// ����1000Ϊ ���뵥λ
	g_dwSaveTimes = dwSaveTimes *1000;
	CDBProxy *pNewDBProxy = new CDBProxy;
	if (NULL == pNewDBProxy)
	{
		pTrace->TraceErrorLn("�����ݿ��������ڴ�ʧ��!");
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
		g_pTrace->TraceErrorLn("���ݿ������ʧ��!");
		return FALSE;
	}

	*ppDBProxy = static_cast<IDBProxy *>(pNewDBProxy);

	return TRUE;
}

