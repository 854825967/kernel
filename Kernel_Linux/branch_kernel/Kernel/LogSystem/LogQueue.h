/* 
 * File:   LogQueue.h
 * Author: traveler
 *
 * Created on January 10, 2013, 3:03 PM
 */

#ifndef LOGQUEUE_H
#define	LOGQUEUE_H

#include "ILogQueue.h"

template<UI32 SIZE = 4096 >
        class LogQueue : public ILogQueue { //你这里思考下 为什么要继承一个ILogQueue,并不完全是位了统一接口
public:

    LogQueue() {
        m_nCrtOut = 0;
        m_nCrtIn = 0;
    }

    virtual bool Out(Log & log) {
        if (m_nCrtOut >= SIZE) {
            m_nCrtOut = 0;
        }
        if (NOT_IN_USE == m_logpool[m_nCrtOut].m_nType ) {
            return false;
        }

        log = m_logpool[m_nCrtOut];
        m_logpool[m_nCrtOut].m_nType = NOT_IN_USE;
        m_nCrtOut++;
        return true;
    }

    virtual bool In(const Log & log) {
        if(log.m_nType == NOT_IN_USE) {
            Assert(false);
            return false;
        }
        if (m_nCrtIn >= SIZE) {
            m_nCrtIn = 0;
        }
        if (NOT_IN_USE != m_logpool[m_nCrtIn].m_nType) {
            return false;
        }
        
        m_logpool[m_nCrtIn] = log;
        m_nCrtIn++;
        return true;
    }

    virtual void Clear() {

    }

    ~LogQueue() {

    }
private:
    Log m_logpool[SIZE];
    UI32 m_nCrtOut; //position about current out
    UI32 m_nCrtIn; //position about current in
};

#endif	/* LOGQUEUE_H */

