/*****************************************************************************
模块名      : 事件引擎实现类
文件名      : EventEngine.h
相关文件    : 
文件实现功能: 实现事件引擎相关的功能
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/

#ifndef __EVENT__ENGINE__H
#define __EVENT__ENGINE__H

#include "include/GameSys.h"
#include "include/IEventEngine.h"
#include "core/tools/EventEngineT.h"
 
struct OnVoteObject
{
	bool operator() (IEventVoteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen)
	{
		if(pSink == NULL)
		{
			return false;
		}

		return pSink->OnVote(wEventID, bSrcType, qwSrcID, pszContext, nLen);		
	}
};

struct OnExecuteObject
{
	bool operator() (IEventExecuteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen)
	{
		if(pSink == NULL)
		{
			return false;
		}

		pSink->OnExecute(wEventID, bSrcType, qwSrcID, pszContext, nLen);

		return true;
	}
};

class CEventEngine : public IEventEngine
{
	typedef TEventEngine< IEventVoteSink, OnVoteObject >		TCENTER_VOTE;

	typedef TEventEngine< IEventExecuteSink, OnExecuteObject >	TCENTER_EXECUTE;
public:
	////////////////////////IEventEngine///////////////////////////////
	/** 释放
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void		Release(void);

	/** 
	@param   
	@param   
	@return  
	*/
	/** 发送投票事件   
	@param   wEventID ：事件ID
	@param   bSrcType ：发送源类型
	@param   qwSrcID : 发送源标识（UID中"序列号"部份）
	@param   pszContext : 上下文
	@param   nLen : 上下文长度	  
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		FireVote(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen);

	/** 发送执行事件
	@param   wEventID ：事件ID
	@param   bSrcType ：发送源类型
	@param   qwSrcID : 发送源标识（UID中"序列号"部份）
	@param   pszContext : 上下文
	@param   nLen : 上下文长度	  
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void		FireExecute(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen);

	/** 订阅投票事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（UID中"序列号"部份），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		Subscibe(IEventVoteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszDesc);

	/** 订阅执行事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（UID中"序列号"部份），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		Subscibe(IEventExecuteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszDesc);

	/** 取消订阅投票事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（UID中"序列号"部份），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		UnSubscibe(IEventVoteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID);

	/** 取消订阅执行事件
	@param   pSink : 回调sink
	@param   wEventID : 事件ID
	@param   bSrcType ：发送源类型
	@param	 qwSrcID : 发送源标识（UID中"序列号"部份），如果为0，则表示订阅所有
	@param	 pDesc : 订阅者描述，用来调试程序
	@return  成功返回true,失败返回false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		UnSubscibe(IEventExecuteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID);

	////////////////////////CEventEngine///////////////////////////////
	/** 创建
	@param   
	@param   
	@return  
	*/
	bool				Create(void);

	/** 
	@param   
	@param   
	@return  
	*/
	CEventEngine(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CEventEngine(void);	
private:	
	// 投票中心
	TCENTER_VOTE			m_VoteCenter;
	
	// 执行中心
	TCENTER_EXECUTE			m_ExecuteCenter;
};

#endif  // __EVENT__ENGINE__H

