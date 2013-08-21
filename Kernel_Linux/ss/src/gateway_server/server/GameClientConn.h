/*******************************************************************
** 文件名:	GameClientConn.h
** 版  权:	(C)  
** 创建人:	庄雪锋
** 日  期:	2011/08/01
** 版  本:	1.0
** 描  述:	游戏服网关客户端
** 应  用:  服务器 

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef _GAMECLIENTCONN_H_
#define _GAMECLIENTCONN_H_
#include "DGatewayMsg.h"
#include "core/connection_task.h"
#include "core/tcp_client.h"

// 宏定义
#define CLIENT_CONNECT_MAX_NUM		4096

using namespace core;

// 类声明
class CGameClientMgr;

class CGameClientConn : public TCPClient, public ConnectionTask {
public:
	// 构造函数
	CGameClientConn(const InetAddress &server_address, const std::string &name);

	// 析构函数
	virtual ~CGameClientConn(void);

	// 释放
	virtual void Release();

	// 创建
	BOOL Create(CGameClientMgr *pGameClientMgr, u32 dwSceneID);
	
	// 是否运行
	inline BOOL IsRun() const { return m_bISRun; }

	// 获取游戏服id
	inline u32 GetGameID() const { return m_dwGameID; }

	// 接受数据处理
	virtual void OnRecieve(const char *message, int size);

	// 连接建立成功时
	virtual ConnectionTask *OnConnectionEstablished();

	// 断开连接
	virtual void OnCloseConnection(bool force);

	// 连接成功
	virtual void OnConnectionOK();

	// 发送数据, 减少拷贝次数
	BOOL SendData(const char *Buf, int nLen);

	// 获取游戏服的IP地址
	inline LPCSTR GetServerIP() const { return m_lpszAppIP; }

	// 获取游戏服的端口
	inline u16 GetPort() const { return m_wPort; }

	// 获取游戏服类型
	inline u8 GetServerType() const { return m_SAppServerInfo.nType; }
	

private:
	SAppServerInfo		m_SAppServerInfo;	// 服务器信息
	CGameClientMgr		*m_pGameClientMgr;
	char			m_lpszAppIP[17];	// IP
	u16			m_wPort;		// 端口号
	BOOL			m_bISRun;		// 是否可以允许提供正常服务
	u32			m_dwGameID;		// 游戏服ID号
	u32			m_dwSocketsArray[CLIENT_CONNECT_MAX_NUM];
};

#endif // _GAMECLIENTCONN_H_
