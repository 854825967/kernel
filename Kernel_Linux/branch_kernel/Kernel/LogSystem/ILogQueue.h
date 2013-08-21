/* 
 * File:   ILogQueue.h
 * Author: traveler
 *
 * Created on January 10, 2013, 3:34 PM
 */

#ifndef ILOGQUEUE_H
#define	ILOGQUEUE_H

#include "../../Public/ComDefine.h"
#include <string>
using namespace std;


enum {
    NOT_IN_USE = 0,
    LOG_OUT_CONSOLE,
    LOG_WRITE_TRACE,
    LOG_WRITE_DEBUG,
    LOG_WRITE_ERROR,
};

class Log {
public:
    UI8 m_nType;
    UI64 m_nTick;
    char m_strLog[LOG_MAX_SIZE];

    Log() {
        m_nType = NOT_IN_USE;
        m_nTick = 0;
        m_strLog[LOG_MAX_SIZE-1] = 0;
    }

    inline Log & operator=(const Log & target) {
        m_nType = target.m_nType;
        m_nTick = target.m_nTick;
        snprintf(m_strLog, LOG_MAX_SIZE-1, "%s", target.m_strLog);
        return *this;
    }

};

class ILogQueue {
public:
    virtual bool Out(Log &) = 0; //get log from queue
    virtual bool In(const Log &) = 0; //log in queue
    virtual void Clear() = 0;
};

#endif	/* ILOGQUEUE_H */

