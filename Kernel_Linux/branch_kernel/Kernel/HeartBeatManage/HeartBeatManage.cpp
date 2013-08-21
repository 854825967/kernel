#include "HeartBeatManage.h"
#include "../../Public/Tools.h"
#include "../Kernel.h"
#include <algorithm>
#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif //_DEBUG

HeartBeatManage * HeartBeatManage::m_pSelf = NULL;
IKernel * HeartBeatManage::m_pKernel = NULL;

IHeartBeatManage * HeartBeatManage::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW HeartBeatManage;
        if (!m_pSelf->Bron()) {
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

HeartBeatManage::HeartBeatManage() {
}

HeartBeatManage::~HeartBeatManage() {
    
}

bool HeartBeatManage::Bron() {
    return true;
}

bool HeartBeatManage::Dead() {
    return true;
}

bool HeartBeatManage::Initialize() {
    if (NULL == (m_pKernel = Kernel::Employ())) {
        Assert(false);
        return false;
    }

    return true;
}

bool HeartBeatManage::Destroy() {
    if(m_pSelf != NULL) {
        delete m_pSelf;
        m_pSelf = NULL;
    }
    
    return true;
}

bool HeartBeatManage::AddHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun,
        const UI64 nFrequency, const UI32 nMaxBeatCount, const bool beatatonce) {

    CHashMap<UI64, vector<HeartBeat> >::iterator ifind = m_heartbeatcont.find(obj.nAgency);

    HeartBeat hbt(pBeatFun, nFrequency, nMaxBeatCount, beatatonce);

    if (ifind == m_heartbeatcont.end()) {
        m_heartbeatcont.insert(make_pair(obj.nAgency, vector<HeartBeat > ())).first->second.push_back(hbt);
    } else {
        vector<HeartBeat>::iterator ibegin = ifind->second.begin();
        vector<HeartBeat>::iterator iend = ifind->second.end();
        vector<HeartBeat>::iterator itor = find(ibegin, iend, hbt);
        if (itor != iend) {
//            Assert(false);
            return false;
        }

        ifind->second.push_back(hbt);
    }

    return true;
}

bool HeartBeatManage::DelHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) {
    CHashMap<UI64, vector<HeartBeat> >::iterator ifind = m_heartbeatcont.find(obj.nAgency);

    HeartBeat hbt(pBeatFun);

    if (ifind == m_heartbeatcont.end()) {
        Assert(false);
        return false;
        //m_heartbeatcont.insert(make_pair(obj.nAgency, vector<HeartBeat > ())).first->second.push_back(hbt);
    } else {
        vector<HeartBeat>::iterator ivbegin = ifind->second.begin();
        vector<HeartBeat>::iterator ivend = ifind->second.end();
        vector<HeartBeat>::iterator ivtor = find(ivbegin, ivend, hbt);
        if (ivtor != ivend) {
            ifind->second.erase(ivtor);
            return true;
        }
        Assert(false);
    }

    return false;
}

#ifdef _DEBUG

void HeartBeatManage::Test() {
    CHashMap<UI64, vector<HeartBeat> >::iterator ibegin = m_heartbeatcont.begin();
    CHashMap<UI64, vector<HeartBeat> >::iterator iend = m_heartbeatcont.end();
    while (ibegin != iend) {
        vector<HeartBeat>::iterator ivbegin = ibegin->second.begin();
        vector<HeartBeat>::iterator ivend = ibegin->second.end();
        while (ivbegin != ivend) {
            cout << ibegin->first << "  " << (UI64) (ivbegin->m_pBeatFun) << endl;
            ivbegin++;
        }
        ibegin++;
    }
}

#endif //_DEBUG

bool HeartBeatManage::IsExistsHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) {
    CHashMap<UI64, vector<HeartBeat> >::iterator ifind = m_heartbeatcont.find(obj.nAgency);

    HeartBeat hbt(pBeatFun);

    if (ifind == m_heartbeatcont.end()) {
        return false;
        //m_heartbeatcont.insert(make_pair(obj.nAgency, vector<HeartBeat > ())).first->second.push_back(hbt);
    } else {
        vector<HeartBeat>::iterator ibegin = ifind->second.begin();
        vector<HeartBeat>::iterator iend = ifind->second.end();
        vector<HeartBeat>::iterator itor = find(ibegin, iend, hbt);
        if (itor != iend) {
            return true;
        }

        //return false;
    }

    return false;
}

void HeartBeatManage::ClearHeartBeat(const CIdentity & obj) {
    CHashMap<UI64, vector<HeartBeat> >::iterator ifind = m_heartbeatcont.find(obj.nAgency);

    if (ifind == m_heartbeatcont.end()) {
        return;
    } else {
        ifind->second.clear();
    }

    return;
}

void HeartBeatManage::Beat() {
    UI64 nCurrentTime = GetCurrentTimeTick();

    CHashMap<UI64, vector<HeartBeat> >::iterator ibegin = m_heartbeatcont.begin();
    CHashMap<UI64, vector<HeartBeat> >::iterator iend = m_heartbeatcont.end();
    while (ibegin != iend) {
        vector<HeartBeat>::iterator ivbegin = ibegin->second.begin();
        vector<HeartBeat>::iterator ivend = ibegin->second.end();
        while (ivbegin != ivend) {
            ivbegin->Beat(m_pKernel, CIdentity_INIT(ibegin->first), nCurrentTime);
            if (!ivbegin->IsAlive()) {
                ivbegin = ibegin->second.erase(ivbegin);
                ivend = ibegin->second.end();
            } else {
                ivbegin++;
            }
        }
        ibegin++;
    }
}
