#ifndef __CONNECTSINKMGR_H__
#define __CONNECTSINKMGR_H__

#include <ext/hash_map>

#include "ArrayAlloter.h"
#include "RunStateSink.h"

//连接池
class CConnectSinkPool 
{
public:
	//取得一个运行态连接槽
	IConnectSink* GetARunSink(void);

	CConnectSinkPool();
	~CConnectSinkPool();

public:
	CArrayAlloter2<MAX_CONNECT_NUM, CRunStateSink, is_element_canuse<CRunStateSink> > m_RunningSinkArray;
};


//登陆信号槽管理器
class CConnectSinkManager
{
	typedef __gnu_cxx::hash_map<u32, IConnectSink *> TMAP_CONNECTSINK;

public:
	//更新sink
	void UpdateConnectSink(u32 dwConnectIndex, IConnectSink *pConnectSink);

	//取得sink
	IConnectSink* GetConnectSink(u32 dwConnectIndex);

	//取得ConnectIndex
	DWORD GetConnectIndex(void);

	//////////////////////////////////////////////////////////////////////////
	// 描  述：获得所有正在使用的ConnState态连接
	// 输  入：pBuf为存放ConnState态连接指针的缓冲区，nNum为缓冲区可以存放 IConnectSink* 的数目
	//         ConnState指明要获取的连接态类型
	// 返回值：创建成功返回TRUE，
	//         pBuf中返回所有ConnState态连接的指针，nNum返回pBuf中指针的数目
	//////////////////////////////////////////////////////////////////////////
	BOOL GetAllCSink_ByState(IConnectSink **pBuf, s32 &nNum, CONN_STATE ConnState);

	// 获取连接数，即玩家数量
	u32 GetConnectNum() { return m_mapConnectSink.size();}

	// 清空所有数据
	void Restore();

	CConnectSinkManager(void);

	~CConnectSinkManager(void);

private:
	TMAP_CONNECTSINK m_mapConnectSink;	//记录所有正在使用的连接槽
	u32 m_dwConnectIndex;
};

#endif //__CONNECTSINKMGR_H__
