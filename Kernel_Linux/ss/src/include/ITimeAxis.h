/*****************************************************************************
模块名      : 时间轴接口
文件名      : ITimeAxis.h
相关文件    : 
文件实现功能: 时间轴接口
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/
#ifndef _ITIMEAXIS_H_
#define _ITIMEAXIS_H_

#include "include/GameType.h"
#include "core/timer_handler.h"

//////////////////////////////////////////////////////////////////////////
/************************* TimerAxis Config *****************************/


// 时间轴长度
#define INFINITY_CALL -1

//////////////////////////////////////////////////////////////////////////
// 定时器回调接口
struct ITimerHandler : public core::TimerHandler
{
	// 定时检查时间轴
	virtual void OnTimer(DWORD dwEventID) = 0;
};


// 时间轴
struct ITimerAxis
{
  virtual ~ITimerAxis() {}
	// 销毁ITimerAxis
	virtual void Release(void) = 0;

	/**
	@purpose          : 设置一个定时器
	@param	 timerID  : 定时器ID
	@param   interval : 定时器调用间隔
	@param   handler  : 处理接口
	@param   callTimes: 调用次数,默认调用无穷次
	@param   debugInfo: 调试信息
	@return		      : 如果设置成功则返回true
	*/

	virtual bool SetTimer( DWORD timerID,DWORD interval,ITimerHandler * handler,int callTimes=INFINITY_CALL,const char * debugInfo=__FILE__ )= 0;

	/**
	@purpose          : 删除定时器
	@param	 timerID  : 定时器ID
	@param   handler  : 处理接口
	@return		      : 返回是否删除成功
	*/
	virtual bool KillTimer( DWORD timerID,ITimerHandler * handler )= 0;
};

#endif // _ITIMEAXIS_H_

