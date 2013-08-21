#ifndef IKERNEL_H
#define IKERNEL_H

#include "ComDefine.h"

class VarList;
class Archive;
class IKernel;
class ILogicModule;
typedef I32 (__cdecl * CALLFUN)(IKernel *, const UI64, const VarList &);

enum eventtype
{
    //事件枚举
    EVENT_LAUNCH = 0,       //Launch初始化启动完成(即引擎启动完成,可正常工作)
    EVENT_CONNECT = 1,      //连接成功
    EVENT_NEW_CONNECT = 2,   //有新的连接
    EVENT_DISCONNECT = 3,   //Disconnect断开连接
};

class IKernel
{
public:
    //获取当前应用ID
    virtual const UI32_ID GetAppID() = 0;
    //获取当前集群ID
    virtual const UI32_ID GetClusterID() = 0;
    //获取当前服务器ID
    virtual const UI32_ID GetServerID() = 0;
    /*
     *获取当前开放的端口
     *portInfo (0:UI16开放端口数量,1:const char * 连接类型(Lister,Server等),2:const char * ip, 3:UI16 端口号,4:const char * 连接类型(Lister,Server等),5:const char * ip,6:UI16 端口号...
     */
    virtual bool GetPublicPort(VarList & portInfo) = 0;

    //注册消息回调
    virtual bool AddMsgCall(const char * pStrPeerName, const UI32_ID nMsgID, const CALLFUN pFun) = 0;
    //注册事件回调 事件定义在enum eventtype
    virtual bool AddEventCall(const char * pStrPeerName, const UI32_ID nEventID, const CALLFUN pFun) = 0;
    //查找其它逻辑模块
    virtual ILogicModule * FindModule(const char * pStrModuleName) = 0;

    //发送Tcp消息
    virtual bool TcpSend(const UI16 nConID, const Archive & arch) = 0;

protected:
private:
};

#endif