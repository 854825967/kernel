#ifndef CNET_H
#define CNET_H

#include "INet.h"
#include "CStream.h"

class CSockDataMgr;
class SockPlus;

class CNet : public INet {
public:
    virtual bool CListen(const char * ip, const u16 port, const u16 count) const;
    virtual bool CConnectEx(const char * ip, const u16 port, const char * buff, const u32 size) const;
    virtual bool CSendMsg(const u16 conid, char * buff, const u16 size) const;
    virtual bool CClose(const u16 conid) const;
    virtual void CStartLoop() const;

    virtual bool CGetRemoteInfo(const u16 conid, const char * & ip, u16 & port) const;

    virtual void CSetNetThreadCount(const u8 count);
    virtual bool CSetConnectedCall(const CALL_FUN pcntedfun);
    virtual bool CSetRecvCall(const CALL_FUN precvfun);

    CNet(const u8 threadcount, const u16 linkcount);
    ~CNet();

private:
    static DWORD WINAPI CLoop(LPVOID p);
    void CNetEvent(SockPlus * pSockPlus, const u32 nSize) const;
    void CAccept(SOCKET sock) const;
    void CRecv(SockPlus * pSockPlus, const u32 nRecvSize) const;
    void CSend(SockPlus * pSockPlus, const u32 nRecvSize) const;
    void CConnect(SockPlus * pSockPlus) const;

    inline void CloseSockPlus(SockPlus * pSockPlus) const;

private:
    LPFN_ACCEPTEX m_pFunAcceptEx;
    LPFN_CONNECTEX m_pFunConnectEx;
    CALL_FUN m_pRecvFun;
    CALL_FUN m_pConnectedFun;
    u8 m_nNetThreadCount;
    CSockDataMgr * m_pSockDataMgr;
    HANDLE m_hCompletionPort;
    BOOL m_endIocp;
};

#endif