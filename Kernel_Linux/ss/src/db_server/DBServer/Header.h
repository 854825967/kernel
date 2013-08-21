#ifndef _HEADER_H__
#define _HEADER_H__
#include "GameSys.h"
#include "ILog.h"

// 最大连接个数
#define MAX_CONNECT_NUM		255

extern ILog *g_pServerLog;
extern char LogFileName[MAX_PATH];

// 输出信息日志
extern "C" void PrintInfoLog(LPCSTR lpszFormat, ...);

// 获取TickCount
extern "C" u32 GetTickCount();

#endif //_HEADER_H__
