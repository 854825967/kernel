#ifndef INET_H
#define INET_H

#include "MultiSys.h"

class INet;

typedef INet* (__cdecl *FUN_GET_NET)(const u8, const u16);

#define NAME_OF_GET_NET_FUN "GetNet"
#define GET_NET_FUN GetNet

typedef void (__cdecl *FUN_RETURN_NET)(INet *);

#define NAME_OF_RETURN_NET_FUN "ReturnNet"
#define RETURN_NET_FUN ReturnNet

typedef void (*CALL_FUN)(const u16 conid, const char * buff, const u32 size);

class INet {
public:
    virtual bool CListen(const char * ip, const u16 port, const u16 count = 200) const = 0;
    virtual bool CConnectEx(const char * ip, const u16 port, const char * buff = NULL, const u32 size = 0) const = 0;
    virtual bool CClose(const u16 conid) const = 0;
    virtual bool CSendMsg(const u16 conid, char * buff, const u16 size) const = 0;

    virtual bool CGetRemoteInfo(const u16 conid, const char * & ip, u16 & port) const = 0;

    virtual bool CSetConnectedCall(const CALL_FUN pcntedfun) = 0;
    virtual bool CSetRecvCall(const CALL_FUN precvfun) = 0;
    //virtual void CSetNetThreadCount(const u8 count) = 0;
    virtual void CStartLoop() const = 0;
};

#endif