/* 
 * File:   LogSystem.cpp
 * Author: traveler
 * 
 * Created on January 5, 2013, 11:03 AM
 */

#include "../../Public/Tools.h"
#include "LogSystem.h"
#include "LogQueue.h"
#include <iostream>
using namespace std;

LogSystem * LogSystem::m_pSelf = NULL;
bool LogSystem::m_active = false;
UI64 LogSystem::m_nLastCreatLogFileTick = 0;
UI64 LogSystem::m_nServerStartTime = 0;
pthread_t LogSystem::m_writethreadid;
CHashMap<Cthread_id, ILogQueue *> LogSystem::m_logQueuePool;

ILogSystem * LogSystem::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW LogSystem;
        if (!m_pSelf->Bron()) {
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

LogSystem::~LogSystem() {
    CHashMap<Cthread_id, ILogQueue *>::iterator ibegin = m_logQueuePool.begin();
    CHashMap<Cthread_id, ILogQueue *>::iterator iend = m_logQueuePool.end();
    while (ibegin != iend) {
        if (ibegin->second != NULL) {
            delete ibegin->second;
            ibegin->second = NULL;
        }
        ibegin++;
    }
    m_logQueuePool.clear();
}

bool LogSystem::Bron() {
    m_active = true;
    m_nLastCreatLogFileTick = 0;
    m_nServerStartTime = GetCurrentTimeTick();
    m_logQueuePool.clear();
    return true;
}

bool LogSystem::Dead() {
    return true;
}

bool LogSystem::Initialize() {
    int error = pthread_create(&m_writethreadid, NULL, WriteThread, NULL);
    if (error != 0) {
        cout << "Cant't create write log thread:" << strerror(error) << endl;
        Assert(false);
        return false;
    }
    return true;
}

bool LogSystem::Destroy() {
    m_active = false;
    usleep(1);
    if (m_pSelf != NULL) {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

const string LogSystem::GetLogFilePath(UI64 nCurrent) {
    char path[256] = {0}; //string(GetAppPath()) + "/Log/" +  ctime((__time_t*)&ntick);// + ".log";
    nCurrent = nCurrent / 1000;
    snprintf(path, 256, "%s/Log/%s", GetAppPath(), ctime((__time_t*) & nCurrent));
    path[strlen(path) - 1] = 0;

    return path;
}

bool LogSystem::AddLog(const Log& log) {
    Cthread_id threadid = GetCurrentThreadID();
    CHashMap<Cthread_id, ILogQueue *>::iterator ifind = m_logQueuePool.find(threadid);
    CHashMap<Cthread_id, ILogQueue *>::iterator iend = m_logQueuePool.end();
    if (ifind == iend) {
        ILogQueue * pLogQueue = NEW LogQueue<>;
        printf("LogSystem::AddLog\n");
        Assert(pLogQueue != NULL);
        m_logQueuePool.insert(make_pair(threadid, pLogQueue));
        if (!pLogQueue->In(log)) {
            Assert(false);
            return false;
        }
    } else {
        if (NULL == ifind->second) {
            //这里要屏幕输出错误      
        }
        if (!ifind->second->In(log)) {
            Assert(false);
            return false;
        }
    }

    return true;
}

CHandle LogSystem::GetLogFileHandle(const UI64 nCurrentTick) {
    static CHandle handleID = -1;
    if (0 == m_nLastCreatLogFileTick || handleID < 0) {
        m_nLastCreatLogFileTick = nCurrentTick;
        string path = GetLogFilePath(m_nLastCreatLogFileTick);
        handleID = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
        Assert(handleID >= 0);
        if (handleID < 0) {
            //这里要标准输出错误
        }
    } else if (nCurrentTick - m_nLastCreatLogFileTick > LOGFILE_SEGMENTATION_TIME) {
        m_nLastCreatLogFileTick = nCurrentTick;
        if (handleID >= 0) {
            close(handleID);
        }
        string path = GetLogFilePath(m_nLastCreatLogFileTick);
        handleID = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
        Assert(handleID >= 0);
        if (handleID < 0) {
            //这里要标准输出错误
        }
    }

    return handleID;
}

void LogSystem::WriteLog(Log& log) {
    CHandle handleId = GetLogFileHandle(log.m_nTick);
    if (handleId < 0 || log.m_nType == NOT_IN_USE) {
        //这里输出标准错误
        return;
    }
    switch (log.m_nType) {
        case LOG_OUT_CONSOLE:
            cout << log.m_strLog;
            break;
        case LOG_WRITE_TRACE:
        case LOG_WRITE_DEBUG:
        case LOG_WRITE_ERROR:
        {
            int nLength = strlen(log.m_strLog);
            int nSize = write(handleId, log.m_strLog, nLength);
            if (nSize != nLength) {
                //这里输出标准错误
            }
        }
            break;
    }

    return;
}

void * LogSystem::WriteThread(void * args) {
    CHandle handleId = -1;
    Log log;
    while (true) {
        CHashMap<Cthread_id, ILogQueue *>::iterator itor = m_logQueuePool.begin();
        CHashMap<Cthread_id, ILogQueue *>::iterator iend = m_logQueuePool.end();
        while (itor != iend) {
            ILogQueue * pLogQueue = itor->second;
            Assert(pLogQueue != NULL);
            if (NULL == pLogQueue) {
                //这里要输出标准错误
            }
            while (pLogQueue->Out(log)) {
                WriteLog(log);
            }
            itor++;
        }
        if(!m_active) {
            return NULL;
        }
        usleep(1);
    }

    return NULL;
}

bool LogSystem::Trace(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) {
    if (NULL == pStrLog || 0 == strlen(pStrLog) || NULL == pStrFile || NULL == pFunName) {
        Assert(false);
        return false;
    }
    Log log;
    log.m_nType = LOG_WRITE_TRACE;
    UI64 nCrttimetick = GetCurrentTimeTick();
    log.m_nTick = nCrttimetick;
    nCrttimetick /= 1000;
    snprintf(log.m_strLog, LOG_MAX_SIZE, "%s | Trace | FileName : %s | Line : %d | Function : %s | Log : %s \n", \
            ctime((__time_t*) & nCrttimetick), pStrFile, nLine, pFunName, pStrLog);


    if (!AddLog(log)) {
        usleep(1);
        if (!AddLog(log)) {
            Assert(false);
            return false;
        }
    }

    return true;
}

bool LogSystem::Echo(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) {
    if (NULL == pStrLog || 0 == strlen(pStrLog) || NULL == pStrFile || NULL == pFunName) {
        Assert(false);
        return false;
    }
    Log log;
    log.m_nType = LOG_OUT_CONSOLE;
    UI64 nCrttimetick = GetCurrentTimeTick();
    log.m_nTick = nCrttimetick;
    nCrttimetick /= 1000;
    snprintf(log.m_strLog, LOG_MAX_SIZE, "%s | Echo | FileName : %s | Line : %d | Function : %s | Log : %s \n", \
            ctime((__time_t*) & nCrttimetick), pStrFile, nLine, pFunName, pStrLog);

    if (!AddLog(log)) {
        usleep(1);
        if (!AddLog(log)) {
            Assert(false);
            return false;
        }
    }

    return true;
}

bool LogSystem::Debug(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) {
    if (NULL == pStrLog || 0 == strlen(pStrLog) || NULL == pStrFile || NULL == pFunName) {
        Assert(false);
        return false;
    }
    Log log;
    log.m_nType = LOG_WRITE_DEBUG;
    UI64 nCrttimetick = GetCurrentTimeTick();
    log.m_nTick = nCrttimetick;
    nCrttimetick /= 1000;
    snprintf(log.m_strLog, LOG_MAX_SIZE - 1, "%s | Debug | FileName : %s | Line : %d | Function : %s | Log : %s \n", \
            ctime((__time_t*) & nCrttimetick), pStrFile, nLine, pFunName, pStrLog);

    if (!AddLog(log)) {
        usleep(1);
        if (!AddLog(log)) {
            Assert(false);
            return false;
        }
    }

    return true;
}

bool LogSystem::Error(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) {
    if (NULL == pStrLog || 0 == strlen(pStrLog) || NULL == pStrFile || NULL == pFunName) {
        Assert(false);
        return false;
    }
    Log log;
    log.m_nType = LOG_WRITE_ERROR;
    UI64 nCrttimetick = GetCurrentTimeTick();
    log.m_nTick = nCrttimetick;
    nCrttimetick /= 1000;
    snprintf(log.m_strLog, LOG_MAX_SIZE - 1, "%s | Error | FileName : %s | Line : %d | Function : %s | Log : %s \n", \
            ctime((__time_t*) & nCrttimetick), pStrFile, nLine, pFunName, pStrLog);

    if (!AddLog(log)) {
        usleep(1);
        if (!AddLog(log)) {
            Assert(false);
            return false;
        }
    }

    return true;
}



