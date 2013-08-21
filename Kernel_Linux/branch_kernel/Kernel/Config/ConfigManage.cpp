#include "ConfigManage.h"
#include "../../Public/Tools.h"
#include "../../Public/CIniConfig.h"

ConfigManage * ConfigManage::m_pSelf = NULL;

IConfigManage * ConfigManage::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW ConfigManage;
        if (!m_pSelf->Bron()) {
            Assert(false);
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

bool ConfigManage::Bron() {
    char FilePath[1024] = {0};
    //memset(FilePath, 0, 256);
    snprintf(FilePath, 1024, "%s/%s", GetAppPath(), CConfig::FILE_PATH_GLOBLA_CONFIG);
    CIniConfig * pConfig = NEW CIniConfig;
    if (!pConfig->LoadConfig(FilePath)) {
        Assert(false);
        return false;
    }
    m_config.insert(make_pair((UI8) KERNEL_CONFIG_GLOBLA_INI, pConfig));

    memset(FilePath, 0, 256);
    snprintf(FilePath, 265, "%s/%s", GetAppPath(), CConfig::FILE_PATH_BASE_CONFIG);
    pConfig = NEW CIniConfig;
    if (!pConfig->LoadConfig(FilePath)) {
        Assert(false);
        return false;
    }
    m_config.insert(make_pair((UI8) KERNEL_CONFIG_BASE_INI, pConfig));
    return true;
}

bool ConfigManage::Dead() {
    return true;
}

bool ConfigManage::Initialize() {

    return true;
}

bool ConfigManage::Destroy() {
    if(NULL != m_pSelf) {
        delete m_pSelf;
        m_pSelf = NULL;
    }
    return true;
}

ConfigManage::ConfigManage() {
    
}

ConfigManage::~ConfigManage() {
    map<UI8, CIniConfig *>::iterator ibegin = m_config.begin();
    map<UI8, CIniConfig *>::iterator iend = m_config.end();
    while(ibegin != iend) {
        if(ibegin->second != NULL) {
            delete ibegin->second;
            ibegin->second = NULL;
        }
        ibegin ++;
    }
    m_config.clear();    
}

const CIniConfig * ConfigManage::GetConfig(const UI8 nConfigID) {

    map<UI8, CIniConfig *>::iterator itor = m_config.find(nConfigID);
    if (itor == m_config.end()) {
        Assert(false);
        return NULL;
    }

    return itor->second;
}
