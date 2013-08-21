#include "NetSystem.h"
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <unistd.h>
#include <errno.h>
#include <iostream>
#include "../../Public/Archive.h"
#include "../../Public/VarList.h"
#include "../../Public/CIniConfig.h"
#include "../Kernel.h"
#include "../Config/ConfigManage.h"
#include "../HeartBeatManage/HeartBeatManage.h"
#include "../CallBackSystem/CallBackSystem.h"
#include "../ObjectManage/ObjectManage.h"
#include "../LogSystem/LogSystem.h"
#include <string>
using namespace std;
bool NetSystem::m_alive = false;
NetSystem * NetSystem::m_pSelf = NULL;
ICallBackSystem * NetSystem::m_pCallBackSystem = NULL;
IKernel * NetSystem::m_pKernel = NULL;
IConfigManage * NetSystem::m_pConfigManage = NULL;
IHeartBeatManage * NetSystem::m_pHeartBeatManage = NULL;
IObjectManage * NetSystem::m_pObjectManage = NULL;
ILogSystem * NetSystem::m_pLogSystem = NULL;

INetSystem * NetSystem::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW NetSystem;
        if (!m_pSelf->Bron()) {
            LOG_ERROR("NetSystem bron failed");
            Assert(false);
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

NetSystem::NetSystem() {

}

bool NetSystem::Bron() {
    m_epfd = epoll_create(MAX_FDS);
    memset(m_events, 0, sizeof (m_events));

    return true;
}

bool NetSystem::Dead() {
    m_alive = false;
}

bool NetSystem::Initialize() {
    if (NULL == (m_pKernel = Kernel::Employ()) ||
            NULL == (m_pCallBackSystem = CallBackSystem::Employ()) ||
            NULL == (m_pConfigManage = ConfigManage::Employ()) ||
            NULL == (m_pObjectManage = ObjectManage::Employ()) ||
            NULL == (m_pHeartBeatManage = HeartBeatManage::Employ()) ||
            NULL == (m_pLogSystem = LogSystem::Employ())) {
        LOG_ERROR("NetSystem initialize failed");
        Assert(false);
        return false;
    }

    m_alive = true;
    const CIniConfig * globlaconfig = m_pConfigManage->GetConfig(KERNEL_CONFIG_GLOBLA_INI);
    if (NULL == globlaconfig) {
        LOG_ERROR("Get GloblaConfig Failed");
        Assert(false);
        return false;
    }

    const char * pStrServerTypes = globlaconfig->GetStringConfig("Global", "ServerTypes");
    if ("" == string(pStrServerTypes)) {
        LOG_ERROR("Get ServerTypes Failed");
        Assert(false);
        return false;
    }

    VarList types;
    SafeSplitString(pStrServerTypes, ";", types);
    UI32 nCount = types.Count();
    if (0 >= nCount) {
        LOG_ERROR("Count Of ServerTypes : 0");
        Assert(0);
        return false;
    }

    for (UI32 i = 0; i < nCount; i++) {
        m_linkmanage.AddLinkType(types.GetString(i));
    }

    const CIniConfig * baseconfig = m_pConfigManage->GetConfig(KERNEL_CONFIG_BASE_INI);
    if (NULL == baseconfig) {
        LOG_ERROR("Get BaseConfig failed ");
        Assert(false);
        return false;
    }

    const char * pstartlisten = baseconfig->GetStringConfig("Base", "Listen");
    if (pstartlisten != NULL && strlen(pstartlisten) != 0) {
        VarList lslist;
        SafeSplitString(pstartlisten, ";", lslist);
        nCount = lslist.Count();
        for (UI32 i = 0; i < nCount; i++) {
            VarList listeninfo;
            SafeSplitString(lslist.GetString(i), ",", listeninfo);
            if (listeninfo.Count() != 3) {
                LOG_ERROR("Check the format of you listen config : %s", lslist.GetString(i));
                Assert(false);
                return false;
            }

            Listen(listeninfo.GetString(0), listeninfo.GetString(1), StringAsInt(listeninfo.GetString(2)), LISTEN_GAME_SOCKET);
        }
    }

    const char * pstartconnects = baseconfig->GetStringConfig("Base", "Connect");
    if (pstartconnects != NULL && strlen(pstartconnects) != 0) {
        VarList connects;
        SafeSplitString(pstartconnects, ";", connects);
        nCount = connects.Count();
        for (UI32 i = 0; i < nCount; i++) {
            VarList connectinfo;
            SafeSplitString(connects.GetString(i), ",", connectinfo);
            if (connectinfo.Count() != 3) {
                LOG_ERROR("Check the format of you connect config : %s", connects.GetString(i));
                Assert(false);
                return false;
            }

            Connect(connectinfo.GetString(0), connectinfo.GetString(1), StringAsInt(connectinfo.GetString(2)));
        }
    }

    const char * pConsolelisten = baseconfig->GetStringConfig("Base", "Console");
    if (pConsolelisten != NULL && strlen(pConsolelisten) != 0) {
        VarList csllist;
        SafeSplitString(pConsolelisten, ";", csllist);
        nCount = csllist.Count();
        for (UI32 i = 0; i < nCount; i++) {
            VarList listeninfo;
            SafeSplitString(csllist.GetString(i), ",", listeninfo);
            if (listeninfo.Count() != 3) {
                LOG_ERROR("Check the format of you listen config : %s", csllist.GetString(i));
                Assert(false);
                return false;
            }

            Listen(listeninfo.GetString(0), listeninfo.GetString(1), StringAsInt(listeninfo.GetString(2)), LISTEN_CONSOLE_SOCKET);
        }
    }

    return true;
}

NetSystem::~NetSystem() {
    close(m_epfd);
}

bool NetSystem::Destroy() {
    if (m_pSelf != NULL) {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

bool NetSystem::Connect(const char * remotetype, const char * pStrIp, const UI16 nPort) {
    if (NULL == pStrIp ||
            !m_linkmanage.IsExsitType(remotetype)) {
        LOG_ERROR("Connet to IP : %s RemoteType : %s Port : %d", pStrIp, remotetype, nPort);
        Assert(false);
        return false;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serveraddr;

    memset(&serveraddr, 0, sizeof (serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_aton(pStrIp, &(serveraddr.sin_addr));
    serveraddr.sin_port = htons(nPort);

    /* connect to the server */
    int result = connect(sockfd, (struct sockaddr *) &serveraddr, sizeof (serveraddr));
    if (result == -1) {
        LOG_ERROR("connect failed ");
        Assert(false);
        return false;
    }

    //把socket设置为非阻塞方式
    if (!Setnonblocking(sockfd)) {
        LOG_ERROR("Set socket nonblock failed");
        Assert(false);
        close(sockfd);
        exit(1);
    }

    LinkInfo * pLinkInfo = m_linkmanage.NewLink(sockfd, remotetype);
    pLinkInfo->m_usefor = GAME_SOCKET;
    //这里执行回调
    m_pCallBackSystem->ExKernelEvent(m_pKernel,
            remotetype, KERNEL_EVENT_CONNECT_SUCCESS, sockfd, VarList());

    struct epoll_event ev;
    ev.data.ptr = pLinkInfo;
    ev.events = EPOLLOUT | EPOLLOUT | EPOLLET;
    epoll_ctl(m_epfd, EPOLL_CTL_ADD, sockfd, &ev);

    return true;
}

bool NetSystem::BroadCast(const char * pLinkType, const IArchive & msg,
        const IVarList & blacklist) {
    if (NULL == pLinkType || !m_linkmanage.IsExsitType(pLinkType) || 0 == msg.Length()) {
        LOG_ERROR("LinkType : %s, MsgLength : %d", pLinkType, msg.Length());
        Assert(false);
        return false;
    }

    const vector<LinkInfo *> * pVct = m_linkmanage.GetTypeOfLinks(pLinkType);
    vector<LinkInfo *>::const_iterator itor = pVct->begin();
    const vector<LinkInfo *>::const_iterator iend = pVct->end();
    UI32 nCount = blacklist.Count();
    while (itor != iend) {
        for (UI32 i = 0; i < nCount; i++) {
            if (blacklist.Type(i) != TYPE_INT) {
                LOG_ERROR("Error BlackList element type");
                Assert(false);
                continue;
            }

            if ((*itor)->m_socket == blacklist.GetInt(i)) {
                continue;
            }
        }

        (*itor)->m_sendstream.WriteBuff(msg.GetStream(), msg.Length());

        struct epoll_event ev;
        ev.data.ptr = *itor;
        ev.events = EPOLLOUT | EPOLLET;
        epoll_ctl(m_epfd, EPOLL_CTL_MOD, (*itor)->m_socket, &ev);

        itor++;
    }

    return true;
}

bool NetSystem::Send(const UI32 nSocket, const IArchive & msg) {
    if (nSocket >= 65335) { //如何控制这个端口的范围
        LOG_ERROR("NetSystem::Send nSocket : %d", nSocket);
        Assert(false);
        return false;
    }

    LinkInfo * pLinkInfo = m_linkmanage.FindLinkBySocket(nSocket);
    if (NULL == pLinkInfo) {

        LOG_ERROR("NetSystem::Send LinkInfo is NULL");

        Assert(false);
        return false;
    }

    pLinkInfo->m_sendstream.WriteBuff(msg.GetStream(), msg.Length());

    struct epoll_event ev;
    ev.data.ptr = pLinkInfo;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
    epoll_ctl(m_epfd, EPOLL_CTL_MOD, pLinkInfo->m_socket, &ev);

    return true;
}

bool NetSystem::Listen(const char * remotetype, const char* pStrIp, const UI16 nPort, const UI8 nUsefor) {
    if (NULL == remotetype ||
            !m_linkmanage.IsExsitType(remotetype) ||
            NULL == pStrIp ||
            nPort < 0) {
        Assert(false);
        return false;
    }

    //listen
    int listenfd;
    if (-1 == (listenfd = socket(AF_INET, SOCK_STREAM, 0))) {
        Assert(false);
        return false;
    }

    //把socket设置为非阻塞方式
    if (!Setnonblocking(listenfd)) {
        Assert(false);
        return false;
    }

    ListenInfo * pListen = m_linkmanage.NewLink(listenfd);
    pListen->SetRemoteType(remotetype);
    pListen->m_usefor = nUsefor;
    pListen->m_socket = listenfd;

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof (serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_aton(pStrIp, &(serveraddr.sin_addr));
    serveraddr.sin_port = htons(nPort);

    if (-1 == bind(listenfd, (sockaddr *) & serveraddr, sizeof (serveraddr)) ||
            -1 == (listen(listenfd, LISTEN_QUENE))) {
        Assert(false);
        return false;
    }

    struct epoll_event ev;
    ev.data.ptr = pListen;
    ev.events = EPOLLIN; // | EPOLLET;
    epoll_ctl(m_epfd, EPOLL_CTL_ADD, listenfd, &ev);

    return true;
}

void NetSystem::CompleteAccept(struct epoll_event & event) {
    LinkInfo * pListen = (LinkInfo *) event.data.ptr;
    while (true) {
        int connfd = -1;
        struct sockaddr_in clientaddr;
        socklen_t socklen;
        //如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接
        if (0 > (connfd = accept(pListen->m_socket, (sockaddr *) & clientaddr, &socklen))) {
            break;
        }
        //把socket设置为非阻塞方式
        if (!Setnonblocking(connfd)) {
            LOG_ERROR("NetSystem::MainLoop Setnonblocking error");
            close(connfd);
            break;
        }

        LinkInfo * pNewLink = m_linkmanage.NewLink(connfd, pListen->m_remotetype);
        pNewLink->SetRemoteType(pListen->m_remotetype);
        pNewLink->SetIp(inet_ntoa(clientaddr.sin_addr));
        pNewLink->m_remoteport = clientaddr.sin_port;
        switch (pListen->m_usefor) {
            case LISTEN_GAME_SOCKET:
                pNewLink->m_usefor = GAME_SOCKET;
                //kernel event call
                m_pCallBackSystem->ExKernelEvent(m_pKernel, pListen->m_remotetype,
                        KERNEL_EVENT_NEW_CONNECTION, connfd, VarList());
                break;
            case LISTEN_CONSOLE_SOCKET:
                pNewLink->m_usefor = CONSOLE_SOCKET;
                break;
        }
        struct epoll_event ev;
        ev.data.ptr = pNewLink;
        ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
        epoll_ctl(m_epfd, EPOLL_CTL_ADD, connfd, &ev);
    }

    return;
}

void NetSystem::CompleteRecv(epoll_event& event) {
    LinkInfo * pLink = (LinkInfo *) event.data.ptr;
    //如果是已经连接的用户，并且收到数据，那么进行读入。
    char recvbuff[RECVBUF_SIZE];
    memset(recvbuff, 0, RECVBUF_SIZE);
    int nRecvLen = 0;
    //在这里会不会出现因为tpc接受缓冲区一直有东西存在 所以就直卡死在这个read中 所以改成read一次
    //但是有可能出现消息丢失
    while (true) { //这里注意 要增加 频率检测
        if ((nRecvLen = read(pLink->m_socket, recvbuff, RECVBUF_SIZE)) <= 0) {
            if (EAGAIN == errno && -1 == nRecvLen) {
                break;
            }

            if (0 == nRecvLen) {
                LOG_ERROR("NetSystem::MainLoop client is EOF, LinkID : %d", pLink->m_socket);
                m_pCallBackSystem->ExKernelEvent(m_pKernel,
                        pLink->m_remotetype, KERNEL_EVENT_CONNECTION_EOF, pLink->m_socket, VarList());
            } else {
                LOG_ERROR("NetSystem::MainLoop client is break off, LinkID : %d", pLink->m_socket);
                m_pCallBackSystem->ExKernelEvent(m_pKernel,
                        pLink->m_remotetype, KERNEL_EVENT_CONNECTION_BREAK, pLink->m_socket, VarList());
            }

            CleanLink(pLink);
            event.data.ptr = NULL;
            break;
        }

        if (!pLink->m_recvstream.WriteBuff(recvbuff, nRecvLen)) {
            LOG_TRACE("NetSystem::MainLoop WriteBuff error, LinkID : %d", pLink->m_socket);
            m_pCallBackSystem->ExKernelEvent(m_pKernel,
                    pLink->m_remotetype, KERNEL_EVENT_CONNECTION_BREAK, pLink->m_socket, VarList());
            CleanLink(pLink);
            event.data.ptr = NULL;
            break;
        }

        Archive msg;
        VarList args;
        while (pLink->m_recvstream.ReadArchive(msg)) {
            if (msg.ToVarList(args)) {
                if (args.Type(0) != TYPE_INT) {
                    LOG_ERROR("NetSystem::MainLoop Error msg");
                    m_pCallBackSystem->ExKernelEvent(m_pKernel,
                            pLink->m_remotetype, KERNEL_EVENT_CONNECTION_BREAK, pLink->m_socket, VarList());
                    CleanLink(pLink);
                    event.data.ptr = NULL;
                    break;
                }

                UI32 nMsgId = args.GetInt(0);
                m_pCallBackSystem->ExMsgCall(m_pKernel, pLink->m_remotetype, nMsgId, pLink->m_socket, args);

                const CIdentity player = m_pObjectManage->QueryPlayer(pLink->m_socket);
                if (player != CIdentity_INIT()) {
                    m_pCallBackSystem->ExMsgCall(m_pKernel, pLink->m_remotetype, nMsgId, player, args);
                }
            }
        }
    }

    if (pLink != NULL) {
        //设置用于写操作的文件描述符
        struct epoll_event ev;
        ev.data.ptr = pLink;
        ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
        epoll_ctl(m_epfd, EPOLL_CTL_MOD, pLink->m_socket, &ev);
    }

    return;
}

void NetSystem::CompleteSend(epoll_event& event) {
    LinkInfo * pLink = (LinkInfo *) event.data.ptr;
    //分块发送
    UI32 nLength = SEND_BLOCK_SIZE;
    struct epoll_event ev;
    ev.data.ptr = pLink;
    void * pBuff = NULL;
    while (true) {
        //从发送缓冲区读出数据
        pBuff = pLink->m_sendstream.ReadBuff(nLength);
        if (0 == nLength) {
            if (pLink->m_closeit) {
                LOG_DEBUG("Send over, close");
                m_pCallBackSystem->ExKernelEvent(m_pKernel,
                        pLink->m_remotetype, KERNEL_EVENT_CONNECTION_CLOSE, pLink->m_socket, VarList());
                CleanLink(pLink);
                event.data.ptr = NULL;
                break;
            }
            //设置用于注测的写操作事件 becasue sendstream is empty, so do not need to epollout
            ev.events = EPOLLIN | EPOLLET;
            epoll_ctl(m_epfd, EPOLL_CTL_MOD, pLink->m_socket, &ev);
            break;
        }

        int nSendSize = write(pLink->m_socket, pBuff, nLength);

        if (-1 == nSendSize && NULL != event.data.ptr) {
            LOG_ERROR("link break, or exists sm error");
            m_pCallBackSystem->ExKernelEvent(m_pKernel,
                    pLink->m_remotetype, KERNEL_EVENT_CONNECTION_BREAK, pLink->m_socket, VarList());
            CleanLink(pLink);
            event.data.ptr = NULL;
            break;
        }
        //底层缓冲区满了或者sendstream里面的数据全发晚了
        if (nSendSize < nLength) {
            //回收没法送掉的但是已经从stream里取出来的数据
            pLink->m_sendstream.Recover(SEND_BLOCK_SIZE - (nLength - nSendSize));
            if (pLink->m_closeit) {
                LOG_TRACE("NetSystem::MainLoop peer has been close on logic, so don't recv anything");
                ev.events = EPOLLOUT | EPOLLET;
            } else {
                ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
            }
            epoll_ctl(m_epfd, EPOLL_CTL_MOD, pLink->m_socket, &ev);
            break;
        }
    }
}

inline void NetSystem::CleanLink(LinkInfo * & pLink) {
    epoll_ctl(m_epfd, EPOLL_CTL_DEL, pLink->m_socket, NULL);
    m_pObjectManage->Logoff(pLink->m_socket);
    m_linkmanage.RecycleLink(pLink);
}

bool NetSystem::MainLoop(const UI8 nWaitTimeOut, const UI8 nMaxRecvFrequency) {
    int nfds = 0;
    while (true) {
        //等待epoll事件的发生
        nfds = epoll_wait(m_epfd, m_events, EVENT_QUENE_SIZE, nWaitTimeOut);
        if (nfds < 0) {
            if (EINTR == errno) {
                continue;
            } else {
                LOG_ERROR("NetSystem::MainLoop epoll_wait %d(%s)", errno, strerror(errno));
                return false;
            }
        }

        //处理所发生的所有事件
        for (int i = 0; i < nfds; ++i) {
            if (((LinkInfo *) (m_events[i].data.ptr))->m_usefor == LISTEN_GAME_SOCKET
                    || ((LinkInfo *) (m_events[i].data.ptr))->m_usefor == LISTEN_CONSOLE_SOCKET) {
                CompleteAccept(m_events[i]);
            } else if (((LinkInfo *) (m_events[i].data.ptr))->m_usefor == GAME_SOCKET) {
                if (m_events[i].events & EPOLLIN) {
                    CompleteRecv(m_events[i]);
                } else if (m_events[i].events & EPOLLOUT) {
                    CompleteSend(m_events[i]);
                }
            } else if (((LinkInfo *) (m_events[i].data.ptr))->m_usefor == CONSOLE_SOCKET) {
                m_alive = false;
            }
        }

        m_pHeartBeatManage->Beat();
        if (!m_alive) {
            break;
        }
        usleep(1);
    }

    return true;
}

bool NetSystem::Setnonblocking(int sockfd) {
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) == -1) {
        return false;
    }

    return true;
}

bool NetSystem::Close(const UI32 nLinkID) {

    LinkInfo * pLink = m_linkmanage.FindLinkBySocket(nLinkID);
    if (NULL == pLink) {
        //Assert(false);
        LOG_ERROR("NetSystem::Close LinkID is not Exists");
        return false;
    }

    pLink->m_closeit = true;

    return true;
}
