#include "PeerManage.h"
#include "CallBackSystem.h"
#include "PathDefine.h"
#include "./TinyXml/tinyxml.h"
#include "Tools.h"
#include "CoreModuleManage.h"

PeerManage * PeerManage::m_pSelf = NULL;
CoreModuleManage * PeerManage::m_pCoreModuleManage = NULL;

PeerManage::PeerManage()
{
    m_pCallBackSystem = NULL;
    m_hashmapPeerIndex.clear();
    m_hashmapPeerInfo.clear();
}

PeerManage::~PeerManage()
{
    hash_map<UI32_ID, PeerInfo *>::iterator itor = m_hashmapPeerInfo.begin();
    hash_map<UI32_ID, PeerInfo *>::iterator iEnd = m_hashmapPeerInfo.end();

    while (itor != iEnd)
    {
        delete itor->second;
        itor++;
    }
}

bool PeerManage::Employ(const char * pStrModuleName)
{
    Assert(NULL == m_pSelf);
    if (NULL == m_pSelf)
    {
        m_pSelf = NEW PeerManage;
        if (NULL == (m_pCoreModuleManage = CoreModuleManage::Employ()))
        {
            Assert(NULL != m_pCoreModuleManage);
            LOG_ERROR("PeerManage::Employ Get CoreModuleManage error");
            return false;
        }
        if (false == (m_pCoreModuleManage->AddModule(pStrModuleName, m_pSelf)))
        {
            Assert(false);
            LOG_ERROR("PeerManage::Employ CoreModuleManage::AddModule error");
            return false;
        }
    }

    return true;
}

bool PeerManage::Destroy()
{
    Assert(NULL != m_pSelf);
    if (NULL != m_pSelf)
    {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

bool PeerManage::Initialize()
{

    return true;
}

bool PeerManage::DelayInitialize()
{
    if (NULL == (m_pCallBackSystem = (CallBackSystem *)m_pCoreModuleManage->GetModule("CallBackSystem")))
    {
        Assert(false);
        LOG_ERROR("Get CallBackSystem error");
        return false;
    }

    char strConfigPath[PATH_LENGTH] = {0};
    const char * pStrPathFolder = GetAppPath();
    sprintf_s(strConfigPath, "%s/%s", pStrPathFolder, CONFIG_PATH_PEERCONFIG);

    TiXmlDocument xmlConfig;
    if (false == xmlConfig.LoadFile(strConfigPath))
    {
        LOG_ERROR("Load PeerManage Error");
        return false;
    }

    TiXmlElement * pRootElement = xmlConfig.RootElement();
    TiXmlElement * pPeerTypeElm = pRootElement->FirstChildElement("PeerType");

    while (pPeerTypeElm != NULL)
    {
        if (false == GetConfig(pPeerTypeElm))
        {
            LOG_ERROR("Load PeerManage Error");
        }
        pPeerTypeElm = pPeerTypeElm->NextSiblingElement();
    }

    return true;
}

bool PeerManage::GetConfig(TiXmlElement * pPeerTypeElm)
{
    if (NULL == pPeerTypeElm)
    {
        LOG_ERROR("Load PeerManage Error");
        return false;
    }

    UI32_ID nID = 0;
    if (NULL == pPeerTypeElm->Attribute("ID", (int *)&nID))
    {
        LOG_ERROR("Load PeerManage Error");
        return false;
    }

    const char * pStrName = NULL;
    if (NULL == (pStrName = pPeerTypeElm->Attribute("Name")))
    {
        LOG_ERROR("Load PeerManage Error");
        return false;
    }

    PeerInfo * pInfo = NEW PeerInfo;
    pInfo->strName[NAME_LENGTH - 1] = 0;
    pInfo->nID = nID;

    UI32 nLen = strlen(pStrName) + 1;    //配置文件中的Name属性值长队最大不得超过 NAME_LENGTH - 1
    if (nLen >= NAME_LENGTH)
    {
        nLen = NAME_LENGTH - 1;
    }

    memcpy(pInfo->strName, pStrName, nLen);
    m_hashmapPeerIndex.insert(make_pair(string(pStrName), nID));
    m_hashmapPeerInfo.insert(make_pair(nID, pInfo));

    pInfo->nMsgCallConntainerID = m_pCallBackSystem->RegisterCallContainer();
    pInfo->nEventCallConntainerID = m_pCallBackSystem->RegisterCallContainer();

    return true;
}

UI32_ID PeerManage::GetPeerTypeID(const char * pStrName)
{
    hash_map<string, UI32_ID>::iterator itor = m_hashmapPeerIndex.find(pStrName);
    if (itor == m_hashmapPeerIndex.end())
    {
        return ERROR_ID;
    }

    return itor->second;
}

const char * PeerManage::GetPeerTypeName(UI32_ID nID)
{
    hash_map<UI32_ID, PeerInfo *>::iterator itor = m_hashmapPeerInfo.find(nID);
    if (itor == m_hashmapPeerInfo.end())
    {
        return NULL;
    }

    return itor->second->strName;
}

bool PeerManage::AddMsgCall(const UI32_ID nPeerCfgID, const UI32_ID nMsgID, const CALLFUN pFun)
{
    PeerInfo * pInfo = NULL;
    hash_map<UI32_ID, PeerInfo *>::iterator itor = m_hashmapPeerInfo.find(nPeerCfgID);
    if (itor == m_hashmapPeerInfo.end())
    {
        LOG_ERROR("PeerConfigID is not exsits!");
        return false;
    }

    pInfo = itor->second;
    if (NULL == pInfo)
    {
        LOG_ERROR("PeerInfo is not exsits!");
        return false;
    }

    return m_pCallBackSystem->AddCall(pInfo->nMsgCallConntainerID, nMsgID, pFun);
}

bool PeerManage::ExecMsgCallBack(const UI32_ID nPeerCfgID, const UI32_ID nMsgID, IKernel * pKernel, const UI64 nConID, const VarList & args)
{
    PeerInfo * pInfo = NULL;
    hash_map<UI32_ID, PeerInfo *>::iterator itor = m_hashmapPeerInfo.find(nPeerCfgID);
    if (itor == m_hashmapPeerInfo.end())
    {
        LOG_ERROR("PeerConfigID is not exsits!");
        return false;
    }

    pInfo = itor->second;
    if (NULL == pInfo)
    {
        LOG_ERROR("PeerInfo is not exsits!");
        return false;
    }

    return m_pCallBackSystem->ExecCallBack(pInfo->nMsgCallConntainerID, nMsgID, pKernel, nConID, args);
}


bool PeerManage::AddEventCall(const UI32_ID nPeerCfgID, const UI32_ID nEventID, const CALLFUN pFun)
{
    PeerInfo * pInfo = NULL;
    hash_map<UI32_ID, PeerInfo *>::iterator itor = m_hashmapPeerInfo.find(nPeerCfgID);
    if (itor == m_hashmapPeerInfo.end())
    {
        LOG_ERROR("PeerConfigID is not exsits!");
        return false;
    }

    pInfo = itor->second;
    if (NULL == pInfo)
    {
        LOG_ERROR("PeerInfo is not exsits!");
        return false;
    }

    return m_pCallBackSystem->AddCall(pInfo->nEventCallConntainerID, nEventID, pFun);
}

bool PeerManage::ExecEventCallBack(const UI32_ID nPeerCfgID, const UI32_ID nEventID, IKernel * pKernel, const UI64 nConID, const VarList & args)
{
    PeerInfo * pInfo = NULL;
    hash_map<UI32_ID, PeerInfo *>::iterator itor = m_hashmapPeerInfo.find(nPeerCfgID);
    if (itor == m_hashmapPeerInfo.end())
    {
        LOG_ERROR("PeerConfigID is not exsits!");
        return false;
    }

    pInfo = itor->second;
    if (NULL == pInfo)
    {
        LOG_ERROR("PeerInfo is not exsits!");
        return false;
    }

    return m_pCallBackSystem->ExecCallBack(pInfo->nEventCallConntainerID, nEventID, pKernel, nConID, args);
}

