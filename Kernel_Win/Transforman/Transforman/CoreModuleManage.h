#ifndef COREMODULEMANAGE_H
#define COREMODULEMANAGE_H

#include <map>
#include <string>
using namespace std;
#include "ComDefine.h"
#include "ICoreModule.h"

#define EMPLOY_MODULE(name) \
    name::Employ(#name);

typedef struct icmodulelist
{
    string name;
    ICoreModule * pModule;
    struct icmodulelist * next;
}ICModuleList;

class CoreModuleManage
{
public:
    static CoreModuleManage * Employ();

    bool Destroy();
    bool AddModule(const char * pStrModuleName, ICoreModule * ICModule);
    ICoreModule * GetModule(const char * pStrModuleName);
    bool InitializeCModules();
    bool DelayInitializeCModules();
private:
    CoreModuleManage();
    ~CoreModuleManage();

private:
    static CoreModuleManage * m_pSelf;
    ICModuleList * m_pListICModule;
};

#endif  //COREMODULEMANAGE_H