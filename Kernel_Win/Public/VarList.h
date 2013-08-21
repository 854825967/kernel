#ifndef VARLIST_H
#define VARLIST_H

#define STACK_SIZE 32

#include "ComDefine.h"
//#include "IVarList.h"

class Buff;

class VarList// : public IVarList
{
public:
    VarList();
    ~VarList();
    bool Clear();

    UI8_TYPE Type(const UI32_INDEX & nIndex) const;
    UI32 Count()  const;

    bool AddInt(const I32 & nValue);
    bool AddInt64(const I64 & n64Value);
    bool AddDouble(const double & dValue);
    bool AddString(const char * & pString);
    bool AddWideStr(const wchar_t * & pWideStr);

    bool SetInt(const I32 & nIndex, const I32 & nValue);
    bool SetInt64(const I32 & nIndex, const I64 & n64Value);
    bool SetDouble(const I32 & nIndex, const double & dValue);
    bool SetString(const I32 & nIndex, const char * & pString);
    bool SetWideStr(const I32 & nIndex, const wchar_t * & pWideStr);

    const I32 GetInt(const I32 & nIndex) const;
    const I64 GetInt64(const I32 & nIndex) const;
    const double GetDouble(const I32 & nIndex) const;
    const char * GetString(const I32 & nIndex) const;
    const wchar_t * GetWideStr(const I32 & nIndex) const;

    VarList & operator << (const I32 & nValue)
    {
        AddInt(nValue);
        return *this;
    }

    VarList & operator << (const UI32 & nValue)
    {
        AddInt(nValue);
        return *this;
    }

    VarList & operator << (const double & dValue)
    {
        AddDouble(dValue);
        return *this;
    }

    VarList & operator << (const char * pString)
    {
        AddString(pString);
        return *this;
    }

    VarList & operator << (const I64 & n64Value)
    {
        AddInt64(n64Value);
        return *this;
    }

    VarList & operator << (const UI64 & n64Value)
    {
        AddInt64(n64Value);
        return *this;
    }

    VarList & operator << (const wchar_t * pWideStr)
    {
        AddWideStr(pWideStr);
        return *this;
    }

protected:
    bool AllocSpace();
    bool RellocHeap();

private:
    UI32 m_nCurrent;
    UI32 m_nMaxSize;
    VarData m_Stack[STACK_SIZE];
    VarData * m_pData;
    Buff * m_pBuff;
};

#endif