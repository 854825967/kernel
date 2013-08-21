/* 
 * File:   ObjectManage.cpp
 * Author: traveler
 * 
 * Created on December 26, 2012, 2:12 PM
 */

#include "ObjectManage.h"
#include "../LogSystem/LogSystem.h"
#include "../HeartBeatManage/HeartBeatManage.h"

ObjectManage * ObjectManage::m_pSelf = NULL;
ILogSystem * ObjectManage::m_pLogSystem = NULL;
IHeartBeatManage * ObjectManage::m_pHeartBeatManage = NULL;

ObjectManage::ObjectManage() {

}

ObjectManage::~ObjectManage() {

}

IObjectManage * ObjectManage::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW ObjectManage;
        if (!m_pSelf->Bron()) {
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

bool ObjectManage::Bron() {
    return true;
}

bool ObjectManage::Dead() {
    return true;
}

bool ObjectManage::Initialize() {
    if (NULL == (m_pLogSystem = LogSystem::Employ()) ||
            NULL == (m_pHeartBeatManage = HeartBeatManage::Employ())) {
        Assert(false);
        return false;
    }
    return true;
}

bool ObjectManage::Destroy() {
    if (m_pSelf != NULL) {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

bool ObjectManage::IsExsit(const CIdentity & player) {
    CHashMap<UI64, UI32>::iterator itorplayer = m_mapkeyplayer.find(player.nAgency);
    if (itorplayer == m_mapkeyplayer.end()) {
        return false;
    }

    return true;
}

bool ObjectManage::Register(const UI32 nLinkID, const CIdentity & player) {

    CHashMap<UI32, UI64>::iterator itorpeer = m_mapkeypeer.find(nLinkID);
    CHashMap<UI64, UI32>::iterator itorplayer = m_mapkeyplayer.find(player.nAgency);

    if (itorpeer != m_mapkeypeer.end() || itorplayer != m_mapkeyplayer.end()) {
        Assert(false);
        return false;
    }

    m_mapkeypeer.insert(make_pair(nLinkID, player.nAgency));
    m_mapkeyplayer.insert(make_pair(player.nAgency, nLinkID));

    return true;
}

bool ObjectManage::Logoff(const CIdentity & player) {
    CHashMap<UI64, UI32>::iterator itorplayer = m_mapkeyplayer.find(player.nAgency);
    if (itorplayer == m_mapkeyplayer.end()) {
        Assert(false);
        return false;
    }

    UI32 nLinkID = itorplayer->second;
    CHashMap<UI32, UI64>::iterator itorpeer = m_mapkeypeer.find(nLinkID);
    if (itorpeer == m_mapkeypeer.end()) {
        Assert(false);
        return false;
    }

    m_pHeartBeatManage->ClearHeartBeat(CIdentity_INIT(itorplayer->second));

    m_mapkeyplayer.erase(itorplayer);
    m_mapkeypeer.erase(itorpeer);

    return true;
}

bool ObjectManage::Logoff(const UI32 nLinkID) {
    CHashMap<UI32, UI64>::iterator itorpeer = m_mapkeypeer.find(nLinkID);
    if (itorpeer == m_mapkeypeer.end()) {
        //        Assert(false);
        return false;
    }

    UI64 nPlayerID = itorpeer->second;
    CHashMap<UI64, UI32>::iterator itorplayer = m_mapkeyplayer.find(nPlayerID);
    if (itorplayer == m_mapkeyplayer.end()) {
        //        Assert(false);
        return false;
    }
    m_pHeartBeatManage->ClearHeartBeat(CIdentity_INIT(itorplayer->second));
    m_mapkeyplayer.erase(itorplayer);
    m_mapkeypeer.erase(itorpeer);

    return true;
}

const UI32 ObjectManage::QueryLinkID(const CIdentity & player) const {
    CHashMap<UI64, UI32>::const_iterator itorplayer = m_mapkeyplayer.find(player.nAgency);

    if (itorplayer == m_mapkeyplayer.end()) {
        //        Assert(false);
        return 0;
    }

    return itorplayer->second;
}

const CIdentity ObjectManage::QueryPlayer(const UI32 nLinkID) const {
    CHashMap<UI32, UI64>::const_iterator itorpeer = m_mapkeypeer.find(nLinkID);

    if (itorpeer == m_mapkeypeer.end()) {
        return CIdentity_INIT();
    }

    return CIdentity_INIT(itorpeer->second);
}
