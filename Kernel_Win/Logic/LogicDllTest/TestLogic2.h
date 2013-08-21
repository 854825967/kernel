#ifndef TESTLOGIC2_H
#define TESTLOGIC2_H

#include "IKernel.h"
#include "ILogicModule.h"
#include "VarList.h"
#include "Archive.h"
#include "MessageDefine.h"
#include <iostream>
using namespace std;

class TestLogic2 : public ILogicModule
{
public:
    TestLogic2(){}
    ~TestLogic2(){}

    virtual bool Initialize(IKernel * pKernel)
    {
        m_pSelf = this;
        return true;
    }

    virtual bool DelayInitialize(IKernel * pKernel)
    {
        pKernel->AddMsgCall("Lister", MESSAGE_TEST, TestLogic2::Test);
        pKernel->AddEventCall("Lister", EVENT_CONNECT, TestLogic2::ConnectLister);
        pKernel->AddEventCall("Lister", EVENT_NEW_CONNECT, TestLogic2::NewConnectOnLister);
        return true;
    }

    virtual bool Destroy(IKernel * pKernel)
    {
        delete m_pSelf;
        m_pSelf = NULL;
        return true;
    }

private:
    static I32 Test(IKernel * pKernel, const UI64 nConnectID, const VarList & args)
    {
        cout << "Test" << endl;

        Archive archive;
        archive << args.GetInt(0) << args.GetInt(1) << args.GetString(2);
        pKernel->TcpSend(nConnectID, archive);
        return 0;
    }

    static I32 NewConnectOnLister(IKernel * pKernel, const UI64 nConnectID, const VarList & args)
    {
        if (args.Count() != 2 ||
            args.Type(1) != TYPE_STRING)
        {
            return 0;
        }

        UI32 nMsgID = args.GetInt(0);
        const char * pStr = args.GetString(1);

        Archive archive;
        archive << MESSAGE_TEST << nMsgID << pStr;

        pKernel->TcpSend(nConnectID, archive);

        return 0;
    }

    static I32 ConnectLister(IKernel * pKernel, const UI64 nConnectID, const VarList & args)
    {
        UI32 nID = nConnectID;

        UI32 nAppID = pKernel->GetAppID();
        UI32 nClusterID = pKernel->GetClusterID();
        UI32 nServerID = pKernel->GetServerID();

        Archive archive;
        archive << 1000 << "Hello World";

        pKernel->TcpSend(nConnectID, archive);
        return 0;
    }

private:
    static TestLogic2 * m_pSelf;
};

TestLogic2 * TestLogic2::m_pSelf = NULL;

#endif
