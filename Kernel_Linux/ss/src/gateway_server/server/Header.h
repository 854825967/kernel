#ifndef _HEADER_H__
#define _HEADER_H__
#include "GameSys.h"

struct ILog;

extern ILog *g_pServerLog;
extern char LogFileName[MAX_PATH];

// 输出信息日志
void PrintInfoLog(LPCSTR lpszFormat, ...);

#endif //_HEADER_H__
