#include "ConnectionPool.h"
#include "BaseConfig.h"
#include "CoreModuleManage.h"

ConnectionPool * ConnectionPool::m_pSelf = NULL;
CoreModuleManage * ConnectionPool::m_pCoreModuleManage = NULL;

bool ConnectionPool::Employ(const char * pStrModuleName) {
    Assert(NULL == m_pSelf);
    if (NULL == m_pSelf) {
        m_pSelf = NEW ConnectionPool;
        if (NULL == (m_pCoreModuleManage = CoreModuleManage::Employ())) {
            Assert(NULL != m_pCoreModuleManage);
            LOG_ERROR("ConnectionPool::Employ Get CoreModuleManage error");
            return false;
        }

        if (false == (m_pCoreModuleManage->AddModule(pStrModuleName, m_pSelf))) {
            Assert(false);
            LOG_ERROR("ConnectionPool::Employ CoreModuleManage::AddModule error");
            return false;
        }
    }

    return true;
}

ConnectionPool::ConnectionPool() {
    m_pBaseConfig = NULL;
    m_pConInfo = NULL;
    m_nMaxConCount = 0;
    m_nMaxClientCount = 0;
    m_nConCurrent = 0;
    m_vctRecycleBin.clear();
}

ConnectionPool::~ConnectionPool() {
    if (NULL != m_pConInfo) {
        delete[] m_pConInfo;
        m_pConInfo = NULL;
    }

    m_vctRecycleBin.clear();
}

bool ConnectionPool::Destroy() {
    Assert(NULL != m_pSelf);
    if (NULL != m_pSelf) {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

bool ConnectionPool::Initialize() {
    return true;
}

bool ConnectionPool::DelayInitialize() {    
    if (NULL == (m_pBaseConfig = (BaseConfig *)m_pCoreModuleManage->GetModule("BaseConfig"))) {
        Assert(false);
        return false;
    }

    m_nMaxClientCount = m_pBaseConfig->m_nMaxClientCount;
    m_nMaxConCount = m_pBaseConfig->m_nMaxConnectionCount;
    m_pConInfo = NEW ConnectionInfo[m_nMaxConCount];
    if (NULL == m_pConInfo) {
        //打印日志
        return false;
    }

    for (UI32 i=0; i<m_nMaxConCount; i++) {
        m_pConInfo[i].bInUse = false;
        m_pConInfo[i].connectSock = SOCKET_ERROR;
    }

    return true;
}

const UI32_ID ConnectionPool::QueryPeerTypeID(const UI32 nConID)
{
    if (nConID >= m_nMaxConCount || false == m_pConInfo[nConID].bInUse) {
        //输出日志 提示ID无效
        return ERROR_ID;
    }
    
    return m_pConInfo[nConID].nPeerTypeID;
}

bool ConnectionPool::RecordIpAndPort(UI32_ID nConID) {
    if (nConID >= m_nMaxConCount || false == m_pConInfo[nConID].bInUse) {
        //输出日志 提示ID无效
        return false;
    }

    struct sockaddr_in peerAddr;
    int nLen = sizeof(peerAddr);
    int nRes = getpeername(m_pConInfo[nConID].connectSock, (struct sockaddr *)&peerAddr, &nLen);
    if (0 != nRes) {
        //LOG
        return false;
    }

    m_pConInfo[nConID].nIP = peerAddr.sin_addr.S_un.S_addr;
    m_pConInfo[nConID].nPort = peerAddr.sin_port;

    return true;
}

bool ConnectionPool::RecoverConnection(UI32_ID nConID) {
    if (nConID >= m_nMaxConCount || false == m_pConInfo[nConID].bInUse) {
        //输出日志 提示要回收的ID无效
        return false;
    }

    closesocket(m_pConInfo[nConID].connectSock);
    m_pConInfo[nConID].bInUse = false;
    m_vctRecycleBin.push_back(nConID);
    m_nConCurrent--;

    return true;
}

UI32_ID ConnectionPool::RegisterConnection(SOCKET & sock, UI32_ID nPeerTypeID) {
    UI32_ID nID = ERROR_ID;

    if (!m_vctRecycleBin.empty()) {
        nID = m_vctRecycleBin[HEAD];
        m_vctRecycleBin.erase(m_vctRecycleBin.begin());
        m_nConCurrent++;
    } else {
        if (m_nConCurrent >= m_nMaxConCount) {
            //输出日志 表示连接池已经满了
            sock = SOCKET_ERROR;
            return ERROR_ID;
        }

        nID = m_nConCurrent++;       
    }
    m_pConInfo[nID].connectSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    m_pConInfo[nID].bInUse = true;
    m_pConInfo[nID].recvStream.Clear();
    m_pConInfo[nID].nPeerTypeID = nPeerTypeID;
    sock = m_pConInfo[nID].connectSock;

    return nID;
}

bool ConnectionPool::WriteConStream(UI32_ID nConID, void * pBuff, UI32 nLen) {
    if (NULL == pBuff || 0 == nLen) {
        return false;
    }

    if (nConID >= m_nMaxConCount || false == m_pConInfo[nConID].bInUse) {
        //输出日志 提示连接ID无效
        return false;
    }

    return m_pConInfo[nConID].recvStream.WriteBuff(pBuff, nLen);
}

bool ConnectionPool::ReadArchiveFromCon(UI32_ID nConID, Archive & archive) {
    if (nConID >= m_nMaxConCount || false == m_pConInfo[nConID].bInUse) {
        //输出日志 提示连接ID无效
        return false;
    }

    return m_pConInfo[nConID].recvStream.ReadArchive(archive);
}

bool ConnectionPool::SavePeerInfo(const UI32_ID nConID, const UI32_ID nAppID, const UI32_ID nClusterID, const UI32_ID nServerID, const UI32_ID nIdentity) {

    return true;
}

const UI32_ID ConnectionPool::GetPeerAppID(const UI32_ID nConID) {

    return ERROR_ID;
}

const UI32_ID ConnectionPool::GetPeerClusterID(const UI32_ID nConID) {

    return ERROR_ID;
}

const UI32_ID ConnectionPool::GetPeerServerID(const UI32_ID nConID) {

    return ERROR_ID;
}

const UI32_ID ConnectionPool::GetPeerIdentity(const UI32_ID nConID) {

    return ERROR_ID;
}
