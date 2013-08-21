/* 
 * File:   IGateServer.h
 * Author: traveler
 *
 * Created on January 4, 2013, 5:55 PM
 */

#ifndef IGATESERVER_H
#define	IGATESERVER_H

#include "../Public/ILogicModule.h"

class IGateServer : public ILogicModule {
public:
    virtual UI32 GetLoginServerPeerID() = 0;
};


#endif	/* IGATE_H */

