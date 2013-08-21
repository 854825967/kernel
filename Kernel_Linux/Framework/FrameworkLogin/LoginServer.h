/* 
 * File:   Login.h
 * Author: traveler
 *
 * Created on January 4, 2013, 5:56 PM
 */

#ifndef LOGINSERVER_H
#define	LOGINSERVER_H

#include "../Public/ComDefine.h"
#include "../FrameworkInterface/ILoginServer.h"
#include "../Public/ServerMessage.h"
#include "../Public/Tools.h"
#include "../Public/IKernel.h"

class LoginServer : public ILoginServer {
public:
    virtual bool Initialize(IKernel * pKernel) {
        LOG_ECHO(name, 256, "ServerType : %s", pKernel->GetServerType());
        
        return true;
    }
    virtual bool DelayInitialize(IKernel * pKernel) {
        pKernel->AddMsgCall("Gate", 10000, LoginServer::NewGateConnectIn);
        pKernel->AddMsgCall("Gate", 10002, LoginServer::Test2);
        
        return true;
    }
    virtual bool Destroy(IKernel * pKernel) {
        return true;
    }
    
private:
    static I32 Test2(const IKernel * pKernel, const UI32 nLinkID, const UI32, const IVarList & args) {
        if(args.Count() != 2 ||
                args.Type(1) != TYPE_INT) {
            Assert(false);
            return -1;
        }

        return 0;        
    }
    
    static I32 NewGateConnectIn(const IKernel * pKernel, const UI32 nLinkID, const UI32, const IVarList &) {
        CIdentity player = CIdentity_INIT(nLinkID);
        pKernel->Register(nLinkID, player);
        UI32 nfr = RandomInt(1000) * 10;
        while(nfr < 500) {
            nfr = 500;
        }
        pKernel->AddHeartBeat(player, LoginServer::TestHeartBeat, nfr);
        printf("LinkID %d\n", nLinkID);
        LOG_ECHO(log, 128, "LinkID %d", nLinkID);
        return 0;
    }
    
    static I32 TestHeartBeat(const IKernel * pKernel, const CIdentity & player, const I32 nBeatCount) {
        pKernel->SendMsg(player, Archive() << 10001 << "HeartBeat" << nBeatCount);
    }
};

#endif	/* GATE_H */

