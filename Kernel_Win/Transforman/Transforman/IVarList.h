#ifndef IVARLIST_H
#define IVARLIST_H

#define STACK_SIZE 32
#define BUFFER_SIZE 256

#include "ComDefine.h"

class IVarList
{
public:
    virtual bool AddInt(const I32 & nValue) = 0;
    virtual bool AddInt64(const I64 * n64Value) = 0;
    virtual bool AddDouble(const double & dValue) = 0;
    virtual bool AddString(const char * & pString) = 0;
    virtual bool AddWideStr(const wchar_t * & pWideStr) = 0;

    virtual bool SetInt(const I32 & nIndex, const I32 & nValue) = 0;
    virtual bool SetInt64(const I32 & nIndex, const I64 & n64Value) = 0;
    virtual bool SetDouble(const I32 & nIndex, const double & dValue) = 0;
    virtual bool SetString(const I32 & nIndex, const char * & pString) = 0;
    virtual bool SetWideStr(const I32 & nIndex, const wchar_t * & pWideStr) = 0;

    virtual const I32 GetInt(const I32 & nIndex) = 0;
    virtual const I64 GetInt64(const I32 & nIndex) = 0;
    virtual const double GetDouble(const I32 & nIndex) = 0;
    virtual const char * GetString(const I32 & nIndex) = 0;
    virtual const wchar_t * GetWideStr(const I32 & nIndex) = 0;

    IVarList & operator << (const I32 & nValue)
    {
        AddInt(nValue);
        return *this;
    }

    IVarList & operator << (const double & dValue)
    {
        AddDouble(dValue);
        return *this;
    }

    IVarList & operator << (const char * & pString)
    {
        AddString(pString);
        return *this;
    }

    IVarList & operator << (const I64 * n64Value)
    {
        AddInt64(n64Value);
        return *this;
    }

    IVarList & operator << (const wchar_t * & pWideStr)
    {
        AddWideStr(pWideStr);
        return *this;
    }
};

#endif