/* 
 * File:   IObjectManage.h
 * Author: traveler
 *
 * Created on December 26, 2012, 2:13 PM
 */

#ifndef IOBJECTMANAGE_H
#define	IOBJECTMANAGE_H

#include "IBase.h"
#include "../../Public/ComDefine.h"

class IObjectManage : public IBase {
public:
    virtual bool IsExsit(const CIdentity & player) = 0;
    virtual bool Register(const UI32 nLinkID, const CIdentity & player) = 0;
    virtual bool Logoff(const CIdentity & player) = 0;
    virtual bool Logoff(const UI32 nLinkID) = 0;
    virtual const UI32 QueryLinkID(const CIdentity & player) const = 0;
    virtual const CIdentity QueryPlayer(const UI32 nLinkID) const = 0;
};

#endif	/* IOBJECTMANAGE_H */

