/* 
 * File:   LogSystem.h
 * Author: traveler
 *
 * Created on January 5, 2013, 11:03 AM
 */

#ifndef LOGSYSTEM_H
#define LOGSYSTEM_H

#include "../../Public/ComDefine.h"
#include "../Interface/ILogSystem.h"
#include "../../Public/CHashMap.h"
#include "LogQueue.h"
#include <string>
using namespace std;

#define MAX_SIZE 4096
#define LOGFILE_SEGMENTATION_TIME 15 * 60 * 1000


class LogSystem : public ILogSystem {
public:
    static ILogSystem * Employ();

    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();

    virtual bool Trace(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName);
    virtual bool Echo(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName);
    virtual bool Debug(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName);
    virtual bool Error(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName);
private:
    LogSystem() {
    }
    static bool AddLog(const Log & log);
    static void * WriteThread(void * args);
    static const string GetLogFilePath(UI64 nCurrent);
    static CHandle GetLogFileHandle(const UI64 nCurrentTick);
    static void WriteLog(Log & log);
private:
    static LogSystem * m_pSelf;
    ~LogSystem();
        
    static bool m_active;
    static pthread_t m_writethreadid;
    static UI64 m_nLastCreatLogFileTick;
    static UI64 m_nServerStartTime;
    static CHashMap<Cthread_id, ILogQueue *> m_logQueuePool;
};

#endif	/* LOGSYSTEM_H */

