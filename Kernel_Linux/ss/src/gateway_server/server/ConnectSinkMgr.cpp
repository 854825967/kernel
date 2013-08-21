#include "ConnectSinkMgr.h"

#include "ILog.h"
#include "GateWayServiceMgr.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////// CConnectSinkPool ////////////////////////////
CConnectSinkPool::CConnectSinkPool()
{
}

CConnectSinkPool::~CConnectSinkPool()
{
}

//取得一个运行态连接槽
IConnectSink* CConnectSinkPool::GetARunSink(void)
{
	s32 nIndex = m_RunningSinkArray.Allot();
	if(nIndex < 0 || nIndex >= MAX_CONNECT_NUM)
	{
		return NULL;
	}

	return &m_RunningSinkArray[nIndex];
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// CConnectSinkManager ///////////////////////////
CConnectSinkManager::CConnectSinkManager(void) : m_dwConnectIndex(0)
{
	m_mapConnectSink.clear();
}

CConnectSinkManager::~CConnectSinkManager(void)
{
}

// 更新sink
void CConnectSinkManager::UpdateConnectSink(u32 dwConnectIndex, IConnectSink *pConnectSink)
{
	if (NULL == pConnectSink)
	{
		//删除sink
		m_mapConnectSink.erase(dwConnectIndex);
	}
	else
	{
		//更新或者增加sink
		m_mapConnectSink[dwConnectIndex] = pConnectSink;
	}

	if (m_mapConnectSink.size() > MAX_CONNECT_NUM)
	{
		g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("玩家连接数目超出允许值: %d",
			m_mapConnectSink.size());
	}
}

//取得sink
IConnectSink* CConnectSinkManager::GetConnectSink(u32 dwConnectIndex)
{
	TMAP_CONNECTSINK::iterator it = m_mapConnectSink.find(dwConnectIndex);
	if(it == m_mapConnectSink.end())
	{
		return NULL;
	}

	return (*it).second;
}

//取得ConnectIndex
u32 CConnectSinkManager::GetConnectIndex(void)
{
	return (++m_dwConnectIndex);
}

//////////////////////////////////////////////////////////////////////////
// 描  述：获得所有正在使用的ConnState态连接
// 输  入：pBuf为存放ConnState态连接指针的缓冲区，nNum为缓冲区可以存放 IConnectSink* 的数目
//         ConnState指明要获取的连接态类型
// 返回值：创建成功返回TRUE，
//         pBuf中返回所有ConnState态连接的指针，nNum返回pBuf中指针的数目
//////////////////////////////////////////////////////////////////////////
BOOL CConnectSinkManager::GetAllCSink_ByState(IConnectSink **pBuf, s32 &nNum, CONN_STATE ConnState)
{
	if (NULL == pBuf || nNum < 1 || ConnState < 0 || ConnState >= enConnState_Max)
	{
		nNum = 0;
		return FALSE;
	}

	IConnectSink **ppConnectSink = pBuf;
	IConnectSink *pConnectSink = NULL;

	s32 nLimit = nNum;
	nNum = 0;

	TMAP_CONNECTSINK::iterator it = m_mapConnectSink.begin();
	for (; it != m_mapConnectSink.end(); ++it)
	{
		if (nNum >= nLimit)
		{
			return TRUE;
		}

		pConnectSink = (*it).second;
		if (NULL != pConnectSink && ConnState == pConnectSink->GetConnectSinkState())
		{
			*ppConnectSink = pConnectSink;
			ppConnectSink++;
			nNum++;
		}
	}

	return TRUE;
}

void CConnectSinkManager::Restore()
{
	if( m_mapConnectSink.empty() )
	{
		return;
	}

	TMAP_CONNECTSINK::iterator it = m_mapConnectSink.begin();
	for (; it != m_mapConnectSink.end(); ++it)
	{
		IConnectSink* pConnectSink = it->second;
		if( NULL != pConnectSink )
		{
			if( pConnectSink->IsHaveUsed() )
			{
				pConnectSink->Clean(FALSE);
			}
		}
	}
	m_mapConnectSink.clear();
}

