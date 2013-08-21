#ifndef TESTLOGIC_H
#define TESTLOGIC_H

#include "IKernel.h"
#include "ILogicModule.h"
#include "TestLogic2.h"

class TestLogic : public ILogicModule
{
public:
    TestLogic(){}
    ~TestLogic(){}

    virtual bool Initialize(IKernel * pKernel)
    {
        m_pSelf = this;
        m_pTestLogic2 = (TestLogic2 *)pKernel->FindModule("TestLogic2");
        return true;
    }

    virtual bool DelayInitialize(IKernel * pKernel)
    {
        //pKernel->AddMsgCall("Logic", 10000, TestLogic::Test);
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
    static TestLogic * m_pSelf;
    TestLogic2 * m_pTestLogic2;
};

TestLogic * TestLogic::m_pSelf = NULL;

#endif
