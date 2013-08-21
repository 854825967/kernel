#ifndef CSOCKET_H
#define CSOCKET_H

#include "MultiSys.h"

struct CSocket {
private:
    SOCKET m_scok;

public:
    CSocket();
    UI32 Send(void * pBuff, UI16 nSize);
    UI32 Recv(void * pBuff, UI16 nSize);
    bool SetBlock();
    void Close();
};

#endif