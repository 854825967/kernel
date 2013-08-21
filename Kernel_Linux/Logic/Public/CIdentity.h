/* 
 * File:   CIdentity.h
 * Author: traveler
 *
 * Created on January 11, 2013, 3:16 PM
 */

#ifndef CIDENTITY_H
#define	CIDENTITY_H

#include "ComDefine.h"

class CIdentity {
public:

    inline bool operator ==(const CIdentity & b) const {
        return (nAgency == b.nAgency);
    }

    inline bool operator !=(const CIdentity & b) const {
        return (nAgency != b.nAgency);
    }

    CIdentity & operator =(const CIdentity & a) {
        nAgency = a.nAgency;
        return *this;
    }

    inline bool operator>(const CIdentity & a) const {
        return (nAgency > a.nAgency);
    }

    inline bool operator<(const CIdentity & a) const {
        return (nAgency < a.nAgency);
    }

    inline bool IsNull() {
        return (0 == nAgency);
    }

protected:

    CIdentity() {
    }

public:

    union {

        struct {
            UI32 nIdent;
            UI32 nSerial;
        };

        UI64 nAgency;
    };
};

class CIdentity_INIT : public CIdentity {
public:

    CIdentity_INIT() {
        nAgency = 0;
    }

    CIdentity_INIT(UI64 val) {
        nAgency = val;
    }

    CIdentity_INIT(UI32 ident, UI32 serial) {
        nIdent = ident;
        nSerial = serial;
    }

    CIdentity_INIT & operator=(const CIdentity & src) {
        nAgency = src.nAgency;
        return *this;
    }
};

#endif	/* CIDENTITY_H */

