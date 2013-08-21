#include "CoreModuleManage.h"

CoreModuleManage * CoreModuleManage::m_pSelf = NULL;

CoreModuleManage::CoreModuleManage()
{
    m_pListICModule = NULL;
}

CoreModuleManage::~CoreModuleManage()
{
    while (m_pListICModule != NULL)
    {
        if (NULL == m_pListICModule->pModule)
        {
            m_pListICModule = m_pListICModule->next;
            continue;
        }
        m_pListICModule->pModule->Destroy();
        m_pListICModule = m_pListICModule->next;
    }
}

ICoreModule * CoreModuleManage::GetModule(const char * pStrModuleName)
{
    if (NULL == pStrModuleName)
    {
        LOG_ERROR("CoreModuleManage::GetModule : pass a NULL point");
        return false;
    }

    ICModuleList * pList = m_pListICModule;

    while (pList != NULL)
    {
        if (pList->name == pStrModuleName)
        {
            return pList->pModule;
        }
        pList = pList->next;
    }

    return NULL;
}

CoreModuleManage * CoreModuleManage::Employ()
{
    if (NULL == m_pSelf)
    {
        m_pSelf = NEW CoreModuleManage;
    }

    return m_pSelf;
}

bool CoreModuleManage::Destroy()
{
    if (NULL != m_pSelf)
    {
        delete m_pSelf;
        m_pSelf = NULL;
    }
    return true;
}

bool CoreModuleManage::AddModule(const char * pStrModuleName, ICoreModule * ICModule) {
    if (NULL == pStrModuleName || NULL == ICModule) {
        LOG_ERROR("CoreModuleManage::AddModule : pass a NULL point");
        return false;
    }

    static ICModuleList * pListEnd = NULL;

    if (NULL == m_pListICModule) {
        m_pListICModule = NEW ICModuleList;
        m_pListICModule->name = pStrModuleName;
        m_pListICModule->pModule = ICModule;
        m_pListICModule->next = NULL;
        pListEnd = m_pListICModule;
    } else {
        pListEnd->next = NEW ICModuleList;
        pListEnd->next->name = pStrModuleName;
        pListEnd->next->pModule = ICModule;
        pListEnd->next->next = NULL;
        pListEnd = pListEnd->next;
    }

    return true;
}

bool CoreModuleManage::InitializeCModules()
{
    ICModuleList * pList = m_pListICModule;

    while (pList != NULL) {
        if (NULL != pList->pModule) {
            pList->pModule->Initialize();
        }
        pList = pList->next;
    }

    return true;
}

bool CoreModuleManage::DelayInitializeCModules()
{
    ICModuleList * pList = m_pListICModule;

    while (pList != NULL) {
        if (NULL != pList->pModule) {
            pList->pModule->DelayInitialize();
        }
        pList = pList->next;
    }

    return true;
}