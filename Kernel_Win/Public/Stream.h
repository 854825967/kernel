#ifndef STREAM_H
#define STREAM_H

#include "ComDefine.h"

#define STREAM_LENGTH 2048
#define STREAM_IS_EMPTY 0

class Archive;

class Stream
{
public:
    Stream();
    ~Stream();
    void Clear();
    bool WriteBuff(void * pBuff, UI32 nLength);
    void * ReadBuff(UI32 & nLength); 
    bool ReadArchive(Archive & archive);
private:
    char * m_pBuff;
    UI32 m_nReadCurrent;
    UI32 m_nWriteCurrent;
    UI32 m_nMaxLength;
};

#endif