/* 
 * File:   ILogSystem.h
 * Author: traveler
 *
 * Created on January 3, 2013, 1:25 PM
 */

#ifndef ILOGSYSTEM_H
#define ILOGSYSTEM_H
#include "IBase.h"
#include "../../Public/ComDefine.h"

#define LOG_ECHO(format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        m_pLogSystem->Echo( log , __FILE__, __LINE__, __FUNCTION__); \
    }

#define LOG_TRACE(format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        m_pLogSystem->Trace( log , __FILE__, __LINE__, __FUNCTION__); \
    }
#define LOG_DEBUG(format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        m_pLogSystem->Debug( log , __FILE__, __LINE__, __FUNCTION__); \
    }

#define LOG_ERROR(format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        m_pLogSystem->Error( log , __FILE__, __LINE__, __FUNCTION__); \
    }

class ILogSystem : public IBase {
public:
    virtual bool Trace(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) = 0;
    virtual bool Echo(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) = 0;
    virtual bool Debug(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) = 0;
    virtual bool Error(const char * pStrLog, const char * pStrFile, const UI32 nLine, const char * pFunName) = 0;
};

#endif //ILOGSYSTEM_H