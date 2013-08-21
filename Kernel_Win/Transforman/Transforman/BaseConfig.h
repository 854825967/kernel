#ifndef BASECONFIG_H
#define BASECONFIG_H

#include "ComDefine.h"
#include "ICoreModule.h"
#include <map>
using namespace std;

class ComIocp;
class CoreModuleManage;
struct _ipport;
typedef struct _ipport IPPORT;

class BaseConfig : public ICoreModule
{
public:
    static bool Employ(const char * pStrModuleName);
    virtual bool Initialize();
    virtual bool DelayInitialize();
    virtual bool Destroy();

public:
    string m_strPeertype;
    UI32_ID m_nAppID;    //应用ID
    UI32_ID m_nClusterID;    //集群ID
    UI32_ID m_nServerID; //当前服务器ID
    string m_strNoticPeerType;
    string m_strNoticIP;
    UI16 m_nNoticPort;
    UI32 m_nMaxConnectionCount;    //最大连接数
    UI32 m_nMaxClientCount;    //最大客户端连接数
    UI32 m_nPublicListenCount;
    map<string, IPPORT> m_mapListen;
    

protected:
    BaseConfig();
    ~BaseConfig();
private:
    static BaseConfig * m_pSelf;
    static CoreModuleManage * m_pCoreModuleManage;
    ComIocp * m_pComIocp;
};

#endif    //BASECONFIG_H
