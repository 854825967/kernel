#include "Header.h"
#include <time.h>

#include "util/Util.h"

// 全局Log指针
ILog *g_pTrace = NULL;
// 全局时间轴指针
ITimerAxis		*g_pTimeAxis= NULL;
// 全局数据库引擎指针
IDBEngine		*g_pDBEngine= NULL;
// 全局用户处理回调指针
IDBProxyUserSink	*g_pUserSink= NULL;
// 存盘时间全局定义
u32 g_dwSaveTimes =0 ;

extern "C" u32 GetTickCount()
{
/*
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC,&ts);//此处可以判断一下返回值
	return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
  */

  return util::GetTickCount();
}



