#include "Kernel.h"
#include "BaseConfig.h"
#include "PeerManage.h"
#include "LogicModuleManage.h"
#include "CoreModuleManage.h"
#include "ComIocp.h"
#include "VarList.h"
#include "Archive.h"

Kernel * Kernel::m_pSelf = NULL;
CoreModuleManage * Kernel::m_pCoreModuleManage = NULL;

bool Kernel::Employ(const char * pStrModuleName)
{
    Assert(NULL == m_pSelf);
    if (NULL == m_pSelf)
    {
        m_pSelf = NEW Kernel;
        if (NULL == (m_pCoreModuleManage = CoreModuleManage::Employ()))
        {
            Assert(NULL != m_pCoreModuleManage);
            LOG_ERROR("Kernel::Employ Get CoreModuleManage error");
            return false;
        }
        if (false == (m_pCoreModuleManage->AddModule(pStrModuleName, m_pSelf)))
        {
            Assert(false);
            LOG_ERROR("Kernel::Employ CoreModuleManage::AddModule error");
            return false;
        }
    }

    return true;
}


Kernel::Kernel()
{
    m_pPeerConfig = NULL;
    m_pLogicModuleManage = NULL;
}

Kernel::~Kernel()
{

}

bool Kernel::Destroy()
{
    Assert(NULL != m_pSelf);
    if (NULL != m_pSelf)
    {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

bool Kernel::Initialize()
{


    return true;
}

bool Kernel::DelayInitialize()
{
    if (NULL == (m_pBaseConfig = (BaseConfig *)m_pCoreModuleManage->GetModule("BaseConfig")) ||
        NULL == (m_pPeerConfig = (PeerManage *)m_pCoreModuleManage->GetModule("PeerManage")) ||
        NULL == (m_pLogicModuleManage = (LogicModuleManage *)m_pCoreModuleManage->GetModule("LogicModuleManage")) ||
        NULL == (m_pComIocp = (ComIocp *)m_pCoreModuleManage->GetModule("ComIocp")))
    {
        Assert(false);
        LOG_ERROR("Get PeerManage Module Error");
        return false;
    }

    return true;
}

//获取当前应用ID
const UI32_ID Kernel::GetAppID()
{
    return m_pBaseConfig->m_nAppID;
}
//获取当前集群ID
const UI32_ID Kernel::GetClusterID()
{
    return m_pBaseConfig->m_nClusterID;
}
//获取当前服务器ID
const UI32_ID Kernel::GetServerID()
{
    return m_pBaseConfig->m_nServerID;
}
/*
*获取当前开放的端口
*portInfo (0:UI16开放端口数量,1:const char * 连接类型(Lister,Server等),2:const char * ip, 3:UI16 端口号,4:const char * 连接类型(Lister,Server等),5:const char * ip,6:UI16 端口号...
*/
bool Kernel::GetPublicPort(VarList & portInfo)
{
    portInfo.Clear();
    portInfo << m_pBaseConfig->m_nPublicListenCount;
    map<string, IPPORT>::iterator itor = m_pBaseConfig->m_mapListen.begin();
    map<string, IPPORT>::iterator iend = m_pBaseConfig->m_mapListen.end();
    while (itor != iend)
    {
        portInfo << itor->first.c_str() << itor->second.ip.c_str() << itor->second.port;
        itor ++;
    }

    return true;
}

bool Kernel::AddMsgCall(const char *pStrPeerName, const UI32 nMsgID, const CALLFUN pFun)
{
    UI32_ID nPeerCfgID = m_pPeerConfig->GetPeerTypeID(pStrPeerName);

    return m_pPeerConfig->AddMsgCall(nPeerCfgID, nMsgID, pFun);
}

bool Kernel::AddEventCall(const char * pStrPeerName, const UI32_ID nEventID, const CALLFUN pFun)
{
    UI32_ID nPeerCfgID = m_pPeerConfig->GetPeerTypeID(pStrPeerName);

    return m_pPeerConfig->AddEventCall(nPeerCfgID, nEventID, pFun);
}

ILogicModule * Kernel::FindModule(const char * pStrModuleName)
{
    return m_pLogicModuleManage->FindModule(pStrModuleName);
}


//发送Tcp消息
bool Kernel::TcpSend(const UI16 nConID, const Archive & arch)
{
    return m_pComIocp->CSend(nConID, arch.GetStream(), arch.Length());
}
