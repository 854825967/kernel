#ifndef COMDEFINE_H
#define COMDEFINE_H

#ifdef WIN32
#include <winsock2.h>
#include <Windows.h> 
#include <shlwapi.h>
#include <Mswsock.h>
#include <time.h>
#include <assert.h>

#pragma comment( lib, "ws2_32.lib" )
#pragma comment(lib, "shlwapi.lib")
#endif //WIN32

#include "MemoryPool.h"

#define LOG_ERROR(strLog) \
    printf(strLog); \
    printf("\n");

#define NAME_LENGTH 64
#define MAX_PORT 65535

inline void _AssertionFail(const char * strFile, int nLine) {
    ::fflush(stdout);
    ::fprintf(stderr, "Asssertion failed: file %s, line %d", strFile, nLine);
    ::fflush(stderr);
    ::abort();
}

#ifdef _DEBUG
#define  Assert(p) ((p) ? (void)0 : (void)_AssertionFail(__FILE__, __LINE__))
#else
#define  Assert(p) 
#endif    //_DEBUG

typedef unsigned char UI8,UI8_TYPE;
typedef unsigned short int UI16;
typedef unsigned int UI32,UI32_ID,UI32_INDEX;

typedef char I8;
typedef short int I16;
typedef int I32;

#ifdef WIN64
typedef unsigned long UI64;
typedef long I64;
#else
#ifdef WIN32
typedef unsigned long long UI64;
typedef long long I64;
#endif
#endif

/*
#define UI32_ID UI32
#define UI8_TYPE UI8
#define UI32_INDEX UI32
*/
#define HEAD 0
#define ERROR_ID (UI32)-1
#define ERROR_INDEX (UI32)-1
#define NEW_LISTEN (UI32)-1

enum
{
    TYPE_UNKWON = 0,
    TYPE_BOOL,
    TYPE_INT,
    TYPE_INT64,
    TYPE_STRING,
    TYPE_WIDESTR,
    TYPE_DOUBLE,
    TYPE_OBJECTSIGN,
};

typedef struct _VarData
{
    UI8 type;
    union
    {
        bool        boolValue;
        I32            intValue;
        I64         int64Value;
        double      doubleValue;
        UI32        strIndex;
        UI32        wstrIndex;
    };
}VarData;

inline void SetDataType(VarData & var, const UI32 type)
{
    var.type = type;
}

inline bool SetDataValue(VarData & var, const bool bValue)
{
    if (var.type != TYPE_BOOL)
    {
        return false;
    }

    var.boolValue = bValue;
    return true;
}

inline bool SetDataValue(VarData & var, const I32 nValue)
{
    if (var.type != TYPE_INT)
    {
        return false;
    }

    var.intValue = nValue;
    return true;
}

inline bool SetDataValue(VarData & var, const I64 n64Value)
{
    if (var.type != TYPE_INT64)
    {
        return false;
    }

    var.int64Value = n64Value;
    return true;
}

inline bool SetDataValue(VarData & var, const double dbValue)
{
    if (var.type != TYPE_DOUBLE)
    {
        return false;
    }

    var.doubleValue = dbValue;
    return true;
}

inline bool SetDataString(VarData & var, const I32 nStrPos)
{
    if (var.type != TYPE_STRING)
    {
        return false;
    }

    var.strIndex = nStrPos;
    return true;
}

inline bool SetDataWideStr(VarData & var, const I32 nWideStrPos)
{
    if (var.type != TYPE_WIDESTR)
    {
        return false;
    }

    var.wstrIndex = nWideStrPos;
    return true;
}

#endif  //COMDEFINE_H
