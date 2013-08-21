#include "LogicModuleManage.h"
#include "PathDefine.h"
#include "ILogicModule.h"
#include "Kernel.h"
#include "./TinyXml/tinyxml.h"
#include "Tools.h"
#include "CoreModuleManage.h"
#include <iostream>

using namespace std;

LogicModuleManage * LogicModuleManage::m_pSelf = NULL;
CoreModuleManage * LogicModuleManage::m_pCoreModuleManage = NULL;


bool LogicModuleManage::Employ(const char * pStrModuleName)
{
    Assert(NULL == m_pSelf);
    if (NULL == m_pSelf)
    {
        m_pSelf = NEW LogicModuleManage;
        if (NULL == (m_pCoreModuleManage = CoreModuleManage::Employ()))
        {
            Assert(NULL != m_pCoreModuleManage);
            LOG_ERROR("LogicModuleManage::Employ Get CoreModuleManage error");
            return false;
        }
        if (false == (m_pCoreModuleManage->AddModule(pStrModuleName, m_pSelf)))
        {
            Assert(false);
            LOG_ERROR("LogicModuleManage::Employ CoreModuleManage::AddModule error");
            return false;
        }
    }

    return true;
}

LogicModuleManage::LogicModuleManage()
{
    m_pKernel = 0;
    m_mapModule.clear();
}

bool LogicModuleManage::DelayInitialize()
{
    if (NULL == (m_pKernel = (Kernel *)m_pCoreModuleManage->GetModule("Kernel")))
    {
        Assert(false);
        return false;
    }

    ModulesInitialize();
    ModulesDelayInitialize();

    return true;
}

bool LogicModuleManage::Destroy()
{
    Assert(NULL != m_pSelf);
    if (NULL != m_pSelf)
    {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

LogicModuleManage::~LogicModuleManage()
{
    map<string, ILogicModule *>::iterator itor = m_mapModule.begin();
    map<string, ILogicModule *>::iterator iend = m_mapModule.end();

    while (itor != iend)
    {
        itor->second->Destroy(m_pKernel);
        itor++;
    }
}


bool LogicModuleManage::Initialize()
{
    char strConfigPath[PATH_LENGTH] = {0};
    const char * pStrPathFolder = GetAppPath();
    sprintf_s(strConfigPath, "%s/%s", pStrPathFolder, CONFIG_PATH_MODULE_CONFIG);

    TiXmlDocument xmlConfig;
    if (false == xmlConfig.LoadFile(strConfigPath))
    {
        LOG_ERROR("Load LogicModuleManage Error");
        return false;
    }

    TiXmlElement * pRootElement = xmlConfig.RootElement();
    TiXmlElement * pModuleElm = pRootElement->FirstChildElement("DllName");

    while (pModuleElm != NULL)
    {
        const char * pStrDLLName = NULL;
        if (NULL == (pStrDLLName = pModuleElm->Attribute("Name")))
        {
            LOG_ERROR("Load LogicModuleManage Error");
            return false;
        }

        char strDLLPath[PATH_LENGTH] = {0};
        const char * pStrPathFolder = GetAppPath();
        sprintf_s(strDLLPath, "%s/%s%s", pStrPathFolder, CONFIG_PATH_MODULE_DLL_ROOT, pStrDLLName);

        //sprintf_s(strDLLPath, CONFIG_PATH_MODULE_DLL_ROOT, pStrDLLName);

        HINSTANCE hinst = ::LoadLibrary(strDLLPath);
        DllFun pFunGetModule = (DllFun)::GetProcAddress(hinst, NAME_OF_GET_LOGIC_FUN);

        if (NULL == pFunGetModule)
        {
            Assert(NULL != pFunGetModule);
            LOG_ERROR("Load Modules Dll Error");
            LOG_ERROR(strDLLPath);
            return false;
        }

        ILogicModule * pLogicModule = pFunGetModule();
        while (NULL != pLogicModule)
        {
            const char * pModuleName = pLogicModule->GetName();
            map<string, ILogicModule *>::iterator itor = m_mapModule.find(pModuleName);
            if (itor != m_mapModule.end())
            {
                Assert(itor == m_mapModule.end());
                LOG_ERROR("Module is exists");
                return false;
            }

            m_mapModule.insert(make_pair(pModuleName, pLogicModule));
            pLogicModule = pLogicModule->GetNext();
        }


        pModuleElm = pModuleElm->NextSiblingElement();
    }

    return true;
}

bool LogicModuleManage::ModulesInitialize()
{
    map<string, ILogicModule *>::iterator itor = m_mapModule.begin();
    map<string, ILogicModule *>::iterator iend = m_mapModule.end();

    while (itor != iend)
    {
        itor->second->Initialize(m_pKernel);
        itor++;
    }

    return true;
}

bool LogicModuleManage::ModulesDelayInitialize()
{
    map<string, ILogicModule *>::iterator itor = m_mapModule.begin();
    map<string, ILogicModule *>::iterator iend = m_mapModule.end();

    while (itor != iend)
    {
        itor->second->DelayInitialize(m_pKernel);
        itor++;
    }

    return true;
}

ILogicModule * LogicModuleManage::FindModule(const char * pStrModuleName)
{
    map<string, ILogicModule *>::iterator ifind = m_mapModule.find(pStrModuleName);
    map<string, ILogicModule *>::iterator iend = m_mapModule.end();

    if (ifind == iend)
    {
        LOG_ERROR("Module is not exists");
        return NULL;
    }
    
    return ifind->second;
}
