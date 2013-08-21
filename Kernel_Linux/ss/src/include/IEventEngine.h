/*****************************************************************************
模块名      : 事件引擎接口
文件名      : ITimeAxis.h
相关文件    : 
文件实现功能: 事件引擎接口
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/
#ifndef __IEVENT__ENGINE__H
#define __IEVENT__ENGINE__H

#include "GameType.h"
 
/// 投票事件sink
struct IEventVoteSink 
{
  virtual ~IEventVoteSink() {}
	/** 
	@param   wEventID ：事件ID
	@param   bSrcType ：发送源类型
	@param   qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0）
	@param   pszContext : 上下文
	@param   nLen : 上下文长度
	@return  如果返回false : 则中断执行，否则继续向下执行
	*/
	virtual bool		OnVote(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen) = 0;	
};

/// 执行事件sink
struct IEventExecuteSink 
{
  virtual ~IEventExecuteSink() {}
	/** 
	@param   wEventID ：事件ID
	@param   bSrcType ：发送源类型
	@param   qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0）
	@param   pszContext : 上下文
	@param   nLen : 上下文长度
	*/
	virtual void		OnExecute(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen) = 0;
};

/// 事件引擎
struct IEventEngine
{
  virtual ~IEventEngine() {}
	/** 释放*/
	virtual void		Release(void) = 0;

	/** 发送投票事件   
	@param   wEventID ：事件ID
	@param   bSrcType ：发送源类型
	@param   qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0）
	@param   pszContext : 上下文
	@param   nLen : 上下文长度	  
 	*/
	virtual bool		FireVote(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen) = 0;

	/** 发送执行事件
	@param   wEventID ：事件ID
	@param   bSrcType ：发送源类型
	@param   qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0）
	@param   pszContext : 上下文
	@param   nLen : 上下文长度 
	*/
	virtual void FireExecute(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen) = 0;

	/** 订阅投票事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false 
	*/
	virtual bool Subscibe(IEventVoteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszDesc) = 0;

	/** 订阅执行事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false 
	*/
	virtual bool Subscibe(IEventExecuteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszDesc) = 0;

	/** 取消订阅投票事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false 
	*/
	virtual bool UnSubscibe(IEventVoteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID) = 0;

	/** 取消订阅执行事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（实体为UID中"序列号"部份，非实体就为0），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false 
	*/
	virtual bool UnSubscibe(IEventExecuteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID) = 0;
};

#endif  // __IEVENT__ENGINE__H

