#ifndef CSOCKPLUSMGR_H
#define CSOCKPLUSMGR_H

#include "CLock.h"
#include "CStream.h"

#include <hash_map>
#include <list>
using namespace std;
using namespace stdext;

#include "CInetAddress.h"

enum {
    EVENT_RECV = 0x01,
    EVENT_SEND = 0x02,
    EVENT_ACCEPT = 0x04,
    EVENT_CONNECT = 0x08,
};

#define BUFF_SIZE 4096
#define MAX_SOCKPLUS_COUNT 4096

class SockData;

class SockPlus
{
public:
    OVERLAPPED m_overlapped;  //不解释,该成员变量必须放在第一位
    SockData * m_pSockData;
    u8 m_events;
    WSABUF m_wBuf;
    DWORD m_dwBytes, m_dwFlags;
    char m_buff[BUFF_SIZE];
    SockPlus() {
        Initialize();
    }

    ~SockPlus(){

    }

    void Initialize() {
        memset(this, 0, sizeof(SockPlus));
        m_wBuf.len = BUFF_SIZE;
        m_wBuf.buf = m_buff;
    }
};

class SockData {
public:
    CInetAddress m_address;
    u16 m_id;
    SOCKET m_sock;            //当前连接
    SOCKET m_listenSock;
    bool m_waitclose;

    bool SendBuff(char * buff, u32 size) {
        return m_sendbuff.In(buff, size);
    }

    char * GetBuff(u32 & size) {
        size = m_sendbuff.GetLength();
        return m_sendbuff.GetBuff();
    }

    void ClearBuff() {
        m_sendbuff.Clear();
    }

    void Out(u32 nSize) {
        m_sendbuff.Out(nSize);
    }

    SockData() {
        m_id = 0;
        m_sock = INVALID_SOCKET;
        m_listenSock = INVALID_SOCKET;
        m_waitclose = false;
    }
private :
    CStream m_sendbuff;
};

typedef hash_map<u16, SockData *> ID_SOCKPLUS;
typedef list<u16> LIST_ID;

class CSockDataMgr {
public:
    CSockDataMgr(const u16 size = MAX_SOCKPLUS_COUNT);
    ~CSockDataMgr();
    SockData * CreateSockData();
    SockData * QuerySockPlus(const u16 id);
    void RecoveSockData(SockData * pSockData);

private:
    //createlock
    LIST_ID m_IdRecycleBin;

    SockData * m_pSockDataArray;
    u16 m_nCurrentMark;
    u16 m_nMaxCount;
};

#endif    //CSOCKPLUSMGR_H