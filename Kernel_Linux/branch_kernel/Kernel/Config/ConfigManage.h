#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <map>
#include "../Interface/IConfigManage.h"
using namespace std;

namespace CConfig {
    static const char * FILE_PATH_GLOBLA_CONFIG = "Config/Kernel/Globla.ini";
    static const char * FILE_PATH_BASE_CONFIG = "Config/Kernel/Base.ini";
};

class ConfigManage : public IConfigManage {
public:
    static IConfigManage * Employ();
    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();
    virtual const CIniConfig * GetConfig(const UI8 nConfigID);
private:
    ConfigManage();
    ~ConfigManage();
    static ConfigManage * m_pSelf;
    map<UI8, CIniConfig *> m_config;
};

#endif //_CONFIG_H_
