/* 
 * File:   XXAL_chat.h
 * Author: traveler
 *
 * Created on December 19, 2012, 2:27 PM
 */

#ifndef CHAT_H
#define	CHAT_H

#include "../Public/ILogicModule.h"
#include "../Public/EventDefine.h"
#include "../Public/IKernel.h"
#include "../Public/CHashMap.h"
#include <unistd.h>
#include <iostream>
using namespace std;

#define MSG(main, sub) (((main) << 16) + (sub))

enum {
    CLIENT_MSG_LOGIN = MSG(0x1, 0x1), //args: (string)username
    CLIENT_MSG_GET_ONLINE_LIST = MSG(0x1, 0x3), //args: (u64)userid
    CLIENT_MSG_SEND_GROUP_MSG = MSG(0x1, 0x4), //args: (u64)userid, (64)groupid, (string)msg_cont

    CLIENT_MSG_LOGOUT = MSG(0x1, 0x5), //args: (u64)userid
};

enum {
    SERVER_MSG_LOGIN_RESULT = MSG(0x2, 0x1), //args: (s32)rescode(0Ϊ�ɹ�, ��0Ϊʧ��), (u64)userid
    SERVER_MSG_ONLINE_LIST = MSG(0x2, 0x2), //args: (u16)friendCount, {(u64)friend_userid, (string)friend_name,....}
    SERVER_MSG_GROUP_MSG = MSG(0x2, 0x3), //args: (u64)sender_userid, (u64)group_id, (u64)timetick, (string)msg_cont
};

class XXAL_chat : public ILogicModule {
public:

    virtual bool Initialize(IKernel * pKernel);
    virtual bool DelayInitialize(IKernel * pKernel);
    virtual bool Destroy(IKernel * pKernel);
private:
    static I32 Login(const IKernel * pKernel, UI32 nPeerID, UI32 notuse, const IVarList & args);

private:
    static CHashMap<string, UI64> m_mapOnlineUser;
    static UI64 m_nUserID;
};

#endif	/* CHAT_H */

