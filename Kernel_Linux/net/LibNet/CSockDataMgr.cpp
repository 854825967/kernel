#include "CSockDataMgr.h"
#include <algorithm>

CSockDataMgr::CSockDataMgr(const u16 size) {
    m_pSockDataArray = NEW SockData[size];
    m_nMaxCount = size;
    m_nCurrentMark = 1;
    m_IdRecycleBin.clear();
}

CSockDataMgr::~CSockDataMgr() {
    if(m_pSockDataArray != NULL) {
        delete[] m_pSockDataArray;
        m_pSockDataArray = NULL;
    }
}

SockData * CSockDataMgr::CreateSockData() {

    SockData * pSockData = NULL;
    if (m_IdRecycleBin.empty()) {
        if(m_nCurrentMark > m_nMaxCount) {
            ECHO_ERROR("SockPlus Pool is full, current count : %d", m_nCurrentMark);
            return NULL;
        }
        pSockData = m_pSockDataArray + m_nCurrentMark++ - 1;
        pSockData->m_id = m_nCurrentMark - 1;
    } else {
        LIST_ID::iterator itor = m_IdRecycleBin.begin();
        pSockData = m_pSockDataArray + *itor - 1;
        pSockData->m_id = *itor;
        m_IdRecycleBin.erase(itor);
    }

    return pSockData;
}

SockData * CSockDataMgr::QuerySockPlus(const u16 id) {
    if(!m_IdRecycleBin.empty()) {
        LIST_ID::iterator iend = m_IdRecycleBin.end();
        LIST_ID::iterator ifind = ::find(m_IdRecycleBin.begin(), iend, id);
        if (ifind != iend) {
            ECHO_WARN("Cant find the sockdata witch id is %d", id);
            return NULL;
        }
    }

    if (id >= m_nCurrentMark) {
        ASSERT(false);
        return NULL;
    }

    return m_pSockDataArray + id - 1;
}

void CSockDataMgr::RecoveSockData(SockData * pSockData) {

    pSockData->ClearBuff();
    m_IdRecycleBin.push_back(pSockData->m_id);

}