/*****************************************************************************
模块名      : 引擎模板类
文件名      : EventEngineT.h
相关文件    : 
文件实现功能: 引擎模板
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/

#ifndef _EVENTENGINET_H__
#define _EVENTENGINET_H__

#include <string.h>

#include <list>
#include <ext/hash_map>

#include "include/GameSys.h"

// 发送最大层数
#define FIRE_MAX_LAYERNUM			20

// 引用最大层数
#define REF_MAX_LAYERNUM			5

// 事件key
struct __EventKey
{
	u64		qwSrcID;			// 发送源标识（UID中"序列号"部份）	
	BYTE	bSrcType;			// 发送源类型
	u16		wEventID;			// 事件ID 
};

struct SEventKey
{
/*
	union
	{
		__EventKey			_key;
		u64				_value;
	};
*/
	__EventKey _key;

	SEventKey(void)
	{
		_key.qwSrcID = 0;
		_key.bSrcType = 0;
		_key.wEventID = 0;
	}

	bool operator == (const SEventKey &eventkey) const
	{
		return _key.qwSrcID == eventkey._key.qwSrcID &&
			_key.bSrcType == eventkey._key.bSrcType &&
			_key.wEventID == eventkey._key.wEventID;
	}

	bool operator < (const SEventKey &eventkey) const
	{
		if(_key.qwSrcID != eventkey._key.qwSrcID)
			return _key.qwSrcID < eventkey._key.qwSrcID;
		else if(_key.bSrcType != eventkey._key.bSrcType)
			return _key.bSrcType < eventkey._key.bSrcType;
		else
			return _key.wEventID < eventkey._key.wEventID;
	}
};
/*
// 特化hash函数
namespace stdext
{
	inline size_t hash_value(const SEventKey &eventkey)
	{
		DWORD k1 = (eventkey._key.qwSrcID & 0xFFFF) << 16;
		DWORD k2 = (eventkey._key.wEventID & 0xFF) << 8;
		DWORD k3 = eventkey._key.bSrcType;
		return k1 + k2 + k3;
	}
}
*/

struct hash_value {
  size_t operator()(const SEventKey &eventkey) const {
    u32 k1 = (eventkey._key.qwSrcID & 0xFFFFF) << 16;
    u32 k2 = (eventkey._key.wEventID & 0xFF) << 8;
    u32 k3 = eventkey._key.bSrcType;
    return k1 + k2 + k3;
  }
};

// 事件引擎模板
template< class TSink, class TOnEventObject >
class TEventEngine
{	
private:	
	struct SSubscibeInfo
	{
		TSink *		pSink;
		char		szDesc[32];
		int			nCallCount;
		bool		bRemoveFlag;

		SSubscibeInfo(TSink * pPrameSink, LPCSTR pDesc)
		{
			pSink = pPrameSink;		
			nCallCount = 0;
			bRemoveFlag = false;
			if(pDesc != NULL)
			{
				strncpy(szDesc, pDesc, sizeof(szDesc));
			}
			else
			{
				szDesc[0] = '\0';
			}
		}

		void Add(void)
		{
			nCallCount++;
		}

		void Sub(void)
		{
			nCallCount--;
			if (nCallCount <= 0)
			{
				nCallCount = 0;
			}
		}
	};
	// 一个事件KEY的订阅者列表
	typedef std::list< SSubscibeInfo >							TLIST_SUBSCIBEINFO;

	// 所有事件KEY的订阅者列表
	// typedef stdext::hash_map<SEventKey, TLIST_SUBSCIBEINFO >	TMAP_SAFESINK;
	typedef __gnu_cxx::hash_map<SEventKey, TLIST_SUBSCIBEINFO, hash_value >	TMAP_SAFESINK;
public:
	/** 
	@param   
	@param   
	@return  
	*/
	TEventEngine()
	{
		m_nFireLayerNum = 0;
	}

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~TEventEngine()
	{
		typename TMAP_SAFESINK::iterator it = m_mapSafeSink.begin();
		for( ; it != m_mapSafeSink.end(); ++it)
		{
			TLIST_SUBSCIBEINFO * plisSubscibeInfo = &((*it).second);
			plisSubscibeInfo->clear();
		}

		m_mapSafeSink.clear();
	}

	/** 
	@param   
	@param   
	@return  
	*/
	bool Subscibe(TSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszDesc)	
	{
		if(pSink == NULL)
		{
			return false;
		}

		// 事件KEY
		SEventKey eventkey;
		eventkey._key.wEventID = wEventID;
		eventkey._key.bSrcType = bSrcType;
		eventkey._key.qwSrcID = qwSrcID;

		// 订阅者信息
		SSubscibeInfo subscibeinfo(pSink, pszDesc);

		// 加入到订阅列表
		typename TMAP_SAFESINK::iterator it = m_mapSafeSink.find(eventkey);
		if(it == m_mapSafeSink.end())
		{
			TLIST_SUBSCIBEINFO listSubscibeInfo;
			listSubscibeInfo.push_front(subscibeinfo);

			// 加入到订阅列表					
			m_mapSafeSink.insert(std::make_pair(eventkey, listSubscibeInfo));
		}
		else
		{
			TLIST_SUBSCIBEINFO * plistSubscibeInfo = &((*it).second);
			plistSubscibeInfo->push_front(subscibeinfo);
		}

		return true;		
	}

	/** 
	@param   
	@param   
	@return  
	*/
	bool UnSubscibe(TSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID)
	{
		if(pSink == NULL)
		{
			return false;
		}	

		SEventKey eventkey;
		eventkey._key.wEventID = wEventID;
		eventkey._key.bSrcType = bSrcType;
		eventkey._key.qwSrcID = qwSrcID;

		typename TMAP_SAFESINK::iterator it = m_mapSafeSink.find(eventkey);
		if(it != m_mapSafeSink.end())
		{
			TLIST_SUBSCIBEINFO * plistSubscibeInfo = &((*it).second);

			typename TLIST_SUBSCIBEINFO::iterator itList = plistSubscibeInfo->begin();
			for( ; itList != plistSubscibeInfo->end(); ++itList)
			{
				SSubscibeInfo * pSubscibeInfo = &(*itList);
				if(pSubscibeInfo->pSink == pSink)
				{
					if(pSubscibeInfo->nCallCount == 0)
					{
						plistSubscibeInfo->erase(itList);
					}
					else
					{
						pSubscibeInfo->bRemoveFlag = true;
					}

					break;
				}
			}				
		}

		return true;	
	}

	/** 
	@param   
	@param   
	@return  
	*/
	bool Fire(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, int nLen)
	{
		SEventKey eventkey;
		eventkey._key.wEventID = wEventID;
		eventkey._key.bSrcType = bSrcType;

		// 先发送有源指针的
		eventkey._key.qwSrcID = qwSrcID;
		if(eventkey._key.qwSrcID != 0)
		{
			bool bResult = Fire(eventkey, wEventID, bSrcType, qwSrcID, pszContext, nLen);
			if(!bResult) 
			{
				return false;
			}
		}
		
		// 然后发送源指针的
		eventkey._key.qwSrcID = 0;
		bool bResult = Fire(eventkey, wEventID, bSrcType, qwSrcID, pszContext, nLen);
		if(!bResult)
		{
			return false;
		}

		return true;
	}

private:
	/** 
	@param   
	@param   
	@return  
	*/
	bool Fire(SEventKey &eventkey, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, int nLen)
	{
		m_nFireLayerNum++;

		if(m_nFireLayerNum >= FIRE_MAX_LAYERNUM)
		{
			//g_pServerKernelLog->TraceLn("事件服务器非法！死循环调用 EVENTID =  %d SRCTYPE ＝ %d",wEventID, bSrcType);
			m_nFireLayerNum--;
			return false;
		}

		typename TMAP_SAFESINK::iterator itMap = m_mapSafeSink.find(eventkey);
		if(itMap != m_mapSafeSink.end())
		{
			TLIST_SUBSCIBEINFO * plistSubscibeInfo = &((*itMap).second);
			
			typename TLIST_SUBSCIBEINFO::iterator itList = plistSubscibeInfo->begin();
			for( ; itList != plistSubscibeInfo->end(); )
			{
				SSubscibeInfo * pSubscibeInfo = &(*itList);

				if(pSubscibeInfo->nCallCount >= REF_MAX_LAYERNUM)
				{
					//g_pServerKernelLog->TraceErrorLn("事件服务器内同一事件循环调用！严重问题！EVENTID = %d, 描述 = %s",wEventID,pSubscibeInfo->szDesc);
					
					m_nFireLayerNum--;
					return false;
				}

				if(!pSubscibeInfo->bRemoveFlag)
				{					
					bool bResult = false;
					try
					{
						pSubscibeInfo->Add();
						bResult = m_FireEventObject(pSubscibeInfo->pSink, wEventID, bSrcType, qwSrcID, pszContext, nLen);
						pSubscibeInfo->Sub();						
					}
					catch(...)
					{
						pSubscibeInfo->Sub();	
						//g_pServerKernelLog->TraceErrorLn("事件服务器非法 EVENTID = %d, 描述 = %s",wEventID,pSubscibeInfo->szDesc);
 						return false;
					}

					if(pSubscibeInfo->bRemoveFlag && pSubscibeInfo->nCallCount == 0)
					{
						itList = plistSubscibeInfo->erase(itList);
					}					
					else
					{
						++itList;
					}

					if(!bResult) 
					{
						m_nFireLayerNum--;
						return false;
					}
				}
				else
				{
					if(pSubscibeInfo->nCallCount == 0)				
					{
						itList = plistSubscibeInfo->erase(itList);
					}
					else
					{
						++itList;
					}
				}
			}
		}

		m_nFireLayerNum--;

		return true;
	}
	
private:
	// 事件发送对像
	TOnEventObject		m_FireEventObject;

	// 事件对像列表
	TMAP_SAFESINK		m_mapSafeSink;

	// 发送层数
	int					m_nFireLayerNum;	
};

#endif // _EVENTENGINET_H__

