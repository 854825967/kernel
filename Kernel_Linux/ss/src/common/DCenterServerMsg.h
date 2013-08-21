/*****************************************************************************
模块名      : 其他服务器和大厅服务器通信的消息结构
文件名      : DCenterServerMsg.h
相关文件    : 
文件实现功能: 其他服务器和大厅服务器通信的消息结构
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/07/06  0.1         庄雪锋      创建
******************************************************************************/

#ifndef __DCENTERSERVERMSG_H__
#define __DCENTERSERVERMSG_H__

#include <string.h>

#include "HashFun.h"
#include "GameType.h"

// 客户端到服务器消息码定义
#define	CENTER_CSMSG_SERVER_LOGIN		1	// 服务器登录
#define CENTER_CSMSG_ROOM_UPDATELIST	2	// 房间更新列表
#define CENTER_CSMSG_ROOM_LOGIN			3	// 房间登录
#define CENTER_CSMSG_ROOM_LOGOUT		4	// 房间退出
#define CENTER_CSMSG_ACTOR_UPDATELIST	5	// 角色更新列表
#define CENTER_CSMSG_ACTOR_LOGIN		6	// 角色登录
#define CENTER_CSMSG_ACTOR_LOGOUT		7	// 角色退出
#define CENTER_CSMSG_SENDTO_ACTOR		8	// 发送数据给某个角色
#define CENTER_CSMSG_SENDTO_ROOM		9	// 发送数据给某个房间
#define CENTER_CSMSG_BROADCAST_DATA		10	// 发送数据给所有服务器
#define CENTER_CSMSG_SENDTO_PLUGIN		11	// 发送数据给插件
#define CENTER_CSMSG_NEW_ROOM			12	// 创建新房间

// 服务器到客户端消息码定义
#define	CENTER_SCMSG_SERVER_LOGIN		20	// 服务器登录
#define CENTER_SCMSG_ROOM_UPDATELIST	21	// 房间更新列表
#define CENTER_SCMSG_ROOM_LOGIN			22	// 房间登录
#define CENTER_SCMSG_ROOM_LOGOUT		23	// 房间退出
#define CENTER_SCMSG_SENDTO_ACTOR		24	// 发送数据给某个角色
#define CENTER_SCMSG_SENDTO_ROOM		25	// 发送数据给某个房间
#define CENTER_SCMSG_BROADCAST_DATA		26	// 发送数据给所有服务器
#define CENTER_SCMSG_ONLINENUM_UPDATE	27	// 在线人数更新

#define CENTER_SCMSG_GATEWAYINFO_UPDATE	28	// 网关信息更新

#define CENTER2LOGIN_ACTOR_LOGIN_LOGOUT	35  // 玩家登录|登出

#define CENTER_SCMSG_SERVERINFO_UPDATE	50	// 网关信息更新
#define CENTER_SCMSG_SENDTO_SOCIETY		60	// 发送数据到社会服务器


// 其他定义
#define CENTER_MAX_SERVERNAME_LEN		33	// 最大服务器名字长度
#define CENTER_MAX_SERVERIP_LEN			33	// 最大服务器IP长度
#define CENTER_MAX_DESC_LEN				128	// 最大描述字符串长度
#define CENTER_INVALID_ACTORID			0	// 无效角色ID

// 服务器类型定义
enum
{
	CENTER_ST_LOGIN = 0,	// 登录服
	CENTER_ST_GATEWAY = 1,	// 网关服
	CENTER_ST_ROOM = 2,		// 房间服
	CENTER_ST_SOCIETY = 3,	// 社会服
	CENTER_ST_CENTER = 4,	// 中心服
	CENTER_ST_LOBBY	= 5,	// 大厅服
  CENTER_ST_CACHE_PROXY = 6, // cache代理服务器
};

// 特殊服务器ID宏定义
enum 
{
	SERVER_ID_LOGIN = 0,	// 登陆服ID
};

//////////////////////////////////////////////////////////////////////////
// 插件消息消息码定义

////////////////////////// 与中心服根层消息码 ///////////////////////////////

#define S_CS_ROOT_MSGKEY_CHAT			1	// 聊天
#define CS_S_ROOT_MSGKEY_CHAT			1

#define S_CS_ROOT_MSGKEY_INTERACT		2	// 交互系统消息码
#define CS_S_ROOT_MSGKEY_INTERACT		2


#define S_CS_ROOT_MSGKEY_ACTOR			3	// 角色上下线相关
#define CS_S_ROOT_MSGKEY_ACTOR			3

#define S_CS_ROOT_MASGKEY_RELATION      4   // 角色关系相关（好友，黑名单）
#define CS_S_ROOT_MASGKEY_RELATION      4

#define S_CS_ROOT_MSGKEY_TEAM			5	// 组队
#define CS_S_ROOT_MSGKEY_TEAM			5

#define LS_S_ROOT_MSGKEY_LS				6	// 登录服系统消息码
#define S_LS_ROOT_MSGKEY_LS				6


#pragma pack(push, 1)

// 服务器Key
struct SServerKey
{
	BYTE	nType;	// 服务器类型
	char	szIP[CENTER_MAX_SERVERIP_LEN];	// 服务器IP
	WORD	wPort;	// 服务器开放的端口

	SServerKey()
	{
		memset(this, 0, sizeof(*this));
	}

	SServerKey(BYTE Type, char* IP, WORD Port)
	{
		if (IP)
		{
			nType = Type;
			wPort = Port;
			strncpy(szIP,IP,sizeof(szIP));
		}
	}

	bool operator == (const SServerKey &ServerKey) const
	{
		return (strcmp(szIP, ServerKey.szIP) == 0 && wPort == ServerKey.wPort);
	}

	size_t operator() (const SServerKey &ServerKey) const
	{
		return hash::HashString(ServerKey.szIP) + ServerKey.wPort;
	}

	bool operator < (const SServerKey &ServerKey) const
	{
  /*
		union UKey
		{
			struct
			{
				size_t nIP;
				size_t nPort;
			}data;
			u64	 key;
		};
    */
    struct UKey {
      size_t nIP;
      WORD wPort;
    };

		UKey key1 ;
		key1.nIP = hash::HashString(ServerKey.szIP);
		key1.wPort = ServerKey.wPort;

		UKey key2 ;
		key2.nIP = hash::HashString(szIP);
		key2.wPort = wPort;

    if(key1.nIP == key2.nIP) {
      return key1.wPort < key2.wPort;
    } else {
      return key1.nIP < key2.nIP;
    }
	}
};

// 服务器登陆信息
struct SServerLoginInfo
{
 	char	szName[CENTER_MAX_SERVERNAME_LEN];		// 服务器名字
	s32	ServerID;								// ServerID
	BYTE	nType;									// 服务器类型
	char	szIP[CENTER_MAX_SERVERIP_LEN];			// 服务器IP
	WORD	wPort;									// 服务器开放的端口
	BOOL	bLoginBlg;								// 登陆标志

	SServerLoginInfo()
	{
		memset(this, 0, sizeof(*this));
	}

	bool operator == (const SServerLoginInfo &ServerKey) const
	{
		return (strcmp(szName, ServerKey.szName) == 0 && strcmp(szIP, ServerKey.szIP) == 0 && 
			ServerID == ServerKey.ServerID && nType == ServerKey.nType && wPort == ServerKey.wPort );
	}
};

// 服务器登录现场数据
struct SCenterServerLoginContext
{
	char	szName[CENTER_MAX_SERVERNAME_LEN];	// 服务器名
	BYTE	nType;								// 服务器类型
	DWORD 	dwID;								// 服务器ID 
	WORD	wPort;								// 服务器开放的端口

	SCenterServerLoginContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 服务器登录结果现场数据
struct SCenterServerLoginResContext
{
	BOOL	bResult;								// 成功与否
	int		nNo;									// 服务器序号
	char	GameServerName[32];						// 游戏世界名字
	char	szDescription[CENTER_MAX_DESC_LEN];		// 描述

	SCenterServerLoginResContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 更新地图结果现场数据
struct SCenterRoomUpdateListResContext
{
	char	szIP[CENTER_MAX_SERVERIP_LEN];	// 更新地图的服务器IP
	WORD	wPort;		// 端口
	int		nRoomNum;	// 地图数目
	BOOL	bFirst;		// 分批更新时是否是第一次

	SCenterRoomUpdateListResContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 发送在线人数现场数据
struct SCenterOnlineNumUpdate
{
	BYTE	nType;							// 服务器类型 
	char	szIP[CENTER_MAX_SERVERIP_LEN];	// 服务器IP
	WORD	wPort;							// 端口
	int	nOnlineNum;						// 服务器在线人数
	int	nTotalOnlineNum;				// 总在线人数

	SCenterOnlineNumUpdate()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 发送在线人数现场数据
struct SCenterGateWayInfoUpdate
{
	BYTE	nType;							// 服务器类型 
	char	szIP[CENTER_MAX_SERVERIP_LEN];	// 服务器IP
	WORD	wPort;							// 端口
	int	nOnlineNum;						// 服务器在线人数
	int	nTotalOnlineNum;				// 总在线人数

	SCenterGateWayInfoUpdate()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 角色登录现场数据,用于批量同步时使用
struct SCenterActorLoginContext
{	
	int	lActorID;		// 角色ID
	char	szName[18];		// 角色名

	SCenterActorLoginContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 角色登录
struct SCenterActorLoginPacket : public SCenterActorLoginContext
{
	s64	qwUserID;	// 账号ID
	BYTE	byType;		//  0：上线登陆，1：跨场景服登陆
	
	SCenterActorLoginPacket()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 角色登出
struct SCenterActorLogoutPacket
{
	s64 qwUserID;		// 账号ID
	int	lActorID;		// 角色ID
	BYTE	byType;			// 1：登出，2：登出（跨场景服的情况）	

	SCenterActorLogoutPacket()
	{
		memset(this,0,sizeof(*this));
	}
};

// 对战双方列表
struct SBattleUnitInfo
{
	u8		byType;		// 玩家、假人、怪物
	u32		dwUnitID;	// 玩家、假人(角色ID), 怪物(模板ID)
	s64 qwUserID;
	u16		wOutHeroId;	// 目前没有出战佣兵(1表示是PVP活动)
	// 多个玩家ActorID

	SBattleUnitInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define TRAIN_MAP_ID	-1				// 试炼之塔地图ID
// 服务器登录现场数据
struct SCenterServerNewRoomContext
{
	SServerKey			serKey;			// 创建的服务器key
	s32 				nNewRoomID;		// 新房间ID 
	s32 				nMapID;		// 地图ID 
//////////////////////////////////////////////////////////////////////////
	//SBattleUnitInfo	attInfo;		// 攻方信息
	//SBattleUnitInfo	defineInfo;		// 守方信息

	SCenterServerNewRoomContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

/////////////////////////////////////////////////////////
//消  息    码：MAINACTION_MSGID_CS_LOGINOUT
//描        述：场景服登录或者登出中心服
//支持流通类型：SS
/////////////////////////////////////////////////////////
struct CS_LoginOut
{
	BYTE chType;			//1：场景服登录，2：场景服登出
	DWORD dwAppServer;		//对应场景服IAppServer的指针

	CS_LoginOut()
	{
		chType = 0;
		dwAppServer = 0;
	}
};



//////////////////// S_CS_ROOT_MSGKEY_ACTOR //////////////////////
//////////////////// CS_S_ROOT_MSGKEY_ACTOR //////////////////////
// 角色登录现场数据
struct SCenterActorInfor
{
	char	chLogin;		// 0：登陆，1：登出，2：登出（跨场景服的情况）
	char	chLoginType;	// 0：上线登陆，1：跨场景服登陆（chLogin为0时有效）
	s64 qwUserID;		// 帐号的UserID
	int	lActorID;		// 角色ID
	char	szName[18];		// 角色名
	int	lConsortiaID;	// 佣兵团ID
	char	chCampID;		// 角色的阵营ID

	SCenterActorInfor()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 游戏世界角色信息数据
struct SGlobalActorInfor
{
	char	chLogin;		// 0：登陆，1：登出，2：登出（跨场景服的情况）

	s64 qwUserID;		// 帐号的UserID
	int	lActorID;		// 角色ID
	char	chServerID;		// 角色所在的服务器ID

	SGlobalActorInfor()
	{
		memset(this, 0, sizeof(*this));
	}
};


struct S_CS_ROOT_HEAD
{
	WORD wRootMsgID;

	S_CS_ROOT_HEAD()
	{
		wRootMsgID = 0;
	}
};

struct CS_S_ROOT_HEAD
{
	WORD wRootMsgID;

	CS_S_ROOT_HEAD()
	{
		wRootMsgID = 0;
	}
};


//////////////////// LS_S_ROOT_MSGKEY_LS //////////////////////
//////////////////// S_LS_ROOT_MSGKEY_LS //////////////////////
#define LS_S_LOGIN_MAIN_KICK		1		//踢玩家
#define S_LS_LOGIN_MAIN_KICK		1


//登录服系统主消息码
struct LS_MainKey
{
	BYTE byKeyMain;			//见上面的定义

	LS_MainKey(void)
	{
		byKeyMain = 0;
	}
};

//踢玩家
struct LS_S_Login_Kick : public LS_MainKey
{
	s64 qwUserID;			//被踢玩家的账号ID

	LS_S_Login_Kick()
	{
		byKeyMain = LS_S_LOGIN_MAIN_KICK;
		qwUserID = 0;
	}
};

// 
// 玩家登出 Center2LOGIN_ACTOR_LOGIN_LOGOUT
// 
struct SCenterNotifyActorLoginLogout
{
	BYTE byOpType;	// 0 登入; 非0 登出
	s64 qwUserID;  // 用户ID

	SCenterNotifyActorLoginLogout()
	{
		memset(this,0,sizeof(*this));
	}

	SCenterNotifyActorLoginLogout(BYTE byOpType_, s64 qwUserID_)
	{
		byOpType = byOpType_;
		qwUserID = qwUserID_;
	}
};

#pragma pack(pop)

#endif // __DCENTERSERVERMSG_H__
