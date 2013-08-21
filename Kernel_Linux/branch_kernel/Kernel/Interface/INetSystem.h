/* 
 * File:   INetSystem.h
 * Author: traveler
 *
 * Created on December 10, 2012, 2:20 PM
 */

#ifndef INETSYSTEM_H
#define	INETSYSTEM_H

#include "../../Public/ComDefine.h"
#include "IBase.h"
class Archive;

class INetSystem : public IBase {
public:
    virtual bool BroadCast(const char * pLinkType, const IArchive & msg, const IVarList & blacklist) = 0;
    virtual bool Send(const UI32 nSocket, const IArchive & msg) = 0;
    virtual bool Connect(const char * remotetype, const char * pStrIp, const UI16 nPort) = 0;
    virtual bool Listen(const char * remotetype, const char * pStrIp, const UI16 nPort, const UI8 nUsefor) = 0;
    virtual bool Close(const UI32 nLinkID) = 0;
    virtual bool MainLoop(const UI8 nWaitTimeOut, const UI8 nMaxRecvFrequency) = 0;
};

#endif	/* INETSYSTEM_H */
