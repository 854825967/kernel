#ifndef COMDEFINE_H
#define COMDEFINE_H

/*
 * system define
 * __LINUX_32__
 * __LINUX_64__
 * __WIN_32__
 * __WIN_64__
 */
#define __LINUX_64__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#if defined __LINUX_32__ || defined __LINUX_64__
#define _NORMAL_BLOCK 1
#include <libgen.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>


typedef pid_t Cthread_id;
typedef int CHandle;
#endif //__LINUX_32__ || __LINUX_64__

#ifdef __WIN_32__
#include <winsock2.h>
#include <Windows.h>
#include <shlwapi.h>
#include <Mswsock.h>
#include <time.h>
#include <assert.h>

#pragma comment( lib, "ws2_32.lib" )
#pragma comment(lib, "shlwapi.lib")
#endif //WIN32
//#include "MemoryPool.h"

#define NAME_LENGTH 64
#define MAX_PORT 65535

inline void _AssertionFail(const char * strFile, int nLine, const char * pFunName) {
    sleep(1);
    ::fflush(stdout);
    ::fprintf(stderr, "\nAsssertion failed: file %s, line %d, function %s ", strFile, nLine, pFunName);
    ::fflush(stderr);
    ::abort();
}

#ifdef _DEBUG
#define NEW new //::new(__FILE__, __LINE__)
#define  Assert(p) ((p) ? (void)0 : (void)_AssertionFail(__FILE__, __LINE__, __FUNCTION__))
#else
#define NEW new
#define  Assert(p) void(0);
#endif    //_DEBUG

//#if defined __LINUX_64__  || defined __LINUX_32__
//#define RAND_MAX 0x7fff
//#endif

typedef unsigned char UI8, UI8_TYPE;
typedef unsigned short int UI16;
typedef unsigned int UI32, UI32_ID, UI32_INDEX;

typedef char I8;
typedef short int I16;
typedef int I32;

#if defined __LINUX_64__ || defined __WIN_64__
typedef unsigned long UI64;
typedef long I64;
#else
#if defined __LINUX_32__ || defined __WIN_32__
typedef unsigned long long UI64;
typedef long long I64;
#endif
#endif

#define HEAD 0
#define ERROR_ID (UI32)-1
#define ERROR_INDEX (UI32)-1
#define NEW_LISTEN (UI32)-1

#define LOG_MAX_SIZE 4096

//后期这里 按照需求来该 SOCKETCALL的定义
class IKernel;
class IVarList;
class IArchive;
class CIdentity;

typedef I32(*SOCKETCALL)(const IKernel *, const UI32, const UI32, const IVarList &); //事件回调函数定义
typedef I32(*OBJCALL)(const IKernel *, const CIdentity &, const CIdentity &, const IVarList &);
typedef I32(*HEARTBEATFUN)(const IKernel *, const IVarList &);
typedef I32(*BEATFUN)(const IKernel *, const CIdentity &, const I32 nBeatCount);


#endif  //COMDEFINE_H
