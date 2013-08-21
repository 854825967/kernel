#include "CXmlConfig.h"
#include "VarList.h"
#include "Tools.h"

CXmlConfig::CXmlConfig(const char* pFilePath) {
    m_pTiXmlDocument.LoadFile(pFilePath);
    m_pRootElement = m_pTiXmlDocument.RootElement();
}

const char * CXmlConfig::GetValue(const IVarList& tree, const char* pStrName) {
    UI32 nCount = tree.Count();
    if (nCount <= 0) {
        Assert(false);//
        return 0;
    }

    TiXmlElement * pElement = m_pRootElement;

    for (UI32 i = 0; i < nCount; i++) {
        if (tree.Type(i) != TYPE_STRING || NULL == pElement) {
            Assert(false);//
            return 0;
        }
        pElement = pElement->FirstChildElement(tree.GetString(i));
    }

    return pElement->Attribute(pStrName);
}

I32 CXmlConfig::GetIntValue(const IVarList & tree, const char * pStrName) {
    return StringAsInt( GetValue(tree, pStrName) );
}

double CXmlConfig::GetDoubleValue(const IVarList & tree, const char * pStrName) {
    return StringAsFloat( GetValue(tree, pStrName) );
}

const char * CXmlConfig::GetStringValue(const IVarList & tree, const char * pStrName) {
    return GetValue(tree, pStrName);
}
