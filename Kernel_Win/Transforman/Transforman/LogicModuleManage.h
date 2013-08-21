#ifndef LOGICMODULEMANAGE_H
#define LOGICMODULEMANAGE_H

#include "ComDefine.h"
#include <string>
#include <map>
using namespace std;
#include "ICoreModule.h"

class IKernel;
class ILogicModule;
class TiXmlElement;
class CoreModuleManage;

typedef ILogicModule* (__cdecl *DllFun)();

class LogicModuleManage : public ICoreModule
{
public:
    static bool Employ(const char * pStrModuleName);

    virtual bool Initialize();
    virtual bool DelayInitialize();
    virtual bool Destroy();

    bool ModulesInitialize();
    bool ModulesDelayInitialize();

    ILogicModule * FindModule(const char * pStrModuleName);
protected:
    LogicModuleManage();
    ~LogicModuleManage();
private:
    static LogicModuleManage * m_pSelf;
    static CoreModuleManage * m_pCoreModuleManage;
    IKernel * m_pKernel;
    map<string, ILogicModule *> m_mapModule;
};

#endif    //LOGICMODULEMANAGE_H
