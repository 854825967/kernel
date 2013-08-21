/*
 * File:   IHeartBeatManage.h
 * Author: traveler
 *
 * Created on December 28, 2012, 10:48 AM
 */

#ifndef IHEARTBEATMANAGE_H
#define	IHEARTBEATMANAGE_H

#include "../../Public/ComDefine.h"
#include "IBase.h"

class IHeartBeatManage : public IBase {
public:
    virtual bool AddHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun,
            const UI64 nFrequency = 1000, const UI32 nMaxBeatCount = 0, const bool beatatonce = false) = 0;
    virtual bool DelHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) = 0;
    virtual bool IsExistsHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) = 0;
    virtual void Beat() = 0;
    virtual void ClearHeartBeat(const CIdentity & obj) = 0;
};

#endif	/* IHEARTBEATMANAGE_H */

