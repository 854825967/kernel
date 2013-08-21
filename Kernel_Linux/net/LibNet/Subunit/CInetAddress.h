#ifndef CINETADDRESS_H
#define CINETADDRESS_H

#include "MultiSys.h"

struct CInetAddress {
    struct sockaddr_in m_address;


    CInetAddress(const char * pStrIp = NULL, const u16 nPort = 0, const u8 type = AF_INET);
    bool SetIp(const char * pStrIp);
    bool SetPort(const u16 nPort);

    const char * GetIp();
    const u16 GetPort();
};

#endif