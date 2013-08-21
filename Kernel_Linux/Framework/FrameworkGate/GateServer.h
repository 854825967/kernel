/* 
 * File:   GateServer.h
 * Author: traveler
 *
 * Created on January 4, 2013, 5:56 PM
 */

#ifndef GATESERVER_H
#define GATESERVER_H
#include "../Public/ILogicModule.h"
#include "../FrameworkInterface/IGateServer.h"
#include "../Public/IKernel.h"

class GateServer : public IGateServer {
public:
    virtual bool Initialize(IKernel * pKernel) {
        LOG_ECHO("ServerType : %s", pKernel->GetServerType());
        
        return true;
    }
    virtual bool DelayInitialize(IKernel * pKernel) {
        pKernel->AddKernelEvent("Login", KERNEL_EVENT_CONNECT_SUCCESS, GateServer::ConnectedToLoginServer);
        pKernel->AddMsgCall("Login", 10001, GateServer::TestHeartBeat);
        
        return true;
    }
    virtual bool Destroy(IKernel * pKernel) {
        
        return true;
    }
    virtual UI32 GetLoginServerPeerID() {
        return 0;
    }
private:
    static I32 ConnectedToLoginServer(const IKernel * pKernel, const UI32 nLinkID, const UI32, const IVarList &) {
        LOG_ECHO("%d", nLinkID);
        pKernel->SendMsg(nLinkID, Archive() << 10000 << pKernel->GetServerID());
        return 0;
    }
    
    static I32 TestHeartBeat(const IKernel * pKernel, const UI32 nLinkID, const UI32, const IVarList & args) {
        if(args.Count() != 3 ||
                args.Type(1) != TYPE_STRING ||
                args.Type(2) != TYPE_INT) {
            Assert(false);
        }
        LOG_ECHO("Beat : %d", args.GetInt(2));
        pKernel->SendMsg(nLinkID, Archive() << 10002 << args.GetInt(2));
        
        return 0;
    }

private:
    static GateServer * m_pSelf;
    UI32 m_nLoginSrvPeerID;
};

#endif	/* GATESERVER_H */

