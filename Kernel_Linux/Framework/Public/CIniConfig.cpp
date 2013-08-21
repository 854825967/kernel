#include "CIniConfig.h"
#include "Tools.h"

CIniConfig::CIniConfig() {
    m_isload = false;
}

CIniConfig::CIniConfig(const char* pIniFilePath) {
    if (m_ini.LoadFile(pIniFilePath) < 0) {
        Assert(false);
        m_isload = false;
    }

    m_isload = true;
}

bool CIniConfig::LoadConfig(const char* pIniFilePath) {
    if (m_ini.LoadFile(pIniFilePath) < 0) {
        Assert(false);
        m_isload = false;
        return false;
    }

    m_isload = true;
    return true;
}

I32 CIniConfig::GetIntConfig(const char* pConfigName, const char* pKeyName) const {
    if (false == m_isload) {
        //assert
        return 0;
    }

    return StringAsInt(m_ini.GetValue(pConfigName, pKeyName, "0"));
}

double CIniConfig::GetDoubleConfig(const char* pConfigName, const char* pKeyName) const {
    if (false == m_isload) {
        //assert
        return 0;
    }

    return StringAsFloat(m_ini.GetValue(pConfigName, pKeyName, "0"));
}

const char * CIniConfig::GetStringConfig(const char* pConfigName, const char* pKeyName) const {
    if (false == m_isload) {
        //assert
        return 0;
    }

    return m_ini.GetValue(pConfigName, pKeyName, "0");
}
