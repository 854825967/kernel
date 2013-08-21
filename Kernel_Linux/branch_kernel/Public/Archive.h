#ifndef BASEARCHIVE_H
#define BASEARCHIVE_H

#include "ComDefine.h"
#include "IVarList.h"
#include "IArchive.h"
#define UPDATE_STAGE 1024

class Archive : public IArchive {
public:
    Archive();
    ~Archive();

    virtual bool InBuff(void * pBuff, I32 nLength);
    virtual bool ToVarList(IVarList & argc);
    virtual bool Clear();
    //入流
    virtual bool In(const I32 nValue);
    virtual bool In(const I64 llValue);
    virtual bool In(const double dValue);
    virtual bool In(const char * pString);
    virtual bool In(const wchar_t * pWideStr);
    //流出
    virtual void * GetStream() const;
    virtual UI32 Length() const;
    virtual UI8 GetNextType();
    virtual const I32 OutI32();
    virtual const I64 OutI64();
    virtual const double OutDouble();
    virtual const char * OutString();
    virtual const wchar_t * OutWideStr();

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