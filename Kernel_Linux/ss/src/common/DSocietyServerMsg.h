/*******************************************************************
** 文件名:  DSocietyServerMsg.h
** 版  权:	(C)  
** 创建人:	庄雪锋
** 日  期:	2011/08/16
** 版  本:	1.0
** 描  述:	社会服与其他服务器通信的数据包结构定义,只用于服务器之间
** 应  用:  服务器
** 备  注:

文件分4部分：
1、辅助数字宏定义
2、辅助数据包结构体定义
3、消息头定义
4、通信数据包定义
********************************************************************/

#ifndef _DSOCIETYSERVERMSG_H__
#define _DSOCIETYSERVERMSG_H__
#include "DSocietyServerDef.h"
#include "DCenterServerMsg.h"

#pragma pack(push,1)

//////////////////////////////////////////////////////////////////////////
// 插件消息消息码定义

////////////////////////// 与社会服根层消息码 ///////////////////////////////

#define S_YS_ROOT_MSGKEY_CHAT			1	// 聊天
#define YS_S_ROOT_MSGKEY_CHAT			1
 

#define S_YS_ROOT_MSGKEY_ACTOR			2	// 角色上下线相关
#define YS_S_ROOT_MSGKEY_ACTOR			2

#define S_YS_ROOT_MASGKEY_RELATION      3   // 角色关系相关（好友，黑名单）
#define YS_S_ROOT_MASGKEY_RELATION      3

#define S_YS_ROOT_MSGKEY_TEAM			4	// 组队
#define YS_S_ROOT_MSGKEY_TEAM			4

#define S_YS_ROOT_MASGKEY_MAIL          5   // 邮件
#define YS_S_ROOT_MASGKEY_MAIL          5

#define S_YS_ROOT_MASGKEY_UNION			6	// 家族
#define YS_S_ROOT_MASGKEY_UNION			6	// 家族

#define YS_S_ROOT_MASGKEY_BATTLE		7	// 战场


//与社会服关系插件与场景服关系插件通信的子消息码 S_CS_ROOT_MASGKEY_RELATION

#define CSC_DATA_TRANSMIT                        10  //游戏服转发社会服消息

//#define CSC_RELATIONMSG_DATA_UPDATE              10   // 关系数据下发
//#define CSC_RELATIONMSG_ONLINE_UPDATE            11   // 在线情况通知

#define CSC_RELATIONMSG_STRANGER                 11   // 陌生人数据通信
struct StrangerInfo_CSC
{
	int    lActorID;               //请求加陌生人的id

	int	lStrangerID;			// 玩家ID
	char	szActorName[19];		// 玩家名字
	BYTE    bSex;                   // 性别
	BYTE	wProfession;			// 职业
	BYTE	bNation;				// 国家

	StrangerInfo_CSC()
	{
		memset(this, 0, sizeof(*this));
	}
};

// part_2
//////////////////////////////////////////////////////////////////////////
typedef struct _ActorBaseInfo
{
	int	lActorID;						// 角色ID
	char	szName[LEN_MAX_ACTOR_NAME];		// 角色名

	_ActorBaseInfo()
	{
		memset(this,0,sizeof(*this));
	}
} ActorBaseInfo, *PActorBaseInfo;

// 用于批量更新玩家属性到社会服务器
typedef struct _ActorBaseInfoEx : public ActorBaseInfo
{
	int	lLevel;							// 等级
	int	lRoomID;						// 房间ID
	DWORD	dwUnion;						// 家族ID
	DWORD	dwSex;							// 性别

	_ActorBaseInfoEx()
	{
		memset(this,0,sizeof(*this));
	}

} ActorBaseInfoEx, *PActorBaseInfoEx;

// part_3
//////////////////////////////////////////////////////////////////////////
// 其他服务器与社会服通信消息定义[消息头]
enum
{
	CMD_INVAILD				= 0,		// 无效

	//
	// ISocietyClient -> SocietySvr
	//
	CMD_ACTOR_LOGIN				= 1,		// 角色登陆
	CMD_ACTOR_LOGOUT			= 2,		// 角色登出
	CMD_ACTOR_LIST_UPDATE		= 3,		// 角色列表更新
	CMD_BROADCAST_DATA			= 4,		// 发送数据到社会服，让其发给所有服务器(游戏服务)
	CMD_SENDTO_PLUGIN			= 5,		// 发送数据给社会服插件
	CMD_SOCIETY_CLIENT_LOGIN	= 6,		// ISocietyClient登陆SocietySvr
	CMD_ACTOR_PROPERTY_UPDATE	= 7,		// 角色属性更新，比如等级，金钱等

	//
	// SocietySvr -> ISocietyClient
	// 
	CMD_SOCIETY_CLIENT_LOGIN_RES= 100,		// SocietySvr响应ISocietyClient登陆
	CMD_SEND_TO_ACTOR			= 101,		// 发送给某个角色
	CMD_SEND_TO_ROOM			= 102,		// 发送到某个房间
	CMD_SOCIETY_BROADCAST_DATA  = 103,		// 广播数据
	CMD_UPDATE_ONLINE_NUM		= 104,		// 更新在线人数

	CMD_MAX_NUM,							// 最大值
};

// part_4
//////////////////////////////////////////////////////////////////////////
// 数据包头
typedef struct _SBasePacket 
{
	WORD	wHeader;				
	WORD	wSubHeader;

	_SBasePacket()
	{
		memset(this,0,sizeof(*this));
		wHeader = CMD_INVAILD;
	}
} SBasePacket, *PSBasePacket;

// 角色登录
typedef struct _SActorLoginPacket : public SBasePacket
{
	ActorBaseInfo	data;
	BYTE			byType;		//  0：上线登陆，1：跨游戏服登陆

	_SActorLoginPacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_ACTOR_LOGIN;
	}
} SActorLoginPacket, *PSActorLoginPacket;

// 角色登出
typedef struct _SActorLogoutPacket : public SBasePacket
{
	int	lActorID;						// 角色ID
	BYTE	byType;							// 1：登出，2：登出（跨游戏服的情况）	

	_SActorLogoutPacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_ACTOR_LOGOUT;
	}
} SActorLogoutPacket, *PSActorLogoutPacket;

// 角色列表更新
typedef struct _SActorListUpdatePacket : public SBasePacket
{
	BYTE	byFirst;							// 是否第一次更新
	WORD	wNum;								// 本次更新的实际个数

	// 后面跟wNum个ActorBaseInfoEx数据

	_SActorListUpdatePacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_ACTOR_LIST_UPDATE;
	}
} SActorListUpdatePacket, *PSActorListUpdatePacket;

// 发送到社会服进行广播
typedef struct _SBoardcastDataPacket : public SBasePacket
{
	// n个字节数据

	_SBoardcastDataPacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_BROADCAST_DATA;
	}
} SBoardcastDataPacket, *PSBoardcastDataPacket;

// 发送数据给社会服的插件
typedef struct _SSendToPluginPacket : public SBasePacket
{
	WORD wEventID;						// 事件id
	BYTE bySrcTypeID;					// 源类型id
	
	// 后面跟n个字节数据

	_SSendToPluginPacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_SENDTO_PLUGIN;
	}
} SSendToPluginPacket, *PSSendToPluginPacket;

// ISocietyClient请求登陆社会服
typedef struct _SSocietyClientLoginPacket : public SBasePacket
{
	char	szSvrName[LEN_MAX_SVR_NAME];	// 服务器名字/描述
	DWORD	dwID;							// 服务器ID
	BYTE	byType;							// 服务器类型
	WORD	wPort;							// 服务器开放的端口
	
	_SSocietyClientLoginPacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_SOCIETY_CLIENT_LOGIN;
	}
} SSocietyClientLoginPacket, *PSSocietyClientLoginPacket;


typedef struct _SActorPropertyUpdatePacket : public SBasePacket
{
	enum
	{
		APU_INVALID = 0,
		APU_LEVEL,			// 等级更新
		APU_ROOM_CHANGE,	// 房间切换
		APU_UNION,			// 家族
		APU_SEX,			// 性别
		APU_NUM,
	};
	
	BYTE	byType;			// 更新类型，取值范围:[APU_LEVEL,APU_NUM]
	int	lActorID;		// 角色ID
	
	union
	{
		int	nLevel;			// 最新等级
		int	nRoomID;		// 最新房间id
		DWORD	dwUnionID;		// 家族ID
		DWORD	dwSex;			// 性别
	};

	_SActorPropertyUpdatePacket()
	{
		memset(this,0,sizeof(*this));
		wHeader = CMD_ACTOR_PROPERTY_UPDATE;
	}
} SActorPropertyUpdatePacket, *PSActorPropertyUpdatePacket;

//////////////////////////////////////////////////////////////////////////

// SocietySvr响应ISocietyClient登陆
typedef struct _SSocietyClientLoginResPacket : public SBasePacket
{
	BYTE	byResult;								// 成功与否,1 成功；0 失败
	int		nNo;									// 服务器序号
	char	szDescription[LEN_MAX_SOCIETY_SVR_DESC];// 描述

	_SSocietyClientLoginResPacket()
	{
		memset(this,0,sizeof(*this));
		wHeader = CMD_SOCIETY_CLIENT_LOGIN_RES;
	}
} SSocietyClientLoginResPacket, *PSSocietyClientLoginResPacket;

// 发送给某个角色数据
typedef struct _SSendToActorPacket : public SBasePacket
{
	int lActorID;					// 角色ID

	// 后面跟n个字节数据				// buf

	_SSendToActorPacket()
	{
		memset(this,0,sizeof(*this));
		wHeader = CMD_SEND_TO_ACTOR;
	}
} SSendToActorPacket, *PSSendToActorPacket;

// 发送给某个Room数据
typedef struct _SSendToRoomPacket : public SBasePacket
{
	int lRoomID;					// 房间ID

	// 后面跟n个字节数据				// buf

	_SSendToRoomPacket()
	{
		memset(this,0,sizeof(*this));
		wHeader = CMD_SEND_TO_ROOM;
	}
} SSendToRoomPacket, *PSSendToRoomPacket;

// 社会服广播数据
typedef struct _SSocietyBoardcastDataPacket : public SBasePacket
{
	// n个字节数据

	_SSocietyBoardcastDataPacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_SOCIETY_BROADCAST_DATA;
	}
} SSocietyBoardcastDataPacket, *PSSocietyBoardcastDataPacket;

// 更新在线人数
typedef struct _SUpdateOnlineNumPacket : public SBasePacket
{
	BYTE	nType;						// 服务器类型 
	char	szIP[LEN_MAX_SERVER_IP];	// 服务器IP
	WORD	wPort;						// 端口
	int	nOnlineNum;					// 服务器在线人数
	int	nTotalOnlineNum;			// 总在线人数

	_SUpdateOnlineNumPacket()
	{
		memset(this, 0, sizeof(*this));
		wHeader = CMD_UPDATE_ONLINE_NUM;
	}
} SUpdateOnlineNumPacket, *PSUpdateOnlineNumPacket;

#pragma pack(pop)

#endif//_DSOCIETYSERVERMSG_H__
