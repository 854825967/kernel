/* 
 * File:   XXAL_chat.cpp
 * Author: traveler
 * 
 * Created on December 19, 2012, 2:27 PM
 */

#include "XXAL_chat.h"


CHashMap<string, UI64> XXAL_chat::m_mapOnlineUser;
UI64 XXAL_chat::m_nUserID = 0;

bool XXAL_chat::Initialize(IKernel * pKernel) {
    LOG_ECHO("ServerType : %s", pKernel->GetServerType());
    return true;
}

bool XXAL_chat::DelayInitialize(IKernel * pKernel) {
    XXAL_chat::m_mapOnlineUser.clear();
    XXAL_chat::m_nUserID = 0;
    pKernel->AddMsgCall("CLIENT", CLIENT_MSG_LOGIN, XXAL_chat::Login);
    return true;
}

bool XXAL_chat::Destroy(IKernel * pKernel) {
    return true;
}

I32 XXAL_chat::Login(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args) {
    if (args.Count() != 2 ||
            args.Type(1) != TYPE_STRING) {
        LOG_ECHO("client login : error msg format");
        return -1;
    }

    string username = args.GetString(1);

    Archive msg;
    if (m_mapOnlineUser.find(username) == m_mapOnlineUser.end()) {
        msg << SERVER_MSG_LOGIN_RESULT << 1 << 0;
    } else {
        m_mapOnlineUser.insert(make_pair(username, m_nUserID));
        msg << SERVER_MSG_LOGIN_RESULT << 0 << m_nUserID++;
    }

    pKernel->SendMsg(nPeerID, msg);

    return 0;
}
