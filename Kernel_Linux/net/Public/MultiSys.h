#ifndef MULTISYS_H
#define MULTISYS_H

#include <stdio.h>

#if defined _WIN32 || defined _WIN64 
#include <winsock2.h>
#include <Windows.h> 
#include <shlwapi.h>
#include <Mswsock.h>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>

#pragma comment( lib, "ws2_32.lib" )
#pragma comment(lib, "shlwapi.lib")

#define CSleep(n) Sleep(n)
#define SafeSprintf _snprintf_s

#define ECHO(format, ...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##__VA_ARGS__); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN); \
    printf("%s\n", log); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY); \
    }

#define ECHO_TRACE(format, ...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##__VA_ARGS__); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); \
    printf("[info] %s|%d|%s\n\t%s\n", __FILE__, __LINE__, __FUNCTION__, log); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY); \
    }

#define ECHO_WARN(format, ...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##__VA_ARGS__); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN); \
    printf("[warn]%s|%d|%s\n\t%s\n", __FILE__, __LINE__, __FUNCTION__, log); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY); \
    }

#define ECHO_ERROR(format, ...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##__VA_ARGS__); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); \
    printf("[error]%s|%d|%s\n\t%s\n", __FILE__, __LINE__, __FUNCTION__, log); \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY); \
    ASSERT(false); \
    }


#endif

//Add POSIX system
//#if defined linux....


#if defined _WIN32 || defined _LINUX32
    typedef unsigned char u8;
    typedef unsigned short u16;
    typedef unsigned int u32;
    typedef unsigned long long u64;

    typedef char s8;
    typedef short s16;
    typedef int s32;
    typedef long long s64;
#endif


inline void _AssertionFail(const char * strFile, int nLine, const char * pFunName) {
    CSleep(1);
    ::fflush(stdout);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); \
    ::fprintf(stderr, "\nAsssertion failed: file %s, line %d, function %s ", strFile, nLine, pFunName);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY); \
    ::fflush(stderr);
    ::abort();
}

#ifdef _DEBUG
#define NEW ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define  ASSERT(p) ((p) ? (void)0 : (void)_AssertionFail(__FILE__, __LINE__, __FUNCTION__))
#else
#define NEW new
#define  ASSERT(p) void(0);
#endif    //_DEBUG

#endif