#include "Header.h"
#include "AsynObjectList.h"
#include "base/auto_mutex.h"
#include "util/Util.h"

#ifdef PERFORMANCE_TEST
u64 CAsynObjectList::count = 0;
#endif

// 构造函数
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

// 析构函数
CAsynObjectList::~CAsynObjectList()
{
}

// 创建异步对象队列
BOOL CAsynObjectList::Create(int nID, ASYNLISTINFO &AsynListInfo)
{
	if( NULL != m_pThread )
	{
		return FALSE;
	}

	m_AsynListInfo = AsynListInfo;

	// 创建CDBADO对象
	if (FALSE == m_DBADO.Create())
	{
		return FALSE;
	}

	// 设置所属异步队列指针
	m_DBADO.SetAsynObjectList(this);

	// 连接数据库
	if (FALSE == m_DBADO.Connect(m_AsynListInfo.szServerName,
		m_AsynListInfo.nServerPort,
		m_AsynListInfo.szDBName,
		m_AsynListInfo.szUserName,
		m_AsynListInfo.szPassword))
	{
		return FALSE;
	}

	m_nID = nID;

	// 创建新线程来执行异步对象队列的主处理
	m_pThread = new LoopThread((BaseLoop*)this, "AsynObjectList", true);
	if (NULL == m_pThread)
	{
		return FALSE;
	}
	m_pThread->StartLoop();

	return TRUE;
}

// 释放异步对象队列
void CAsynObjectList::Close(void)
{
	// 销毁线程
	if (m_pThread != NULL)
	{
		m_pThread->StopLoop();
		delete m_pThread;
		m_pThread = NULL;
	}

	// 关闭数据库
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

// 队列主处理
void CAsynObjectList::Process(void)
{
	list<CAsynObject>::iterator		itRequest;
	list<CAsynObject>::iterator		itRetry;

	CAsynObject		AsynObject;
	CAsynObject		*pAsynObject = NULL;

	// 处理请求数据包
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
			// 如果该异步对象相关的对象已经在重试队列中则要放到重试队列中
			if (m_RetryRegHash.find(pAsynObject->GetUserID()) != m_RetryRegHash.end())
			{
				m_RetryList.push_back(AsynObject);
				m_nRetryListSize ++;
				RegisterRetry(pAsynObject->GetUserID());
				continue;
			}
#ifdef PERFORMANCE_TEST
      timespec ts;
			// 请求耗时统计
			s64 startCounter = 0;
      clock_gettime(CLOCK_MONOTONIC, &ts);
      startCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
			//::QueryPerformanceCounter((LARGE_INTEGER *)&startCounter);
#endif

			s32 nRet = pAsynObject->OnRequest();

#ifdef PERFORMANCE_TEST
			// 请求耗时统计
			s64 endCounter = 0;
			//::QueryPerformanceCounter((LARGE_INTEGER *)&endCounter);
      clock_gettime(CLOCK_MONOTONIC, &ts);
      endCounter = (u64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
			g_pDBEngine->PerformanceTest(pAsynObject->GetRequestID(), PT_REQUESTCAST,
				endCounter - startCounter);
#endif

			switch(nRet)
			{
				// 返回成功, 把异步对象放到管理器的返回队列中
			case DBRET_OK:
				g_pDBEngine->AddReturnObject(AsynObject);
				break;

				// 返回表死锁, 根据重要度要把异步对象放到重试队列
			case DBRET_ERROR_LOCK:
				// 如果重要度达到重试重要度则要放到重试队列
				if (AsynObject.GetWeightness() >= m_AsynListInfo.nRetryWeightness)
				{
					m_RetryList.push_back(AsynObject);
					m_nRetryListSize ++;
					// 注册该对象在重试队列的信息
					RegisterRetry(AsynObject.GetUserID());
				}
				// 抛包
				else
				{
					g_pDBEngine->AddReturnObject(AsynObject);
					// 记录抛包日志
					ReduceLog(AsynObject, "返回死锁且重要度低于重试重要度");
				}

				break;

				// 引擎返回未知错误, 把异步对象放到管理器的返回队列中, 并记录抛包日志
			case DBRET_ERROR_UNKNOWN:
				g_pDBEngine->AddReturnObject(AsynObject);
				// 记录抛包日志
				ReduceLog(AsynObject, "返回未知错误");
				break;

				// 数据库返回逻辑错误, 把异步对象放到管理器的返回队列中
			default:
				g_pDBEngine->AddReturnObject(AsynObject);
				break;
			}
		}
	}

	// 如果未处理重试队列计数达到重试间隔数, 就处理一次重试队列中的数据包
	if (m_nNoRetryNum >= m_AsynListInfo.nRetryInternal)
	{
		// 重置未处理重试队列计数
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
					// 返回成功, 把异步对象放到管理器的返回队列中
				case DBRET_OK:
					g_pDBEngine->AddReturnObject(AsynObject);
					// 重置当前对象已重试次数
					m_nCurObjRetryNum = 0;
					// 注销该对象在重试队列中的信息
					DeregisterRetry(AsynObject.GetUserID());
					break;

					// 返回表死锁, 根据当前对象重试次数决定是重新放回重试队列头部还是抛掉
				case DBRET_ERROR_LOCK:
					// 累计当前对象已重试次数
					m_nCurObjRetryNum ++;
					// 当前对象已重试次数达到配置的重试次数, 则抛掉当前对象
					if (m_nCurObjRetryNum >= m_AsynListInfo.nRetryNumber)
					{
						g_pDBEngine->AddReturnObject(AsynObject);
						// 重置当前对象已重试次数
						m_nCurObjRetryNum = 0;
						// 注销该对象的信息
						DeregisterRetry(AsynObject.GetUserID());
						// 记录抛包日志
						ReduceLog(AsynObject, "重试次数过多");
					}
					// 重试队列达到最大长度, 则抛掉当前对象
					else if (m_nRetryListSize >= m_AsynListInfo.nRetryMaxSize)
					{
						g_pDBEngine->AddReturnObject(AsynObject);
						// 重置当前对象已重试次数
						m_nCurObjRetryNum = 0;
						// 注销该对象的信息
						DeregisterRetry(AsynObject.GetUserID());
						// 记录抛包日志
						ReduceLog(AsynObject, "重试队列达到最大长度");
						// 异常报警
						OnWarning(DBWARN_RETRY_MAXSIZE);
					}
					// 当前对象已重试次数小于配置的重试次数, 则重新放回重试队列头部
					else
					{
						m_RetryList.push_front(AsynObject);
						m_nRetryListSize ++;
						return;
					}

					break;

					// 引擎返回未知错误, 把异步对象放到管理器的返回队列中
				case DBRET_ERROR_UNKNOWN:
					g_pDBEngine->AddReturnObject(AsynObject);
					// 重置当前对象已重试次数
					m_nCurObjRetryNum = 0;
					// 注销该对象的信息
					DeregisterRetry(AsynObject.GetUserID());
					// 记录抛包日志
					ReduceLog(AsynObject, "重试时返回未知错误");
					break;

					// 数据库返回逻辑错误, 把异步对象放到管理器的返回队列中
				default:
					g_pDBEngine->AddReturnObject(AsynObject);
					// 重置当前对象已重试次数
					m_nCurObjRetryNum = 0;
					// 注销该对象的信息
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

// 添加一个请求对象到队列
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
	// 应用抛包策略对队列进行精简
	ReduceStrategy();
	// 应用本地缓存策略处理特殊状况
	CacheStrategy();

	// TODO by zipher 通知线程处理
	//SetEvent(m_hRequestEvent);
}

// 动态更新配置信息
BOOL CAsynObjectList::UpdateConfig(ASYNLISTINFO &AsynListInfo)
{
	m_AsynListInfo = AsynListInfo;
	return TRUE;
}

// 异常报警处理
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
		// 数据库连接断开
	case DBWARN_DISCONNECTED:
		sprintf(szMsg, "[%s]: 异步队列ID=%d, 处理类型=%d, 异常描述=%s", szCurTime,
			m_nID, GetRequestType(), "数据库连接断开!");
		break;

		// 数据库连接恢复正常
	case DBWARN_CONNECTED:
		sprintf(szMsg, "[%s]: 异步队列ID=%d, 处理类型=%d, 异常描述=%s", szCurTime,
			m_nID, GetRequestType(), "数据库连接恢复正常!");
		break;

		// 重试队列达到最大长度
	case DBWARN_RETRY_MAXSIZE:
		sprintf(szMsg, "[%s]: 异步队列ID=%d, 处理类型=%d, 异常描述=%s", szCurTime,
			m_nID, GetRequestType(), "重试队列达到最大长度!");
		break;

		// 请求对列执行抛包策略
	case DBWARN_REDUCE_STRATEGY:
		sprintf(szMsg, "[%s]: 异步队列ID=%d, 处理类型=%d, 异常描述=%s", szCurTime,
			m_nID, GetRequestType(), "请求对列执行抛包策略!");
		break;

		// 请求对列执行本地缓存策略
	case DBWARN_CACHE_STRATEGY:
		sprintf(szMsg, "[%s]: 异步队列ID=%d, 处理类型=%d, 异常描述=%s", szCurTime,
			m_nID, GetRequestType(), "请求对列执行本地缓存策略!");
		break;

	default:
		return;
	}

	g_pDBEngine->OnWarning(nReturn, szMsg);
}

// 获取处理请求的类型
s32 CAsynObjectList::GetRequestType(void)
{
	return m_AsynListInfo.nType;
}

// 获取CDBADO指针
CDBADO* CAsynObjectList::GetDBADO(void)
{
	return &m_DBADO;
}

// 获取请求包数量
s32 CAsynObjectList::GetRequestObjNum(void)
{
	return m_nRequestListSize;
}

// 获取重试包数量
s32 CAsynObjectList::GetRetryObjNum(void)
{
	return m_nRetryListSize;
}

// 注册对象在重试队列的信息
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

// 注销对象在重试队列的信息
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

// 执行抛包策略
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
				// 记录抛包日志
				ReduceLog(*pAsynObject, "执行抛包策略");
				it = m_RequestList.erase(it);
				m_nRequestListSize --;
				continue;
			}

			++ it;
		}

		// 异常报警
		OnWarning(DBWARN_REDUCE_STRATEGY);
	}
}

// 抛包日志
void CAsynObjectList::ReduceLog(CAsynObject &AsynObject, LPCSTR szReason)
{
	time_t	now;
	time(&now);
	tm	when = *localtime(&now);
	char	szCurTime[32] = {0};
	strftime(szCurTime, sizeof(szCurTime), "%Y-%m-%d %H:%M:%S", &when);

	char	szMsg[MAX_LINE_NUMBER] = {0};
	sprintf(szMsg, "[%s]: %s, 请求ID=%d, 重要度=%d, 用户ID=%ld!\n",
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

// 本地缓存策略
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

		// 首先写入type信息(4字节)
		if (nFileSize <= 0)
		{
			fwrite(&m_AsynListInfo.nType, sizeof(m_AsynListInfo.nType), 1, fp);
		}

		// 顺序写入每个数据包的信息
		list<CAsynObject>::iterator	it = m_RequestList.begin();
		for (; it != m_RequestList.end(); ++ it)
		{
			CAsynObject	*pAsynObject = &(*it);
			pAsynObject->DumpToFile(fp);
			pAsynObject->Close();
		}

		// 清空异步队列
		m_RequestList.clear();
		m_nRequestListSize = 0;

		fclose(fp);

		// 异常报警
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

