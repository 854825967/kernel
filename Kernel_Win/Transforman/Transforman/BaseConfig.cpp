#include "BaseConfig.h"
#include "./TinyXml/tinyxml.h"
#include "PathDefine.h"
#include "Tools.h"
#include "ComIocp.h"
#include "CoreModuleManage.h"

BaseConfig * BaseConfig::m_pSelf = NULL;
CoreModuleManage * BaseConfig::m_pCoreModuleManage = NULL;

BaseConfig::BaseConfig()
{
    m_strPeertype = "";
    m_nAppID = 0;    //应用ID
    m_nClusterID = 0;    //集群ID
    m_nServerID = 0; //当前服务器ID
    m_strNoticPeerType = "";
    m_strNoticIP = "";
    m_nNoticPort = 0;    //广播端口
    m_nMaxConnectionCount = 0;    //最大连接数
    m_nMaxClientCount = 0;    //最大客户端连接数
    m_nPublicListenCount = 0;

    m_mapListen.clear();
}

BaseConfig::~BaseConfig()
{

}

bool BaseConfig::Destroy()
{
    Assert(NULL != m_pSelf);
    if (m_pSelf != NULL)
    {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

bool BaseConfig::Employ(const char * pStrModuleName)
{
    Assert(NULL == m_pSelf);
    if (NULL == m_pSelf)
    {
        m_pSelf = NEW BaseConfig;
        if (NULL == (m_pCoreModuleManage = CoreModuleManage::Employ()))
        {
            Assert(NULL != m_pCoreModuleManage);
            LOG_ERROR("BaseConfig::Employ Get CoreModuleManage error");
            return false;
        }
        if (false == (m_pCoreModuleManage->AddModule(pStrModuleName, m_pSelf)))
        {
            Assert(false);
            LOG_ERROR("BaseConfig::Employ CoreModuleManage::AddModule error");
            return false;
        }
    }

    return true;
}


bool BaseConfig::Initialize()
{
    m_nPublicListenCount = 0;
    char strConfigPath[PATH_LENGTH] = {0};
    const char * pStrPathFolder = GetAppPath();
    sprintf_s(strConfigPath, "%s/%s", pStrPathFolder, CONFIG_PATH_BASECONFIG);
    
    TiXmlDocument xmlConfig;
    if (false == xmlConfig.LoadFile(strConfigPath))
    {
        Assert(false);
        LOG_ERROR("Load BaseConfig Error");
        return false;
    }

    TiXmlElement * pRootElement = xmlConfig.RootElement();
    TiXmlElement * pBaseElm = pRootElement->FirstChildElement("Base");
    if (NULL == pBaseElm)
    {
        Assert(false);
        LOG_ERROR("Load BaseConfig : Get Base Error");
        return false;
    }
    {//获取<Base>配置
        TiXmlElement * pPeertypeElm = pBaseElm->FirstChildElement("PeerType");
        if (NULL == pPeertypeElm || 
            "" == (m_strPeertype = pPeertypeElm->Attribute("Value")))
        {
            Assert(false);
            LOG_ERROR("Load BaseConfig : Get PeerType Error");
            return false;
        }

        TiXmlElement * pAppIDElm = pBaseElm->FirstChildElement("AppID");
        if (NULL == pAppIDElm || 
            NULL == pAppIDElm->Attribute("Value", (int *)&m_nAppID))
        {
            Assert(false);
            LOG_ERROR("Load BaseConfig : Get AppID Error");
            return false;
        }

        TiXmlElement * pClusterIDElm = pBaseElm->FirstChildElement("ClusterID");
        if (NULL == pClusterIDElm || 
            NULL == pClusterIDElm->Attribute("Value", (int *)&m_nClusterID))
        {
            Assert(false);
            LOG_ERROR("Load BaseConfig : Get ClusterID Error");
            return false;
        }

        TiXmlElement * pServerIDElm = pBaseElm->FirstChildElement("ServerID");
        if (NULL == pServerIDElm || 
            NULL == pServerIDElm->Attribute("Value", (int *)&m_nServerID))
        {
            Assert(false);
            LOG_ERROR("Load BaseConfig : Get ServerID Error");
            return false;
        }

        TiXmlElement * pNoticElm = pBaseElm->FirstChildElement("Notification");
        if (NULL == pNoticElm || 
            "" == (m_strNoticPeerType = pNoticElm->Attribute("PeerType")))
        {
            LOG_ERROR("Load BaseConfig : Get Notification PeerType Error");
        }
        if (NULL == pNoticElm || 
            "" == (m_strNoticIP = pNoticElm->Attribute("IP")))
        {
            LOG_ERROR("Load BaseConfig : Get Notification IP Error");
        }
        if (NULL == pNoticElm || 
            NULL == pNoticElm->Attribute("Port", (int *)&m_nNoticPort))
        {
            LOG_ERROR("Load BaseConfig : Get Notification Port Error");
        }
    }

    TiXmlElement * pConnectionPoolElm = pRootElement->FirstChildElement("ConnectionPool");    
    if (NULL == pConnectionPoolElm)
    {
        Assert(false);
        LOG_ERROR("Load BaseConfig : Get ConnectionPool Error");
        return false;
    }
    {//获取<ConnectionPool>配置
        TiXmlElement * pMaxConnectionCountElm = pConnectionPoolElm->FirstChildElement("MaxConnectionCount");
        if (NULL == pMaxConnectionCountElm || 
            NULL == pMaxConnectionCountElm->Attribute("Value", (int *)&m_nMaxConnectionCount))
        {
            Assert(false);
            LOG_ERROR("Load BaseConfig : Get MaxConnectionCount Error");
            return false;
        }

        TiXmlElement * pMaxClientCountElm = pConnectionPoolElm->FirstChildElement("MaxClientCount");
        if (NULL == pMaxClientCountElm || 
            NULL == pMaxClientCountElm->Attribute("Value", (int *)&m_nMaxClientCount))
        {
            Assert(false);
            LOG_ERROR("Load BaseConfig : Get MaxClientCount Error");
            return false;
        }
    }

    TiXmlElement * pPeerListenElm = pRootElement->FirstChildElement("PeerListen");    
    if (NULL == pPeerListenElm)
    {
        LOG_ERROR("Load BaseConfig : Get PeerListen Error");
        return false;
    }
    {//获取<ConnectionPool>配置
        TiXmlElement * pPeerElm = pPeerListenElm->FirstChildElement("Peer");
        while (NULL != pPeerElm)
        {
            string strName = "";
            IPPORT ipport;
            if ("" == (strName = pPeerElm->Attribute("Name")))
            {
                LOG_ERROR("Load BaseConfig : Get Peer Name Error");
                return false;
            }

            if ("" == (ipport.ip = pPeerElm->Attribute("IP")))
            {
                LOG_ERROR("Load BaseConfig : Get Peer IP Error");
                return false;
            }

            if (NULL == pPeerElm->Attribute("Port", (int *)&ipport.port))
            {
                LOG_ERROR("Load BaseConfig : Get Peer Port Error");
                return false;
            }
            m_mapListen.insert(make_pair(strName, ipport));
            m_nPublicListenCount++;
            pPeerElm = pPeerElm->NextSiblingElement();
        }
    }

    return true;
}

bool BaseConfig::DelayInitialize()
{
    if (NULL == (m_pComIocp = (ComIocp *)m_pCoreModuleManage->GetModule("ComIocp")))
    {
        return false;
    }

    map<string, IPPORT>::iterator itor = m_mapListen.begin();
    map<string, IPPORT>::iterator iend = m_mapListen.end();
    while (itor != iend)
    {
         m_pComIocp->CListen(itor->first.c_str(), itor->second.ip.c_str(), itor->second.port);
         itor++;
    }    

    m_pComIocp->CConnect(m_strNoticPeerType.c_str(), m_strNoticIP.c_str(), m_nNoticPort);

    return true;
}
