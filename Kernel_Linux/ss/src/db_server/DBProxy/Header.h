#ifndef _HEADER_H__
#define _HEADER_H__
#include "ILog.h"

struct ITimerAxis;
struct IDBEngine;
struct IDBProxyUserSink;

// 全局日志指针
extern ILog				*g_pTrace;
// 全局时间轴指针
extern ITimerAxis		*g_pTimeAxis;
// 全局数据库引擎指针
extern IDBEngine		*g_pDBEngine;
// 全局用户处理回调指针
extern IDBProxyUserSink	*g_pUserSink;
// 存盘时间 全局定义
extern u32				g_dwSaveTimes; 

// 获取TickCount
extern "C" u32 GetTickCount();

#endif //_HEADER_H__

