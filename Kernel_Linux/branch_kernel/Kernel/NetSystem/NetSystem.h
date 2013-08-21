#ifndef _NETSYSTEM_H_
#define _NETSYSTEM_H_

#include "../../Public/ComDefine.h"
#include "../../Public/VarList.h"
#include "../Interface/INetSystem.h"
#include "LinkManage.h"
#include <sys/epoll.h>

#define MAX_FDS 512
#define LISTEN_QUENE 100
#define SEND_BLOCK_SIZE 512
#define EVENT_QUENE_SIZE 4096
#define RECVBUF_SIZE 4096

enum {
    LISTEN_GAME_SOCKET = 0,
    GAME_SOCKET ,
    LISTEN_CONSOLE_SOCKET,
    CONSOLE_SOCKET,
};

class IConfigManage;
class IHeartBeatManage;
class ICallBackSystem;
class IKernel;
class IObjectManage;
class ILogSystem;

class NetSystem : public INetSystem {
public:
    static INetSystem * Employ();
    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();
    //interface
    virtual bool BroadCast(const char * pLinkType, const IArchive & msg, const IVarList & blacklist = VarList() );
    virtual bool Send(const UI32 nSocket, const IArchive & msg);
    virtual bool Connect(const char * remotetype, const char * pStrIp, const UI16 nPort);
    virtual bool Listen(const char * remotetype, const char * pStrIp, const UI16 nPort, const UI8 nUsefor);
    virtual bool Close(const UI32 nLinkID); //添加是否立即关闭，还是等所有缓存中的消息全部发送出去后再关闭
    virtual bool MainLoop(const UI8 nWaitTimeOut, const UI8 nMaxRecvFrequency);
private:
    NetSystem();
    ~NetSystem();
    bool Setnonblocking(int sock);
    //这里到底要不要封装 接受 发送 接收函数。。。。
    void CompleteAccept(struct epoll_event & event);
    void CompleteSend(struct epoll_event & event);
    void CompleteRecv(struct epoll_event & event);
    inline void CleanLink(LinkInfo * & pLink);
private:
    //声明epoll句柄
    int m_epfd;
    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
    struct epoll_event m_events[EVENT_QUENE_SIZE];
    //IniConfig m_config;
    char m_localtype[64];
    LinkManage m_linkmanage;
    
    static bool m_alive;
    
    static NetSystem * m_pSelf;
    //回调管理器
    static ICallBackSystem * m_pCallBackSystem;
    //引擎入口
    static IKernel * m_pKernel;
    //配置管理器
    static IConfigManage * m_pConfigManage;
    //心跳管理器
    static IHeartBeatManage * m_pHeartBeatManage;
    //对象管理器
    static IObjectManage * m_pObjectManage;
    //log system
    static ILogSystem * m_pLogSystem;
    //配置
    //CIniConfig m_BaseConfig;
};

#endif //_NETSYSTEM_H_
