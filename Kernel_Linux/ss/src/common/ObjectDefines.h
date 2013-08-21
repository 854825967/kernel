/*******************************************************************
** 文件名:  ObjectDefines.h
** 版  权:	(C)  
** 创建人:	Zipher
** 日  期:	2010-01-05
** 版  本:	1.0
** 描  述:	场景服 游戏对象公用宏定义
** 应  用:  

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef _OBJECTDEFINES_H__
#define _OBJECTDEFINES_H__

#include "DServerDef.h"

#define MAX_PATH_LEN	256				//最大路径长度

#define MAX_MOVESPEED_LEVEL		9		//移动的速度等级

#define	MAX_SEND_BUFLEN		4000	// 最大发送长度


/////////////////////////////对象类型///////////////////////////////
enum TypeID
{
	TYPEID_OBJECT        = 0,
	TYPEID_ITEM          = 1,	// 道具
	TYPEID_CONTAINER     = 2,	// 背包
	TYPEID_UNIT          = 3,	// 怪物或NPC
	TYPEID_PLAYER        = 4,	// 玩家
	TYPEID_BOX			 = 5,	// 盒子物件
	TYPEID_HERO          = 6,	// 佣兵
	TYPEID_DUMMY		 = 7,	// 假人
	MAX_TYPEID			 = 8
};


//NPC（非玩家角色）的类型 
//2010 年 4月3日 修改
enum NPC_TYPE
{
	enNPCType_NPCSAFE = 1,			// 不可攻击NPC	（人和怪都不会攻击）
	enNPCType_NPCATTACK,			// 可攻击NPC	（只攻击怪）

 	enNPCType_GENERAL,				// 普通怪		（只攻击人）
	enNPCType_POLISH,				// 精英怪		（只攻击人）
	enNPCType_RARE,					// 稀有怪		（只攻击人）
	enNPCType_BOSS,					// BOSS怪		（只攻击人）
	enNPCType_VALOR,				// 勇猛怪		（人和怪都会攻击）

	enNPCType_LIFE,					// 生灵			（小猫、小狗等）


	enNPCType_GUARD,				// 守卫			（攻击红名和非阵营的人和怪）

	enNPCType_PAWNLUO,				// 爪牙型召唤兽 （可同时拥有多个）
	enNPCType_PAWNPET,				// 宠物型召唤兽	（只允许拥有一个，有固定目标环）

	enNPCType_GUYONG,				// 雇佣怪		（跟勇猛怪没区别，只是由AI召出）

	enNPCType_Build,				//  建筑 
	enNPCType_Build_P,				//  生产建筑，不可攻击
	enNPCType_Trap,					//  陷阱
	enNPCType_Furniture,			//  家具 
	enNPCType_Max					//  最大值
};

//怪物子类型
enum MONSTER_SUBTYPE
{
	enMonster_SUBTYPE_PASSIVE		= 0,			// 非主动怪
	enMonster_SUBTYPE_ATTIVE,						// 主动怪
};

//NPC子类型
enum NPC_SUBTYPE
{
    enNPC_SUBTYPE_Common			= 0,			//	普通NPC
    enNPC_SUBTYPE_Vendor_Food       = 1,			//	杂货商人
	enNPC_SUBTYPE_Vendor_Weapon     = 2,            //  武器商人
	enNPC_SUBTYPE_Vendor_Armor		= 3,	        //	防具商人
	enNPC_SUBTYPE_Transmit		    = 4,			//	传送用NPC
	enNPC_SUBTYPE_Flight_Master     = 5,			//	坐骑管理员
	enNPC_SUBTYPE_Banker			= 6,		    //	仓库管理员
    enNPC_SUBTYPE_Vendor_Travel     = 7,			//	旅行商人

	enNPC_SUBTYPE_Knight            = 8,			//	爵位兑换npc
	enNPC_SUBTYPE_Official          = 9,			//	官位兑换npc
	enNPC_SUBTYPE_GoldCoin          = 10,			//	黄金布币兑换npc
	enNPC_SUBTYPE_WayField          = 11,			//	战场排队npc

    enNPC_SUBTYPE_Picker            = 12,			//	采集技能导师
	enNPC_SUBTYPE_Producer          = 13,			//	生产技能导师

	enNPC_SUBTYPE_Activity_Organizer = 14,			//	活动介绍npc
	enNPC_SUBTYPE_Menke_Admin       = 15,			//	门客管理员
    enNPC_SUBTYPE_Mail_Admin        = 16,			//	邮件管理员
	enNPC_SUBTYPE_City_Admin        = 17,			//	城市管理员
	enNPC_SUBTYPE_State_Admin       = 18,			//	国家管理员
	enNPC_SUBTYPE_Marry_Admin       = 19,			//	婚姻管理员
	enNPC_SUBTYPE_Brother_Admin     = 20,			//	结拜管理员
	enNPC_SUBTYPE_Master_Admin      = 21,			//	师徒管理员
	enNPC_SUBTYPE_Pet_Admin         = 22,		    //	宠物管理员

    enNPC_SUBTYPE_Refine            = 23,		    //	精炼npc
    enNPC_SUBTYPE_Enchase           = 24,		    //	镶嵌npc
    enNPC_SUBTYPE_MakeHole          = 25,		    //	打孔npc

	enNPC_SUBTYPE_Max,		    
};

///////////////////////人物性别////////////////////////////////////
enum PERSONSEX
{
	PERSON_SEX_MALE = 0,				// 男性
	PERSON_SEX_FEMALE,					// 女性
};

enum CAMP_DEFINE
{
	CAMP_DEFINE_MIN = 0,		/// 最小值
	CAMP_DEFINE_MAX = 21,		/// 最大值
};

//生物行为状态
enum CRT_STATE
{
	enCrt_State_Unknow	=	0,		//生物处于未知状态
	enCrt_State_Stand,				//生物处于站立状态
	enCrt_State_Die,				//生物处于死亡状态
	enCrt_State_Shoot,				// 切换进程
	enCrt_State_Max,

	// 下面的状态是掩码
	enCrt_State_Fighting = 0x80,	//玩家处于战斗状态
};

enum SkillSchools
{
	SPELL_SCHOOL_WIND                   = 0,		// 风
	SPELL_SCHOOL_FIRE                   = 1,		// 火
	SPELL_SCHOOL_WATER					= 2,		// 水
	SPELL_SCHOOL_THUNDER                = 3,		// 雷
	SPELL_SCHOOL_POISON                 = 4,		// 毒
	SPELL_SCHOOL_MAGIC					= 5,		// 魔
	MAX_SPELL_SCHOOL					= 6
};

enum BoxState
{
	BOX_STATE_OPEN		=	0,
	BOX_STATE_CLOSE,
};

enum BoxType
{
	BOX_TYPE_PACK				=	0,	// 包裹（人物或怪物死亡掉下来的包裹）
	BOX_TYPE_TASKBOX,					// 任务相关的场景物件
	BOX_TYPE_HERBALMEDICINE,			// 草药	
	BOX_TYPE_MINERALRESOURCES,			// 矿藏
	BOX_TYPE_PRECIOUSDEPOSITS,			// 宝藏
	BOX_TYPE_CONTAINER,					// 场景物件容器(掉落+第一次打开触发事件)

};

#define	HERO_SHORTCUT_BUF_LEN			12			//佣兵快捷栏Buffer长度



////////////////////////// ＰＫ模式 ///////////////////////////////
enum
{
	EPKMode_Name_Safe = 0,							// 安全模式
	EPKMode_Name_Blind,								// 全体模式
	EPKMode_Name_Team,								// 队伍模式
	EPKMode_Name_Clan,								// 氏族模式
	EPKMode_Name_Nation,							// 国家模式
	EPKMode_Name_Justice,							// 善恶模式
	EPKMode_Name_Camp,								// 阵营模式
	EPKMode_Name_Max,								// .......
};

////////////////////////// ＰＫ区域 ///////////////////////////////
enum
{
	EPK_AreaName_General = 0,						// 普通区
	EPK_AreaName_Arena,								// 切磋区
	EPK_AreaName_Safe,								// 安全区	
	EPK_AreaName_Risky,								// 危险区

	EPK_AreaName_Stall = 20,						// 摆摊区
	EPK_AreaName_EstopStall,						// 禁止摆摊区
};

////////////////////////// 玩家名字颜色 ///////////////////////////
enum
{
	EPK_NameColor_Blue = 0,							// 蓝名
	EPK_NameColor_White,							// 白名	
	EPK_NameColor_Yellow,							// 黄名
	EPK_NameColor_Red,								// 红名

	EPK_NameColor_Max,								// ...
};

////////////////////////// 死亡惩罚原因 //////////////////////////
enum
{
	EDiePunish_Type_Absolve = 0,					// 死亡不掉装
	EDiePunish_Type_AreaGeneral,					// 普通区死亡
	EDiePunish_Type_AreaRisky,						// 危险区死亡

	EDiePunish_Type_Max,							// ....
};

///////////////////////// 进度条类型 /////////////////////////////
enum EProgressBar_Type
{
	EProgressBar_Type_Invalid	=	0,
	EProgressBar_Type_PickUp,						// 采集进度条
	EProgressBar_Type_OpenDoor,						// 开门进度条
	EProgressBar_Type_StandFlag,					// 占领点进度条
	EProgressBar_Type_PetOut,						// 宠物出战进度条
};

// 商城Tab页下标
enum eMindShopIdx
{
	eMindShopIdx_Hot		=0,	// 热卖商品
	eMindShopIdx_Rebate,		// 打折商品
	eMindShopIdx_ScareBuy,		// 限时抢购商品
	eMindShopIdx_Equip,			// 装备强化商品
	eMindShopIdx_LevelUp,		// 升级辅助商品
	eMindShopIdx_Fashion,		// 时装外形商品
	eMindShopIdx_Material,		// 生产材料商品
	eMindShopIdx_PetAndHorse,	// 宠物坐骑商品
	eMindShopIdx_Bind,			// 福利商品
	eMindShopIdx_Max,
};

// 商城购买商品结果
enum eMindBuyGoodsResult
{
	eMindBuyGoodsResult_Success	=	0,	// 购买成功
	eMindBuyGoodsResult_GoodsDown,		// 商品下架
	eMindBuyGoodsResult_PacketFull,		// 背包满
	eMindBuyGoodsResult_MoneyLittle,	// 元宝或绑定元宝不足
};

//游戏结束队伍总评级
enum eFightEndLevel
{
	eENDLEVEL_D = 1,
	eENDLEVEL_C ,
	eENDLEVEL_B ,
	eENDLEVEL_A ,
	eENDLEVEL_S ,
};

enum eFeedConditionType
{
	FEED_TYPE_LVUP=1,						// 人物提升等级时
	FEED_TYPE_STRENGTHEN_WEAPON,			// 强化武器成功			
	FEED_TYPE_STRENGTHEN_CARD,				// 融合卡片成功	
	FEED_TYPE_STRENGTHEN_JADE,				// 强化饰品成功
	FEED_TYPE_GO_ECTYPE,					// 通某个副本时
	FEED_TYPE_COMPLETE_TASK,				// 完成某个任务时	
	FEED_TYPE_FIGHT_RES,					// 分享战斗结果
	FEED_TYPE_COMPLETE_ACHIEVEMENT,			// 完成某个成就
	FEED_TYPE_TRAIN_CONTINUE_WIN,			// 试炼之塔连胜
	FEED_TYPE_TRAIN_PERIOD_REWORD,			// 发布领取试炼之塔届奖励新鲜事
	FEED_TYPE_COLLECT,				// 单机切磋好友收集新鲜事
	FEED_TYPE_PVPPRIZE,					// PVP活动领取奖励新鲜事
	FEED_TYPE_INSTANCEPRIZE,			// 碎片搜集奖励新鲜事
	FEED_TYPE_MAX
};

enum eFeedPrizeType
{
	PRIZE_TYPE_VIM = 1,						// 奖励精力
	PRIZE_TYPE_ITEM,						// 奖励道具
	PRIZE_TYPE_WITHE_MONEY,					// 奖励银币
	PRIZE_TYPE_GOLD_MONEY,					// 奖励金币
	PRIZE_TYPE_EXP,						    // 奖励经验
	PRIZE_TYPE_SCORE,						// 奖励积分
};


#endif //_OBJECTDEFINES_H__
