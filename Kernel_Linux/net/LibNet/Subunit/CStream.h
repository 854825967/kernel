#ifndef STREAM_H
#define STREAM_H

#include "MultiSys.h"
#include "CLock.h"

#define STREAM_LENGTH 10 * 1024
#define STREAM_IS_EMPTY 0

class CStream
{
public:
    CStream();
    ~CStream();
    void Clear();
    char * GetBuff() const;
    u32 GetLength() const;
    bool In(const char * pBuff, u32 nLength);
    char * Out(u32 & nLength);
private:
    char * m_pBuff;
    u32 m_nReadCurrent;
    u32 m_nWriteCurrent;
    u32 m_nMaxLength;
};

#endif