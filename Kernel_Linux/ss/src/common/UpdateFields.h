/*******************************************************************
** 文件名:  UpdateFields.h
** 版  权:	(C)  
** 创建人:	Zipher
** 日  期:	2010-01-05
** 版  本:	1.0
** 描  述:	场景服 游戏对象属性公用宏定义
** 应  用:  

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef _UPDATEFIELDS_H__
#define _UPDATEFIELDS_H__

enum EObjectFields
{
	OBJECT_FIELD_TYPE			=	0x0000,		// 对象类型
	OBJECT_FIELD_ENTRY_ID,						// 对象模版id
	OBJECT_END,
};
#define OBJECT_FIELD_NUM		(OBJECT_END)

enum EBoxFields
{
	/***************** 盒子可见属性 *******************************/
	BOX_FIELD_VISIBLE_BGN				=	OBJECT_END,
	BOX_FIELD_STATE						=	BOX_FIELD_VISIBLE_BGN,		// 盒子状态
	BOX_FIELD_TYPE,														// 盒子类型
	BOX_FIELD_OPENNEEDTIME,												// 打开时间
	BOX_FIELD_RESID,													// 盒子外观资源ID
	BOX_FIELD_MAPINLINEIDX,												// 场景内嵌索引
	BOX_FIELD_VISIBLE_END,
	/***************** 盒子可见属性 *******************************/

	/***************** 盒子不可见属性 *****************************/
	BOX_FIELD_BORNREASON				=	BOX_FIELD_VISIBLE_END,		// 出生原因
	BOX_FIELD_END,
	/***************** 盒子不可见属性 *****************************/
};
#define BOX_FIELD_VISIBLE_NUM	(BOX_FIELD_VISIBLE_END - BOX_FIELD_VISIBLE_BGN)
#define BOX_FIELD_NUM			(BOX_FIELD_END - OBJECT_END)

enum EItemFields
{
	/***************** 物品可见属性 *******************************/
	ITEM_FIELD_VISIBLE_BGN		=	OBJECT_END,
	ITEM_FIELD_VISIBLE_BINDTYPE =	ITEM_FIELD_VISIBLE_BGN,				// 绑定类型
	ITEM_FIELD_VISIBLE_END,
	/***************** 物品可见属性 *******************************/

	/***************** 物品不可见属性 *****************************/
	ITEM_FIELD_CONTAINER			=	ITEM_FIELD_VISIBLE_END,			// 容器Id
	ITEM_FIELD_COUNT,													// 堆叠数量
	ITEM_FIELD_SURVIVETIME,												// 持续时间
	ITEM_FIELD_END,
	/***************** 物品不可见属性 *****************************/
};
#define ITEM_FIELD_VISIBLE_NUM	(ITEM_FIELD_VISIBLE_END - ITEM_FIELD_VISIBLE_BGN)
#define ITEM_FIELD_NUM			(ITEM_FIELD_END - OBJECT_END)

enum EEquipFields
{
	/***************** 装备可见属性 *******************************/
	EQUIP_FIELD_VISIBLE_BGN		=	ITEM_FIELD_END,
	EQUIP_FIELD_VISIBLE_END		=	EQUIP_FIELD_VISIBLE_BGN,
	/***************** 物品可见属性 *******************************/

	/***************** 装备不可见属性 *****************************/
	EQUIP_FIELD_EFFECTRAND1			=	EQUIP_FIELD_VISIBLE_END,		// 装备随机效果1
	EQUIP_FIELD_EFFECTRAND2,											// 装备随机效果2
	EQUIP_FIELD_EFFECTRAND3,											// 装备随机效果3
	EQUIP_FIELD_EFFECTRAND4,											// 装备随机效果4
	EQUIP_FIELD_EFFECTRAND_ACTIVE,										// 装备随机效果是否激活
	EQUIP_FIELD_SLOTQTY_AND_SLOT1,										// 1:插槽1中的宝石 0:插槽数量
	EQUIP_FIELD_SLOT2_AND_SLOT3,										// 1:插槽3中的宝石 0:插槽2中的宝石
	EQUIP_FIELD_SMELTLEVEL,												// 精炼等级
	EQUIP_FIELD_DURABILITY,												// 当前耐久
	EQUIP_FIELD_MAXDURABILITY,											// 最大耐久
	EQUIP_FIELD_END,
	/***************** 装备不可见属性 *****************************/
};

#define EQUIP_FIELD_VISIBLE_NUM	(EQUIP_FIELD_VISIBLE_END - EQUIP_FIELD_VISIBLE_BGN)
#define EQUIP_FIELD_NUM			(EQUIP_FIELD_END - ITEM_FIELD_END)

enum EKitbagFields
{
	/***************** 背包不可见属性 *****************************/
	KITBAG_FIELD_BGN			=	ITEM_FIELD_END,
	KITBAG_FIELD_SIZE			=	KITBAG_FIELD_BGN,							// 背包格子数量
	KITBAG_FIELD_END,
	/***************** 背包不可见属性 *****************************/
};
#define KITBAG_FIELD_NUM		(KITBAG_FIELD_END - KITBAG_FIELD_BGN)

enum EUnitFields
{
	/***************** 生物可见属性 *******************************/
	UNIT_FIELD_VISIBLE_BGN					=	OBJECT_END,
	UNIT_FIELD_VISIBLE_SIT_ID				=	UNIT_FIELD_VISIBLE_BGN,			// 座位编号
	UNIT_FIELD_VISIBLE_LEVEL,													// 等级
	UNIT_FIELD_VISIBLE_HP,														// HP
	UNIT_FIELD_VISIBLE_HP_MAX,													// 最大HP
	UNIT_FIELD_VISIBLE_MP_EARTH,												// MP(地)
	UNIT_FIELD_VISIBLE_MP_EARTH_MAX,											// MP(地)
	UNIT_FIELD_VISIBLE_MP_WATER,												// MP(水)
	UNIT_FIELD_VISIBLE_MP_WATER_MAX,											// MP(水)
	UNIT_FIELD_VISIBLE_MP_FIRE,													// MP(火)
	UNIT_FIELD_VISIBLE_MP_FIRE_MAX,												// MP(火)
	UNIT_FIELD_VISIBLE_MP_WIND,													// MP(风)
	UNIT_FIELD_VISIBLE_MP_WIND_MAX,												// MP(风)
	UNIT_FIELD_VISIBLE_MP_THUNDER,												// MP(雷)
	UNIT_FIELD_VISIBLE_MP_THUNDER_MAX,											// MP(雷)
	UNIT_FIELD_VISIBLE_ATTACKPOWER_EARTH,										// 攻击力(地)
	UNIT_FIELD_VISIBLE_ATTACKPOWER_WATER,										// 攻击力(水)
	UNIT_FIELD_VISIBLE_ATTACKPOWER_FIRE,										// 攻击力(火)
	UNIT_FIELD_VISIBLE_ATTACKPOWER_WIND,										// 攻击力(风)
	UNIT_FIELD_VISIBLE_ATTACKPOWER_THUNDER,										// 攻击力(雷)
	UNIT_FIELD_VISIBLE_POINT_MP_EARTH,											// 魔法吸收(地)
	UNIT_FIELD_VISIBLE_POINT_MP_WATER,											// 魔法吸收(水)
	UNIT_FIELD_VISIBLE_POINT_MP_FIRE,											// 魔法吸收(火)
	UNIT_FIELD_VISIBLE_POINT_MP_WIND,											// 魔法吸收(风)
	UNIT_FIELD_VISIBLE_POINT_MP_THUNDER,										// 魔法吸收(雷)
	UNIT_FIELD_VISIBLE_ARMOR_EARTH,												// 护甲值(地)
	UNIT_FIELD_VISIBLE_ARMOR_WATER,												// 护甲值(水)
	UNIT_FIELD_VISIBLE_ARMOR_FIRE,												// 护甲值(火)
	UNIT_FIELD_VISIBLE_ARMOR_WIND,												// 护甲值(风)
	UNIT_FIELD_VISIBLE_ARMOR_THUNDER,											// 护甲值(雷)
	UNIT_FIELD_VISIBLE_LUCKY_POINT,												// 幸运值
	UNIT_FIELD_VISIBLE_CARD_NO_EFFECT,											// 封印卡片
	UNIT_FIELD_VISIBLE_END,
	/***************** 生物可见属性 *******************************/

	/***************** 生物不可见属性 *****************************/
	UNIT_FIELD_RESISTANCE_ARMOR_EARTH			=	UNIT_FIELD_VISIBLE_END,		// 护甲抵消(地)
	UNIT_FIELD_RESISTANCE_ARMOR_WATER,											// 护甲抵消(水)
	UNIT_FIELD_RESISTANCE_ARMOR_FIRE,											// 护甲抵消(火)
	UNIT_FIELD_RESISTANCE_ARMOR_WIND,											// 护甲抵消(风)
	UNIT_FIELD_RESISTANCE_ARMOR_THUNDER,										// 护甲抵消(雷)
	UNIT_FIELD_CRIT,															// 暴击率
	UNIT_FIELD_LUCKY_CRIT,														// 幸运值暴击率
	UNIT_FIELD_SLIENT_PHYSICS_LEVEL,											// 物理沉默等级
	UNIT_FIELD_SLIENT_MAGIC_LEVEL,												// 法术沉默等级
	UNIT_FIELD_IMMUNE_PHYSICS_LEVEL,											// 物理免疫等级
	UNIT_FIELD_IMMUNE_MAGIC_LEVEL,												// 法术免疫等级
	UNIT_FIELD_END,
	/***************** 生物不可见属性 *****************************/

	/************* 生物属性(不同步到客户端) ***********************/
	UNIT_FIELD_SERVER_BASE_VALUE_HEALTH		=	UNIT_FIELD_END,					// 最大HP+
	UNIT_FIELD_SERVER_BASE_PCT_HEALTH,											// 最大HP%
	UNIT_FIELD_SERVER_DAMAGE_BASE, 												// 最终伤害+
	UNIT_FIELD_SERVER_DAMAGE_COFF, 												// 最终伤害%
	UNIT_FIELD_SERVER_DAMAGE_BASE_EARTH, 												// 最终伤害+（地）
	UNIT_FIELD_SERVER_DAMAGE_COFF_EARTH, 												// 最终伤害%（地）
	UNIT_FIELD_SERVER_DAMAGE_BASE_WATER, 												// 最终伤害+（水）
	UNIT_FIELD_SERVER_DAMAGE_COFF_WATER, 												// 最终伤害%（水）
	UNIT_FIELD_SERVER_DAMAGE_BASE_FIRE, 												// 最终伤害+（火）
	UNIT_FIELD_SERVER_DAMAGE_COFF_FIRE, 												// 最终伤害%（火）
	UNIT_FIELD_SERVER_DAMAGE_BASE_WIND, 												// 最终伤害+（风）
	UNIT_FIELD_SERVER_DAMAGE_COFF_WIND, 												// 最终伤害%（风）
	UNIT_FIELD_SERVER_DAMAGE_BASE_THUNDER, 												// 最终伤害+（雷）
	UNIT_FIELD_SERVER_DAMAGE_COFF_THUNDER, 												// 最终伤害%（雷）
	UNIT_FIELD_SERVER_BE_DAMAGE_BASE, 											// 受到最终伤害+
	UNIT_FIELD_SERVER_BE_DAMAGE_COFF, 											// 受到最终伤害%
	UNIT_FIELD_SERVER_BE_DAMAGE_BASE_EARTH, 											// 受到最终伤害+（地）
	UNIT_FIELD_SERVER_BE_DAMAGE_COFF_EARTH, 											// 受到最终伤害%（地）
	UNIT_FIELD_SERVER_BE_DAMAGE_BASE_WATER, 											// 受到最终伤害+（水）
	UNIT_FIELD_SERVER_BE_DAMAGE_COFF_WATER, 											// 受到最终伤害%（水）
	UNIT_FIELD_SERVER_BE_DAMAGE_BASE_FIRE, 											// 受到最终伤害+（火）
	UNIT_FIELD_SERVER_BE_DAMAGE_COFF_FIRE, 											// 受到最终伤害%（火）
	UNIT_FIELD_SERVER_BE_DAMAGE_BASE_WIND, 											// 受到最终伤害+（风）
	UNIT_FIELD_SERVER_BE_DAMAGE_COFF_WIND, 											// 受到最终伤害%（风）
	UNIT_FIELD_SERVER_BE_DAMAGE_BASE_THUNDER, 											// 受到最终伤害+（雷）
	UNIT_FIELD_SERVER_BE_DAMAGE_COFF_THUNDER, 											// 受到最终伤害%（雷）
	UNIT_FIELD_SERVER_ARMO_COFF_EARTH, 											// 护甲值%(地)
	UNIT_FIELD_SERVER_ARMO_BASE_EARTH, 											// 护甲值+(地)
	UNIT_FIELD_SERVER_ARMO_COFF_WATER, 											// 护甲值%(水)
	UNIT_FIELD_SERVER_ARMO_BASE_WATER, 											// 护甲值+(水)
	UNIT_FIELD_SERVER_ARMO_COFF_FIRE, 											// 护甲值%(火)
	UNIT_FIELD_SERVER_ARMO_BASE_FIRE, 											// 护甲值+(火)
	UNIT_FIELD_SERVER_ARMO_COFF_WIND, 											// 护甲值%(风)
	UNIT_FIELD_SERVER_ARMO_BASE_WIND, 											// 护甲值+(风)
	UNIT_FIELD_SERVER_ARMO_COFF_THUNDER, 										// 护甲值%(雷)
	UNIT_FIELD_SERVER_ARMO_BASE_THUNDER, 										// 护甲值+(雷)
	UNIT_FIELD_SERVER_ATTACKPOWER_COFF_EARTH, 									// 地属性攻击力%
	UNIT_FIELD_SERVER_ATTACKPOWER_BASE_EARTH, 									// 地属性攻击力+
	UNIT_FIELD_SERVER_ATTACKPOWER_COFF_WATER, 									// 水属性攻击力%
	UNIT_FIELD_SERVER_ATTACKPOWER_BASE_WATER, 									// 水属性攻击力+
	UNIT_FIELD_SERVER_ATTACKPOWER_COFF_FIRE, 									// 火属性攻击力%
	UNIT_FIELD_SERVER_ATTACKPOWER_BASE_FIRE, 									// 火属性攻击力+
	UNIT_FIELD_SERVER_ATTACKPOWER_COFF_WIND, 									// 风属性攻击力%
	UNIT_FIELD_SERVER_ATTACKPOWER_BASE_WIND, 									// 风属性攻击力+
	UNIT_FIELD_SERVER_ATTACKPOWER_COFF_THUNDER, 								// 雷属性攻击力%
	UNIT_FIELD_SERVER_ATTACKPOWER_BASE_THUNDER, 								// 雷属性攻击力+
	UNIT_FIELD_SERVER_POINT_MP_COFF_EARTH,										// 魔法吸收(地)%
	UNIT_FIELD_SERVER_POINT_MP_BASE_EARTH,										// 魔法吸收(地)+
	UNIT_FIELD_SERVER_POINT_MP_COFF_WATER,										// 魔法吸收(水)%
	UNIT_FIELD_SERVER_POINT_MP_BASE_WATER,										// 魔法吸收(水)+
	UNIT_FIELD_SERVER_POINT_MP_COFF_FIRE,										// 魔法吸收(火)%
	UNIT_FIELD_SERVER_POINT_MP_BASE_FIRE,										// 魔法吸收(火)+
	UNIT_FIELD_SERVER_POINT_MP_COFF_WIND,										// 魔法吸收(风)%
	UNIT_FIELD_SERVER_POINT_MP_BASE_WIND,										// 魔法吸收(风)+
	UNIT_FIELD_SERVER_POINT_MP_COFF_THUNDER,									// 魔法吸收(雷)%
	UNIT_FIELD_SERVER_POINT_MP_BASE_THUNDER,									// 魔法吸收(雷)+
	UNIT_FIELD_SERVER_CRIT_BASE,												// 暴击率+
	UNIT_FIELD_SERVER_CRIT_TIMES_BASE,											// 暴击倍数+
	UNIT_FIELD_SERVER_LUCKY_POINT_BASE,											// 幸运值+
	UNIT_FIELD_SERVER_LUCKY_POINT_COFF,											// 幸运值%

	// 战斗过程数据 ---------------------------------------------------------------------------------------------
	UNIT_FIELD_SERVER_TMP_GEM_EARTH,											// 最近一次消的宝石数量(地)
	UNIT_FIELD_SERVER_TMP_GEM_WATER,											// 最近一次消的宝石数量(水)
	UNIT_FIELD_SERVER_TMP_GEM_FIRE,												// 最近一次消的宝石数量(火)
	UNIT_FIELD_SERVER_TMP_GEM_WIND,												// 最近一次消的宝石数量(风)
	UNIT_FIELD_SERVER_TMP_GEM_THUNDER,											// 最近一次消的宝石数量(雷)
	UNIT_FIELD_SERVER_TMP_GEM_UNKNOW,											// 最近一次消的宝石数量(特殊)
	UNIT_FIELD_SERVER_TMP_GEM_BOSS,												// 最近一次消的宝石数量(Boss)
	UNIT_FIELD_SERVER_TMP_TOTALGEM,												// 总消的宝石数量

	UNIT_FIELD_SERVER_TMP_MP_USE,												// 最近一次消耗的能量

	UNIT_FIELD_SERVER_TMP_COMBOS, 												// 最近一次连击数
	UNIT_FIELD_SERVER_TMP_MAXCOMBOS,											// 最高连击数--xcliu
	UNIT_FIELD_SERVER_TMP_TOTALCOMBOS,											// 总连击数--xcliu
	UNIT_FIELD_SERVER_TMP_DAMAGE, 												// 最近一次消宝石伤害数值
	UNIT_FIELD_SERVER_TMP_DTOTALMAGE, 											// 造成总伤害数值--xcliu
	UNIT_FIELD_SERVER_TMP_BEDAMAGE, 											// 最近一次受到伤害的数值
	UNIT_FIELD_SERVER_TMP_BEONEMAXDAMAGE, 										// 单次受到最高伤害的数值
	UNIT_FIELD_SERVER_TMP_BTOTALMAGE, 											// 受到总伤害的数值--xcliu
	UNIT_FIELD_SERVER_TMP_USETIMES, 											// 最近一回合行动时间

	UNIT_FIELD_SERVER_FOURSTAR,													// 四连星--xcliu
	UNIT_FIELD_SERVER_FIVESTAR,													// 五连星--xcliu
	UNIT_FIELD_SERVER_SIXSTAR,													// 六连星--xcliu
	UNIT_FIELD_SERVER_SEVENSTAR,												// 七连星--xcliu

	UNIT_FIELD_SERVER_TMP_GEM_TILL_EARTH,										// 连续消宝石次数(地)
	UNIT_FIELD_SERVER_TMP_GEM_TILL_WATER,										// 连续消宝石次数(水)
	UNIT_FIELD_SERVER_TMP_GEM_TILL_FIRE,										// 连续消宝石次数(火)
	UNIT_FIELD_SERVER_TMP_GEM_TILL_WIND,										// 连续消宝石次数(风)
	UNIT_FIELD_SERVER_TMP_GEM_TILL_THUNDER,										// 连续消宝石次数(雷)
	UNIT_FIELD_SERVER_TMP_GEM_TILL_UNKNOW,										// 连续消宝石次数(特殊)
	UNIT_FIELD_SERVER_LASTSCORE,												// 最后一次在试炼之塔中获得的积分

	// 战斗过程数据 ------------------------------------------------------------------------------------------------
	UNIT_FIELD_SERVER_HP_TOP,													// 最大HP极限值
	UNIT_FIELD_SERVER_MP_EARTH_TOP,											// MP极限值(地)
	UNIT_FIELD_SERVER_MP_WATER_TOP,											// MP极限值(水)
	UNIT_FIELD_SERVER_MP_FIRE_TOP,												// MP极限值(火)
	UNIT_FIELD_SERVER_MP_WIND_TOP,												// MP极限值(风)
	UNIT_FIELD_SERVER_MP_THUNDER_TOP,											// MP极限值(雷)
	
	UNIT_FIELD_SERVER_END,
	/************* 生物属性(不同步到客户端) ***********************/
};
#define UNIT_FIELD_VISIBLE_NUM		(UNIT_FIELD_VISIBLE_END - UNIT_FIELD_VISIBLE_BGN)
#define UNIT_FIELD_CLIENT_NUM		(UNIT_FIELD_END - UNIT_FIELD_VISIBLE_BGN)
#define UNIT_FIELD_TOTAL_NUM		(UNIT_FIELD_SERVER_END - UNIT_FIELD_VISIBLE_BGN)

enum EHeroFields
{
	/***************** 佣兵可见属性 *********************************/
	HERO_FIELD_VISIBLE_BGN				= OBJECT_END,
	HERO_FIELD_VISIBLE_SUMMONEDBY		= HERO_FIELD_VISIBLE_BGN,				// 召唤者的角色Id
	HERO_FIELD_VISIBLE_LEVEL,													// 等级
	HERO_FIELD_VISIBLE_HP_MAX,													// 最大HP
	HERO_FIELD_VISIBLE_ATTACKPOWER_EARTH,										// 攻击力(地)
	HERO_FIELD_VISIBLE_ATTACKPOWER_WATER,										// 攻击力(水)
	HERO_FIELD_VISIBLE_ATTACKPOWER_FIRE,										// 攻击力(火)
	HERO_FIELD_VISIBLE_ATTACKPOWER_WIND,										// 攻击力(风)
	HERO_FIELD_VISIBLE_ATTACKPOWER_THUNDER,										// 攻击力(雷)
	HERO_FIELD_VISIBLE_ARMOR,													// 护甲值
	HERO_FIELD_VISIBLE_CRIT,													// 暴击率
	HERO_FIELD_VISIBLE_STATE,													// 状态(0：状态 1：无 2：无 3：无)
	HERO_FIELD_VISIBLE_HUNGRY,													// 饱食度
	HERO_FIELD_VISIBLE_END,									
	/***************** 佣兵可见属性 *********************************/

	/***************** 佣兵不可见属性 *******************************/
	HERO_FIELD_EXP						= HERO_FIELD_VISIBLE_END,				// 佣兵经验
	HERO_FIELD_EXP_MAX,															// 最大经验
	HERO_FIELD_INDEX,															// 佣兵INDEX
	HERO_FIELD_END,
	/***************** 佣兵不可见属性 *****************************/

	/************* 佣兵属性(不同步到客户端) ***********************/
	HERO_FIELD_SERVER_BGN	=	HERO_FIELD_END,		
	HERO_FIELD_SERVER_END	=	HERO_FIELD_SERVER_BGN,
	/************* 佣兵属性(不同步到客户端) ***********************/
};
#define HERO_FIELD_VISIBLE_NUM		(HERO_FIELD_VISIBLE_END - HERO_FIELD_VISIBLE_BGN)
#define HERO_FILED_CLIENT_NUM		(HERO_FIELD_END - HERO_FIELD_VISIBLE_BGN)
#define HERO_FILED_TOTAL_NUM		(HERO_FIELD_SERVER_END - HERO_FIELD_VISIBLE_BGN)

enum ECreatureFields
{
	/***************** 怪物或NPC可见属性 *******************************/
	CREATURE_FIELD_VISIBLE_BGN			=	UNIT_FIELD_SERVER_END,
	CREATURE_FIELD_VISIBLE_END			=	CREATURE_FIELD_VISIBLE_BGN,
	/***************** 怪物或NPC可见属性 *******************************/

	/***************** 怪物或NPC不可见属性 *****************************/
	CREATURE_FIELD_END					=	CREATURE_FIELD_VISIBLE_END,
	/***************** 怪物或NPC不可见属性 *****************************/
};
#define CREATURE_FIELD_VISIBLE_NUM	(CREATURE_FIELD_VISIBLE_END - CREATURE_FIELD_VISIBLE_BGN)
#define CREATURE_FIELD_NUM			(CREATURE_FIELD_END - CREATURE_FIELD_VISIBLE_BGN)

enum EPlayerFields
{
	/***************** 玩家可见属性 *******************************/
	PLAYER_FIELD_VISIBLE_BGN			=	UNIT_FIELD_SERVER_END,
	PLAYER_FIELD_VISIBLE_HEADID			=	PLAYER_FIELD_VISIBLE_BGN,			// 头像编号（0：头像编号 1：性别 2：当天精力值购买点数）
	PLAYER_FIELD_VISIBLE_ACTORID,												// 玩家数据库角色Id
	PLAYER_FIELD_VISIBLE_NOTCH_ID,												// 卡槽栏容器Id
	PLAYER_FIELD_VISIBLE_VIPTIME,												// VIP时长（分钟）
	PLAYER_FIELD_VISIBLE_END,
	/***************** 玩家可见属性 *******************************/

	/***************** 玩家不可见属性 *****************************/
	PLAYER_FIELD_ROOMID					=	PLAYER_FIELD_VISIBLE_END,			// 房间ID
	PLAYER_FIELD_ENERGY,														// 当前精力值
	PLAYER_FIELD_ENERGY_MAX,													// 最大精力值
	PLAYER_FIELD_GOODS_ENERGY,													// 通过道具获取的精力值
	PLAYER_FIELD_EXP,															// 经验
	PLAYER_FIELD_EXP_MAX,														// 最大经验
	PLAYER_FIELD_MONEY,															// 金币
	PLAYER_FIELD_RMB,															// 钻石币（商城币）
	PLAYER_FIELD_ADD_TIME,														// 附加行动时间
	PLAYER_FIELD_SLIENT_ITEM_LEVEL, 											// 道具沉默等级
	PLAYER_FIELD_IMMUNE_ITEM_LEVEL, 											// 道具免疫等级
	PLAYER_FIELD_PACKET_1_C_ID,													// 包裹1容器Id
	PLAYER_FIELD_PACKET_2_C_ID,													// 包裹2容器Id
	PLAYER_FIELD_CARD_1_C_ID,													// 卡片包裹容器Id
	PLAYER_FIELD_CARD_2_C_ID,													// 卡片包裹容器Id
	PLAYER_FIELD_PET_1_C_ID,													// 魔灵包裹Id
	PLAYER_FIELD_PVP_TIMES,														// 打竞技场次数
	PLAYER_FIELD_PVP_WIN_TIMES,													// 打竞技场赢的次数
	PLAYER_FIELD_GUIDER_STEP,													// 新手引导进度
	PLAYER_FIELD_CUR_INSTANCE_ID,												// 当前关卡ID
	PLAYER_FIELD_TRAIN_RANK,													// 大赛昨日排名 
	PLAYER_FIELD_TRAIN_COUNT,													// 大赛领取标示和挑战次数(0:昨日排名领取标志 1:前天排名领取标志 2:挑战次数 3:当前声望等级)
	PLAYER_FIELD_TRAIN_CDTIME,													// 大赛CD时间 
	PLAYER_FIELD_TRAIN_REPUTATION,													// 声望
	PLAYER_FIELD_CONTINUE_LOGIN_COUNT,											// 连续登陆奖励（0：连续登陆次数 1：是否已经领取奖励 2：邀请好友领取奖励 3：每日好友收集的总次数）
	PLAYER_FIELD_INVITE_REWARD_NUM,												// 邀请好友抽奖次数
	PLAYER_FIELD_INVITE_FRIEND_COUNT,											// 邀请好友数量
	PLAYER_FIELD_FEED_SCORE,													// 新鲜事分享积分(0: 积分 1: 抽奖标识)
	PLAYER_FIELD_LAST_UPGRADE_PET,												// 最近一次融合的宠物
	PLAYER_FIELD_DAY_PRIZE_FLAG,												// 每日领取标志位（1~32位 1：VIP 2:轮盘抽奖 3:每日黄钻 4:年付费用户 5:开通黄钻 6:声望每日金币 7-11:Q点充值）
	PLAYER_FIELD_STRENGTH_LEVEL,												// 强化等级
	PLAYER_FIELD_PAY_MONEY,														// 最近活动充值数
	PLAYER_FIELD_TIMEOUT_COUNT,												// PVP超时次数
	PLAYER_FIELD_PVP_PRIZE,													// PVP奖励(0:PVP次数 1:PVP次数领奖标识 2:PVP胜利次数 3:PVP胜利次数领奖标识)
	PLAYER_FIELD_SERVER_TIME,												// 服务器时钟
	PLAYER_FIELD_ENFORCE_COLLECT,												// 强制征收次数
	PLAYER_FIELD_CARD_ROLL_FLG,												// 抽卡标识(0:友情抽卡次数, 1:符文抽卡, 2:41抽卡, 3:定时征收次数)
  PLAYER_FIELD_DAY_CONSUME_RUNES,                 // 当天消耗的符文数量
  PLAYER_FIELD_ACTIVITY_FLAG,                     // 活动字段(0:当天符文返还次数)
	PLAYER_FIELD_END,
	/***************** 玩家不可见属性 *****************************/

	/************* 玩家属性(不同步到客户端) ***********************/
	PLAYER_FIELD_SERVER_BGN				=	PLAYER_FIELD_END,
	PLAYER_FIELD_SERVER_DAYPRIZE_FLAG	=   PLAYER_FIELD_SERVER_BGN,			// 每日已领标志位（1~32位 1：VIP 2:活动抽奖 3:声望每日金币）
	PLAYER_FIELD_SERVER_VIP_END_TIME,											// VIP到期时间（秒）
	PLAYER_FIELD_SERVER_TOTALVIPINFO,											// QQ VIP信息
	PLAYER_FIELD_SERVER_QQVIPLV,												// QQ 黄钻等级
	PLAYER_FIELD_SERVER_END,
	/************* 玩家属性(不同步到客户端) ***********************/
};
#define PLAYER_FIELD_VISIBLE_NUM	(PLAYER_FIELD_VISIBLE_END - PLAYER_FIELD_VISIBLE_BGN)
#define PLAYER_FIELD_CLIENT_NUM		(PLAYER_FIELD_END - PLAYER_FIELD_VISIBLE_BGN)
#define PLAYER_FIELD_TOTAL_NUM		(PLAYER_FIELD_SERVER_END - PLAYER_FIELD_VISIBLE_BGN)

enum EDummyFields
{
	/***************** 假人可见属性 *******************************/
	DUMMY_FIELD_VISIBLE_BGN			=	UNIT_FIELD_SERVER_END,
	DUMMY_FIELD_VISIBLE_HEADID			=	DUMMY_FIELD_VISIBLE_BGN,			// 头像编号（0：头像编号 1：性别 2：无 3：无）
	DUMMY_FIELD_VISIBLE_ACTORID,												// 假人数据库角色Id
	DUMMY_FIELD_VISIBLE_VIPTIME,												// VIP时长（分钟）
	DUMMY_FIELD_VISIBLE_END,
	/***************** 假人可见属性 *******************************/

	/***************** 假人不可见属性 *****************************/
	DUMMY_FIELD_ROOMID					=	DUMMY_FIELD_VISIBLE_END,			// 房间ID
	DUMMY_FIELD_PVP_TIMES,														// 打竞技场次数
	DUMMY_FIELD_PVP_WIN_TIMES,													// 打竞技场赢的次数
	DUMMY_FIELD_END,
	/***************** 假人不可见属性 *****************************/

	/************* 假人属性(不同步到客户端) ***********************/
	DUMMY_FIELD_SERVER_BGN				=	DUMMY_FIELD_END,
	DUMMY_FIELD_SERVER_END				=   DUMMY_FIELD_SERVER_BGN,
	/************* 假人属性(不同步到客户端) ***********************/
};
#define DUMMY_FIELD_VISIBLE_NUM		(DUMMY_FIELD_VISIBLE_END - DUMMY_FIELD_VISIBLE_BGN)
#define DUMMY_FIELD_CLIENT_NUM		(DUMMY_FIELD_END - DUMMY_FIELD_VISIBLE_BGN)
#define DUMMY_FIELD_TOTAL_NUM		(DUMMY_FIELD_SERVER_END - DUMMY_FIELD_VISIBLE_BGN)

/*
*/

#endif //_UPDATEFIELDS_H__
