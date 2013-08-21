#include "Header.h"
#include "DataProcSaveDB.h"
#include "SaveDBData.h"
#include "IDBStruct.h"


CDataProcSaveDB::CDataProcSaveDB()
{
	m_RequestMap.clear();
	m_MapAllData.clear();
}

CDataProcSaveDB::~CDataProcSaveDB()
{
	MAP_ALL_DATA::iterator it = m_MapAllData.begin();
	for (; it != m_MapAllData.end(); ++it)
	{
		MAP_SDB_DATA &MapSDBData = (*it).second;

		MAP_SDB_DATA::iterator MapIt = MapSDBData.begin();
		for (; MapIt != MapSDBData.end();)
		{
			CSaveDBData *pSDBData = (*MapIt).second;
			if (NULL != pSDBData)
			{
				delete pSDBData;
				MapIt = MapSDBData.begin();
			}
		}
		MapSDBData.clear();
	}
	m_MapAllData.clear();
}

//////////////////////////////////////////////////////////////////////////
////////////////////////////////// CDataProc /////////////////////////////
// ������
BOOL CDataProcSaveDB::Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
							  LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet, LPVOID dwServerID)
{
	//����Ѿ����ڸ�����, �򲻴���
	if (m_RequestMap.find(nIndex) != m_RequestMap.end())
	{
		//g_pTrace->TraceErrorLn("CDataProcSaveDB::Requestʧ��, �����ظ�, RequestID=%d!", nRequestID);
		return FALSE;
	}

	CSaveDBData *pSaveDBData = GetSaveDBData(nRequestID, qwUserID, pInData, nInDataLen, dwServerID);
	if (NULL == pSaveDBData)
	{
		// 		g_pTrace->TraceErrorLn("CDataProcSaveDB::Request, NULL == pSaveDBData, nRequestID: %d, qwUserID: %ld", 
		// 								nRequestID, qwUserID);
		return FALSE;
	}

	//����������ڴ���, �򲻴���
	if (TRUE == pSaveDBData->IsSaving())
	{
		// 		g_pTrace->TraceErrorLn("CDataProcSaveDB::Requestʧ��, nRequestID: %d, qwUserID: %ld���ڴ���...!", 
		// 								nRequestID, qwUserID);
		return FALSE;
	}

	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	switch (nRequestID)
	{
		// ��DB����
	case REQUESTID_INTERACT_LOAD:
		// ����ӻ�����ȡ����ʧ��, ������ݿ���ȡ
		if (FALSE == pSaveDBData->Load(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			if (FALSE == g_pDBEngine->Request(nIndex, nRequestID, qwUserID, pInData, nInDataLen, this))
			{
				g_pTrace->TraceErrorLn("CDataProcSaveDB::Requestʧ��, ����ʧ��, RequestID=%d!", nRequestID);
				return FALSE;
			}

			m_RequestMap[nIndex] = pRet;
			return TRUE;
		}
		break;

		// д����
	case REQUESTID_INTERACT_SAVE:
		if (FALSE == pSaveDBData->Save(nRequestID, pInData, nInDataLen, pOutData, nOutLen))
		{
			//g_pTrace->TraceErrorLn("CDataProcSaveDB::Requestʧ��, ����ʧ��, RequestID=%d!", nRequestID);
			return FALSE;
		}
		break;

	default:
		//g_pTrace->TraceErrorLn("CDataProcSaveDB::Requestʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	pRet->OnRet(nIndex, qwUserID, nRequestID, pInData, nInDataLen, DBRET_OK, pOutData, nOutLen);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
///////////////////////////////// IDBRetSink /////////////////////////////
// ���ݿ����󷵻ػص�����
// nReturn: �ο��������ݿ����󷵻�ֵ����
// pOutData: ������ݻ�����ָ��
// nOutLen: ������ݻ���������
void CDataProcSaveDB::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
							s32 nReturn, LPSTR pOutData, s32 nOutLen)

{
	// ���û���ҵ�������, �򲻴���
	map<s32, IDBProxyRetSink*>::iterator it = m_RequestMap.find(nIndex);
	if (it == m_RequestMap.end())
	{
		//g_pTrace->TraceErrorLn("CDataProcSaveDB::OnRetʧ��, û���ҵ�����, RequestID=%d!", nRequestID);
		return;
	}

	IDBProxyRetSink *pSink = m_RequestMap[nIndex];
	m_RequestMap.erase(nIndex);

	s32 nDataType = GetDataType(nRequestID, pInData, nInLen);
	CSaveDBData *pSDBData = FindDBData(nDataType, qwUserID);
	if (NULL == pSDBData)
	{
		//g_pTrace->TraceErrorLn("CDataProcSaveDB::OnRetʧ��, û���ҵ�����, UserID=%ld!", qwUserID);
		return;
	}

	//����DB��һ��
	if (REQUESTID_INTERACT_LOAD == nRequestID)
	{
		if (NULL != pOutData && sizeof(SInteractLoad_Get) == nOutLen &&
			NULL != pInData && sizeof(SInteractLoad_Set) == nInLen)
		{
			SInteractLoad_Get *pILoad_Get = (SInteractLoad_Get *) pOutData;
			if (1 == pILoad_Get->lReturn)
			{
				SInteractLoad_Set *pILoad_Set = (SInteractLoad_Set *) pInData;

				SInteractSave_Set ISave_Set;
				ISave_Set.lTypeID = pILoad_Set->lTypeID;
				ISave_Set.lServerID = pILoad_Set->lServerID;
				ISave_Set.lOwnerID = pILoad_Set->lOwnerID;
				memcpy(ISave_Set.DataBuffer, pILoad_Get->DataBuffer, sizeof(ISave_Set.DataBuffer));

				char pOutData_Temp[4096] = {0};
				s32 nOutLen_Temp = 4096;

				pSDBData->Save(REQUESTID_INTERACT_SAVE, (char *) &ISave_Set, sizeof(ISave_Set), pOutData_Temp, nOutLen_Temp);
			}
		}	
	}

	pSink->OnRet(nIndex, qwUserID, nRequestID, pInData, nInLen, nReturn, pOutData, nOutLen);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////// CDataProcSaveDB /////////////////////////////
// �������ݣ�nDataType�� MAKE_SDB_DATATYPE �Ķ���
CSaveDBData* CDataProcSaveDB::FindDBData(s32 nDataType, s32 nDataKey)
{
	MAP_ALL_DATA::iterator it = m_MapAllData.find(nDataType);
	if (it == m_MapAllData.end())
	{
		return NULL;
	}
	MAP_SDB_DATA &MapSDBData = (*it).second;

	MAP_SDB_DATA::iterator MapIt = MapSDBData.find(nDataKey);
	if (MapIt == MapSDBData.end())
	{
		return NULL;
	}

	return (*MapIt).second;
}

// ɾ�����ݣ�nDataType�� MAKE_SDB_DATATYPE �Ķ���
void CDataProcSaveDB::DelDBData(s32 nDataType, s32 nDataKey, CSaveDBData *pDBData)
{
	MAP_ALL_DATA::iterator it = m_MapAllData.find(nDataType);
	if (it == m_MapAllData.end())
	{
		return;
	}
	MAP_SDB_DATA &MapSDBData = (*it).second;

	MAP_SDB_DATA::iterator MapIt = MapSDBData.find(nDataKey);
	if (MapIt == MapSDBData.end())
	{
		return;
	}

	if (pDBData == (*MapIt).second)
	{
		MapSDBData.erase(MapIt);
	}
}

//�رշ����������ڴ��������ݵı���
void CDataProcSaveDB::CloseServer(LPVOID dwServerID)
{
	MAP_ALL_DATA::iterator it = m_MapAllData.begin();
	for (; it != m_MapAllData.end(); ++it)
	{
		MAP_SDB_DATA &MapSDBData = (*it).second;

		MAP_SDB_DATA::iterator MapIt = MapSDBData.begin();
		for (; MapIt != MapSDBData.end(); )
		{
			CSaveDBData *pSDBData = (*MapIt).second;
			if (NULL != pSDBData && pSDBData->GetServerID() == dwServerID)
			{
				pSDBData->CloseServer();
				MapIt = MapSDBData.begin();
			}
			else
			{
				++MapIt;
			}
		}
	}
}

//������������
int CDataProcSaveDB::GetDataType(s32 nRequestID, LPSTR pInData, s32 nInDataLen)
{
	int nDataTypeRet = -1;
	if (NULL == pInData)
	{
		//g_pTrace->TraceLn("CDataProcSaveDB::GetDataType, NULL == pInData, nRequestID: %d", nRequestID);
		return nDataTypeRet;
	}

	switch(nRequestID)
	{
	case REQUESTID_INTERACT_LOAD:
		{
			if (sizeof(SInteractLoad_Set) == nInDataLen)
			{
				SInteractLoad_Set *pILoad_Set = (SInteractLoad_Set *) pInData;
				nDataTypeRet = MAKE_SDB_DATATYPE(REQUESTID_INTERACT_LOAD, pILoad_Set->lTypeID, pILoad_Set->lServerID);
			}
		}
		break;

	case REQUESTID_INTERACT_SAVE:
		{
			if (sizeof(SInteractSave_Set) == nInDataLen)
			{
				SInteractSave_Set *pISave_Set = (SInteractSave_Set *) pInData;
				nDataTypeRet = MAKE_SDB_DATATYPE(REQUESTID_INTERACT_LOAD, pISave_Set->lTypeID, pISave_Set->lServerID);
			}
		}
		break;

	default:
		{
			//g_pTrace->TraceLn("CDataProcSaveDB::GetDataType, nRequestID: %d", nRequestID);
		}
		break;
	}

	return nDataTypeRet;
}

//��ȡ����
CSaveDBData* CDataProcSaveDB::GetSaveDBData(s32 nRequestID, s64 qwUserID, LPSTR pInData, s32 nInDataLen, LPVOID dwServerID)
{
	CSaveDBData *pSaveDBData = NULL;

	s32 nDataType = GetDataType(nRequestID, pInData, nInDataLen);
	if (nDataType <= 0)
	{
		return NULL;
	}

	// ������������в����ڸ�����, �����
	MAP_ALL_DATA::iterator it = m_MapAllData.find(nDataType);
	if (it == m_MapAllData.end())
	{
		pSaveDBData = new CSaveDBData(nDataType, qwUserID, dwServerID, this);
		if (NULL == pSaveDBData)
		{
			//g_pTrace->TraceErrorLn("CDataProcSaveDB::GetSaveDBData ʧ��, Newʧ��!");
			return NULL;
		}

		MAP_SDB_DATA MapSDBData;
		MapSDBData[qwUserID] = pSaveDBData;

		m_MapAllData[nDataType] = MapSDBData;
	}
	else
	{
		MAP_SDB_DATA &MapSDBData = (*it).second;

		MAP_SDB_DATA::iterator MapIt = MapSDBData.find(qwUserID);
		if (MapIt == MapSDBData.end())
		{
			pSaveDBData = new CSaveDBData(nDataType, qwUserID, dwServerID, this);
			if (NULL == pSaveDBData)
			{
				//g_pTrace->TraceErrorLn("CDataProcSaveDB::GetSaveDBData ʧ��, Newʧ�� 2!");
				return NULL;
			}
			MapSDBData[qwUserID] = pSaveDBData;
		}
		else
		{
			pSaveDBData = (*MapIt).second;
		}
	}

	return pSaveDBData;
}



