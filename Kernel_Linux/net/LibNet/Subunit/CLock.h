#ifndef CAUTOLOCK_H
#define CAUTOLOCK_H

#include "MultiSys.h"

struct CLockUtil {
    CLockUtil() {
        ::InitializeCriticalSection(&m_lock);
    }

    ~CLockUtil() {
        ::DeleteCriticalSection(&m_lock);
    }

    void Lock() {
        ::EnterCriticalSection(&m_lock);
    }

    void UnLock() {
        ::LeaveCriticalSection(&m_lock);
    }

    bool TryLock() {
        ::TryEnterCriticalSection(&m_lock);
    }

private:
    CRITICAL_SECTION m_lock;
};

class CAutoLock {
public:
    CAutoLock(CLockUtil * pLock) {
        ASSERT(pLock != NULL);
        m_pLock = pLock;
        m_pLock->Lock();
    }

    ~CAutoLock() {
        m_pLock->UnLock();
    }

private:
    CLockUtil * m_pLock;
};

#endif