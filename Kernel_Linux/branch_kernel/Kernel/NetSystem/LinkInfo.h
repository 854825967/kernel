#ifndef _PEERINFO_H_
#define _PEERINFO_H_

#define TYPE_STR_LENGTH 64
#define IP_STR_LENGTH 32

#include "../../Public/Stream.h"


class LinkInfo {
public:
    LinkInfo() {
        Reset();
    }

    void Reset() {
        m_remotetype[TYPE_STR_LENGTH - 1] = 0;
        m_remoteip[IP_STR_LENGTH - 1] = 0;
        m_socket = -1;
        m_usefor = -1;
        m_remoteport = -1;
        m_closeit = false;
        m_lastRecvTimeTick = 0;
    }
    
    void SetIp(const char * pStrIp) {
        snprintf(m_remoteip, IP_STR_LENGTH - 1, "%s", pStrIp);
    }

    void SetRemoteType(const char * pStrType) {
        snprintf(m_remotetype, TYPE_STR_LENGTH - 1, "%s", pStrType);
    }
public:
    char m_remotetype[TYPE_STR_LENGTH]; //连接端类型 
    UI16 m_socket;
    UI8 m_usefor; //socket用途type
    char m_remoteip[IP_STR_LENGTH];
    UI16 m_remoteport;
    Stream m_recvstream;
    Stream m_sendstream;
    UI64 m_lastRecvTimeTick;
    bool m_closeit; //是否关闭该链接
};
typedef LinkInfo ListenInfo;
#endif //_PEERINFO_H_