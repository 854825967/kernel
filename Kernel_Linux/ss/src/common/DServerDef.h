#ifndef _DSERVERDEF_H__
#define _DSERVERDEF_H__
#include "GameSys.h"

//////////////////////////////////////////////////////////////////////////
// 消息移位宏定义

//CIRCULTYPE：流通类型（4位）
//ACTIONID：行为事件的子消息码（8位）
#define MAKE_MSGID(CIRCULTYPE, ACTIONID)	(CIRCULTYPE << 8 | ACTIONID)

//获取消息的CIRCULTYPE（流通类型）
#define PARSE_CIRCULTYPE(MSGID)				(MSGID >> 8)

//获取消息的ACTIONID（行为事件子消息码）
#define PARSE_ACTIONID(MSGID)				(MSGID & 0xFF)

//////////////////////////////////////////////////////////////////////////

//////////////////////// 全局宏 //////////////////////////////////
// 无效uid
#define		INVALID_UID				0
// 无效房间ID
#define		INVALID_ROOMID			0
// 无效的ClientID
#define		INVALID_CLIENT			(ClientID)0xFFFFFFFF

#define		VERSION_NUMBER			9875

#define		INVALID_CONTAINERID		0

#define		MAX_CARD_NUM			3			// 装备镶嵌卡片的最大值


#define		INVALID_EFFECT_ID		0	// 无效效果ID
#define		INVALID_BUFF_ID			0	// 无效buffID
#define		INVALID_SKILL_ID		0	// 无效技能ID

typedef	s64		UID;
// 唯一的ClientID
typedef unsigned int ClientID;

// ClientID结构
struct ClientIDInfo
{
	// u32 nGatewayID : 8;  // 网关ID
	// u32 nConnIndex :24;  // 连接序号
  u32 nGatewayID;
  u32 nConnIndex;
};

#pragma pack(push, 1)
struct _UID
{
	u32		dwRotatoryID;		// 在一个地图中，每个实体的dwRotatoryID是唯一的
	u8		byServerID;			// 服务器ID
	u8		byTypeID;			// 实体类型（enThing_Class_Actor、enThing_Class_Goods）
	u16		wMapID;				// 地图ID
};

struct ServerRoomInfo
{
	u32		nRoomID;		// 房间唯一ID
	s32		nMapID;			// 地图ID

	ServerRoomInfo()
	{
		nRoomID = 0;
		nMapID = 0;
	}
};

#pragma pack(pop)


////////////////////////广播对像类型///////////////////////////////
// 广播对像类型，用于IRoom::BroadcastMessage
enum
{
	/*
	00000000 00000001		// 广播给人物
	00000000 00000010		// 广播给怪物
	11111111 11111111 11111111 11111111		// .....	
	//*/
	tBroadcast_Entity_Actor = 0x0001,		// 广播给人物
	tBroadcast_Entity_Monster = 0x0002,		// 广播给怪物
	tBroadcast_Entity_Dummy = 0x0004,		// 广播给假人
};

enum
{
	ECold_ClassID_Skill = 1,					// 技能冷却组
	ECold_ClassID_Goods,						// 物品冷却组
	ECold_ClassID_Chat,							// 聊天冷却组
	ECold_ClassID_Task,							// 任务冷却组
	ECold_ClassID_Strength,						// 炼金冷却组
	ECold_ClassID_Other,						// 通用冷却组(程序使用,不能用来配置)

	ECold_ClassID_Max,							// 最大
};

enum
{
	ECold_ColdID_Train			= 1,			// 试炼之塔CD
	ECold_ColdID_RefreshTask	= 2,			// 刷新公告任务
	ECold_ColdID_Energy			= 3,			// 精力值回复冷却
	ECold_ColdID_InstanceMoney		= 4,			// 关卡征收金币冷却
};

#endif //_DSERVERDEF_H__
