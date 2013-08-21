/* 
 * File:   IXXAL_login.h
 * Author: traveler
 *
 * Created on January 4, 2013, 4:34 PM
 */

#ifndef IXXAL_LOGIN_H
#define	IXXAL_LOGIN_H
#include "../Public/ILogicModule.h"

enum login_result {
    LOGIN_SUCCEED = 0,
    LOGIN_FAILD = 1,
};

enum query_identity_result {
    IDENTITY_EXISTS = 0,
    IDENTITY_NOT_EXISTS = 1,
};

class IXXAL_login : public ILogicModule {
    
};

#endif	/* IXXAL_LOGIN_H */

