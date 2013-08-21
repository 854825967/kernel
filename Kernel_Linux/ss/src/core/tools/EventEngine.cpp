#include "EventEngine.h"

/** 
@param   
@param   
@return  
*/
CEventEngine::CEventEngine(void)
{

}

/** 
@param   
@param   
@return  
*/
CEventEngine::~CEventEngine(void)
{

}

/** 释放
@param   
@param   
@param   
@return  
@note     
@warning 
@retval buffer 
*/
void CEventEngine::Release(void)
{
	delete this;
}

/** 创建
@param   
@param   
@return  
*/
bool CEventEngine::Create(void)
{
	return true;
}

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
bool CEventEngine::FireVote(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen)
{
	//LARGE_INTEGER dwTimeBegin;
	//::QueryPerformanceCounter(&dwTimeBegin);

	bool bRet = m_VoteCenter.Fire(wEventID, bSrcType, qwSrcID, pszContext, nLen);

	//LARGE_INTEGER dwTimeEnd;
	//QueryPerformanceCounter(&dwTimeEnd);
	//LARGE_INTEGER litmp;
	//::QueryPerformanceFrequency(&litmp);
	//LONGLONG dwTime = (dwTimeEnd.QuadPart - dwTimeBegin.QuadPart) * 1000000 / litmp.QuadPart;
	//if(g_pServerKernelLog && (dwTime > 300))
	//	g_pServerKernelLog->TraceErrorLn("FireVote花费时间(%5lldns)------->wEventID(%5d), bSrcType(%2d)", dwTime, wEventID, bSrcType);

	return bRet;
}

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
void CEventEngine::FireExecute(u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszContext, s32 nLen)
{
	//LARGE_INTEGER dwTimeBegin;
	//::QueryPerformanceCounter(&dwTimeBegin);

	m_ExecuteCenter.Fire(wEventID, bSrcType, qwSrcID, pszContext, nLen);

	//LARGE_INTEGER dwTimeEnd;
	//QueryPerformanceCounter(&dwTimeEnd);
	//LARGE_INTEGER litmp;
	//::QueryPerformanceFrequency(&litmp);
	//LONGLONG dwTime = (dwTimeEnd.QuadPart - dwTimeBegin.QuadPart) * 1000000 / litmp.QuadPart;
	//if(g_pServerKernelLog && (dwTime > 300))
	//	g_pServerKernelLog->TraceErrorLn("FireExecute花费时间(%5lldns)------->wEventID(%5d), bSrcType(%2d)", dwTime, wEventID, bSrcType);
}

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
bool CEventEngine::Subscibe(IEventVoteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszDesc)
{
	//LARGE_INTEGER dwTimeBegin;
	//::QueryPerformanceCounter(&dwTimeBegin);

	bool bRet = m_VoteCenter.Subscibe(pSink, wEventID, bSrcType, qwSrcID, pszDesc);

	//LARGE_INTEGER dwTimeEnd;
	//QueryPerformanceCounter(&dwTimeEnd);
	//LARGE_INTEGER litmp;
	//::QueryPerformanceFrequency(&litmp);
	//LONGLONG dwTime = (dwTimeEnd.QuadPart - dwTimeBegin.QuadPart) * 1000000 / litmp.QuadPart;
	//if(g_pServerKernelLog && (dwTime > 300))
	//	g_pServerKernelLog->TraceErrorLn("m_VoteCenter.Subscibe花费时间(%5lldns)------->wEventID(%5d), bSrcType(%2d)", dwTime, wEventID, bSrcType);

	return bRet;
}

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
bool CEventEngine::Subscibe(IEventExecuteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID, LPCSTR pszDesc)
{
	//LARGE_INTEGER dwTimeBegin;
	//::QueryPerformanceCounter(&dwTimeBegin);

	bool bRet = m_ExecuteCenter.Subscibe(pSink, wEventID, bSrcType, qwSrcID, pszDesc);

	//LARGE_INTEGER dwTimeEnd;
	//QueryPerformanceCounter(&dwTimeEnd);
	//LARGE_INTEGER litmp;
	//::QueryPerformanceFrequency(&litmp);
	//LONGLONG dwTime = (dwTimeEnd.QuadPart - dwTimeBegin.QuadPart) * 1000000 / litmp.QuadPart;
	//if(g_pServerKernelLog && (dwTime > 300))
	//	g_pServerKernelLog->TraceErrorLn("m_ExecuteCenter.Subscibe花费时间(%5lldns)------->wEventID(%5d), bSrcType(%2d)", dwTime, wEventID, bSrcType);

	return bRet;
}

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
bool CEventEngine::UnSubscibe(IEventVoteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID)
{
	//LARGE_INTEGER dwTimeBegin;
	//::QueryPerformanceCounter(&dwTimeBegin);

	bool bRet = m_VoteCenter.UnSubscibe(pSink, wEventID, bSrcType, qwSrcID);

	//LARGE_INTEGER dwTimeEnd;
	//QueryPerformanceCounter(&dwTimeEnd);
	//LARGE_INTEGER litmp;
	//::QueryPerformanceFrequency(&litmp);
	//LONGLONG dwTime = (dwTimeEnd.QuadPart - dwTimeBegin.QuadPart) * 1000000 / litmp.QuadPart;
	//if(g_pServerKernelLog && (dwTime > 300))
	//	g_pServerKernelLog->TraceErrorLn("m_VoteCenter.UnSubscibe花费时间(%5lldns)------->wEventID(%5d), bSrcType(%2d)", dwTime, wEventID, bSrcType);

	return bRet;
}

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
bool CEventEngine::UnSubscibe(IEventExecuteSink * pSink, u16 wEventID, BYTE bSrcType, u64 qwSrcID)
{
	//LARGE_INTEGER dwTimeBegin;
	//::QueryPerformanceCounter(&dwTimeBegin);

	bool bRet = m_ExecuteCenter.UnSubscibe(pSink, wEventID, bSrcType, qwSrcID);

	//LARGE_INTEGER dwTimeEnd;
	//QueryPerformanceCounter(&dwTimeEnd);
	//LARGE_INTEGER litmp;
	//::QueryPerformanceFrequency(&litmp);
	//LONGLONG dwTime = (dwTimeEnd.QuadPart - dwTimeBegin.QuadPart) * 1000000 / litmp.QuadPart;
	//if(g_pServerKernelLog && (dwTime > 300))
	//	g_pServerKernelLog->TraceErrorLn("m_ExecuteCenter.UnSubscibe花费时间(%5lldns)------->wEventID(%5d), bSrcType(%2d)", dwTime, wEventID, bSrcType);

	return bRet;
}
