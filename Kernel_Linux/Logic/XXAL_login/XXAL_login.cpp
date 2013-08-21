/* 
 * File:   XXAL_login.cpp
 * Author: traveler
 * 
 * Created on January 4, 2013, 12:23 PM
 */

#include "XXAL_login.h"
#include "../Public/ComDefine.h"
#include "../LogicDefine/ServerCommand.h"
#include "../../Framework/FrameworkInterface/IGateServer.h"

IGateServer * XXAL_login::m_pGateServer = NULL;
XXAL_login * XXAL_login::m_pSelf = NULL;

bool XXAL_login::Initialize(IKernel * pKernel) {
    m_pSelf = this;
    return true;
}

bool XXAL_login::DelayInitialize(IKernel * pKernel) {

    //    m_pGateServer = (IGateServer *) pKernel->FindModule("GateServer");
    //    Assert(m_pGateServer != NULL);
    //
    //    string strServerType = pKernel->GetServerType();
    //
    //    if (strServerType == "Gate") {
    //        pKernel->AddMsgSOCKETCALL("Client", MSG_FROM_CLIENT_TO_GATE_LOGIN, XXAL_login::GateServer_Login);
    //        pKernel->AddMsgSOCKETCALL("Login", MSG_FROM_LOGIN_TO_GATE_LOGIN_RESULT, XXAL_login::GateServer_LoginResult);
    //    } else if (strServerType == "Login") {
    //        pKernel->AddMsgSOCKETCALL("Gate", MSG_FROM_GATE_TO_LOGIN_LOGIN, XXAL_login::LoginServer_Login);
    //        //pKernel->AddMsgSOCKETCALL();
    //    } else if (strServerType == "Logic") {
    //
    //    }
    
    string strSrvType = pKernel->GetServerType();
    LOG_ECHO(strSrvType.c_str());
    if (strSrvType == "man") {
        pKernel->AddKernelEventSOCKETCALL("woman", KERNEL_EVENT_CONNECT_SUCCESS, XXAL_login::SayHiToWoman);
        pKernel->AddMsgSOCKETCALL("woman", MSG_SAY_HI_TO_MAN, XXAL_login::RecvHiFromWoman);
    } else if (strSrvType == "woman") {
        pKernel->AddMsgSOCKETCALL("man", MSG_SAY_HI_TO_WOMAN, XXAL_login::RecvHiFromMan);
    }

    return true;
}

bool XXAL_login::Destroy(IKernel * pKernel) {

    return true;
}

I32 XXAL_login::GateServer_Login(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args) {
    if (args.Count() < 4 ||
            args.Type(1) != TYPE_STRING ||
            args.Type(2) != TYPE_STRING) {
        LOG_ERROR("Error Msg, MSG_FROM_CLIENT_TO_GATE_LOGIN");
        Assert(false);
        return -1;
    }
    Archive msg;

    msg << MSG_FROM_GATE_TO_LOGIN_LOGIN << nPeerID << args.GetString(1) << args.GetString(2);

    pKernel->SendMsg(m_pGateServer->GetLoginServerPeerID(), msg);

    return 0;
}

I32 XXAL_login::GateServer_LoginResult(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args) {
    if (args.Count() < 5 ||
            args.Type(1) != TYPE_INT ||
            args.Type(2) != TYPE_INT ||
            args.Type(3) != TYPE_INT64 ||
            args.Type(4) != TYPE_STRING) {
        LOG_ERROR("Error Msg, MSG_FROM_LOGIN_TO_GATE_LOGIN_RESULT");
        Assert(false);
        return -1;
    }

    char log[1024] = {0};
    snprintf(log, 1024, "login Result : %d, uid : %ld, identity : %s, backargs peerid : %d", \
            args.GetInt(2), args.GetInt64(3), args.GetString(4), args.GetInt(1));
    LOG_TRACE(log);



    return 0;
}

I32 XXAL_login::LoginServer_Login(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args) {
    if (args.Count() < 4 ||
            args.Type(1) != TYPE_INT ||
            args.Type(2) != TYPE_STRING ||
            args.Type(3) != TYPE_STRING) {
        LOG_ERROR("Error Msg, MSG_FROM_GATE_TO_LOGIN_LOGIN");
        Assert(false);
        return -1;
    }

    const char * pStrName = args.GetString(2);
    const char * pStrPwd = args.GetString(3);
    char log[1024] = {0};
    snprintf(log, 1024, "login name : %s, pwd : %s, backargs peerid : %d", pStrName, pStrPwd, args.GetInt(1));
    LOG_TRACE(log);

    Archive msg;
    msg << MSG_FROM_LOGIN_TO_GATE_LOGIN_RESULT << args.GetInt(1) << LOGIN_SUCCEED << (UI64) 100086 << "ABECFJKDSLFDSFF";
    pKernel->SendMsg(nPeerID, msg);

    return 0;
}

I32 XXAL_login::SayHiToWoman(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args) {
    Archive msg;
    //cout << "hello girl" << endl;
    msg << MSG_SAY_HI_TO_WOMAN << "Hi,girl";

    pKernel->SendMsg(nPeerID, msg);

    return 0;
}

I32 XXAL_login::RecvHiFromMan(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args) {
    if (args.Count() != 2 ||
            args.Type(1) != TYPE_STRING) {
        Assert(false);
        return -1;
    }

    LOG_ECHO(args.GetString(1));

    Archive msg;
    msg << MSG_SAY_HI_TO_MAN << "hi,boy";

    pKernel->SendMsg(nPeerID, msg);

    return 0;
}

I32 XXAL_login::RecvHiFromWoman(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args) {
    if (args.Count() != 2 ||
            args.Type(1) != TYPE_STRING) {
        Assert(false);
        return -1;
    }

    LOG_ECHO(args.GetString(1));
    
    return 0;
}
