#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "./Interface/IBase.h"
#include "../Public/IKernel.h"
//#include "./Interface/IConfigManage.h"
//#include "./Interface/ICallBackSystem.h"

class IConfigManage;
class ILogicManage;
class ICallBackSystem;
class INetSystem;
class IVarList;
class IArchive;
class IObjectManage;
class IHeartBeatManage;
class ILogSystem;

class Kernel : public IKernel, public IBase {
public:
    static IKernel * Employ();

    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();
    //配置
    virtual const char * GetPath() const;
    virtual const UI32 GetServerID() const;
    virtual const char * GetServerType() const;
    virtual bool GetIniConfig(const char * pStrPath/*相对与引擎执行文件的路径*/, CIniConfig & iniconfig) const;
    virtual bool GetXmlConfig(const char * pStrPath/*相对与引擎执行文件的路径*/, CXmlConfig & xmlconfig) const;

    //逻辑模块之间
    virtual ILogicModule * FindModule(const char * pModuleName) const;
    
    //log system
    virtual bool Echo(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const;
    virtual bool Trace(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const;
    virtual bool Debug(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const;
    virtual bool Error(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const;

    //注册连接与玩家对象的关联
    virtual bool Register(const UI32 nLinkID, const CIdentity & player) const;

    //注册回调
    //heartbeat callback
    virtual bool AddHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun,
            const UI64 nFrequency = 1000, const UI32 nMaxBeatCount = 0, const bool beatatonce = false) const;
    virtual bool DelHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) const;
    virtual bool IsExistsHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) const;

    //msg and event callback
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const SOCKETCALL pFun) const;
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const OBJCALL pFun) const; //玩家对象
    virtual bool AddKernelEvent(const char * pLinkType, const UI32 nEventId, const SOCKETCALL pFun) const;

    //消息操作
    virtual bool SendMsg(const UI32 nLinkID, const IArchive & msg) const; //发送消息 最好都用这条 因为这条消息会少一次内存copy操作 性能要高一些 
    virtual bool SendMsg(const CIdentity player, const IArchive & msg) const; //发送消息 最好都用这条 因为这条消息会少一次内存copy操作 性能要高一些  

    virtual bool BroadCastByLinkType(const char * pLinkType, const IArchive & msg, const IVarList & blacklist = VarList()) const; //广播消息 最好都用这条 因为这条消息会少一次内存copy操作 性能要高一些

    virtual bool SendMsg(const UI32 nLinkID, const IVarList & msg) const;
    virtual bool SendMsg(const CIdentity player, const IVarList & msg) const;

    virtual bool BroadCastByLinkType(const char * pLinkType, const IVarList & msg, const IVarList & blacklist = VarList()) const;
    virtual bool Close(const UI32 nLinkID) const; //会在当前发送缓冲区的数据全部发送完之后关掉这条连接，并且调用该方法后该条连接不回在接受任何数据.
private:
    Kernel();
    ~Kernel();
private:
    static Kernel * m_pSelf;
    static IConfigManage * m_pConfigManage;
    static ICallBackSystem * m_pCallBackSystem;
    static ILogicManage * m_pLogicManage;
    static INetSystem * m_pNetSystem;
    static IObjectManage * m_pObjectManage;
    static IHeartBeatManage * m_pHeartBeatManage;
    static ILogSystem * m_pLogSystem;
};

#endif //_KERNEL_H_

