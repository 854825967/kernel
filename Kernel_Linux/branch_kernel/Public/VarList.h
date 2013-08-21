#ifndef VARLIST_H
#define VARLIST_H

#define STACK_SIZE 1024

#include "ComDefine.h"
#include "IVarList.h"

class Buff;

class VarList : public IVarList
{
public:
    VarList();
    ~VarList();
    virtual bool Clear();

    virtual UI8_TYPE Type(const UI32_INDEX nIndex) const;
    virtual UI32 Count() const;

    virtual bool AddInt(const I32 nValue);
    virtual bool AddInt64(const I64 n64Value);
    virtual bool AddDouble(const double dValue);
    virtual bool AddString(const char * pString);
    virtual bool AddWideStr(const wchar_t * pWideStr);
    virtual bool AddObject(const CIdentity obj);

    virtual bool SetInt(const I32 nIndex, const I32 nValue);
    virtual bool SetInt64(const I32 nIndex, const I64 n64Value);
    virtual bool SetDouble(const I32 nIndex, const double dValue);
    virtual bool SetString(const I32 nIndex, const char * pString);
    virtual bool SetWideStr(const I32 nIndex, const wchar_t * pWideStr);
    virtual bool SetObject(const I32 nIndex, const CIdentity obj);

    virtual const I32 GetInt(const I32 nIndex) const;
    virtual const I64 GetInt64(const I32 nIndex) const;
    virtual const double GetDouble(const I32 nIndex) const;
    virtual const char * GetString(const I32 nIndex) const;
    virtual const wchar_t * GetWideStr(const I32 nIndex) const;
    virtual const CIdentity GetObject(const I32 nIndex) const;

protected:
    bool AllocSpace();
    bool RellocHeap();

private:
    UI32 m_nCurrent;
    UI32 m_nMaxSize;
    Var m_Stack[STACK_SIZE];
    Var * m_pData;
    Buff * m_pBuff;
};

#endif