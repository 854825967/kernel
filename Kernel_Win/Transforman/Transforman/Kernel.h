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

    //获取当前应用ID
    virtual const UI32_ID GetAppID();
    //获取当前集群ID
    virtual const UI32_ID GetClusterID();
    //获取当前服务器ID
    virtual const UI32_ID GetServerID();
    /*
    *获取当前开放的端口
    *portInfo (0:UI16开放端口数量,1:const char * 连接类型(Lister,Server等),2:const char * ip, 3:UI16 端口号,4:const char * 连接类型(Lister,Server等),5:const char * ip,6:UI16 端口号...
    */
    virtual bool GetPublicPort(VarList & portInfo);
    //注册消息回调
    virtual bool AddMsgCall(const char * pStrPeerName, const UI32_ID nMsgID, const CALLFUN pFun);
    //注册事件回调 事件定义在enum eventtype
    virtual bool AddEventCall(const char * pStrPeerName, const UI32_ID nEventID, const CALLFUN pFun);
    //查找其它逻辑模块
    virtual ILogicModule * FindModule(const char * pStrModuleName);

    //发送Tcp消息
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