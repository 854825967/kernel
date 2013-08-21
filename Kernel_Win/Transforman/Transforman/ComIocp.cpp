#include "ComIocp.h"
#include "ConnectionPool.h"
#include "PeerManage.h"
#include "Archive.h"
#include "VarList.h"
#include "Kernel.h"
#include "CoreModuleManage.h"
#include "BaseConfig.h";
#include <iostream>
using namespace std;

ComIocp * ComIocp::m_pSelf = NULL;
CoreModuleManage * ComIocp::m_pCoreModuleManage = NULL;

bool ComIocp::Employ(const char * pStrModuleName) {
    Assert(NULL == m_pSelf);
    if (NULL == m_pSelf) {
        m_pSelf = NEW ComIocp;
        if (NULL == (m_pCoreModuleManage = CoreModuleManage::Employ())) {
            Assert(NULL != m_pCoreModuleManage);
            LOG_ERROR("ComIocp::Employ Get CoreModuleManage error");
            return false;
        }

        if (false == (m_pCoreModuleManage->AddModule(pStrModuleName, m_pSelf))) {
            Assert(false);
            LOG_ERROR("ComIocp::Employ CoreModuleManage::AddModule error");
            return false;
        }
    }

    return true;
}

ComIocp::ComIocp() {
    m_hCompletionPort = NULL;
    m_lpfnAcceptEx = NULL;
    m_pConnectionPool = NULL;
    m_pPeerConfig = NULL;
    m_pKernel = NULL;
}

ComIocp::~ComIocp() {

}

bool ComIocp::Destroy() {
    Assert(NULL != m_pSelf);
    if (NULL != m_pSelf) {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

bool ComIocp::Initialize() {
    WSADATA wsd;   
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0) {
        //打印日志
        Assert(false);
        return false;
    }

    //创建完成端口的句柄  
    if ((m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0)) == NULL) {
        //打印日志
        Assert(false);
        return false;
    }

    //获取AcceptEx函数地址
    if (!GetAcceptExFun(m_lpfnAcceptEx)) {
        //打印日志
        Assert(false);
        return false;
    }

    return true;
}

bool ComIocp::DelayInitialize() {
    if ( NULL == (m_pConnectionPool = (ConnectionPool *)m_pCoreModuleManage->GetModule("ConnectionPool")) ||
        NULL == (m_pPeerConfig = (PeerManage *)m_pCoreModuleManage->GetModule("PeerManage")) ||
        NULL == (m_pKernel = (Kernel *)m_pCoreModuleManage->GetModule("Kernel")) ||
        NULL == (m_pBaseConfig = (BaseConfig *)m_pCoreModuleManage->GetModule("BaseConfig")) 
    ) {
        //这里获取其他模块出错...
        //打印日志
        Assert(false);
        return false;
    }
    return true;
}

bool ComIocp::GetAcceptExFun(LPFN_ACCEPTEX & acceptfun) {
    GUID GuidConnectEx = WSAID_ACCEPTEX;
    DWORD dwBytes;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidConnectEx, 
        sizeof(GuidConnectEx), &acceptfun, sizeof(acceptfun), 
        &dwBytes, NULL, NULL);

    if (NULL == acceptfun) {
        //获取AcceptEx函数出错
        //打印日志
        Assert(false);
        return false;
    }

    return true;
}

bool ComIocp::CListen(const char * pStrPeer, const char * pStrIp, const UI16 nPort) {
    //数据判断
    if (NULL == pStrIp || 0 >= nPort || MAX_PORT < nPort) {
        LOG_ERROR("ComIocp::CListen : Error port or error ip, maybe both");
        Assert(false);
        return false;
    }

    UI32_ID nPeerTypeID = m_pPeerConfig->GetPeerTypeID(pStrPeer);
    if (ERROR_ID == nPeerTypeID) {
        LOG_ERROR("ComIocp::CListen : Unknow peer type");
        Assert(false);
        return false;
    }

    SOCKET acceptSock = SOCKET_ERROR;
    UI32_ID nNewConID = m_pConnectionPool->RegisterConnection(acceptSock, nPeerTypeID);
    SOCKET listenSock =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ERROR_ID == nNewConID || SOCKET_ERROR == acceptSock || SOCKET_ERROR == listenSock) {
        //连接池出错或者侦听socket申请出错
        //答应日志
        Assert(false);
        return false;
    }

    OVERLAPPEDPLUS * pOverlappedPlus = GetNewOverlappedPlus();
    pOverlappedPlus->nOptType = OPT_ACCEPT;
    pOverlappedPlus->nConID = nNewConID;

    sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.S_un.S_addr = inet_addr(pStrIp);
    local.sin_port = htons(nPort);

    if (bind(listenSock, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
        //输入log bind出错
        Assert(false);
        return false;
    }

    ListenInfo * pListenInfo = NEW ListenInfo;
    pListenInfo->socket = listenSock;
    pListenInfo->nPeerTypeID = nPeerTypeID;

    if (m_hCompletionPort != (CreateIoCompletionPort((HANDLE)listenSock, (HANDLE)m_hCompletionPort, (u_long)pListenInfo, 0))) {
        //关联完成端口出错
        //打印日志
        Assert(false);
        return false;
    }

    if (listen( listenSock, 100 ) == SOCKET_ERROR) {
        //listen出错
        //打印日志
        Assert(false);
        return false;
    } 

    //这里使完成端口并不会在连接后返回,而是在连接后第一次接收到消息之后才返回.
    BOOL res = m_lpfnAcceptEx(
        listenSock,
        acceptSock,
        pOverlappedPlus->buff,
        BUFF_SIZE - ((sizeof(sockaddr_in) + 16) * 2),
        sizeof(sockaddr_in) + 16,
        sizeof(sockaddr_in) + 16,
        &pOverlappedPlus->dwBytes, 
        (LPOVERLAPPED)pOverlappedPlus
    );

    I32 nError = WSAGetLastError();
    if (res == FALSE && nError != WSA_IO_PENDING) {
        //异步侦听出错
        //打印日志
        Assert(false);
        return false;
    }

    return true;
}

UI32_ID ComIocp::CConnect(const char * pStrPeer, const char * pStrIp, const UI16 nPort) {
    if (NULL == pStrIp || 0 >= nPort || MAX_PORT < nPort) {
        LOG_ERROR("Error port or error ip, maybe both");
        Assert(false);
        return ERROR_ID;
    }

    UI32_ID nPeerTypeID = m_pPeerConfig->GetPeerTypeID(pStrPeer);
    if (ERROR_ID == nPeerTypeID) {
        LOG_ERROR("Unknow peer type");
        Assert(false);
        return ERROR_ID;
    }

    SOCKET connectSock = SOCKET_ERROR;
    UI32_ID nNewConID = m_pConnectionPool->RegisterConnection(connectSock, nPeerTypeID);
    if (ERROR_ID == nNewConID || SOCKET_ERROR == connectSock) {
        //表示连接池有问题 输出log
        LOG_ERROR("ConnectionPool Error");
        Assert(false);
        return ERROR_ID;
    }

    sockaddr_in service; 
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(pStrIp);
    service.sin_port = htons(nPort);

    ListenInfo * pListenInfo = NEW ListenInfo;
    pListenInfo->socket = SOCKET_ERROR;
    pListenInfo->nPeerTypeID = nPeerTypeID;

    if ((HANDLE)m_hCompletionPort != CreateIoCompletionPort((HANDLE)connectSock, (HANDLE)m_hCompletionPort, (u_long)pListenInfo, 0)) {
        //绑定完成端口出错
        LOG_ERROR("Relate CompletionPort Error");
        Assert(false);
       return ERROR_ID;
    }

    if (SOCKET_ERROR == connect(connectSock, (SOCKADDR*)&service, sizeof(service))) {
        //连接出错
        int nLastError = WSAGetLastError();
        LOG_ERROR("Failed to connect NoticServer");
        Assert(false);
        return ERROR_ID;
    }

    VarList args;
    m_pPeerConfig->ExecEventCallBack(nPeerTypeID, EVENT_CONNECT, m_pKernel, nNewConID, args);

    OVERLAPPEDPLUS * pNewOverlappedPlus = GetNewOverlappedPlus();
    pNewOverlappedPlus->nConID = nNewConID;
    pNewOverlappedPlus->nOptType = OPT_READ;

    if ( SOCKET_ERROR == WSARecv(
        connectSock,
        &pNewOverlappedPlus->wBuf, 
        1, 
        &pNewOverlappedPlus->dwBytes, 
        &pNewOverlappedPlus->dwFlags, 
        (LPWSAOVERLAPPED)pNewOverlappedPlus, 
        NULL)
    ) {
        int nLastError = WSAGetLastError();
        if (nLastError != WSA_IO_PENDING) {
            //输出log 提示在异步接收时出错
            DestroyOverlappedplus(pNewOverlappedPlus);
        }
    }

    return nNewConID;
}

bool ComIocp::CSend(UI32_ID nConID, const void * pBuff, DWORD nIOBytes)
{
    OVERLAPPEDPLUS * pOverlappedPlus = GetNewOverlappedPlus();
    pOverlappedPlus->nOptType = OPT_WRITE;
    pOverlappedPlus->nConID = nConID;
    pOverlappedPlus->wBuf.len = nIOBytes;
    pOverlappedPlus->wBuf.buf = (char *)pBuff;

    DWORD dwRecvBytes=0, dwFlags = 0;

    if (SOCKET_ERROR == WSASend(m_pConnectionPool->GetSocket(nConID), &pOverlappedPlus->wBuf, 1, &dwRecvBytes, dwFlags, (LPWSAOVERLAPPED)pOverlappedPlus, NULL)) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
            printf("Error occured at WSASend()\n");
            DestroyOverlappedplus(pOverlappedPlus);
        }
    }

    return true;
}

void ComIocp::CWork() {
    ListenInfo * pListenInfo;   
    OVERLAPPEDPLUS * pOverlappedPlus;   
    DWORD nIOBytes; 

    while(true) {   
        I32 nIores = GetQueuedCompletionStatus(m_hCompletionPort, &nIOBytes, (PULONG_PTR)&pListenInfo, (LPOVERLAPPED *)&pOverlappedPlus, INFINITE);   

        if (NULL == pOverlappedPlus) {
            continue;
        }

        UI8_TYPE nOptType = pOverlappedPlus->nOptType;

        if (ERROR_SUCCESS == nIores && WSAGetLastError() != 0) {
            DestroyOverlappedplus(pOverlappedPlus);
        }

        if (OPT_WRITE == nOptType)
        {
            continue;
        }

        switch (nOptType) {
            case OPT_READ: {
                if (NULL == pOverlappedPlus) {
                    continue;
                }

                UI32_ID nConID = pOverlappedPlus->nConID;
                SOCKET connectSock = m_pConnectionPool->GetSocket(nConID);

                m_pConnectionPool->WriteConStream(nConID, pOverlappedPlus->wBuf.buf, nIOBytes);
                Archive archive;
                while (m_pConnectionPool->ReadArchiveFromCon(nConID, archive)) {
                    VarList args;
                    archive.FormartToVarList(args);
                    if (args.Type(0) != TYPE_INT) {
                        continue;
                    }
                    UI32_ID nMsgID = args.GetInt(0);
                    m_pPeerConfig->ExecMsgCallBack(pListenInfo->nPeerTypeID, nMsgID, m_pKernel, nConID, args);
                    archive.Clear();
                }

                if ( SOCKET_ERROR == WSARecv(
                        connectSock,
                        &pOverlappedPlus->wBuf, 
                        1, 
                        &pOverlappedPlus->dwBytes, 
                        &pOverlappedPlus->dwFlags, 
                        (LPWSAOVERLAPPED)pOverlappedPlus, 
                        NULL)
                ) {
                    int nLastError = WSAGetLastError();
                    if (nLastError != WSA_IO_PENDING) {
                        //输出log 提示在异步接收时出错
                        DestroyOverlappedplus(pOverlappedPlus);
                    }
                }
                break;
            }

            case OPT_ACCEPT: {
                SOCKET acceptSock = SOCKET_ERROR;
                UI32_ID nNewConID = m_pConnectionPool->RegisterConnection(acceptSock, pListenInfo->nPeerTypeID);
                SOCKET listenSock =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                if (ERROR_ID == nNewConID || SOCKET_ERROR == acceptSock || SOCKET_ERROR == listenSock) {
                    //连接池出错或者侦听socket申请出错
                    //答应日志
                    Assert(false);
                }

                OVERLAPPEDPLUS * pNewOverlappedPlus = GetNewOverlappedPlus();
                pNewOverlappedPlus->nOptType = OPT_ACCEPT;
                pNewOverlappedPlus->nConID = nNewConID;

                BOOL res = m_lpfnAcceptEx(
                    pListenInfo->socket,
                    acceptSock,
                    pNewOverlappedPlus->buff,
                    BUFF_SIZE - ((sizeof(sockaddr_in) + 16) * 2),
                    sizeof(sockaddr_in) + 16,
                    sizeof(sockaddr_in) + 16,
                    &pNewOverlappedPlus->dwBytes, 
                    (LPOVERLAPPED)pNewOverlappedPlus
                );

                if (NULL == pOverlappedPlus) {
                    continue;
                }

                UI32_ID nConID = pOverlappedPlus->nConID;
                SOCKET connectSock = m_pConnectionPool->GetSocket(nConID);

                m_pConnectionPool->WriteConStream(nConID, pOverlappedPlus->wBuf.buf, nIOBytes);
                Archive archive;
                while (m_pConnectionPool->ReadArchiveFromCon(nConID, archive)) {
                    VarList args;
                    archive.FormartToVarList(args);
                    m_pPeerConfig->ExecEventCallBack(pListenInfo->nPeerTypeID, EVENT_NEW_CONNECT, m_pKernel, nConID, args);
                    archive.Clear();
                }

                pOverlappedPlus->nOptType = OPT_READ;
                if ( SOCKET_ERROR == WSARecv(
                        connectSock,
                        &pOverlappedPlus->wBuf, 
                        1, 
                        &pOverlappedPlus->dwBytes, 
                        &pOverlappedPlus->dwFlags, 
                        (LPWSAOVERLAPPED)pOverlappedPlus, 
                        NULL
                    )
                ) {
                    int nLastError = WSAGetLastError();
                    if (nLastError != WSA_IO_PENDING) {
                        //输出log 提示在异步接收时出错
                        DestroyOverlappedplus(pOverlappedPlus);
                    }
                }
                break;
            }

            case OPT_WRITE: {
                delete pOverlappedPlus;
                break;
            }
        }
    }   

    return;
}

inline void ComIocp::DestroyOverlappedplus(OVERLAPPEDPLUS * & pOverlapPlus) {
    if (NULL == pOverlapPlus) {
        return ;
    }
    m_pConnectionPool->RecoverConnection(pOverlapPlus->nConID);
    delete pOverlapPlus;
    pOverlapPlus = NULL;
}
