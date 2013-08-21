#ifndef _COMIOCP_H_
#define _COMIOCP_H_

#include <map>
using namespace std;

#include "ComDefine.h" 
#include "ICoreModule.h"

#define LISTEN_PORT 10300
#define BUFF_SIZE 4096

class IKernel;
class ConnectionPool;
class Archive;
class PeerManage;
class CoreModuleManage;
class BaseConfig;

enum OptionType
{
    OPT_READ = 0,
    OPT_WRITE = 1,
    OPT_ACCEPT = 2,
    OPT_CONNECT = 3,
};

typedef struct _listeninfo 
{
    SOCKET socket;
    UI32_ID nPeerTypeID;
}ListenInfo;

typedef struct _overlappedplus
{   
    OVERLAPPED overlapped;  //不解释
    UI32_ID nConID;            //当前连接池的ID
    UI8 nOptType;           //操作类型 连接? 收发? 等等
    WSABUF wBuf;
    DWORD dwBytes, dwFlags;
    char buff[BUFF_SIZE];
}OVERLAPPEDPLUS;

inline OVERLAPPEDPLUS * GetNewOverlappedPlus() {
    OVERLAPPEDPLUS * pNewOverlappedPlus = NEW OVERLAPPEDPLUS;
    memset(pNewOverlappedPlus, 0, sizeof(OVERLAPPEDPLUS));
    pNewOverlappedPlus->dwBytes = 0;
    pNewOverlappedPlus->dwFlags = 0;
    pNewOverlappedPlus->wBuf.len = BUFF_SIZE;
    pNewOverlappedPlus->wBuf.buf = pNewOverlappedPlus->buff;

    return pNewOverlappedPlus;
}

typedef struct _ipport 
{
    string ip;
    UI16 port;

    struct _ipport & operator=(struct _ipport & _target)
    {
        ip = _target.ip;
        port = _target.port;
        return *this;
    }

}IPPORT;

class ComIocp : public ICoreModule
{
public:
    static bool Employ(const char * pStrModuleName);
    virtual bool Initialize();
    virtual bool DelayInitialize();
    virtual bool Destroy();

public:
    bool CListen(const char * pStrPeer, const char * pStrIp, const UI16 nPort);
    UI32_ID CConnect(const char * pStrPeer, const char * pStrIp, const UI16 nPort);
    bool CUdpSend(const char * pStrIp, const UI16 nPort, const void * pBuff, DWORD nBytes);
    bool CSend(UI32_ID nConID, const void * pBuff, DWORD nBytes);
    void CWork();
private:
    ComIocp();
    ~ComIocp();
    bool GetAcceptExFun(LPFN_ACCEPTEX & acceptfun);

private:
    inline void DestroyOverlappedplus(OVERLAPPEDPLUS * & pOverlappedPlus);
    inline bool CheckIocpError();

private:
    static ComIocp * m_pSelf;
    static CoreModuleManage * m_pCoreModuleManage;

    HANDLE m_hCompletionPort;
    LPFN_ACCEPTEX m_lpfnAcceptEx;
    ConnectionPool * m_pConnectionPool;
    PeerManage * m_pPeerConfig;
    BaseConfig * m_pBaseConfig;
    IKernel * m_pKernel;
};

#endif