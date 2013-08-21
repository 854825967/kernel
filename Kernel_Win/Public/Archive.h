#ifndef BASEARCHIVE_H
#define BASEARCHIVE_H

#include "ComDefine.h"

#define UPDATE_STAGE 32

class VarList;

class Archive
{
public:
    Archive();
    bool InBuff(void * pBuff, I32 nLength);
    ~Archive();

    bool FormartToVarList(VarList & argc);
    bool Clear();
    void * GetStream() const;
    UI32 Length() const;
//入流
    bool In(const I32 nValue);
    bool In(const I64 llValue);
    bool In(const double dValue);
    bool In(const char * pString, const UI32 nStrSize);
    bool In(const wchar_t * pWideStr, const UI32 nWideStrSize);

    Archive & operator << (const UI32 nValue);
    Archive & operator << (const I32 nValue);
    Archive & operator << (const UI64 llValue);
    Archive & operator << (const I64 llValue);
    Archive & operator << (const double dValue);
    Archive & operator << (const char * pString);
    Archive & operator << (const wchar_t * pWideStr);

//流出
    UI8 GetNextType();

    const I32 OutI32();
    const I64 OutI64();
    const double OutDouble();
    const char * OutString();
    const wchar_t * OutWideStr();

    bool operator >> (I32 & nValue);
    bool operator >> (I64 & llValue);
    bool operator >> (double & dValue);
    bool operator >> (float & fValue);
    bool operator >> (const char * & pString);
    bool operator >> (const wchar_t * & pWideStr);

private:
    bool CheckSize();
    bool AllotSpace(const UI32 nIncreaseLength);
private:
    char * m_pStream;
    char * m_pRoot;
    UI32 m_nCurrentInIndex;
    UI32 m_nCurrentOutIndex;
    UI32 m_nStreamMaxSize;
};

#endif