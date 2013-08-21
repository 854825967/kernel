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
    UI32_ID m_nAppID;    //Ӧ��ID
    UI32_ID m_nClusterID;    //��ȺID
    UI32_ID m_nServerID; //��ǰ������ID
    string m_strNoticPeerType;
    string m_strNoticIP;
    UI16 m_nNoticPort;
    UI32 m_nMaxConnectionCount;    //���������
    UI32 m_nMaxClientCount;    //���ͻ���������
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
