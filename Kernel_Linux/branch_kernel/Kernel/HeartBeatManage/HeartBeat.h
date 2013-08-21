#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "../../Public/ComDefine.h"
#include "../../Public/Tools.h"

class HeartBeat
{
public:
    HeartBeat();
    HeartBeat(const BEATFUN pBeatFun, const UI64 nFrequency = 1000, const UI32 nMaxBeatCount = 0, const bool beatatonce = false);
    bool InitHeart(const BEATFUN pBeatFun, const UI64 nFrequency, const UI32 nMaxBeatCount, const bool beatatonce = false);
    bool IsAlive();
    bool Beat(const IKernel * pKernel, const CIdentity & host, const UI64 nCurrentTimeTick);
    HeartBeat & operator = (const HeartBeat & target);
    bool operator == (const HeartBeat & target);
#ifndef _DEBUG
private:
#endif //_DEBUG
    bool m_Alive;       //心跳是否存活
    BEATFUN m_pBeatFun; //心跳函数指针
    UI32 m_nMaxBeatCount;       //心跳最大跳动次数，超过这个次数就死掉
    UI32 m_nCurrentBeatCount;   //心跳当前跳动次数
    UI32 m_nFrequency;   //心跳频率，单位ms
    UI64 m_nLastBeatTime;       //上一次心跳事件
};

#endif //HEARTBEAT_H
