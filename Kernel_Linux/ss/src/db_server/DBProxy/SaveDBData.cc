#include "Header.h"
#include "SaveDBData.h"
#include "DataProcSaveDB.h"
#include "IDBStruct.h"

#define TIMER_ID_SDB			11					//��������Ƿ��޸ĵĶ�ʱ��
#define TIME_SAVE_DATA_SDB		60 * 60 * 1000		//ÿ60���Ӽ��һ�������Ƿ��޸�

CSaveDBData::CSaveDBData(s32 nDataType, s64 qwDataKey, LPVOID dwServerID, CDataProcSaveDB *pDataProcUser)
:m_nDataType(nDataType)
,m_qwDataKey(qwDataKey)
,m_dwServerID(dwServerID)
,m_pProcSaveDB(pDataProcUser)
{
	m_bSaving = FALSE;
	m_dwLastSave = GetTickCount();

	m_nSaveRID = 0;

	m_VecData.clear();

	g_pTimeAxis->SetTimer(TIMER_ID_SDB, TIME_SAVE_DATA_SDB, (ITimerHandler*)this, INFINITY_CALL,  "CSaveDBData::CSaveDBData");
}

CSaveDBData::~CSaveDBData()
{
	g_pTimeAxis->KillTimer(TIMER_ID_SDB, this);

	m_VecData.clear();

	m_pProcSaveDB->DelDBData(m_nDataType, m_qwDataKey, this);
}

//////////////////////////////////////////////////////////////////////////
////////////////////////////////// IDBRetSink ////////////////////////////
// ���ݿ����󷵻ػص�����
// nReturn: �ο��������ݿ����󷵻�ֵ����
// pOutData: ������ݻ�����ָ��
// nOutLen: ������ݻ���������
void CSaveDBData::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
						s32 nReturn, LPSTR pOutData, s32 nOutLen)
{
	if (nReturn != DBRET_OK)
	{
		g_pTrace->TraceErrorLn("CSaveDBData::OnRetʧ��, UserID=%ld, RequestID=%d, Return=%d!",
			qwUserID, nRequestID, nReturn);
	}

	if (REQUESTID_INTERACT_SAVE == nRequestID && TRUE == m_bSaving)
	{
		delete this;
	}
}

//////////////////////////////////////////////////////////////////////////
////////////////////////////////// ITimerSink ////////////////////////////
// ��ʱ���ص�
void CSaveDBData::OnTimer(u32 dwTimerID)
{
	if (m_nSaveRID > 0)
	{
		if (FALSE == g_pDBEngine->Request(0, m_nSaveRID, m_qwDataKey, &m_VecData[0], m_VecData.capacity(), this))
		{
			g_pTrace->TraceLn("CUserData::OnTimerʧ��, nRequestID: %d, nDataKey: %d", m_nSaveRID, m_qwDataKey);
			return;
		}
	}

	//���á���ʱ�䲻�޸���������ݵĻ��ơ�
	//�ж��� TIME_SAVE_DATA_SDB ʱ���ڣ�������û�б�������û�оͱ��沢ɾ���Լ�
	if (::GetTickCount() - m_dwLastSave < TIME_SAVE_DATA_SDB)
	{
		return;
	}

	m_bSaving = TRUE;

	if (m_nSaveRID > 0)
	{
		g_pTimeAxis->KillTimer(TIMER_ID_SDB, this);
	}
	else
	{
		delete this;
	}
}

//////////////////////////////////////////////////////////////////////////
///////////////////////////////// CSaveDBData ////////////////////////////
//�Ƿ����ڴ���
BOOL CSaveDBData::IsSaving(void)
{
	return m_bSaving;
}

//��ȡ������ID
LPVOID CSaveDBData::GetServerID(void)
{
	return m_dwServerID;
}

//���÷�����ID
void CSaveDBData::SetServerID(LPVOID dwServerID)
{
	m_dwServerID = dwServerID;
}

//��������
BOOL CSaveDBData::Save(s32 nRequestID, LPSTR pInData, s32 nInDataLen, LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_bSaving)
	{
		g_pTrace->TraceLn("CSaveDBData::Save, nDataType: %d, nDataKey: %d ���ڴ���", m_nDataType, m_qwDataKey);
		return FALSE;
	}

	if (NULL == pInData || nInDataLen <= 0)
	{
		g_pTrace->TraceLn("CSaveDBData::Save, nDataType: %d, nDataKey: %d, pInData: %p, nInDataLen: %d", 
			m_nDataType, m_qwDataKey, pInData, nInDataLen);
		return FALSE;
	}

	if (m_VecData.capacity() <= 0)
	{
		m_VecData.resize(nInDataLen);
	}

	if (m_VecData.capacity() != (u32)nInDataLen)
	{
		g_pTrace->TraceLn("CSaveDBData::Save, nDataType: %d, nDataKey: %d, capacity: %d, nInDataLen: %d", 
			m_nDataType, m_qwDataKey, m_VecData.capacity(), nInDataLen);
		return FALSE;
	}

	if (REQUESTID_INTERACT_SAVE == nRequestID)
	{
		SInteractSave_Get *pGet = (SInteractSave_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		pGet->szDes[0] = 0;
		nOutDataLen = sizeof(SInteractSave_Get);
	}
	else
	{
		g_pTrace->TraceLn("CSaveDBData::Saveʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	//��������
	m_nSaveRID = nRequestID;
	memcpy(&m_VecData[0], pInData, nInDataLen);

	m_dwLastSave = ::GetTickCount();

	return TRUE;
}

//װ������
BOOL CSaveDBData::Load(s32 nRequestID, LPSTR pInData, s32 nInDataLen, LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_bSaving)
	{
		g_pTrace->TraceLn("CSaveDBData::Load, nDataType: %d, nDataKey: %d���ڴ���", m_nDataType, m_qwDataKey);
		return FALSE;
	}

	//���ݲ�����
	if (m_nSaveRID <= 0)
	{
		return FALSE;
	}

	// ��ȡ��������
	if (REQUESTID_INTERACT_LOAD == nRequestID)
	{
		if (nInDataLen != sizeof(SInteractLoad_Set))
		{
			g_pTrace->TraceLn("CSaveDBData::Load, ��ȡ��������%d != sizeof(SInteractLoad_Set)!", nInDataLen);
			return FALSE;
		}

		if (m_VecData.capacity() != sizeof(SInteractSave_Set))
		{
			g_pTrace->TraceLn("CSaveDBData::Load, ��ȡ��������%d != sizeof(SInteractSave_Set)!", m_VecData.capacity());
			return FALSE;
		}

		SInteractSave_Set Save_Set;
		memcpy((char *) &Save_Set, &m_VecData[0], m_VecData.capacity());

		// ��������
		SInteractLoad_Get *pGet = (SInteractLoad_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		memcpy(pGet->DataBuffer, Save_Set.DataBuffer, sizeof(pGet->DataBuffer));

		nOutDataLen = sizeof(SInteractLoad_Get);
	}
	else
	{
		g_pTrace->TraceErrorLn("CSaveDBData::Loadʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

//�رշ����������ڴ��������ݵı���
void CSaveDBData::CloseServer(void)
{
	m_bSaving = TRUE;

	if (m_nSaveRID > 0)
	{
		g_pTimeAxis->KillTimer(TIMER_ID_SDB, this);
		m_pProcSaveDB->DelDBData(m_nDataType, m_qwDataKey, this);

		if (FALSE == g_pDBEngine->Request(0, m_nSaveRID, m_qwDataKey, &m_VecData[0], m_VecData.capacity(), this))
		{
			g_pTrace->TraceLn("CUserData::OnTimerʧ��, nRequestID: %d, nDataKey: %ld", m_nSaveRID, m_qwDataKey);
		}
	}
	else
	{
		delete this;
	}
}

