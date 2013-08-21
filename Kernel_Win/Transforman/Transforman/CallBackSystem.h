#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
using namespace std;
using namespace stdext;

#include "CallBackDefine.h"
#include "CallBack.h"
#include "ICoreModule.h"

class IKernel;
class CoreModuleManage;

class CallBackSystem : public ICoreModule
{
public:
    static bool Employ(const char * pStrModuleName);

    virtual bool Initialize();
    virtual bool DelayInitialize();
    virtual bool Destroy();

    UI32_ID RegisterCallContainer();
    bool AddCall(const UI32_ID nContainerID, const UI32_ID nCallID, const CALLFUN pFun);

    bool ExecCallBack(const UI32_ID nContainerID, const UI32_ID nCallID, IKernel * pKernel, const UI64 nArgc, const VarList & args);

private:
    CallBackSystem();
    ~CallBackSystem();

private:
    static CallBackSystem * m_pSelf;
    static CoreModuleManage * m_pCoreModuleManage;

    vector< CallBack<UI32_ID> * > m_vctCallContainer;
    UI32 m_nCallContainerCount;
};

#endif  //CONTAINER_H
