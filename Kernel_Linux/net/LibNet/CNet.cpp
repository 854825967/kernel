#include "CNet.h"
#include "WinTools.h"
#include "CInetAddress.h"
#include "CSockDataMgr.h"

CNet::CNet(const u8 threadcount, const u16 linkcount) {

    m_pFunAcceptEx = NULL;
    m_pFunConnectEx = NULL;
    GetAcceptExFun(m_pFunAcceptEx);
    GetConnectExFun(m_pFunConnectEx);
    ASSERT(m_pFunAcceptEx != NULL && m_pFunConnectEx != NULL);

    m_pSockDataMgr = NEW CSockDataMgr(linkcount);
    m_nNetThreadCount = 1;
    m_pRecvFun = NULL;
    m_pConnectedFun = NULL;
    m_endIocp = FALSE;
    if ((m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL) {
        ECHO_ERROR("CreateIoCompletionPort error, error code %s", GetLastError());
        return;
    }
}


CNet::~CNet() {
    if(m_pSockDataMgr != NULL) {
        delete m_pSockDataMgr;
        m_pSockDataMgr = NULL;
    }
}

void CNet::CStartLoop() const {
    for(u32 i=0; i<m_nNetThreadCount; i++) {
        HANDLE hThread = ::CreateThread(NULL, 0, CNet::CLoop, (LPVOID)this, 0, NULL);
        CloseHandle(hThread);
    }
}

void CNet::CSetNetThreadCount(const u8 count) {
    m_nNetThreadCount = count;
}

DWORD WINAPI CNet::CLoop(LPVOID p) {
    ASSERT(p != NULL);
    CNet * pThis = (CNet *)p;
    DWORD nIOBytes = 0;
    BOOL end = 0;
    BOOL nSucceed;
    SockPlus * pSockPlus = NULL;

    while (true)
    {
        nSucceed = ::GetQueuedCompletionStatus(pThis->m_hCompletionPort, &nIOBytes, (PULONG_PTR)&end, (LPOVERLAPPED *)&pSockPlus, 50);

        if(NULL == pSockPlus) {
            continue;
        }

        int nError = ::GetLastError();
        int nWSAError = ::WSAGetLastError();

        if (!nSucceed) {
            if (WAIT_TIMEOUT == nError) {
                continue;
            }
        }


        switch(pSockPlus->m_events) {
            case EVENT_ACCEPT:
                break;
            case EVENT_CONNECT:
                if (ERROR_CONNECTION_REFUSED == nWSAError) {
                    ECHO_WARN("Connection refused, remote ip %s port %d", pSockPlus->m_pSockData->m_address.GetIp(), pSockPlus->m_pSockData->m_address.GetPort());
                    continue;
                }
                break;
            case EVENT_RECV:
                if (0 == nIOBytes) {
                    if (WSA_IO_PENDING != nWSAError) {
                        ECHO_WARN("Link has broken, error code %d", ::GetLastError());
                        pThis->CloseSockPlus(pSockPlus);
                        pSockPlus = NULL;
                        continue;
                    }
                }
                break;
            case EVENT_SEND:
                break;
        }

        

        if (TRUE == end) {
            ECHO_TRACE("Iocp End");
            break;
        }

        if (nSucceed) {
            pThis->CNetEvent(pSockPlus, nIOBytes);
        }

    }

    return 0;
}

void CNet::CNetEvent(SockPlus * pSockPlus, const u32 nSize) const {

    switch (pSockPlus->m_events) {
        case EVENT_RECV:
            CRecv(pSockPlus, nSize);
            break;
        case EVENT_SEND:
            CSend(pSockPlus, nSize);
            break;
        case EVENT_ACCEPT:
            {
                CAccept(pSockPlus->m_pSockData->m_listenSock);

                if (SOCKET_ERROR == ::setsockopt(pSockPlus->m_pSockData->m_sock, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, 
                    (const char*)&pSockPlus->m_pSockData->m_listenSock, sizeof(pSockPlus->m_pSockData->m_listenSock))) {
                    ECHO_ERROR("setsockopt error, last error code : %d", GetLastError());
                    CloseSockPlus(pSockPlus);
                    pSockPlus = NULL;
                    return;
                }
                int len = sizeof(sockaddr);

                if (0 > ::getpeername(pSockPlus->m_pSockData->m_sock, (sockaddr *)&(pSockPlus->m_pSockData->m_address), &len)) {
                    ECHO_ERROR("getpeername error, last error code : %d", GetLastError());
                    CloseSockPlus(pSockPlus);
                    pSockPlus = NULL;
                    return;
                }

                ECHO_TRACE("New Remote connected in, IP %s, port %d, connect id %d", 
                    pSockPlus->m_pSockData->m_address.GetIp(), pSockPlus->m_pSockData->m_address.GetPort(), pSockPlus->m_pSockData->m_id);

                pSockPlus->m_events = EVENT_RECV;
                if (SOCKET_ERROR == ::WSARecv(pSockPlus->m_pSockData->m_sock, &pSockPlus->m_wBuf, 1, &pSockPlus->m_dwBytes, &pSockPlus->m_dwFlags, (LPWSAOVERLAPPED)pSockPlus, NULL)) {
                    s32 nRes = ::WSAGetLastError();
                    if (WSA_IO_PENDING != nRes) {
                        ECHO_ERROR("WSARecv error, error code %d", nRes);
                        CloseSockPlus(pSockPlus);
                        pSockPlus = NULL;
                        return;
                    }
                }
            }
            break;
        case EVENT_CONNECT:
            CConnect(pSockPlus);
            break;
    }
}

inline void CNet::CloseSockPlus(SockPlus * pSockPlus) const {
    closesocket(pSockPlus->m_pSockData->m_sock);
    m_pSockDataMgr->RecoveSockData(pSockPlus->m_pSockData);
    delete pSockPlus;
    pSockPlus = NULL;
}

bool CNet::CGetRemoteInfo(const u16 conid, const char * & ip, u16 & port) const {
    SockData * pSockData = m_pSockDataMgr->QuerySockPlus(conid);
    if(NULL == pSockData) {
        ECHO_WARN("the con is not exists, conid : %d", conid);
        return false;
    }

    ip = pSockData->m_address.GetIp();
    port = pSockData->m_address.GetPort();

    return true;
}

void CNet::CConnect(SockPlus * pSockPlus) const {
    if (m_pConnectedFun != NULL) {
        m_pConnectedFun(pSockPlus->m_pSockData->m_id, pSockPlus->m_wBuf.buf, pSockPlus->m_wBuf.len);
    } else {
        ECHO_ERROR("Do you fogot set connected callback fun???");
    }

    memset(pSockPlus->m_buff, 0, BUFF_SIZE);
    pSockPlus->m_wBuf.len = BUFF_SIZE;

    pSockPlus->m_events = EVENT_RECV;
    if (SOCKET_ERROR == ::WSARecv(pSockPlus->m_pSockData->m_sock, &pSockPlus->m_wBuf, 1, &pSockPlus->m_dwBytes, &pSockPlus->m_dwFlags, (LPWSAOVERLAPPED)pSockPlus, NULL)) {
        s32 nRes = ::WSAGetLastError();
        if (WSA_IO_PENDING != nRes) {
            ECHO_ERROR("WSARecv error,error code %d", nRes);
            CloseSockPlus(pSockPlus);
            pSockPlus = NULL;
            return;
        }
    }
}


bool CNet::CConnectEx(const char * ip, const u16 port, const char * buff, const u32 size) const {

    if (NULL == m_pFunConnectEx) {
        ECHO_ERROR("ConnectEx fun is null");
        return false;
    }

    SockData * pSockData = m_pSockDataMgr->CreateSockData();
    if (INVALID_SOCKET == (pSockData->m_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED)) ) {
        ECHO_ERROR("WSASocket error, last error code : %d", GetLastError());
        m_pSockDataMgr->RecoveSockData(pSockData);
        return false;
    } 

    if (!pSockData->m_address.SetIp(ip)) {
        ECHO_ERROR("Set Remote ip error, Remote ip %s, Remote port %d", ip, port);
        return 0;
    }
    pSockData->m_address.SetPort(port);

    CInetAddress address;
    if (SOCKET_ERROR == ::bind(pSockData->m_sock, (sockaddr *)&address, sizeof(sockaddr_in))) {
        ECHO_ERROR("Bind error, socket : %d, last error code : %d", pSockData->m_sock, GetLastError());
        return false;
    }
    
    if (m_hCompletionPort != ::CreateIoCompletionPort((HANDLE)pSockData->m_sock, m_hCompletionPort, (u_long)m_endIocp, 0)) {
        ECHO_ERROR("CreateIoCompletionPort error, error code %d", GetLastError());
        m_pSockDataMgr->RecoveSockData(pSockData);
        return false;
    }

    SockPlus * pSockPlus = NEW SockPlus;
    pSockPlus->m_pSockData = pSockData;
    pSockPlus->m_events = EVENT_CONNECT;
    pSockPlus->m_wBuf.buf = pSockPlus->m_buff;
    if (size >= BUFF_SIZE) {
        memcpy(pSockPlus->m_buff, buff, BUFF_SIZE - 1);
        pSockPlus->m_buff[BUFF_SIZE - 1] = 0;
        pSockPlus->m_wBuf.len = BUFF_SIZE - 1;
    } else {
        memcpy(pSockPlus->m_buff, buff, size);
        pSockPlus->m_wBuf.len = size;
    }


    u32 nResult = m_pFunConnectEx(pSockData->m_sock, (sockaddr *)&pSockData->m_address, sizeof(sockaddr_in), NULL, 0, &pSockPlus->m_dwBytes, (LPOVERLAPPED)pSockPlus);
    s32 nError = WSAGetLastError();
    if (nResult == FALSE && nError != WSA_IO_PENDING) {
        ECHO_ERROR("ConnectEx error,error code %d", nError);
        CloseSockPlus(pSockPlus);
        pSockPlus = NULL;
        return false;
    }

    return true;
}


bool CNet::CListen(const char * ip, const u16 port, const u16 count) const {
    //这里要分配sockplus
    CInetAddress address(ip, port);

    SOCKET lisnSock = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (INVALID_SOCKET == lisnSock) {
        ECHO_ERROR("Get error, last error code : %d", GetLastError());
        return false;
    }

    int len = 8192;

    if (SOCKET_ERROR == ::setsockopt(lisnSock, SOL_SOCKET, SO_SNDBUF, (char *)&len, sizeof(int))) {
        closesocket(lisnSock);
        ECHO_ERROR("setsockopt error, last error code : %d", GetLastError());
        return false;
    }

    if (SOCKET_ERROR == ::setsockopt(lisnSock, SOL_SOCKET, SO_RCVBUF, (char *)&len, sizeof(int))) {
        closesocket(lisnSock);
        ECHO_ERROR("setsockopt error, last error code : %d", GetLastError());
        return false;
    }

    if (SOCKET_ERROR == ::bind(lisnSock, (sockaddr*)&address, sizeof(sockaddr_in))) {
        ECHO_ERROR("Bind error, last error code : %d", GetLastError());
        return false;
    }
    if (::listen(lisnSock, count) == SOCKET_ERROR) {
        ECHO_ERROR("Listen error, last error code : %d", GetLastError());
        return false;
    } 

    if (m_hCompletionPort != (CreateIoCompletionPort((HANDLE)lisnSock, (HANDLE)m_hCompletionPort, (u_long)m_endIocp, 0))) {
        ECHO_ERROR("CreateIoCompletionPort error, error code %d", GetLastError());
        return false;
    }

    ECHO_TRACE("Start a listen sock, ip : %s, port : %d, socket : %d", ip, port, lisnSock);

    CAccept(lisnSock);


    return true;
}

void CNet::CAccept(SOCKET sock) const {
    if (NULL == m_pFunAcceptEx) {
        ECHO_ERROR("Accept Fun address is NULL");
        return;
    }

    SockData * pSockData = m_pSockDataMgr->CreateSockData();
    if(NULL == pSockData) {
        ECHO_ERROR("Get SockData error");
        return;
    }
    if (INVALID_SOCKET == (pSockData->m_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED))) {
        ECHO_ERROR("Get error, last error code : %d", GetLastError());
        return;
    }
    pSockData->m_listenSock = sock;

    SockPlus * pSockPlus = NEW SockPlus;
    pSockPlus->m_events = EVENT_ACCEPT;
    pSockPlus->m_pSockData = pSockData;

    if (m_hCompletionPort != (CreateIoCompletionPort((HANDLE)pSockPlus->m_pSockData->m_sock, (HANDLE)m_hCompletionPort, (u_long)0, 0))) {
        ECHO_ERROR("CreateIoCompletionPort error, error code %d", GetLastError());
        CloseSockPlus(pSockPlus);
        pSockPlus = NULL;
        return;
    }

    BOOL result = m_pFunAcceptEx(
        sock,
        pSockPlus->m_pSockData->m_sock,
        pSockPlus->m_buff,
        0,
        sizeof(sockaddr_in) + 16,
        sizeof(sockaddr_in) + 16,
        &pSockPlus->m_dwBytes, 
        (LPOVERLAPPED)pSockPlus
    );

    s32 nError = WSAGetLastError();
    if (result == FALSE && nError != WSA_IO_PENDING) {
        ECHO_ERROR("AcceptEx error,error code %d", nError);
        CloseSockPlus(pSockPlus);
        pSockPlus = NULL;
        return;
    }
}

void CNet::CSend(SockPlus * pSockPlus, const u32 nSize) const {
    pSockPlus->m_pSockData->Out(nSize);

    u32 nLeaveSize = 0;
    pSockPlus->m_pSockData->GetBuff(nLeaveSize);
    if (0 == nLeaveSize) {
        delete pSockPlus;
        return;
    }

    pSockPlus->m_wBuf.buf = (char *)pSockPlus->m_pSockData->GetBuff((u32&)pSockPlus->m_wBuf.len);
    u32 nResult = ::WSASend(pSockPlus->m_pSockData->m_sock, &pSockPlus->m_wBuf, 1, NULL, 0, (LPWSAOVERLAPPED)pSockPlus, NULL);
    if (SOCKET_ERROR == nResult) {
        nResult = ::WSAGetLastError();
        if (nResult != WSA_IO_PENDING) {
            ECHO_WARN("WSASend error,error code %d", nResult);
            CloseSockPlus(pSockPlus);
            pSockPlus = NULL;
        }
    }

    
}

void CNet::CRecv(SockPlus * pSockPlus, const u32 nRecvSize) const {

    if (NULL == m_pRecvFun) {
        ECHO_WARN("Do you fogot set Recv callback fun???");
    } else {
        m_pRecvFun(pSockPlus->m_pSockData->m_id, pSockPlus->m_wBuf.buf, nRecvSize);
    }

    if (SOCKET_ERROR == ::WSARecv(pSockPlus->m_pSockData->m_sock, &pSockPlus->m_wBuf, 1, &pSockPlus->m_dwBytes, &pSockPlus->m_dwFlags, (LPWSAOVERLAPPED)pSockPlus, NULL)) {
        s32 res = ::WSAGetLastError();
        if (WSA_IO_PENDING != res) {
            ECHO_WARN("WSARecv error, error code %d", res);
            CloseSockPlus(pSockPlus);
            pSockPlus = NULL;
            return;
        }
    }
}

bool CNet::CSendMsg(const u16 conid, char * buff, const u16 size) const {
    SockData * pSockData = m_pSockDataMgr->QuerySockPlus(conid);
    if (NULL == pSockData) {
        ECHO_WARN("Cant find connection %d", conid);
        return false;
    }

    u32 nSize = 0;
    char * pBuff = pSockData->GetBuff(nSize);
    if ( !pSockData->SendBuff(buff, size) ) {
        ECHO_WARN("Send Data Error, Cant copy buf to send pool");
        return false;
    }

    if(0 == nSize) {
        SockPlus * pSockPlus = NEW SockPlus;

        pSockPlus->m_events = EVENT_SEND;
        pSockPlus->m_pSockData = pSockData;
        pSockPlus->m_wBuf.buf = (char *)pSockData->GetBuff((u32&)pSockPlus->m_wBuf.len);
        u32 nResult = ::WSASend(pSockData->m_sock, &pSockPlus->m_wBuf, 1, NULL, 0, (LPWSAOVERLAPPED)pSockPlus, NULL);

        if (SOCKET_ERROR == nResult) {
            nResult = ::WSAGetLastError();
            if (nResult != WSA_IO_PENDING) {
                ECHO_WARN("WSASend error, error code %d", nResult);
                CloseSockPlus(pSockPlus);
                pSockPlus = NULL;
            }
        }
    }

    return true;
}

bool CNet::CSetRecvCall(const CALL_FUN precvfun) {
    if (NULL == precvfun) {
        ECHO_ERROR("RecvFun address is NULL");
        return false;
    }
    m_pRecvFun = precvfun;
    return true;
}

bool CNet::CClose(const u16 conid) const {

    return false;
}

bool CNet::CSetConnectedCall(const CALL_FUN pcntedfun) {
    if (NULL == pcntedfun) {
        ECHO_ERROR("ConnectedFun address is NULL");
        return false;
    }
    m_pConnectedFun = pcntedfun;
    return true;
}
