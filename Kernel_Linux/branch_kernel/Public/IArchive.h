/* 
 * File:   IArchive.h
 * Author: traveler
 *
 * Created on December 27, 2012, 11:55 AM
 */

#ifndef IARCHIVE_H
#define	IARCHIVE_H

#include "ComDefine.h"

class IArchive {
public:
    virtual bool InBuff(void * pBuff, I32 nLength) = 0;
    virtual bool ToVarList(IVarList & argc) = 0;
    virtual bool Clear() = 0;
    virtual void * GetStream() const = 0;
    virtual UI32 Length() const = 0;
    //入流
    virtual bool In(const I32 nValue) = 0;
    virtual bool In(const I64 llValue) = 0;
    virtual bool In(const double dValue) = 0;
    virtual bool In(const char * pString) = 0;
    virtual bool In(const wchar_t * pWideStr) = 0;


    //流出
    virtual UI8 GetNextType() = 0;
    virtual const I32 OutI32() = 0;
    virtual const I64 OutI64() = 0;
    virtual const double OutDouble() = 0;
    virtual const char * OutString() = 0;
    virtual const wchar_t * OutWideStr() = 0;

    IArchive & operator <<(const UI32 nValue) {
        In((I32) nValue);
        return *this;
    }

    IArchive & operator <<(const UI64 llValue) {
        In((I64) llValue);
        return *this;
    }

    IArchive & operator <<(const I32 nValue) {
        In(nValue);
        return *this;
    }

    IArchive & operator <<(const I64 llValue) {
        In(llValue);
        return *this;
    }

    IArchive & operator <<(const char * pString) {
        In(pString);
        return *this;
    }

    IArchive & operator <<(const wchar_t * pWideStr) {
        In(pWideStr);
        return *this;
    }

    IArchive & operator <<(const double dValue) {
        In(dValue);
        return *this;
    }

    bool operator >>(I32 & nValue) {
        nValue = OutI32();

        return true;
    }

    bool operator >>(UI32 & nValue) {
        nValue = OutI32();

        return true;
    }

    bool operator >>(I64 & llValue) {
        llValue = OutI64();

        return true;
    }

    bool operator >>(UI64 & llValue) {
        llValue = OutI64();

        return true;
    }

    bool operator >>(const char * & pString) {
        pString = OutString();

        return true;
    }

    bool operator >>(double & dValue) {
        dValue = OutDouble();

        return true;
    }

    bool operator >>(float & fValue) {
        fValue = OutDouble();

        return true;
    }

};

#endif	/* IARCHIVE_H */

