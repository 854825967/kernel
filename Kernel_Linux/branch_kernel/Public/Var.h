/* 
 * File:   Var.h
 * Author: traveler
 *
 * Created on January 11, 2013, 3:18 PM
 */

#ifndef VAR_H
#define	VAR_H

#include "ComDefine.h"
#include "CIdentity.h"
enum {
    TYPE_UNKWON = 0,
    TYPE_BOOL,
    TYPE_INT,
    TYPE_INT64,
    TYPE_STRING,
    TYPE_WIDESTR,
    TYPE_DOUBLE,
    TYPE_OBJECT,
};

typedef struct _Var {
    UI8 type;

    union {
        bool boolValue;
        I32 intValue;
        I64 int64Value;
        double doubleValue;
        UI32 strIndex;
        UI32 wstrIndex;
    };
} Var;

inline void SetDataType(Var & var, const UI32 type) {
    var.type = type;
}

inline bool SetDataValue(Var & var, const bool bValue) {
    if (var.type != TYPE_BOOL) {
        return false;
    }

    var.boolValue = bValue;
    return true;
}

inline bool SetDataValue(Var & var, const I32 nValue) {
    if (var.type != TYPE_INT) {
        return false;
    }

    var.intValue = nValue;
    return true;
}

inline bool SetDataValue(Var & var, const I64 n64Value) {
    if (var.type != TYPE_INT64) {
        return false;
    }

    var.int64Value = n64Value;
    return true;
}

inline bool SetDataValue(Var & var, const double dbValue) {
    if (var.type != TYPE_DOUBLE) {
        return false;
    }

    var.doubleValue = dbValue;
    return true;
}

inline bool SetDataValue(Var & var, const CIdentity & obj) {
    if (var.type != TYPE_OBJECT) {
        Assert(false);
        return false;
    }

    var.int64Value = obj.nAgency;
    return true;
}

inline bool SetDataString(Var & var, const I32 nStrPos) {
    if (var.type != TYPE_STRING) {
        return false;
    }

    var.strIndex = nStrPos;
    return true;
}

inline bool SetDataWideStr(Var & var, const I32 nWideStrPos) {
    if (var.type != TYPE_WIDESTR) {
        return false;
    }

    var.wstrIndex = nWideStrPos;
    return true;
}

#endif	/* VAR_H */

