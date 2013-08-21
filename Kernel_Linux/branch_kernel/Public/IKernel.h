#ifndef _IKERNEL_H_
#define _IKERNEL_H_

#include "ComDefine.h"
#include "EventDefine.h"
#include "VarList.h"
#include "Archive.h"
class CIniConfig;
class CXmlConfig;
class ILogicModule;

//针对IKernel 做了特殊写法 这里是位了隐藏 引擎内部的启动机制 
//引擎层 要对逻辑层做到 能不暴露 就不暴露
#ifndef KERNEL_PROCESS
#define LOG_ECHO(format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        pKernel->Echo( log , __FILE__, __LINE__, __FUNCTION__); \
    }
#define LOG_TRACE(name, size, format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        pKernel->Trace( log , __FILE__, __LINE__, __FUNCTION__); \
    }
#define LOG_DEBUG(name, size, format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        pKernel->Debug( log , __FILE__, __LINE__, __FUNCTION__); \
    }
#define LOG_ERROR(name, size, format,a...) \
    { \
        char log[LOG_MAX_SIZE] = {0}; \
        snprintf(log, LOG_MAX_SIZE, format, ##a); \
        pKernel->Error( log , __FILE__, __LINE__, __FUNCTION__); \
    }
#endif // KERNEL_PROCESS

class IKernel {
public:
    //配置
    virtual const char * GetPath() const = 0;
    virtual const UI32 GetServerID() const = 0;
    virtual const char * GetServerType() const = 0;
    virtual bool GetIniConfig(const char * pStrPath/*相对与引擎执行文件的路径*/, CIniConfig & iniconfig) const = 0;
    virtual bool GetXmlConfig(const char * pStrPath/*相对与引擎执行文件的路径*/, CXmlConfig & xmlconfig) const = 0;

    //逻辑模块之间
    virtual ILogicModule * FindModule(const char * pModuleName) const = 0;

    //log system
    virtual bool Echo(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const = 0;
    virtual bool Trace(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const = 0;
    virtual bool Debug(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const = 0;
    virtual bool Error(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const = 0;

    //注册连接与玩家对象的关联
    virtual bool Register(const UI32 nLinkID, const CIdentity & player) const = 0;

    //注册回调
    //heartbeat callback
    virtual bool AddHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun,
            const UI64 nFrequency = 1000, const UI32 nMaxBeatCount = 0, const bool beatatonce = false) const = 0;
    virtual bool DelHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) const = 0;
    virtual bool IsExistsHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) const = 0;

    //msg and event callback
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const SOCKETCALL pFun) const = 0;
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const OBJCALL pFun) const = 0; //玩家对象
    virtual bool AddKernelEvent(const char * pLinkType, const UI32 nEventId, const SOCKETCALL pFun) const = 0;

    //消息操作
    virtual bool SendMsg(const UI32 nLinkID, const IArchive & msg) const = 0; //发送消息 最好都用这条 因为这条消息会少一次内存copy操作 性能要高一些 
    virtual bool SendMsg(const CIdentity player, const IArchive & msg) const = 0; //发送消息 最好都用这条 因为这条消息会少一次内存copy操作 性能要高一些  

    virtual bool BroadCastByLinkType(const char * pLinkType, const IArchive & msg, const IVarList & blacklist = VarList()) const = 0; //广播消息 最好都用这条 因为这条消息会少一次内存copy操作 性能要高一些

    virtual bool SendMsg(const UI32 nLinkID, const IVarList & msg) const = 0;
    virtual bool SendMsg(const CIdentity player, const IVarList & msg) const = 0;

    virtual bool BroadCastByLinkType(const char * pLinkType, const IVarList & msg, const IVarList & blacklist = VarList()) const = 0;
    virtual bool Close(const UI32 nLinkID) const = 0; //会在当前发送缓冲区的数据全部发送完之后关掉这条连接，并且调用该方法后该条连接不回在接受任何数据.
};

#endif //_KERNEL_H_
