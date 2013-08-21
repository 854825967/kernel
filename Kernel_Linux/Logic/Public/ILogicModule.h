#ifndef ILOGICMODULE_H
#define ILOGICMODULE_H

#include "ComDefine.h"
#include "Tools.h"

class IKernel;

#define MODULE_NAME_LENGTH 64

class ILogicModule {
public:
    virtual bool Initialize(IKernel * pKernel) = 0;
    virtual bool DelayInitialize(IKernel * pKernel) = 0;
    virtual bool Destroy(IKernel * pKernel) = 0;

public:

    ILogicModule() {
        m_pNextModule = NULL;
        m_pName[MODULE_NAME_LENGTH - 1] = 0;
    }

    bool SetNext(ILogicModule * & pModule) {
        m_pNextModule = pModule;
        return true;
    }

    ILogicModule * GetNext() {
        return m_pNextModule;
    }

    bool SetName(const char * pName) {
        memcpy(m_pName, pName, MODULE_NAME_LENGTH - 1);
        return true;
    }

    const char * GetName() {
        return m_pName;
    }

private:
    ILogicModule * m_pNextModule;
    char m_pName[MODULE_NAME_LENGTH];
};

typedef ILogicModule * (*GetModuleFun)(void);

#define NAME_OF_GET_LOGIC_FUN "GetLogicModule"
#define GET_LOGIC_FUN GetLogicModule

#ifndef KERNEL_PROCESS
//extern ILogicModule * plogicModule = NULL;

#define CREATE_MODULE(name) \
    class factroy##name    \
    {    \
    public:    \
        factroy##name(ILogicModule * & pModule)    \
        {    \
            ILogicModule * pModule##name = NEW name;    \
            pModule##name->SetName(#name);    \
            pModule##name->SetNext(pModule); \
            pModule = pModule##name;    \
        }    \
    };    \
    factroy##name factroy##name(plogicModule);


#define GET_DLL_ENTRANCE \
static ILogicModule * plogicModule = NULL; \
extern "C" ILogicModule * GET_LOGIC_FUN() {    \
    srand(GetCurrentTimeTick()); \
    return plogicModule; \
}

#endif    //KERNEL_PROCESS

#endif  //ILOGICMODULE_H
