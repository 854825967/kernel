//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 3934 $
// $Author: than $
// $Date: 2012-01-14 20:13:10 +0800 (鍛ㄥ叚, 2012-01-14) $
//
// Some defines.
//

#ifndef __HEADER__H
#define __HEADER__H

struct IServerKernel;
struct ILog;
struct ITimerAxis;

enum TIMER_ID {
  enTimer_ID_KeepAlive = 1,    //心跳包
  enTimer_ID_ReConnect,	       //断线重连
};

// 内核指针
extern IServerKernel *g_pServerKernel;

// 全局指针
extern ILog *g_pTrace;

// 全局时间轴指针
extern ITimerAxis *g_pTimerAxis;

#endif  // __HEADER__H

