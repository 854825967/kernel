#ifndef HEARTBEATMANAGE_H
#define HEARTBEATMANAGE_H

#include "../../Public/ComDefine.h"
#include "../../Public/CHashMap.h"
#include "../Interface/IHeartBeatManage.h"
#include "HeartBeat.h"
#include <string>
#include <vector>

#define MAX_HEARTBEAT_COUNT 4096

class HeartBeatManage : public IHeartBeatManage {
public:
    static IHeartBeatManage * Employ();
    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();
    virtual bool AddHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun,
            const UI64 nFrequency = 1000, const UI32 nMaxBeatCount = 0, const bool beatatonce = false);
    virtual bool DelHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun);
    virtual bool IsExistsHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun);
    virtual void ClearHeartBeat(const CIdentity & obj);
#ifdef _DEBUG
    void Test();
#endif //_DEBUG
    virtual void Beat();
private:
    HeartBeatManage();
    ~HeartBeatManage();

private:
    static HeartBeatManage * m_pSelf;
    static IKernel * m_pKernel;
    CHashMap<UI64, vector<HeartBeat> > m_heartbeatcont;
};

#endif //HEARTBEATMANAGE_H
