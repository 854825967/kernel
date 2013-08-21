#ifndef _CXMLCONFIG_H_
#define _CXMLCONFIG_H_

#include "ComDefine.h"
#include "TinyXml/tinyxml.h"
class IVarList;

class CXmlConfig {
public:
    CXmlConfig(const char * pFilePath);
    I32 GetIntValue(const IVarList & tree, const char * pStrName);
    double GetDoubleValue(const IVarList & tree, const char * pStrName);
    const char * GetStringValue(const IVarList & tree, const char * pStrName);
private:
    const char * GetValue(const IVarList & tree, const char * pStrName);
private:
    TiXmlDocument m_pTiXmlDocument;
    TiXmlElement * m_pRootElement;
};

#endif //_CXMLCONFIG_H_
