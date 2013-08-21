#ifndef _CINICONFIG_H_
#define _CINICONFIG_H_

#include "ComDefine.h"
#include "simpleini/SimpleIni.h"
#include "Var.h"
#include <string>
#include <map>
using namespace std;

struct config {
    map<string, Var> m_details;
};

class CIniConfig {
public:
    CIniConfig();
    CIniConfig(const char * pIniFilePath);
    bool LoadConfig(const char * pIniFilePath);
    I32 GetIntConfig(const char * pConfigName, const char * pKeyName) const;
    double GetDoubleConfig(const char * pConfigName, const char * pKeyName) const;
    const char * GetStringConfig(const char * pConfigName, const char * pKeyName) const;
private:
    CSimpleIni m_ini; 
    bool m_isload;
};

#endif //_CINICONFIG_H_
