/*******************************************************************
** 文件名:  PartFields.h
** 版  权:	(C)  
** 创建人:	Zipher
** 日  期:	2011-08-08
** 版  本:	1.0
** 描  述:	游戏服 游戏对象部件公用宏定义
** 应  用:  

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef _PARTFIELDS_H__
#define _PARTFIELDS_H__

//------------------------------------------------------------------------------------------------
enum EObjectParts
{
	OBJECT_PART_BGN					=	0,
	OBJECT_PART_END					=	0,
};

//------------------------------------------------------------------------------------------------
enum EWorldObjParts
{
	WORLDOBJ_PART_TASK				=	OBJECT_PART_END + 0,		// 任务部件
	WORLDOBJ_PART_CREATURE_COMMON	=	OBJECT_PART_END + 1,		// 生物公共部件
	WORLDOBJ_PART_END				=	OBJECT_PART_END + 2,
};
// WorldObject部件个数
#define WORLDOBJ_PART_NUM	(WORLDOBJ_PART_END - OBJECT_PART_END)

//------------------------------------------------------------------------------------------------
enum EBoxParts
{
	BOX_PART_END					=	WORLDOBJ_PART_END + 0,
};
// 盒子特有部件个数
#define BOX_PART_NUM		(BOX_PART_END - WORLDOBJ_PART_END)

//------------------------------------------------------------------------------------------------
enum EUnitParts
{
	UNIT_PART_BUFF					=	WORLDOBJ_PART_END + 0,		// Buff部件
 	UNIT_PART_SKILL					=	WORLDOBJ_PART_END + 1,		// 技能部件ISkillPart
	UNIT_PART_AI					=   WORLDOBJ_PART_END + 2,		// 生物AI部件IAIPart
	UNIT_PART_DIE					=	WORLDOBJ_PART_END + 3,		// 死亡部件UnitDiePart
 	UNIT_PART_CREATURE_CONJURE		=	WORLDOBJ_PART_END + 4,		// 生物召唤部件IWS_SL_ConjurePart
 	UNIT_PART_END					=	WORLDOBJ_PART_END + 5,
};
// 所有生物类共享部件个数
#define UNIT_PART_NUM		(UNIT_PART_END - WORLDOBJ_PART_END)

//------------------------------------------------------------------------------------------------
enum ECreatureParts
{
	CREATURE_PART_END				=	UNIT_PART_END + 0,
};
// 所有怪物或NPC类共享部件个数
#define CREATURE_PART_NUM	(CREATURE_PART_END - UNIT_PART_END)

//------------------------------------------------------------------------------------------------
enum EHeroParts
{
	HERO_PART_END					=	UNIT_PART_END + 0,
};
// 所有佣兵共享部件个数
#define HERO_PART_NUM	(HERO_PART_END - UNIT_PART_END)

//------------------------------------------------------------------------------------------------
enum EPlayerParts
{
	PLAYER_PART_PACKET				=	UNIT_PART_END + 0,		// 玩家背包部件
	PLAYER_PART_TASK				=	UNIT_PART_END + 1,		// 玩家任务背包部件
	PLAYER_PART_TITLE				=	UNIT_PART_END + 2,		// 玩家称号部件
	PLAYER_PART_SOLT				=	UNIT_PART_END + 3,		// 玩家卡槽部件
	PLAYER_PART_DROP				=	UNIT_PART_END + 4,		// 玩家掉落奖励部件
	PLAYER_PART_CHAT				=	UNIT_PART_END + 5,		// 玩家聊天部件
	PLAYER_PART_COLD				=	UNIT_PART_END + 6,		// 玩家冷却部件
	PLAYER_PART_END					=	UNIT_PART_END + 7,
};
// 玩家特有部件个数
#define PLAYER_PART_NUM		(PLAYER_PART_END - UNIT_PART_END)

//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
enum EDummyParts
{
	DUMMY_PART_SLOT					=	UNIT_PART_END + 0,		// 假人卡槽部件
	DUMMY_PART_END					=	UNIT_PART_END + 1,
};
// 假人特有部件个数
#define DUMMY_PART_NUM		(DUMMY_PART_END - UNIT_PART_END)
//------------------------------------------------------------------------------------------------

#endif //_PARTFIELDS_H__
