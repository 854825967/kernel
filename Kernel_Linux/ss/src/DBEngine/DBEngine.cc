#include "Header.h"
#include "DBEngine.h"
#include "stdarg.h"
#include "base/auto_mutex.h"

#include <time.h>

using namespace core;

// �첽����������������־
#define ASYNLIST_CONFIG_NUM_FLAG		"totalnum ="

// �첽�������ñ�־
#define ASYNOBJECTLIST_CONFIT_FLAG		"asynobject list"

// ���ݿ���������
#define DRIVERTYPE_CONFIT_FLAG			"dbdrivertype ="

// ���ݿ�����������ñ�־
#define SERVERNAME_CONFIG_FLAG			"servername ="
// ���ݿ�������˿����ñ�־
#define SERVERPORT_CONFIG_FLAG                  "serverport ="
// ���ݿ������ñ�־
#define DBNAME_CONFIG_FLAG			"dbname ="
// �û������ñ�־
#define USERNAME_CONFIG_FLAG			"username ="
// �������ñ�־
#define PASSWORD_CONFIG_FLAG			"password ="
// �첽�����������ñ�־
#define ASYNLIST_TYPE_CONFIG_FLAG		"type ="
// �첽���и������ñ�־
#define ASYNLIST_NUM_CONFIG_FLAG		"num ="
// ������Ҫ�����ñ�־
#define RETRY_WEIGHTNESS_CONFIG_FLAG		"retry strategy weightness ="
// ���Լ�����ñ�־
#define RETRY_INTERVAL_CONFIG_FLAG		"retry strategy internal ="
// ���Դ������ñ�־
#define RETRY_NUMBER_CONFIG_FLAG		"retry strategy number ="
// ���Զ�����󳤶�
#define RETRY_MAXSIZE_CONFIG_FLAG		"retry max size ="
// �����װ��Ķ��д�С���ñ�־
#define REDUCE_SIZE_CONFIG_FLAG			"reduce strategy size ="
// �װ���Ҫ�����ñ�־
#define REDUCE_WEIGHTNESS_CONFIG_FLAG		"reduce strategy weightness ="
// ��������Ķ��д�С���ñ�־
#define CACHE_SIZE_CONFIG_FLAG			"cache strategy size ="

// ȫ��ͨ�����ݿ��������ָ��
CDBEngine	*g_pDBEngine = NULL;

// ���캯��
CDBEngine::CDBEngine()
{
	m_AsynObjectListList.clear();

	m_pWarningSink = NULL;
	m_ReturnList.clear();
	m_ReturnList2.clear();
	m_pCurReturnList = &m_ReturnList;
	m_pCurReturnList2 = &m_ReturnList2;

	memset(m_szKey, 0, sizeof(m_szKey));
}

// ��������
CDBEngine::~CDBEngine()
{
	// �����첽����
	CloseAsynObjectList();

	// ��ӡ����������
	PerformanceTest(0, PT_PRINTLOG, 0);

	// �ر����ݿ���������
	g_RequestConfig.Close();

	g_pDBEngine = NULL;

	m_pWarningSink = NULL;

	list<CAsynObject>::iterator	it = m_ReturnList.begin();
	for (; it != m_ReturnList.end(); ++ it)
	{
		CAsynObject	*pReturnObject = &(*it);
		pReturnObject->Close();
	}

	it = m_ReturnList2.begin();
	for (; it != m_ReturnList2.end(); ++ it)
	{
		CAsynObject	*pReturnObject = &(*it);
		pReturnObject->Close();
	}

	m_ReturnList.clear();
	m_ReturnList2.clear();
	m_pCurReturnList = &m_ReturnList;
	m_pCurReturnList2 = &m_ReturnList2;
}

// ����ͨ�����ݿ�����
BOOL CDBEngine::Create(IDBWarningSink *pWarningSink, LPSTR szKey, LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	if (NULL == szKey || strlen(szKey) <= 0)
	{
		return FALSE;
	}

	mcopyptr(m_szKey, szKey, sizeof(m_szKey));
  this->m_log_file_ = log_file;

	// �������ݿ���������
	s32	nErrLine = 0;
	if (FALSE == g_RequestConfig.Create(szDBRequestScp, nErrLine, m_szKey))
	{
		GPrintInfoLog("DBRequest.res ��%d�м��س���!", nErrLine);
		return FALSE;
	}

	// �����쳣�����ӿ�ָ��
	m_pWarningSink = pWarningSink;

	// �����첽����
	nErrLine = 0;
	if (FALSE == CreateAsynObjectList(m_szKey, nErrLine, szDBEngineScp))
	{
		GPrintInfoLog("DBEngine.res ��%d�м��س���!", nErrLine);
		return FALSE;
	}

	return TRUE;
}

// ����ͨ�����ݿ�����
void CDBEngine::Release(void)
{
	delete this;
}

void CDBEngine::OnReturn(void)
{
	{
		AutoMutex auto_mutex(&m_ReturnLock);
		list<CAsynObject> *pSwapReturnList = m_pCurReturnList;
		m_pCurReturnList = m_pCurReturnList2;
		m_pCurReturnList2 = pSwapReturnList;
	}

	list<CAsynObject>::iterator	it = m_pCurReturnList->begin();
	for (; it != m_pCurReturnList->end(); ++ it)
	{
		CAsynObject	*pReturnObject = &(*it);

		static s32 sRequestID = 0;
		static s32 sUserID = 0;

		sRequestID = pReturnObject->GetRequestID();
		sUserID = pReturnObject->GetUserID();

		try
		{
			// ��������
			PerformanceTest((u32)sRequestID, PT_ONRETCASTSTART, 0);

			pReturnObject->OnRet();

			// ��������
			PerformanceTest((u32)sRequestID, PT_ONRETCASTEND, 0);
		}
		catch (...)
		{
			char szMsg[256] = {0};
			sprintf(szMsg, "���󷵻طǷ�, ����ID = %d, �û�ID = %d", sRequestID, sUserID);
			PrintInfoLog(szMsg);
		}

		pReturnObject->Close();
	}
	m_pCurReturnList->clear();
}

// �������ݿ�
BOOL CDBEngine::Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
						LPSTR pInData, s32 nInDataLen, IDBRetSink *pRet)
{
	REQUESTCONFIG *pRequestConfig = g_RequestConfig.FindRequestConfig(nRequestID);
	if (NULL == pRequestConfig)
	{
		PrintInfoLog("����ID = %d������",nRequestID);
		return FALSE;
	}

	CAsynObjectList	*pAsynObjectList[32] = {0};
	s32	nAsynObjectLisgNum = 0;

	// ��������������ƥ��������첽����
	list<CAsynObjectList*>::iterator it = m_AsynObjectListList.begin();
	for (; it != m_AsynObjectListList.end(); ++ it)
	{
		pAsynObjectList[nAsynObjectLisgNum] = (*it);
		if (pRequestConfig->nDBType == pAsynObjectList[nAsynObjectLisgNum]->GetRequestType())
		{
			nAsynObjectLisgNum ++;
			if (nAsynObjectLisgNum >= 32)
			{
				break;
			}
		}
	}

	// û���ҵ�����ƥ����첽������ʧ��
	if (nAsynObjectLisgNum <= 0)
	{
		return FALSE;
	}

	// ���û�IDȡģ�Ա㸺��ƽ��, ͬʱ��֤ͬһ���û������а�����ͬ�첽������
	u64			uiUserID = qwUserID;
	s32			nRequestAsynList = uiUserID % nAsynObjectLisgNum;
	CAsynObject	AsynObject;

	// �����첽������ӵ���Ӧ���첽������
	if (FALSE == AsynObject.Create(nIndex, nRequestID, qwUserID, pInData, nInDataLen,
		pAsynObjectList[nRequestAsynList]->GetDBADO(), pRet))
	{
		return FALSE;
	}

	pAsynObjectList[nRequestAsynList]->AddRequestObject(AsynObject);

	// ��������
	PerformanceTest((DWORD)nRequestID, PT_REQUEST, 0);

	return TRUE;
}

// ��ȡĳ���������͵��첽����״̬��Ϣ
BOOL CDBEngine::GetAsynListState(s32 nRequestType, s32 &nNum,
								 ASYNLISTSTATE *pStateBuf, s32 nBufLen)
{
	if (NULL == pStateBuf || nBufLen <= 0)
	{
		return FALSE;
	}

	nNum = 0;
	list<CAsynObjectList*>::iterator it = m_AsynObjectListList.begin();
	for (; it != m_AsynObjectListList.end(); ++ it)
	{
		CAsynObjectList	*pAsynObjectList = (*it);
		if (nRequestType == pAsynObjectList->GetRequestType() || -1 == nRequestType)
		{
			ASYNLISTSTATE	AsynListState;
			AsynListState.nRequestType = pAsynObjectList->GetRequestType();
			AsynListState.nRequestObjectNum = pAsynObjectList->GetRequestObjNum();
			AsynListState.nRetryObjectNum = pAsynObjectList->GetRetryObjNum();
			if (nBufLen - (nNum + 1) * sizeof(ASYNLISTSTATE) >= 0)
			{
				pStateBuf[nNum++] = AsynListState;
			}
		}
	}

	return TRUE;
}

// ����������Ϣ��֤��
#define ASSERT_ALUPDATE(r)	{ if (!(r)) { return FALSE; } }
/*
// ��̬����������Ϣ(Ŀ�����ݿ���첽���и��ֲ���)
BOOL CDBEngine::UpdateConfig(void)
{
	CDBMemTextFile	FileObj;
	if (FALSE == FileObj.Open(DBENGINE_CONFIG_FILE))
	{
		return FALSE;
	}

	char	szBuf[MAX_LINE_NUMBER] = {0};
	s32		nTotalNum = 0;
	s32		nCurNum = 0;
	s32		nErrLine = 0;

	list<ASYNLISTINFO>	AsynListInfoList;
	ASYNLISTINFO		AsynListInfo;
	s32					nID = 0;
	s32					nNum = 0;

	// "totalnum ="
	ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_CONFIG_NUM_FLAG, nErrLine, szBuf));

	// ��ȡ�첽�������õ�������
	s32	nInputNum = sscanf(szBuf + strlen(ASYNLIST_CONFIG_NUM_FLAG), "%d", &nTotalNum);
	ASSERT_ALUPDATE(1 == nInputNum && nTotalNum > 0);

	// ��ȡ�첽����������Ϣ
	while (FALSE == FileObj.IsEnd())
	{
		// "asynobject list"
		if (FALSE == FindStrInFile(&FileObj, ASYNOBJECTLIST_CONFIT_FLAG, nErrLine, szBuf))
		{
			break;
		}

		// "{"
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));
		// ��ȡ���ݿ��������
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, SERVERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(SERVERNAME_CONFIG_FLAG), "%s", AsynListInfo.szServerName);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szServerName) > 0);
		// ��ȡ���ݿ���
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, DBNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DBNAME_CONFIG_FLAG), "%s", AsynListInfo.szDBName);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szDBName) > 0);
		// ��ȡ�û���
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, USERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(USERNAME_CONFIG_FLAG), "%s", AsynListInfo.szUserName);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szUserName) > 0);
		// ��ȡ����
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, PASSWORD_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(PASSWORD_CONFIG_FLAG), "%s", AsynListInfo.szPassword);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szPassword) > 0);
		// ��ȡ�첽��������
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_TYPE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_TYPE_CONFIG_FLAG), "%d", &AsynListInfo.nType);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nType > 0);
		// ��ȡ�첽���и���
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_NUM_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_NUM_CONFIG_FLAG), "%d", &nNum);
		ASSERT_ALUPDATE(1 == nInputNum && nNum > 0);
		// ��ȡ������Ҫ��
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nRetryWeightness);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nRetryWeightness < REQUEST_WEIGHTNESS_MAX);
		// ��ȡ���Լ��
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_INTERVAL_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_INTERVAL_CONFIG_FLAG), "%d", &AsynListInfo.nRetryInternal);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryInternal >= 0);
		// ��ȡ���Դ���
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_NUMBER_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_NUMBER_CONFIG_FLAG), "%d", &AsynListInfo.nRetryNumber);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryNumber > 0);
		// ��ȡ���Զ�����󳤶�
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_MAXSIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_MAXSIZE_CONFIG_FLAG), "%d", &AsynListInfo.nRetryMaxSize);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryMaxSize >= 100);
		// ��ȡ�����װ��Ķ��д�С
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, REDUCE_SIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_SIZE_CONFIG_FLAG), "%d", &AsynListInfo.nReduceSize);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nReduceSize >= 100);
		// ��ȡ�װ���Ҫ��
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, REDUCE_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nReduceWeightness);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nReduceWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nReduceWeightness < REQUEST_WEIGHTNESS_MAX);
		// ��ȡ��������Ķ��д�С
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, CACHE_SIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(CACHE_SIZE_CONFIG_FLAG), "%d", &AsynListInfo.nCacheSize);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nCacheSize >= 100);
		// "}"
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, "}", nErrLine, szBuf));

		for (s32 i = 0; i < nNum; i ++)
		{
			AsynListInfoList.push_back(AsynListInfo);
		}

		nCurNum ++;
	}

	ASSERT_ALUPDATE(nCurNum == nTotalNum);

	// ��֤������Ҫ�����첽���и�������
	ASSERT_ALUPDATE(AsynListInfoList.size() == m_AsynObjectListList.size());
	// ��֤������Ҫ�����첽�������Ͳ���
	list<ASYNLISTINFO>::iterator		itInfo = AsynListInfoList.begin();
	list<CAsynObjectList*>::iterator	itList = m_AsynObjectListList.begin();
	for (; itInfo != AsynListInfoList.end(); ++ itInfo)
	{
		ASYNLISTINFO	*pInfo = &(*itInfo);
		CAsynObjectList	*pList = (*itList);
		ASSERT_ALUPDATE(pInfo->nType == pList->GetRequestType());
		++ itList;
	}

	// ��ʽ��ʼ��������
	itInfo = AsynListInfoList.begin();
	itList = m_AsynObjectListList.begin();
	for (; itInfo != AsynListInfoList.end(); ++ itInfo)
	{
		ASYNLISTINFO	*pInfo = &(*itInfo);
		CAsynObjectList	*pList = (*itList);
		ASSERT_ALUPDATE(pList->UpdateConfig(*pInfo));
		++ itList;
	}

	return TRUE;
}
*/
// ���һ��Ҫ�ص��Ķ���
void CDBEngine::AddReturnObject(CAsynObject &ReturnObject)
{
	AutoMutex auto_mutex(&m_ReturnLock);
	m_pCurReturnList2->push_back(ReturnObject);
	//TODO by zipher ֪ͨ�߼��߳�
	//SetEvent(m_hReturnEvent);
}

// �쳣��������
void CDBEngine::OnWarning(s32 nReturn, LPSTR szDesc)
{
	if (NULL == m_pWarningSink)
	{
		return;
	}

	AutoMutex auto_mutex(&m_WarningLock);
	m_pWarningSink->OnWarning(nReturn, szDesc);
}

// �����Ϣ��־
void CDBEngine::PrintInfoLog(LPCSTR lpszFormat, ...)
{
	AutoMutex auto_mutex(&m_LogLock);

	va_list	args;
	va_start(args, lpszFormat);

	char szBuffer[10240] = {0};
	vsnprintf(szBuffer, sizeof(szBuffer) - 1, lpszFormat, args);

	time_t now;
	time(&now);
	tm when = *localtime(&now);
	char szCurTime[32] = {0};
	strftime(szCurTime, sizeof(szCurTime), "%Y-%m-%d %H:%M:%S", &when);

	FILE *fp = fopen(this->m_log_file_.c_str(), "a");
	if (fp != NULL)
	{
		fprintf(fp, "[%s][%u]: %s\n", szCurTime, GetTickCount(), szBuffer);
		fclose(fp);
	}

	va_end(args);
}

// �������⺯��
inline void CDBEngine::PerformanceTest(u32 key, s32 flag, s64 value)
{
#ifdef PERFORMANCE_TEST	// ��������
	AutoMutex auto_mutex(&m_TestLock);

  timespec ts;
	static s64 sCpuFreq = 0;
	if (sCpuFreq == 0)
	{
		//::QueryPerformanceFrequency((LARGE_INTEGER *)&sCpuFreq);
	}

	map<u32, DBENGINEPTINFO>::iterator it = m_dbTest.find(key);

	switch(flag)
	{
		// ����
	case PT_REQUEST:
		if (it != m_dbTest.end())
		{
			DBENGINEPTINFO &dbTest = (*it).second;
			dbTest.dwRequestNum ++;
		}
		else
		{
			DBENGINEPTINFO dbTest;
			dbTest.dwRequestNum ++;
			m_dbTest[key] = dbTest;
		}

		break;

		// �����ʱ
	case PT_REQUESTCAST:
		if (it != m_dbTest.end())
		{
			DBENGINEPTINFO &dbTest = (*it).second;
			dbTest.requestTime += value;
		}
		else
		{
			DBENGINEPTINFO dbTest;
			dbTest.requestTime += value;
			m_dbTest[key] = dbTest;
		}

		break;

		// �ص���ʱ��ʼ
	case PT_ONRETCASTSTART:
		if (it != m_dbTest.end())
		{
			DBENGINEPTINFO &dbTest = (*it).second;
			if (dbTest.callTempTime == 0)
			{
        clock_gettime(CLOCK_MONOTONIC, &ts);
        dbTest.callTempTime = (uint64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
				//::QueryPerformanceCounter((LARGE_INTEGER *)&dbTest.callTempTime);
			}
			else
			{
				PrintInfoLog("���ݿ�������������ƿ�ʼʱ����, RequestID=%d!", key);
				break;
			}
		}
		else
		{
			DBENGINEPTINFO dbTest;
      clock_gettime(CLOCK_MONOTONIC, &ts);
      dbTest.callTempTime = (uint64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
			//::QueryPerformanceCounter((LARGE_INTEGER *)&dbTest.callTempTime);
			m_dbTest[key] = dbTest;
		}

		break;

		// �ص���ʱ����
	case PT_ONRETCASTEND:
		if (it != m_dbTest.end())
		{
			DBENGINEPTINFO &dbTest = (*it).second;
			dbTest.dwCallNum ++;

			if (dbTest.callTempTime > 0)
			{
				s64 endCounter = 0;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        endCounter = (uint64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
				//::QueryPerformanceCounter((LARGE_INTEGER *)&endCounter);
				dbTest.callTime += (endCounter - dbTest.callTempTime);
				dbTest.callTempTime = 0;
			}
			else
			{
				PrintInfoLog("���ݿ�������������ƽ���ʱ����, RequestID=%d!", key);
				break;
			}
		}
		else
		{
			PrintInfoLog("���ݿ�������������ƽ���ʱ����, RequestID=%d!", key);
			break;
		}

		break;

		// ��ӡͳ�ƽ��
	case PT_PRINTLOG:
		PrintInfoLog("---------------���ݿ�����������������ʼ---------------");
		for (it = m_dbTest.begin(); it != m_dbTest.end(); ++it)
		{
			u32 dwKey = (*it).first;
			DBENGINEPTINFO &dbTest = (*it).second;
			s32 requestCostUS = 0;
			s32 onretCostUS = 0;
			if (dbTest.dwRequestNum > 0 && sCpuFreq > 0)
			{
				requestCostUS = dbTest.requestTime * 1000000 / sCpuFreq / dbTest.dwRequestNum;
			}
			if (dbTest.dwCallNum > 0 && sCpuFreq > 0)
			{
				onretCostUS = dbTest.callTime * 1000000 / sCpuFreq / dbTest.dwCallNum;
			}
			PrintInfoLog("����ID=%d, ����%d��, ����ƽ����ʱ%dus, �ص�%d��, �ص�ƽ����ʱ%dus!",
				dwKey, dbTest.dwRequestNum, requestCostUS, dbTest.dwCallNum, onretCostUS);
		}

		PrintInfoLog("---------------���ݿ�������������������---------------");
		break;

	default:
		break;
	}
#endif
}

// �����첽���д�����֤��
#define ASSERT_ALCREATE(r)	{ if (!(r)) { return FALSE; } }

// �����첽����
BOOL CDBEngine::CreateAsynObjectList(LPSTR szKey, s32 &nErrLine, LPCSTR szDBEngineScp)
{
	CDBMemTextFile	FileObj;

	if (FALSE == FileObj.Open(szDBEngineScp))
	{
		PrintInfoLog("���ؽű� = %s ����,�ļ�������", szDBEngineScp);
		return FALSE;
	}

	char	szBuf[MAX_LINE_NUMBER] = {0};
	s32		nTotalNum = 0;
	s32		nCurNum = 0;

	ASYNLISTINFO	AsynListInfo;
	s32				nID = 0;
	s32				nNum = 0;

	// "totalnum ="
	ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_CONFIG_NUM_FLAG, nErrLine, szBuf));

	// ��ȡ�첽�������õ�������
	s32	nInputNum = sscanf(szBuf + strlen(ASYNLIST_CONFIG_NUM_FLAG), "%d", &nTotalNum);
	ASSERT_ALCREATE(1 == nInputNum && nTotalNum > 0);

	// ��ȡ�첽����������Ϣ
	while (FALSE == FileObj.IsEnd())
	{
		// "asynobject list"
		if (FALSE == FindStrInFile(&FileObj, ASYNOBJECTLIST_CONFIT_FLAG, nErrLine, szBuf))
		{
			break;
		}

		// "{"
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));

		// ��ȡ���ݿ���������
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DRIVERTYPE_CONFIT_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DRIVERTYPE_CONFIT_FLAG), "%d", &AsynListInfo.nDriverType);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nDriverType > 0); 

		// ��ȡ���ݿ��������
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, SERVERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(SERVERNAME_CONFIG_FLAG), "%s", AsynListInfo.szServerName);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szServerName) > 0);
		// ��ȡ���ݿ�������˿�
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, SERVERPORT_CONFIG_FLAG, nErrLine, szBuf));
                nInputNum = sscanf(szBuf + strlen(SERVERPORT_CONFIG_FLAG), "%d", &AsynListInfo.nServerPort);
                ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nServerPort > 0);
		// ��ȡ���ݿ���
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DBNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DBNAME_CONFIG_FLAG), "%s", AsynListInfo.szDBName);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szDBName) > 0);
		// ��ȡ�û���
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, USERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(USERNAME_CONFIG_FLAG), "%s", AsynListInfo.szUserName);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szUserName) > 0);
		// ��ȡ����
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, PASSWORD_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(PASSWORD_CONFIG_FLAG), "%s", AsynListInfo.szPassword);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szPassword) > 0);
		// ��ȡ�첽��������
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_TYPE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_TYPE_CONFIG_FLAG), "%d", &AsynListInfo.nType);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nType > 0);
		// ��ȡ�첽���и���
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_NUM_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_NUM_CONFIG_FLAG), "%d", &nNum);
		ASSERT_ALCREATE(1 == nInputNum && nNum > 0);
		// ��ȡ������Ҫ��
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nRetryWeightness);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nRetryWeightness < REQUEST_WEIGHTNESS_MAX);
		// ��ȡ���Լ��
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_INTERVAL_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_INTERVAL_CONFIG_FLAG), "%d", &AsynListInfo.nRetryInternal);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryInternal >= 0);
		// ��ȡ���Դ���
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_NUMBER_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_NUMBER_CONFIG_FLAG), "%d", &AsynListInfo.nRetryNumber);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryNumber > 0);
		// ��ȡ���Զ�����󳤶�
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_MAXSIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_MAXSIZE_CONFIG_FLAG), "%d", &AsynListInfo.nRetryMaxSize);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryMaxSize >= 100);
		// ��ȡ�����װ��Ķ��д�С
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, REDUCE_SIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_SIZE_CONFIG_FLAG), "%d", &AsynListInfo.nReduceSize);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nReduceSize >= 100);
		// ��ȡ�װ���Ҫ��
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, REDUCE_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nReduceWeightness);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nReduceWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nReduceWeightness < REQUEST_WEIGHTNESS_MAX);
		// ��ȡ��������Ķ��д�С
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, CACHE_SIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(CACHE_SIZE_CONFIG_FLAG), "%d", &AsynListInfo.nCacheSize);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nCacheSize >= 100);
		// "}"
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, "}", nErrLine, szBuf));

		for (s32 i = 0; i < nNum; i ++)
		{
			CAsynObjectList	*pAsynObjectList = new CAsynObjectList;
			ASSERT_ALCREATE(pAsynObjectList != NULL);
			ASSERT_ALCREATE(pAsynObjectList->Create(nID ++, AsynListInfo));
			m_AsynObjectListList.push_back(pAsynObjectList);
		}

		nCurNum ++;
	}

	ASSERT_ALCREATE(nCurNum == nTotalNum);

	return TRUE;
}

// �����첽����
void CDBEngine::CloseAsynObjectList(void)
{
	list<CAsynObjectList*>::iterator	itAsynObjectList = m_AsynObjectListList.begin();
	for (; itAsynObjectList != m_AsynObjectListList.end(); ++ itAsynObjectList)
	{
		CAsynObjectList	*pAsynObjectList = (*itAsynObjectList);
		pAsynObjectList->Close();
		delete pAsynObjectList;
	}

	m_AsynObjectListList.clear();
}

// �����ַ�������Ŀո��tab��
LPSTR CDBEngine::TrimL(LPSTR szStr)
{
	char	*szTemp = szStr;
	while (*szTemp == ' ' || *szTemp == 9)
	{
		szTemp ++;
	}

	memmove(szStr, szTemp, strlen(szTemp)+1);
	return szStr;
}

// �����ļ�����ĳ���ַ�����ʼ����
BOOL CDBEngine::FindStrInFile(CDBMemTextFile *pFileObj, LPCSTR szStr, s32 &nCurLine, LPSTR szBuf)
{
	if (NULL == pFileObj || NULL == szStr || NULL == szBuf)
	{
		PrintInfoLog("���ؽű�����:  nCurLine = %d",nCurLine);
		return FALSE;
	}

	while (FALSE == pFileObj->IsEnd())
	{
		memset(szBuf, 0, sizeof(szBuf));
		pFileObj->GetLine(szBuf, MAX_LINE_NUMBER);
		TrimL(szBuf);
		nCurLine ++;
		if (0 == memcmp(szBuf, szStr, strlen(szStr)))
		{
			return TRUE;
		}
	}

	return FALSE;
}

// ����ͨ�����ݿ�����(�������)
extern "C" BOOL CreateDBEngine(IDBEngine **ppDBEngine, IDBWarningSink *pWarningSink,
	LPSTR szKey, LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	CDBEngine *pNewDBEngine = new CDBEngine;
	if (NULL == pNewDBEngine)
	{
		GPrintInfoLog("�����ݿ���������ڴ�ʧ��!");
		return FALSE;
	}

	g_pDBEngine = pNewDBEngine; // ��仰��ǰ�������Ϊ�����Create�õ����ָ����

	if (FALSE == pNewDBEngine->Create(pWarningSink, szKey, szDBEngineScp, szDBRequestScp, log_file))
	{
		delete pNewDBEngine;
		pNewDBEngine = NULL;
		g_pDBEngine = NULL;
		GPrintInfoLog("���ݿ����洴��ʧ��!");
		return FALSE;
	}

	*ppDBEngine = static_cast<IDBEngine *>(pNewDBEngine);

	return TRUE;
}
