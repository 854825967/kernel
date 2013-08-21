/* 
 * File:   ObjectManage.h
 * Author: traveler
 *
 * Created on December 26, 2012, 2:12 PM
 */

#ifndef OBJECTMANAGE_H
#define	OBJECTMANAGE_H

#include "../Interface/IObjectManage.h"
#include "../../Public/ComDefine.h"
#include "../../Public/CHashMap.h"
#include <string>
using namespace std;

class ILogSystem;
class IHeartBeatManage;

class ObjectManage : public IObjectManage {
public:
    static IObjectManage * Employ();

    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();

    virtual bool IsExsit(const CIdentity & player);
    
    virtual bool Register(const UI32 nLinkID, const CIdentity & player);
    virtual bool Logoff(const CIdentity & player);
    virtual bool Logoff(const UI32 nLinkID);
    virtual const UI32 QueryLinkID(const CIdentity & player) const;
    virtual const CIdentity QueryPlayer(const UI32 nLinkID) const;

private:
    ObjectManage();
    ~ObjectManage();

private:
    static ObjectManage * m_pSelf;
    static ILogSystem * m_pLogSystem;
    static IHeartBeatManage * m_pHeartBeatManage;
    
    CHashMap<UI32, UI64> m_mapkeypeer;
    CHashMap<UI64, UI32> m_mapkeyplayer;

};

#endif	/* OBJECTMANAGE_H */

