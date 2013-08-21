#include "CallBackSystem.h"
#include "CoreModuleManage.h"

CallBackSystem * CallBackSystem::m_pSelf = NULL;
CoreModuleManage * CallBackSystem::m_pCoreModuleManage = NULL;

bool CallBackSystem::Employ(const char * pStrModuleName)
{
    Assert(NULL == m_pSelf);
    if (NULL == m_pSelf)
    {
        m_pSelf = NEW CallBackSystem;
        if (NULL == (m_pCoreModuleManage = CoreModuleManage::Employ()))
        {
            Assert(NULL != m_pCoreModuleManage);
            LOG_ERROR("CallBackSystem::Employ Get CoreModuleManage error");
            return false;
        }
        if (false == (m_pCoreModuleManage->AddModule(pStrModuleName, m_pSelf)))
        {
            Assert(false);
            LOG_ERROR("CallBackSystem::Employ CoreModuleManage::AddModule error");
            return false;
        }
    }

    return true;
}

bool CallBackSystem::Initialize()
{
    return true;
}

bool CallBackSystem::DelayInitialize()
{

    return true;
}

bool CallBackSystem::Destroy()
{
    Assert(NULL != m_pSelf);
    if (NULL != m_pSelf)
    {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}


CallBackSystem::CallBackSystem()
{
    m_nCallContainerCount = 0;
    m_vctCallContainer.clear();
}

CallBackSystem::~CallBackSystem()
{
    UI32 nCount = m_vctCallContainer.size();
    for (UI32 i=0; i<nCount; i++)
    {
        delete m_vctCallContainer[i];
    }
    m_vctCallContainer.clear();
}

UI32_ID CallBackSystem::RegisterCallContainer()
{
    UI32_ID nID = m_nCallContainerCount++;
    CallBack<UI32_ID> * pCallBack = NEW CallBack<UI32_ID>;
    m_vctCallContainer.push_back(pCallBack);

    return nID;
}

bool CallBackSystem::AddCall(const UI32_ID nConntainerID, const UI32_ID nCallID, const CALLFUN pFun)
{
    if (nConntainerID >= m_nCallContainerCount)
    {
        LOG_ERROR("MsgCallContainer is not exists");
        return false;
    }

    CallBack<UI32_ID> * pContainer = m_vctCallContainer[nConntainerID];
    return pContainer->AddCall(nCallID, pFun);
}

bool CallBackSystem::ExecCallBack(const UI32_ID nContainerID, const UI32_ID nCallID, IKernel * pKernel, const UI64 nUserID, const VarList & args)
{
    if (nContainerID >= m_nCallContainerCount)
    {
        LOG_ERROR("MsgCallContainer is not exists");
        return false;
    }

    CallBack<UI32_ID> * pContainer = m_vctCallContainer[nContainerID];

    return pContainer->ExecCallBack(nCallID, pKernel, nUserID, args);
}