/*******************************************************************
** 文件名:	GameClientMgr.h
** 版  权:	(C)  
** 创建人:	庄雪锋
** 日  期:	2011/08/01
** 版  本:	1.0
** 描  述:	游戏服连接管理器(包括大厅服务器和房间服务器)
** 应  用:  服务器 

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef _GAMECLIENTMGR_H_
#define _GAMECLIENTMGR_H_

#include <vector>
#include <ext/hash_map>

#include "GameClientConn.h"

class CGameClientMgr
{
	typedef __gnu_cxx::hash_map<DWORD , CGameClientConn *> GAMECONNMAP;
public:
	// 构造函数
	CGameClientMgr(void);

	// 析构函数
	~CGameClientMgr(void);

	//   关闭
	void Close();

	// 登陆游戏服
	BOOL CreateGameConn(u32 dwGameID, LPCSTR lpGameIP, u16 wPort);

	// 登陆游戏服
	BOOL AddGameConn(CGameClientConn *pGameConn);

	// 删除一个连接
	BOOL DelGameConn(CGameClientConn *pGameConn);

	// 根据 游戏服ID 查找 游戏服连接指针
	CGameClientConn * FindGameConnByGameID(u32 dwGameID); 

	// 根据 游戏服IP地址和端口 查找 游戏服连接指针
	CGameClientConn * FindGameConnByServerInfo(LPCSTR lpServerIP, u16 wPort); 

	// 发送消息到游戏
	BOOL SendMsgToGame(u32 dwGameID, LPCSTR lpData, s32 nLen);

	// 根据账号ID负载均衡至每个大厅服务器
	CGameClientConn* FindLobbyConn(s64 qwUserID);

private:

	// 创建房间服管理列表
	GAMECONNMAP m_RoomConnMap; 

	// 创建大厅服管理列表
	GAMECONNMAP m_LobbyConnMap;

	// 大厅服务器列表
	std::vector<u32>	m_vectLobbyServerID;
}; 

#endif //_GAMECLIENTMGR_H_

