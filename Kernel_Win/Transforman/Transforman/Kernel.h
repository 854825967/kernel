#ifndef KERNEL_H
#define KERNEL_H

#include <map>
using namespace std;

#include "IKernel.h"
#include "ICoreModule.h"

class PeerManage;
class LogicModuleManage;
class CoreModuleManage;
class BaseConfig;
class ComIocp;

class Kernel : public IKernel, ICoreModule
{
public:
    static bool Employ(const char * pStrName);

    virtual bool Initialize();
    virtual bool DelayInitialize();
    virtual bool Destroy();

    //��ȡ��ǰӦ��ID
    virtual const UI32_ID GetAppID();
    //��ȡ��ǰ��ȺID
    virtual const UI32_ID GetClusterID();
    //��ȡ��ǰ������ID
    virtual const UI32_ID GetServerID();
    /*
    *��ȡ��ǰ���ŵĶ˿�
    *portInfo (0:UI16���Ŷ˿�����,1:const char * ��������(Lister,Server��),2:const char * ip, 3:UI16 �˿ں�,4:const char * ��������(Lister,Server��),5:const char * ip,6:UI16 �˿ں�...
    */
    virtual bool GetPublicPort(VarList & portInfo);
    //ע����Ϣ�ص�
    virtual bool AddMsgCall(const char * pStrPeerName, const UI32_ID nMsgID, const CALLFUN pFun);
    //ע���¼��ص� �¼�������enum eventtype
    virtual bool AddEventCall(const char * pStrPeerName, const UI32_ID nEventID, const CALLFUN pFun);
    //���������߼�ģ��
    virtual ILogicModule * FindModule(const char * pStrModuleName);

    //����Tcp��Ϣ
    virtual bool TcpSend(const UI16 nConID, const Archive & arch);

private:
    Kernel();
    ~Kernel();
private:
    static Kernel * m_pSelf;
    static CoreModuleManage * m_pCoreModuleManage;
    PeerManage * m_pPeerConfig;
    LogicModuleManage * m_pLogicModuleManage;
    BaseConfig * m_pBaseConfig;
    ComIocp * m_pComIocp;
};

#endif