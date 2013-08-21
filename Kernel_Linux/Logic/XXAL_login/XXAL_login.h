/* 
 * File:   XXAL_login.h
 * Author: traveler
 *
 * Created on January 4, 2013, 12:23 PM
 */

#ifndef XXAL_LOGIN_H
#define	XXAL_LOGIN_H

#include "../Public/EventDefine.h"
#include "../Public/IKernel.h"
#include "../Public/ILogicModule.h"
#include "../LogicInterface/IXXAL_login.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;

class IGateServer;

enum {
    MSG_SAY_HI_TO_WOMAN = 100000,
    MSG_SAY_HI_TO_MAN = 100001,
    
};

class XXAL_login : public IXXAL_login {
public:
    virtual bool Initialize(IKernel * pKernel);
    virtual bool DelayInitialize(IKernel * pKernel);
    virtual bool Destroy(IKernel * pKernel);

private:
    //some fun in gate server
    static I32 GateServer_Login(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args);
    static I32 GateServer_LoginResult(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args);
    
    //some fun in login server
    static I32 LoginServer_Login(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args);
    
    //test for chaobi
    static I32 SayHiToWoman(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args);
    static I32 RecvHiFromMan(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args);
    static I32 RecvHiFromWoman(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args);

private:
    static IGateServer * m_pGateServer;
    static XXAL_login * m_pSelf;
    unordered_map<UI64, string> m_mapLoginInfo;
};

#endif	/* XXAL_LOGIN_H */

