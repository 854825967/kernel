#include "Header.h"
#include "DBEngine.h"
#include "stdarg.h"
#include "base/auto_mutex.h"

#include <time.h>

using namespace core;

// 异步队列配置总数量标志
#define ASYNLIST_CONFIG_NUM_FLAG		"totalnum ="

// 异步队列配置标志
#define ASYNOBJECTLIST_CONFIT_FLAG		"asynobject list"

// 数据库驱动类型
#define DRIVERTYPE_CONFIT_FLAG			"dbdrivertype ="

// 数据库服务器名配置标志
#define SERVERNAME_CONFIG_FLAG			"servername ="
// 数据库服务器端口配置标志
#define SERVERPORT_CONFIG_FLAG                  "serverport ="
// 数据库名配置标志
#define DBNAME_CONFIG_FLAG			"dbname ="
// 用户名配置标志
#define USERNAME_CONFIG_FLAG			"username ="
// 密码配置标志
#define PASSWORD_CONFIG_FLAG			"password ="
// 异步队列类型配置标志
#define ASYNLIST_TYPE_CONFIG_FLAG		"type ="
// 异步队列个数配置标志
#define ASYNLIST_NUM_CONFIG_FLAG		"num ="
// 重试重要度配置标志
#define RETRY_WEIGHTNESS_CONFIG_FLAG		"retry strategy weightness ="
// 重试间隔配置标志
#define RETRY_INTERVAL_CONFIG_FLAG		"retry strategy internal ="
// 重试次数配置标志
#define RETRY_NUMBER_CONFIG_FLAG		"retry strategy number ="
// 重试队列最大长度
#define RETRY_MAXSIZE_CONFIG_FLAG		"retry max size ="
// 触发抛包的队列大小配置标志
#define REDUCE_SIZE_CONFIG_FLAG			"reduce strategy size ="
// 抛包重要度配置标志
#define REDUCE_WEIGHTNESS_CONFIG_FLAG		"reduce strategy weightness ="
// 触发缓存的队列大小配置标志
#define CACHE_SIZE_CONFIG_FLAG			"cache strategy size ="

// 全局通用数据库引擎对象指针
CDBEngine	*g_pDBEngine = NULL;

// 构造函数
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

// 析构函数
CDBEngine::~CDBEngine()
{
	// 销毁异步队列
	CloseAsynObjectList();

	// 打印性能评测结果
	PerformanceTest(0, PT_PRINTLOG, 0);

	// 关闭数据库请求配置
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

// 创建通用数据库引擎
BOOL CDBEngine::Create(IDBWarningSink *pWarningSink, LPSTR szKey, LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	if (NULL == szKey || strlen(szKey) <= 0)
	{
		return FALSE;
	}

	mcopyptr(m_szKey, szKey, sizeof(m_szKey));
  this->m_log_file_ = log_file;

	// 创建数据库请求配置
	s32	nErrLine = 0;
	if (FALSE == g_RequestConfig.Create(szDBRequestScp, nErrLine, m_szKey))
	{
		GPrintInfoLog("DBRequest.res 第%d行加载出错!", nErrLine);
		return FALSE;
	}

	// 保存异常报警接口指针
	m_pWarningSink = pWarningSink;

	// 创建异步队列
	nErrLine = 0;
	if (FALSE == CreateAsynObjectList(m_szKey, nErrLine, szDBEngineScp))
	{
		GPrintInfoLog("DBEngine.res 第%d行加载出错!", nErrLine);
		return FALSE;
	}

	return TRUE;
}

// 销毁通用数据库引擎
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
			// 性能评测
			PerformanceTest((u32)sRequestID, PT_ONRETCASTSTART, 0);

			pReturnObject->OnRet();

			// 性能评测
			PerformanceTest((u32)sRequestID, PT_ONRETCASTEND, 0);
		}
		catch (...)
		{
			char szMsg[256] = {0};
			sprintf(szMsg, "请求返回非法, 请求ID = %d, 用户ID = %d", sRequestID, sUserID);
			PrintInfoLog(szMsg);
		}

		pReturnObject->Close();
	}
	m_pCurReturnList->clear();
}

// 请求数据库
BOOL CDBEngine::Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
						LPSTR pInData, s32 nInDataLen, IDBRetSink *pRet)
{
	REQUESTCONFIG *pRequestConfig = g_RequestConfig.FindRequestConfig(nRequestID);
	if (NULL == pRequestConfig)
	{
		PrintInfoLog("请求ID = %d不存在",nRequestID);
		return FALSE;
	}

	CAsynObjectList	*pAsynObjectList[32] = {0};
	s32	nAsynObjectLisgNum = 0;

	// 先搜索处理类型匹配的所有异步对列
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

	// 没有找到类型匹配的异步对列则失败
	if (nAsynObjectLisgNum <= 0)
	{
		return FALSE;
	}

	// 按用户ID取模以便负载平衡, 同时保证同一个用户的所有包在相同异步对列中
	u64			uiUserID = qwUserID;
	s32			nRequestAsynList = uiUserID % nAsynObjectLisgNum;
	CAsynObject	AsynObject;

	// 构造异步对象并添加到相应的异步对列中
	if (FALSE == AsynObject.Create(nIndex, nRequestID, qwUserID, pInData, nInDataLen,
		pAsynObjectList[nRequestAsynList]->GetDBADO(), pRet))
	{
		return FALSE;
	}

	pAsynObjectList[nRequestAsynList]->AddRequestObject(AsynObject);

	// 性能评测
	PerformanceTest((DWORD)nRequestID, PT_REQUEST, 0);

	return TRUE;
}

// 获取某种请求类型的异步队列状态信息
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

// 更新配置信息验证宏
#define ASSERT_ALUPDATE(r)	{ if (!(r)) { return FALSE; } }
/*
// 动态更新配置信息(目标数据库和异步队列各种策略)
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

	// 获取异步队列配置的总数量
	s32	nInputNum = sscanf(szBuf + strlen(ASYNLIST_CONFIG_NUM_FLAG), "%d", &nTotalNum);
	ASSERT_ALUPDATE(1 == nInputNum && nTotalNum > 0);

	// 获取异步队列配置信息
	while (FALSE == FileObj.IsEnd())
	{
		// "asynobject list"
		if (FALSE == FindStrInFile(&FileObj, ASYNOBJECTLIST_CONFIT_FLAG, nErrLine, szBuf))
		{
			break;
		}

		// "{"
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));
		// 获取数据库服务器名
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, SERVERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(SERVERNAME_CONFIG_FLAG), "%s", AsynListInfo.szServerName);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szServerName) > 0);
		// 获取数据库名
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, DBNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DBNAME_CONFIG_FLAG), "%s", AsynListInfo.szDBName);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szDBName) > 0);
		// 获取用户名
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, USERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(USERNAME_CONFIG_FLAG), "%s", AsynListInfo.szUserName);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szUserName) > 0);
		// 获取密码
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, PASSWORD_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(PASSWORD_CONFIG_FLAG), "%s", AsynListInfo.szPassword);
		ASSERT_ALUPDATE(1 == nInputNum && strlen(AsynListInfo.szPassword) > 0);
		// 获取异步队列类型
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_TYPE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_TYPE_CONFIG_FLAG), "%d", &AsynListInfo.nType);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nType > 0);
		// 获取异步队列个数
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_NUM_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_NUM_CONFIG_FLAG), "%d", &nNum);
		ASSERT_ALUPDATE(1 == nInputNum && nNum > 0);
		// 获取重试重要度
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nRetryWeightness);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nRetryWeightness < REQUEST_WEIGHTNESS_MAX);
		// 获取重试间隔
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_INTERVAL_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_INTERVAL_CONFIG_FLAG), "%d", &AsynListInfo.nRetryInternal);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryInternal >= 0);
		// 获取重试次数
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_NUMBER_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_NUMBER_CONFIG_FLAG), "%d", &AsynListInfo.nRetryNumber);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryNumber > 0);
		// 获取重试队列最大长度
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, RETRY_MAXSIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_MAXSIZE_CONFIG_FLAG), "%d", &AsynListInfo.nRetryMaxSize);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nRetryMaxSize >= 100);
		// 获取触发抛包的队列大小
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, REDUCE_SIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_SIZE_CONFIG_FLAG), "%d", &AsynListInfo.nReduceSize);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nReduceSize >= 100);
		// 获取抛包重要度
		ASSERT_ALUPDATE(TRUE == FindStrInFile(&FileObj, REDUCE_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nReduceWeightness);
		ASSERT_ALUPDATE(1 == nInputNum && AsynListInfo.nReduceWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nReduceWeightness < REQUEST_WEIGHTNESS_MAX);
		// 获取触发缓存的队列大小
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

	// 验证新配置要保持异步队列个数不变
	ASSERT_ALUPDATE(AsynListInfoList.size() == m_AsynObjectListList.size());
	// 验证新配置要保持异步队列类型不变
	list<ASYNLISTINFO>::iterator		itInfo = AsynListInfoList.begin();
	list<CAsynObjectList*>::iterator	itList = m_AsynObjectListList.begin();
	for (; itInfo != AsynListInfoList.end(); ++ itInfo)
	{
		ASYNLISTINFO	*pInfo = &(*itInfo);
		CAsynObjectList	*pList = (*itList);
		ASSERT_ALUPDATE(pInfo->nType == pList->GetRequestType());
		++ itList;
	}

	// 正式开始更新配置
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
// 添加一个要回调的对象
void CDBEngine::AddReturnObject(CAsynObject &ReturnObject)
{
	AutoMutex auto_mutex(&m_ReturnLock);
	m_pCurReturnList2->push_back(ReturnObject);
	//TODO by zipher 通知逻辑线程
	//SetEvent(m_hReturnEvent);
}

// 异常报警处理
void CDBEngine::OnWarning(s32 nReturn, LPSTR szDesc)
{
	if (NULL == m_pWarningSink)
	{
		return;
	}

	AutoMutex auto_mutex(&m_WarningLock);
	m_pWarningSink->OnWarning(nReturn, szDesc);
}

// 输出信息日志
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

// 性能评测函数
inline void CDBEngine::PerformanceTest(u32 key, s32 flag, s64 value)
{
#ifdef PERFORMANCE_TEST	// 性能评测
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
		// 请求
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

		// 请求耗时
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

		// 回调耗时开始
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
				PrintInfoLog("数据库引擎性能评测计开始时错误, RequestID=%d!", key);
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

		// 回调耗时结束
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
				PrintInfoLog("数据库引擎性能评测计结束时错误, RequestID=%d!", key);
				break;
			}
		}
		else
		{
			PrintInfoLog("数据库引擎性能评测计结束时错误, RequestID=%d!", key);
			break;
		}

		break;

		// 打印统计结果
	case PT_PRINTLOG:
		PrintInfoLog("---------------数据库引擎性能评测结果开始---------------");
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
			PrintInfoLog("请求ID=%d, 请求%d次, 请求平均耗时%dus, 回调%d次, 回调平均耗时%dus!",
				dwKey, dbTest.dwRequestNum, requestCostUS, dbTest.dwCallNum, onretCostUS);
		}

		PrintInfoLog("---------------数据库引擎性能评测结果结束---------------");
		break;

	default:
		break;
	}
#endif
}

// 创建异步队列处理验证宏
#define ASSERT_ALCREATE(r)	{ if (!(r)) { return FALSE; } }

// 创建异步队列
BOOL CDBEngine::CreateAsynObjectList(LPSTR szKey, s32 &nErrLine, LPCSTR szDBEngineScp)
{
	CDBMemTextFile	FileObj;

	if (FALSE == FileObj.Open(szDBEngineScp))
	{
		PrintInfoLog("加载脚本 = %s 错误,文件不存在", szDBEngineScp);
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

	// 获取异步队列配置的总数量
	s32	nInputNum = sscanf(szBuf + strlen(ASYNLIST_CONFIG_NUM_FLAG), "%d", &nTotalNum);
	ASSERT_ALCREATE(1 == nInputNum && nTotalNum > 0);

	// 获取异步队列配置信息
	while (FALSE == FileObj.IsEnd())
	{
		// "asynobject list"
		if (FALSE == FindStrInFile(&FileObj, ASYNOBJECTLIST_CONFIT_FLAG, nErrLine, szBuf))
		{
			break;
		}

		// "{"
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));

		// 获取数据库驱动类型
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DRIVERTYPE_CONFIT_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DRIVERTYPE_CONFIT_FLAG), "%d", &AsynListInfo.nDriverType);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nDriverType > 0); 

		// 获取数据库服务器名
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, SERVERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(SERVERNAME_CONFIG_FLAG), "%s", AsynListInfo.szServerName);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szServerName) > 0);
		// 获取数据库服务器端口
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, SERVERPORT_CONFIG_FLAG, nErrLine, szBuf));
                nInputNum = sscanf(szBuf + strlen(SERVERPORT_CONFIG_FLAG), "%d", &AsynListInfo.nServerPort);
                ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nServerPort > 0);
		// 获取数据库名
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DBNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DBNAME_CONFIG_FLAG), "%s", AsynListInfo.szDBName);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szDBName) > 0);
		// 获取用户名
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, USERNAME_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(USERNAME_CONFIG_FLAG), "%s", AsynListInfo.szUserName);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szUserName) > 0);
		// 获取密码
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, PASSWORD_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(PASSWORD_CONFIG_FLAG), "%s", AsynListInfo.szPassword);
		ASSERT_ALCREATE(1 == nInputNum && strlen(AsynListInfo.szPassword) > 0);
		// 获取异步队列类型
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_TYPE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_TYPE_CONFIG_FLAG), "%d", &AsynListInfo.nType);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nType > 0);
		// 获取异步队列个数
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, ASYNLIST_NUM_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(ASYNLIST_NUM_CONFIG_FLAG), "%d", &nNum);
		ASSERT_ALCREATE(1 == nInputNum && nNum > 0);
		// 获取重试重要度
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nRetryWeightness);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nRetryWeightness < REQUEST_WEIGHTNESS_MAX);
		// 获取重试间隔
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_INTERVAL_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_INTERVAL_CONFIG_FLAG), "%d", &AsynListInfo.nRetryInternal);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryInternal >= 0);
		// 获取重试次数
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_NUMBER_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_NUMBER_CONFIG_FLAG), "%d", &AsynListInfo.nRetryNumber);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryNumber > 0);
		// 获取重试队列最大长度
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, RETRY_MAXSIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(RETRY_MAXSIZE_CONFIG_FLAG), "%d", &AsynListInfo.nRetryMaxSize);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nRetryMaxSize >= 100);
		// 获取触发抛包的队列大小
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, REDUCE_SIZE_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_SIZE_CONFIG_FLAG), "%d", &AsynListInfo.nReduceSize);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nReduceSize >= 100);
		// 获取抛包重要度
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, REDUCE_WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(REDUCE_WEIGHTNESS_CONFIG_FLAG), "%d", &AsynListInfo.nReduceWeightness);
		ASSERT_ALCREATE(1 == nInputNum && AsynListInfo.nReduceWeightness >= REQUEST_WEIGHTNESS_1 && AsynListInfo.nReduceWeightness < REQUEST_WEIGHTNESS_MAX);
		// 获取触发缓存的队列大小
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

// 销毁异步队列
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

// 过滤字符串左面的空格和tab键
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

// 查找文件中以某个字符串开始的行
BOOL CDBEngine::FindStrInFile(CDBMemTextFile *pFileObj, LPCSTR szStr, s32 &nCurLine, LPSTR szBuf)
{
	if (NULL == pFileObj || NULL == szStr || NULL == szBuf)
	{
		PrintInfoLog("加载脚本错误:  nCurLine = %d",nCurLine);
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

// 创建通用数据库引擎(输出函数)
extern "C" BOOL CreateDBEngine(IDBEngine **ppDBEngine, IDBWarningSink *pWarningSink,
	LPSTR szKey, LPCSTR szDBEngineScp, LPCSTR szDBRequestScp, const char *log_file)
{
	CDBEngine *pNewDBEngine = new CDBEngine;
	if (NULL == pNewDBEngine)
	{
		GPrintInfoLog("给数据库引擎分配内存失败!");
		return FALSE;
	}

	g_pDBEngine = pNewDBEngine; // 这句话提前到这里，因为下面的Create用到这个指针了

	if (FALSE == pNewDBEngine->Create(pWarningSink, szKey, szDBEngineScp, szDBRequestScp, log_file))
	{
		delete pNewDBEngine;
		pNewDBEngine = NULL;
		g_pDBEngine = NULL;
		GPrintInfoLog("数据库引擎创建失败!");
		return FALSE;
	}

	*ppDBEngine = static_cast<IDBEngine *>(pNewDBEngine);

	return TRUE;
}
