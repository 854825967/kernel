#ifndef TestLogic4_H
#define TestLogic4_H

#include "IKernel.h"
#include "ILogicModule.h"

class TestLogic4 : public ILogicModule
{
public:
    TestLogic4(){}
    ~TestLogic4(){}

    virtual bool Initialize(IKernel * pKernel)
    {
        m_pSelf = this;
        return true;
    }

    virtual bool DelayInitialize(IKernel * pKernel)
    {
        pKernel->AddMsgCall("Logic", 10000, TestLogic4::Test);
        return true;
    }

    virtual bool Destroy(IKernel * pKernel)
    {
        delete m_pSelf;
        m_pSelf = NULL;
        return true;
    }


private:
    static I32 Test(IKernel * pKernel, const UI64 nUserID, const VarList & args)
    {
        return 0;
    }

private:
    static TestLogic4 * m_pSelf;
};

TestLogic4 * TestLogic4::m_pSelf = NULL;

#endif
