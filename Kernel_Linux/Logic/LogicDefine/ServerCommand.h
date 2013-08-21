/* 
 * File:   ServerCommand.h
 * Author: traveler
 *
 * Created on January 4, 2013, 12:19 PM
 */

#ifndef SERVERCOMMAND_H
#define	SERVERCOMMAND_H

enum MSG_FROM_CLIENT_TO_GATE {
    //login msg
    //arg0:int(msgid),arg1:string(username),arg2:md5(string(passwd)),
    MSG_FROM_CLIENT_TO_GATE_LOGIN = 100000,
};

enum MSG_FROM_GATE_TO_CLIENT {
    //query identity
    //arg0:int(msgid), arg1:int(login_result, 0:succsed, 1:faild), arg2:int64(userid), arg3:string(strIdentity),
    MSG_FROM_GATE_TO_CLIENT_LOGIN_RESULT = 200000,
};

enum MSG_FROM_GATE_TO_LOGIN {
    //login result arg0:int(msgid), arg1:int(socket), arg2:string(username), arg3:md5(string(passwd))
    MSG_FROM_GATE_TO_LOGIN_LOGIN = 300000,
};

enum MSG_FROM_LOGIN_TO_GATE {
    //query identity
    //arg0:int(msgid), arg1:int(socket), 
    //arg2:int(login_result, 0:succsed, 1:faild), arg3:int64(userid), arg4:string(strIdentity)
    MSG_FROM_LOGIN_TO_GATE_LOGIN_RESULT = 400000,
};

#endif	/* SERVERCOMMAND_H */

