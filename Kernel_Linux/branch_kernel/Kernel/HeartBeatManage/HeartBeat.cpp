#include "HeartBeat.h"

HeartBeat::HeartBeat() {
    m_Alive = false;
    m_pBeatFun = NULL;
    m_nFrequency = 0;
    m_nMaxBeatCount = 0;
    m_nCurrentBeatCount = 0;
    m_nLastBeatTime = 0;
}

HeartBeat::HeartBeat(const BEATFUN pBeatFun, const UI64 nFrequency, const UI32 nMaxBeatCount, const bool beatatonce) {
    InitHeart(pBeatFun, nFrequency, nMaxBeatCount, beatatonce);
}

bool HeartBeat::InitHeart(const BEATFUN pBeatFun, const UI64 nFrequency, const UI32 nMaxBeatCount, const bool beatatonce) {
    m_Alive = true;
    m_pBeatFun = pBeatFun;
    m_nFrequency = nFrequency;
    m_nMaxBeatCount = nMaxBeatCount;
    m_nCurrentBeatCount = 0;
    if (beatatonce) {
        m_nLastBeatTime = 0;
    } else {
        m_nLastBeatTime = GetCurrentTimeTick();
    }

    return true;
}

bool HeartBeat::IsAlive() {
    return m_Alive;
}

bool HeartBeat::Beat(const IKernel * pKernel, const CIdentity & host, const UI64 nCurrentTimeTick) {
    if (!m_Alive) {
        return false;
    }

    if (m_nCurrentBeatCount >= m_nMaxBeatCount && m_nMaxBeatCount != 0) {
        m_Alive = false;
        Assert(false);
        return false;
    }

    if (0 == m_nLastBeatTime) {
        m_pBeatFun(pKernel, host, m_nCurrentBeatCount++);
        m_nLastBeatTime = nCurrentTimeTick;
    } else {
        while (nCurrentTimeTick - m_nLastBeatTime >= m_nFrequency) {
            if (m_nCurrentBeatCount >= m_nMaxBeatCount && m_nMaxBeatCount != 0) {
                m_Alive = false;
                Assert(false);
                return false;
            }
            m_pBeatFun(pKernel, host, m_nCurrentBeatCount++);
            m_nLastBeatTime += m_nFrequency;
        }
    }

    if (m_nCurrentBeatCount >= m_nMaxBeatCount && m_nMaxBeatCount != 0) {
        m_Alive = false;
    }

    return true;
}

HeartBeat & HeartBeat::operator =(const HeartBeat & target) {
    memcpy(this, &target, sizeof (HeartBeat));
    return *this;
}

bool HeartBeat::operator ==(const HeartBeat & target) {
    return (this->m_pBeatFun == target.m_pBeatFun);
}
