/* 
 * File:   IVarList.h
 * Author: traveler
 *
 * Created on December 27, 2012, 10:55 AM
 */

#ifndef IVARLIST_H
#define	IVARLIST_H

#include "ComDefine.h"
#include "CIdentity.h"
#include "Var.h"

class IVarList {
public:
    virtual bool Clear() = 0;

    virtual UI8_TYPE Type(const UI32_INDEX nIndex) const = 0;
    virtual UI32 Count() const = 0;

    virtual bool AddInt(const I32 nValue) = 0;
    virtual bool AddInt64(const I64 n64Value) = 0;
    virtual bool AddDouble(const double dValue) = 0;
    virtual bool AddString(const char * pString) = 0;
    virtual bool AddWideStr(const wchar_t * pWideStr) = 0;
    virtual bool AddObject(const CIdentity obj) = 0;

    virtual bool SetInt(const I32 nIndex, const I32 nValue) = 0;
    virtual bool SetInt64(const I32 nIndex, const I64 n64Value) = 0;
    virtual bool SetDouble(const I32 nIndex, const double dValue) = 0;
    virtual bool SetString(const I32 nIndex, const char * pString) = 0;
    virtual bool SetWideStr(const I32 nIndex, const wchar_t * pWideStr) = 0;
    virtual bool SetObject(const I32 nIndex, const CIdentity obj) = 0;

    virtual const I32 GetInt(const I32 nIndex) const = 0;
    virtual const I64 GetInt64(const I32 nIndex) const = 0;
    virtual const double GetDouble(const I32 nIndex) const = 0;
    virtual const char * GetString(const I32 nIndex) const = 0;
    virtual const wchar_t * GetWideStr(const I32 nIndex) const = 0;
    virtual const CIdentity GetObject(const I32 nIndex) const = 0;

    IVarList & operator <<(const I32 nValue) {
        AddInt(nValue);
        return *this;
    }

    IVarList & operator <<(const UI32 nValue) {
        AddInt(nValue);
        return *this;
    }

    IVarList & operator <<(const double dValue) {
        AddDouble(dValue);
        return *this;
    }

    IVarList & operator <<(const char * pString) {
        AddString(pString);
        return *this;
    }

    IVarList & operator <<(const I64 n64Value) {
        AddInt64(n64Value);
        return *this;
    }

    IVarList & operator <<(const UI64 n64Value) {
        AddInt64(n64Value);
        return *this;
    }

    IVarList & operator <<(const wchar_t * pWideStr) {
        AddWideStr(pWideStr);
        return *this;
    }

    IVarList & operator <<(const CIdentity obj) {
        AddObject(obj);
        return *this;
    }
};

#endif	/* IVARLIST_H */

