#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include "ComDefine.h"
#include "Stream.h"
#include "ICoreModule.h"
#include <vector>
#include <winsock2.h>
using namespace std;

class BaseConfig;
class CoreModuleManage;

typedef struct _connectioninfo {
    SOCKET connectSock;
    UI32 nIP;
    UI16 nPort;
    bool bInUse;
    UI32_ID nPeerTypeID;
    UI32_ID nAppID;//应用ID
    UI32_ID nClusterID;//集群ID
    UI32_ID nServerID;//全架构唯一
    UI32_ID nIdentity;
    Stream recvStream;
}ConnectionInfo;

class ConnectionPool : public ICoreModule {
public:
    static bool Employ(const char * pStrModuleName);
    virtual bool Initialize();
    virtual bool DelayInitialize();
    virtual bool Destroy();

    bool SavePeerInfo(const UI32_ID nConID, const UI32_ID nAppID, const UI32_ID nClusterID, const UI32_ID nServerID, const UI32_ID nIdentity);
    const UI32_ID GetPeerAppID(const UI32_ID nConID);
    const UI32_ID GetPeerClusterID(const UI32_ID nConID);
    const UI32_ID GetPeerServerID(const UI32_ID nConID);
    const UI32_ID GetPeerIdentity(const UI32_ID nConID);


    UI32_ID RegisterConnection(SOCKET & sock, UI32_ID nPeerTypeID);
    const UI32_ID QueryPeerTypeID(const UI32 nConID);
    bool RecoverConnection(UI32_ID nConID);
    bool WriteConStream(UI32_ID nConID, void * pBuff, UI32 nLen);
    bool ReadArchiveFromCon(UI32_ID nConID, Archive & archive);
    bool RecordIpAndPort(UI32_ID nConID);

    inline SOCKET GetSocket(UI32_ID nID) {
        if (nID >= m_nMaxConCount || false == m_pConInfo[nID].bInUse) {
            //输出日志 提示要回收的ID无效
            return SOCKET_ERROR;
        }
        return m_pConInfo[nID].connectSock;
    }

private:
    ConnectionPool();
    ~ConnectionPool();
private:
    static ConnectionPool * m_pSelf;
    static CoreModuleManage * m_pCoreModuleManage;
    BaseConfig * m_pBaseConfig;

    ConnectionInfo * m_pConInfo;
    UI32 m_nMaxConCount;
    UI32 m_nMaxClientCount;

    UI32 m_nConCurrent;
    vector<UI32_ID> m_vctRecycleBin;
};

#endif