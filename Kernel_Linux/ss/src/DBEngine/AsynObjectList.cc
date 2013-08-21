#include "Header.h"
#include "AsynObjectList.h"
#include "base/auto_mutex.h"
#include "util/Util.h"

#ifdef PERFORMANCE_TEST
u64 CAsynObjectList::count = 0;
#endif

// ���캯��
CAsynObjectList::CAsynObjectList()
{
	memset(&m_AsynListInfo, 0, sizeof(m_AsynListInfo));
	m_nID = -1;
	m_dwThread = -1;

	m_RequestList.clear();
	m_nRequestListSize = 0;

	m_RetryList.clear();
	m_nRetryListSize = 0;
	m_RetryRegHash.clear();
	m_nNoRetryNum = 0;
	m_nCurObjRetryNum = 0;

	m_pThread = NULL;
}

// ��������
CAsynObjectList::~CAsynObjectList()
{
}

// �����첽�������
BOOL CAsynObjectList::Create(int nID, ASYNLISTINFO &AsynListInfo)
{
	if( NULL != m_pThread )
	{
		return FALSE;
	}

	m_AsynListInfo = AsynListInfo;

	// ����CDBADO����
	if (FALSE == m_DBADO.Create())
	{
		return FALSE;
	}

	// ���������첽����ָ��
	m_DBADO.SetAsynObjectList(this);

	// �������ݿ�
	if (FALSE == m_DBADO.Connect(m_AsynListInfo.szServerName,
		m_AsynListInfo.nServerPort,
		m_AsynListInfo.szDBName,
		m_AsynListInfo.szUserName,
		m_AsynListInfo.szPassword))
	{
		return FALSE;
	}

	m_nID = nID;

	// �������߳���ִ���첽������е�������
	m_pThread = new LoopThread((BaseLoop*)this, "AsynObjectList", true);
	if (NULL == m_pThread)
	{
		return FALSE;
	}
	m_pThread->StartLoop();

	return TRUE;
}

// �ͷ��첽�������
void CAsynObjectList::Close(void)
{
	// �����߳�
	if (m_pThread != NULL)
	{
		m_pThread->StopLoop();
		delete m_pThread;
		m_pThread = NULL;
	}

	// �ر����ݿ�
	m_DBADO.Close();

	memset(&m_AsynListInfo, 0, sizeof(m_AsynListInfo));
	m_nID = -1;
	m_RequestList.clear();
	m_nRequestListSize = 0;
	m_RetryList.clear();
	m_nRetryListSize = 0;
	m_RetryRegHash.clear();
	m_nNoRetryNum = 0;
	m_nCurObjRetryNum = 0;
}

// ����������
void CAsynObjectList::Process(void)
{
	list<CAsynObject>::iterator		itRequest;
	list<CAsynObject>::iterator		itRetry;

	CAsynObject		AsynObject;
	CAsynObject		*pAsynObject = NULL;

	// �����������ݰ�
	int	nCount = m_nRequestListSize;
	for (int i = 0; i < nCount; i ++)
	{
		pAsynObject = NULL;

		{
#ifdef PERFORMANCE_TEST
      timespec ts;
      u64 startCounter = 0;
      clock_gettime(CLOCK_MONOTONIC, &ts);
      startCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
#endif
			AutoMutex auto_mutex(&m_RequestLock);
#ifdef PERFORMANCE_TEST
      clock_gettime(CLOCK_MONOTONIC, &ts);
      u64 endCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
      count += endCounter - startCounter;
      if(endCounter - startCounter > 20) {
        g_pDBEngine->PrintInfoLog("[MUTEX_TEST] Position1 cost [%lu] ns", endCounter - startCounter);
      }
      if((count & 2000) == 2000) {
        g_pDBEngine->PrintInfoLog("[MUTEX_TEST] total count [%lu] ns", count);
      }
#endif
			itRequest = m_RequestList.begin();
			if (itRequest != m_RequestList.end())
			{
				AsynObject = (*itRequest);
				pAsynObject = &AsynObject;
				m_RequestList.pop_front();
				m_nRequestListSize --;
			}
		}

		if (pAsynObject != NULL)
		{
			// ������첽������صĶ����Ѿ������Զ�������Ҫ�ŵ����Զ�����
			if (m_RetryRegHash.find(pAsynObject->GetUserID()) != m_RetryRegHash.end())
			{
				m_RetryList.push_back(AsynObject);
				m_nRetryListSize ++;
				RegisterRetry(pAsynObject->GetUserID());
				continue;
			}
#ifdef PERFORMANCE_TEST
      timespec ts;
			// �����ʱͳ��
			s64 startCounter = 0;
      clock_gettime(CLOCK_MONOTONIC, &ts);
      startCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
			//::QueryPerformanceCounter((LARGE_INTEGER *)&startCounter);
#endif

			s32 nRet = pAsynObject->OnRequest();

#ifdef PERFORMANCE_TEST
			// �����ʱͳ��
			s64 endCounter = 0;
			//::QueryPerformanceCounter((LARGE_INTEGER *)&endCounter);
      clock_gettime(CLOCK_MONOTONIC, &ts);
      endCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
			g_pDBEngine->PerformanceTest(pAsynObject->GetRequestID(), PT_REQUESTCAST,
				endCounter - startCounter);
#endif

			switch(nRet)
			{
				// ���سɹ�, ���첽����ŵ��������ķ��ض�����
			case DBRET_OK:
				g_pDBEngine->AddReturnObject(AsynObject);
				break;

				// ���ر�����, ������Ҫ��Ҫ���첽����ŵ����Զ���
			case DBRET_ERROR_LOCK:
				// �����Ҫ�ȴﵽ������Ҫ����Ҫ�ŵ����Զ���
				if (AsynObject.GetWeightness() >= m_AsynListInfo.nRetryWeightness)
				{
					m_RetryList.push_back(AsynObject);
					m_nRetryListSize ++;
					// ע��ö��������Զ��е���Ϣ
					RegisterRetry(AsynObject.GetUserID());
				}
				// �װ�
				else
				{
					g_pDBEngine->AddReturnObject(AsynObject);
					// ��¼�װ���־
					ReduceLog(AsynObject, "������������Ҫ�ȵ���������Ҫ��");
				}

				break;

				// ���淵��δ֪����, ���첽����ŵ��������ķ��ض�����, ����¼�װ���־
			case DBRET_ERROR_UNKNOWN:
				g_pDBEngine->AddReturnObject(AsynObject);
				// ��¼�װ���־
				ReduceLog(AsynObject, "����δ֪����");
				break;

				// ���ݿⷵ���߼�����, ���첽����ŵ��������ķ��ض�����
			default:
				g_pDBEngine->AddReturnObject(AsynObject);
				break;
			}
		}
	}

	// ���δ�������Զ��м����ﵽ���Լ����, �ʹ���һ�����Զ����е����ݰ�
	if (m_nNoRetryNum >= m_AsynListInfo.nRetryInternal)
	{
		// ����δ�������Զ��м���
		m_nNoRetryNum = 0;

		nCount = m_nRetryListSize;
		for (s32 j = 0; j < nCount; j ++)
		{
			pAsynObject = NULL;

			itRetry = m_RetryList.begin();
			if (itRetry != m_RetryList.end())
			{
				AsynObject = (*itRetry);
				pAsynObject = &AsynObject;
				m_RetryList.pop_front();
				m_nRetryListSize --;
			}

			if (pAsynObject != NULL)
			{
				switch(pAsynObject->OnRequest())
				{
					// ���سɹ�, ���첽����ŵ��������ķ��ض�����
				case DBRET_OK:
					g_pDBEngine->AddReturnObject(AsynObject);
					// ���õ�ǰ���������Դ���
					m_nCurObjRetryNum = 0;
					// ע���ö��������Զ����е���Ϣ
					DeregisterRetry(AsynObject.GetUserID());
					break;

					// ���ر�����, ���ݵ�ǰ�������Դ������������·Ż����Զ���ͷ�������׵�
				case DBRET_ERROR_LOCK:
					// �ۼƵ�ǰ���������Դ���
					m_nCurObjRetryNum ++;
					// ��ǰ���������Դ����ﵽ���õ����Դ���, ���׵���ǰ����
					if (m_nCurObjRetryNum >= m_AsynListInfo.nRetryNumber)
					{
						g_pDBEngine->AddReturnObject(AsynObject);
						// ���õ�ǰ���������Դ���
						m_nCurObjRetryNum = 0;
						// ע���ö������Ϣ
						DeregisterRetry(AsynObject.GetUserID());
						// ��¼�װ���־
						ReduceLog(AsynObject, "���Դ�������");
					}
					// ���Զ��дﵽ��󳤶�, ���׵���ǰ����
					else if (m_nRetryListSize >= m_AsynListInfo.nRetryMaxSize)
					{
						g_pDBEngine->AddReturnObject(AsynObject);
						// ���õ�ǰ���������Դ���
						m_nCurObjRetryNum = 0;
						// ע���ö������Ϣ
						DeregisterRetry(AsynObject.GetUserID());
						// ��¼�װ���־
						ReduceLog(AsynObject, "���Զ��дﵽ��󳤶�");
						// �쳣����
						OnWarning(DBWARN_RETRY_MAXSIZE);
					}
					// ��ǰ���������Դ���С�����õ����Դ���, �����·Ż����Զ���ͷ��
					else
					{
						m_RetryList.push_front(AsynObject);
						m_nRetryListSize ++;
						return;
					}

					break;

					// ���淵��δ֪����, ���첽����ŵ��������ķ��ض�����
				case DBRET_ERROR_UNKNOWN:
					g_pDBEngine->AddReturnObject(AsynObject);
					// ���õ�ǰ���������Դ���
					m_nCurObjRetryNum = 0;
					// ע���ö������Ϣ
					DeregisterRetry(AsynObject.GetUserID());
					// ��¼�װ���־
					ReduceLog(AsynObject, "����ʱ����δ֪����");
					break;

					// ���ݿⷵ���߼�����, ���첽����ŵ��������ķ��ض�����
				default:
					g_pDBEngine->AddReturnObject(AsynObject);
					// ���õ�ǰ���������Դ���
					m_nCurObjRetryNum = 0;
					// ע���ö������Ϣ
					DeregisterRetry(AsynObject.GetUserID());
					break;
				}
			}
		}
	}
	else
	{
		m_nNoRetryNum ++;
	}
}

// ���һ��������󵽶���
void CAsynObjectList::AddRequestObject(CAsynObject &AsynObject)
{
#ifdef PERFORMANCE_TEST
  timespec ts;
  u64 startCounter = 0;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  startCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
#endif
  AutoMutex auto_mutex(&m_RequestLock);
#ifdef PERFORMANCE_TEST
  clock_gettime(CLOCK_MONOTONIC, &ts);
  u64 endCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
  count += endCounter - startCounter;
  if(endCounter - startCounter > 20) {
    g_pDBEngine->PrintInfoLog("[MUTEX_TEST] Position2 cost [%ld] ns", endCounter - startCounter);
  }
#endif

  m_RequestList.push_back(AsynObject);
	m_nRequestListSize ++;
	// Ӧ���װ����ԶԶ��н��о���
	ReduceStrategy();
	// Ӧ�ñ��ػ�����Դ�������״��
	CacheStrategy();

	// TODO by zipher ֪ͨ�̴߳���
	//SetEvent(m_hRequestEvent);
}

// ��̬����������Ϣ
BOOL CAsynObjectList::UpdateConfig(ASYNLISTINFO &AsynListInfo)
{
	m_AsynListInfo = AsynListInfo;
	return TRUE;
}

// �쳣��������
void CAsynObjectList::OnWarning(int nReturn)
{
	time_t now;
	time(&now);
	tm when = *localtime(&now);
	char szCurTime[32] = {0};
	strftime(szCurTime, sizeof(szCurTime), "%Y-%m-%d %H:%M:%S", &when);

	char szMsg[256] = {0};

	switch(nReturn)
	{
		// ���ݿ����ӶϿ�
	case DBWARN_DISCONNECTED:
		sprintf(szMsg, "[%s]: �첽����ID=%d, ��������=%d, �쳣����=%s", szCurTime,
			m_nID, GetRequestType(), "���ݿ����ӶϿ�!");
		break;

		// ���ݿ����ӻָ�����
	case DBWARN_CONNECTED:
		sprintf(szMsg, "[%s]: �첽����ID=%d, ��������=%d, �쳣����=%s", szCurTime,
			m_nID, GetRequestType(), "���ݿ����ӻָ�����!");
		break;

		// ���Զ��дﵽ��󳤶�
	case DBWARN_RETRY_MAXSIZE:
		sprintf(szMsg, "[%s]: �첽����ID=%d, ��������=%d, �쳣����=%s", szCurTime,
			m_nID, GetRequestType(), "���Զ��дﵽ��󳤶�!");
		break;

		// �������ִ���װ�����
	case DBWARN_REDUCE_STRATEGY:
		sprintf(szMsg, "[%s]: �첽����ID=%d, ��������=%d, �쳣����=%s", szCurTime,
			m_nID, GetRequestType(), "�������ִ���װ�����!");
		break;

		// �������ִ�б��ػ������
	case DBWARN_CACHE_STRATEGY:
		sprintf(szMsg, "[%s]: �첽����ID=%d, ��������=%d, �쳣����=%s", szCurTime,
			m_nID, GetRequestType(), "�������ִ�б��ػ������!");
		break;

	default:
		return;
	}

	g_pDBEngine->OnWarning(nReturn, szMsg);
}

// ��ȡ�������������
s32 CAsynObjectList::GetRequestType(void)
{
	return m_AsynListInfo.nType;
}

// ��ȡCDBADOָ��
CDBADO* CAsynObjectList::GetDBADO(void)
{
	return &m_DBADO;
}

// ��ȡ���������
s32 CAsynObjectList::GetRequestObjNum(void)
{
	return m_nRequestListSize;
}

// ��ȡ���԰�����
s32 CAsynObjectList::GetRetryObjNum(void)
{
	return m_nRetryListSize;
}

// ע����������Զ��е���Ϣ
void CAsynObjectList::RegisterRetry(s64 qwUserID)
{
	map<s64, s32>::iterator	it = m_RetryRegHash.find(qwUserID);
	if (it == m_RetryRegHash.end())
	{
		m_RetryRegHash[qwUserID] = 1;
	}
	else
	{
		(*it).second ++;
	}
}

// ע�����������Զ��е���Ϣ
void CAsynObjectList::DeregisterRetry(s64 qwUserID)
{
	map<s64, s32>::iterator	it = m_RetryRegHash.find(qwUserID);
	if (it != m_RetryRegHash.end())
	{
		(*it).second --;
		if ((*it).second <= 0)
		{
			m_RetryRegHash.erase(it);
		}
	}
}

// ִ���װ�����
void CAsynObjectList::ReduceStrategy(void)
{
	if (m_nRequestListSize > m_AsynListInfo.nReduceSize)
	{
		list<CAsynObject>::iterator	it = m_RequestList.begin();
		while (it != m_RequestList.end())
		{
			CAsynObject	*pAsynObject = &(*it);
			if (pAsynObject->GetWeightness() <= m_AsynListInfo.nReduceWeightness)
			{
				g_pDBEngine->AddReturnObject(*pAsynObject);
				// ��¼�װ���־
				ReduceLog(*pAsynObject, "ִ���װ�����");
				it = m_RequestList.erase(it);
				m_nRequestListSize --;
				continue;
			}

			++ it;
		}

		// �쳣����
		OnWarning(DBWARN_REDUCE_STRATEGY);
	}
}

// �װ���־
void CAsynObjectList::ReduceLog(CAsynObject &AsynObject, LPCSTR szReason)
{
	time_t	now;
	time(&now);
	tm	when = *localtime(&now);
	char	szCurTime[32] = {0};
	strftime(szCurTime, sizeof(szCurTime), "%Y-%m-%d %H:%M:%S", &when);

	char	szMsg[MAX_LINE_NUMBER] = {0};
	sprintf(szMsg, "[%s]: %s, ����ID=%d, ��Ҫ��=%d, �û�ID=%ld!\n",
		szCurTime, szReason,
		AsynObject.GetRequestID(), AsynObject.GetWeightness(),
		AsynObject.GetUserID());

	char	szFile[256] = {0};
	sprintf(szFile, REDUCE_LOG_FILE, m_nID);

	AutoMutex auto_mutex(&m_LogLock);
	FILE	*fp = fopen(szFile, "a");
	if (fp != NULL)
	{
		fprintf(fp, szMsg);
		fclose(fp);
	}
}

// ���ػ������
void CAsynObjectList::CacheStrategy(void)
{
	if (m_nRequestListSize > m_AsynListInfo.nCacheSize)
	{
		char	szFile[256] = {0};
		sprintf(szFile, CACHE_FILE, m_nID);

		FILE	*fp = fopen(szFile, "ab");
		if (NULL == fp)
		{
			return;
		}

		fseek(fp, 0, SEEK_END);
		int	nFileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		// ����д��type��Ϣ(4�ֽ�)
		if (nFileSize <= 0)
		{
			fwrite(&m_AsynListInfo.nType, sizeof(m_AsynListInfo.nType), 1, fp);
		}

		// ˳��д��ÿ�����ݰ�����Ϣ
		list<CAsynObject>::iterator	it = m_RequestList.begin();
		for (; it != m_RequestList.end(); ++ it)
		{
			CAsynObject	*pAsynObject = &(*it);
			pAsynObject->DumpToFile(fp);
			pAsynObject->Close();
		}

		// ����첽����
		m_RequestList.clear();
		m_nRequestListSize = 0;

		fclose(fp);

		// �쳣����
		OnWarning(DBWARN_CACHE_STRATEGY);
	}
}

void CAsynObjectList::Loop()
{
  this->looping_ = true;
	while(this->quit_ == false)
	{
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    util::UpdateTickCount(&ts);
		Process();
		usleep(2000);
	}
  this->looping_ = false;
}

