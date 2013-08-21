#ifndef TestLogic3_H
#define TestLogic3_H

#include "IKernel.h"
#include "ILogicModule.h"
#include "TestLogic4.h"
#include "VarList.h"

#include <iostream>
using namespace std;

class TestLogic3 : public ILogicModule
{
public:
	TestLogic3(){}
	~TestLogic3(){}

	virtual bool Initialize(IKernel * pKernel)
	{
		m_pSelf = this;
        m_pTestLogic4 = (TestLogic4 *)pKernel->FindModule("TestLogic4");
		return true;
	}

	virtual bool DelayInitialize(IKernel * pKernel)
	{
		pKernel->AddMsgCall("Logic", 10000, TestLogic3::Test);
        pKernel->AddEventCall("Lister", EVENT_CONNECT, TestLogic3::Connect);
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
		if (args.Count() != 2 ||
			args.Type(1) != TYPE_INT)
		{
			return 0;
		}

		cout << "MsgID : " << args.GetInt(0) << endl;

		return 0;
	}

    static I32 Connect(IKernel * pKernel, const UI64 nConID, const VarList &args) {
        UI32 i = nConID;

        return i;
    }

private:
	static TestLogic3 * m_pSelf;
    TestLogic4 * m_pTestLogic4;
};

TestLogic3 * TestLogic3::m_pSelf = NULL;

#endif
