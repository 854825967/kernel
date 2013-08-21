/*
 * File:   LogicManage.cpp
 * Author: traveler
 *
 * Created on December 18, 2012, 6:13 PM
 */

#include "LogicManage.h"
#include <dlfcn.h>
#include "../../Public/ComDefine.h"
#include "../Config/ConfigManage.h"
#include "../../Public/CIniConfig.h"
#include "../Kernel.h"
#include "../../Public/ILogicModule.h"
#include "../../Public/VarList.h"
#include "../../Public/Tools.h"
#include "../LogSystem/LogSystem.h"

LogicManage * LogicManage::m_pSelf = NULL;
IKernel * LogicManage::m_pKernel = NULL;
IConfigManage * LogicManage::m_pConfigManage = NULL;
ILogSystem * LogicManage::m_pLogSystem = NULL;

ILogicManage * LogicManage::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW LogicManage;
        if (!m_pSelf->Bron()) {
            Assert(false);
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

bool LogicManage::Bron() {
    return true;
}

bool LogicManage::Dead() {
    return true;
}

bool LogicManage::Initialize() {
    if (NULL == (m_pKernel = Kernel::Employ()) ||
            NULL == (m_pConfigManage = ConfigManage::Employ()) ||
            NULL == (m_pLogSystem = LogSystem::Employ())) {

        LOG_ERROR(log, 128,"LogicManage::Initialize failed|Get Kernel,ConfigManage, LogSystem error");

        Assert(false);
        return false;
    }

    const CIniConfig * baseconfig = m_pConfigManage->GetConfig(KERNEL_CONFIG_BASE_INI);
    if (NULL == baseconfig) {
        LOG_ERROR(log, 128, "LogicManage::Initialize failed|Get BaseConfig Error");
        Assert(false);
        return NULL;
    }
    const char * pStrDllPath = baseconfig->GetStringConfig("Modules", "Path");
    const char * pStrDllList = baseconfig->GetStringConfig("Modules", "DLL");

    if ("" == string(pStrDllPath) ||
            "" == string(pStrDllList)) {
        LOG_ERROR(log, 128, "LogicManage::Initialize failed|Get DllPaht or DllList error");

        Assert(false);
        return false;
    }

    VarList dlls;
    SafeSplitString(pStrDllList, ";", dlls);
    UI32 ndllcount = dlls.Count();
    for (UI32 i = 0; i < ndllcount; i++) {
        char dllpath[256];
        memset(dllpath, 0, 256);
        snprintf(dllpath, 256, "%s/%s/%s", GetAppPath(), pStrDllPath, dlls.GetString(i));

        void * handle = dlopen(dllpath, RTLD_LAZY);
        if (NULL == handle) {
            LOG_ERROR("Dll %s is not exists, Error : %s", dllpath, dlerror());
            Assert(false);
            return false;
        }

        m_vctDllHandle.push_back(handle);
        
        GetModuleFun function = (GetModuleFun) dlsym(handle, "GetLogicModule");

        if (NULL == function) {
            LOG_ERROR("GetLogicModule from dll %s failed", dllpath);
            
            Assert(false);
            return false;
        }

        ILogicModule * plogic = function();

        if (NULL == plogic) {
            LOG_ERROR("ILogicModule point is NULL");
            Assert(false);
        }

        do {
            const char * pName = plogic->GetName();
            map<string, ILogicModule *>::iterator itor = m_mapModules.find(pName);
            if (itor != m_mapModules.end()) {
                LOG_ERROR("LogicModule Name %s is exists", pName);
                Assert(false);
                return false;
            }

            m_mapModules.insert(make_pair(pName, plogic));
            plogic = plogic->GetNext();
        } while (plogic != NULL);

        map<string, ILogicModule *>::iterator itor = m_mapModules.begin();
        map<string, ILogicModule *>::iterator iend = m_mapModules.end();
        while (itor != iend) {
            if (NULL == itor->second) {
                LOG_ERROR("There is no LogciModule exists");
                Assert(false);
                return false;
            }
            itor->second->Initialize(m_pKernel);
            itor++;
        }
        
        itor = m_mapModules.begin();
        while (itor != iend) {
            if (NULL == itor->second) {
                LOG_ERROR("There is no LogciModule exists");
                Assert(false);
                return false;
            }
            itor->second->DelayInitialize(m_pKernel);
            itor++;
        }
    }

    return true;
}

bool LogicManage::Destroy() {
    if (m_pSelf != NULL) {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

LogicManage::~LogicManage() {
    map<string, ILogicModule *>::iterator itor = m_mapModules.begin();
    map<string, ILogicModule *>::iterator iend = m_mapModules.end();
    while (itor != iend) {
        Assert(itor->second != NULL);
        if (NULL != itor->second) {
            itor->second->Destroy(m_pKernel);
            delete itor->second;
            itor->second = NULL;
        }
        itor++;
    }
    m_mapModules.clear();
    
    vector<void *>::iterator ivbegin = m_vctDllHandle.begin();
    vector<void *>::iterator ivend = m_vctDllHandle.end();
    while(ivbegin != ivend) {
        if(*ivbegin != NULL) {
            dlclose(*ivbegin);
        }
        ivbegin ++;
    }
    m_vctDllHandle.clear();
}

ILogicModule * LogicManage::FindModule(const char * pStrModuleName) {
    map<string, ILogicModule *>::iterator itor = m_mapModules.find(pStrModuleName);
    if (itor == m_mapModules.end()) {
        LOG_ERROR("There is no LogciModule named %s", pStrModuleName);
        Assert(false);
        return false;
    }
    if (NULL == itor->second) {
        LOG_ERROR("There is no LogciModule named %s", pStrModuleName);
        Assert(false);
        return false;
    }

    return itor->second;
}
