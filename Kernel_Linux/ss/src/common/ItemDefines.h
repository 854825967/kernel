#ifndef _ITEMDEFINES_H__
#define _ITEMDEFINES_H__

#include "DServerDef.h"

///< 佣兵装备栏
enum EquipmentSlots                                         // 14 slots
{
	EQUIPMENT_SLOT_START  = 0,
	EQUIPMENT_NOTCH_EARTH			= 0,		///地属性插槽（可见）
	EQUIPMENT_NOTCH_WATER			= 1,		///水属性插槽（可见）
	EQUIPMENT_NOTCH_FIRE			= 2,		///火属性插槽（可见）
	EQUIPMENT_NOTCH_WIND			= 3,		///风属性插槽（可见）
	EQUIPMENT_NOTCH_THUNDER			= 4,		///雷属性插槽（可见）
	EQUIPMENT_NOTCH_MAX				= 5,		///
	EQUIPMENT_SLOT_MAINHAND			= EQUIPMENT_NOTCH_MAX + 0,		///主手武器（可见）
	EQUIPMENT_SLOT_HEAD				= EQUIPMENT_NOTCH_MAX + 1,		///头盔    （可见）
	EQUIPMENT_SLOT_CHEST			= EQUIPMENT_NOTCH_MAX + 2,		///衣服    （可见）
	EQUIPMENT_SLOT_VISIBLE_END		= EQUIPMENT_NOTCH_MAX + 3,		///
	EQUIPMENT_SLOT_NECK				= EQUIPMENT_SLOT_VISIBLE_END + 0,	///项链
	EQUIPMENT_SLOT_JADE_1			= EQUIPMENT_SLOT_VISIBLE_END + 1,	///饰品1
	EQUIPMENT_SLOT_JADE_2			= EQUIPMENT_SLOT_VISIBLE_END + 2,	///饰品2
	EQUIPMENT_SLOT_FINGER_1			= EQUIPMENT_SLOT_VISIBLE_END + 3,	///戒指1
	EQUIPMENT_SLOT_FINGER_2			= EQUIPMENT_SLOT_VISIBLE_END + 4,	///戒指2
	EQUIPMENT_SLOT_END,
};

//玩家角色的包裹，保存数据库使用
//备注：值已存入数据库，不能更改，每个容器最大值为40
enum EACTOR_BAG_NEW
{
	enBag_PlayerEquip_Notch,	//0  = 玩家卡槽栏（格子个数见EQUIPMENT_SLOT_END）
	enBag_Packet1,				//1  = 道具包裹1，备注：背包最大为40个格子
	enBag_Equip1,				//2  = 装备包裹1，备注：背包最大为40个格子
	enBag_Card1,				//3  = 卡片包裹1，备注：背包最大为40个格子
	enBag_Card2,				//4  = 卡片包裹2，备注：背包最大为40个格子
	enBag_Max
};

//容器拥有者的容器
enum EHOLDER_C
{
	enC_PlayerEquip_Notch = 1,	//1  = 卡槽对应的容器
	enC_Packet1,				//2  = 道具包裹1对应的容器
	enC_Equip1,					//3  = 装备包裹1对应的容器
	enC_Card1,					//4  = 卡片包裹1对应的容器
	enC_Card2,					//5  = 卡片包裹2对应的容器
	enC_Max						//7  = 无效ID
};

/// 佣兵装备栏索引
enum EHeroEquipPacketIndex
{
	eHeroEquip_Packet1 = 0,		/// 佣兵1装备栏
	eHeroEquip_Packet2,			/// 佣兵2装备栏
	eHeroEquip_Packet3,			/// 佣兵3装备栏
	eHeroEquip_Packet4,			/// 佣兵4装备栏
	eHeroEquip_Packet5,			/// 佣兵5装备栏
	eHeroEquip_Packet6,			/// 佣兵6装备栏
	eHeroEquip_Packet7,			/// 佣兵7装备栏
	eHeroEquip_Packet8,			/// 佣兵8装备栏
	eHeroEquip_Max,
};

enum EPacketIndex
{
	ePacketIndex_Packet1	=	0,	// 包裹1
	ePacketIndex_Equip1,			// 装备1
	ePacketIndex_Card1,				// 卡片包裹1
	ePacketIndex_Card2,				// 卡片包裹2
	Packet_COUNT_MAX,				// 包裹总个数
};

enum RESULT_STRENGTHEN
{
	RESULT_SUCCEED = 1,//融合成功
	RESULT_SREINVALID, //融合的卡片无效
	RESULT_MONEY_LITTLE,
	RESULT_RANDOM_FAILD,//融合随机失败
	RESULT_FAILED,
};

enum RESULT_EQUIPCARDS
{
	RESULT_EQUIPCARDS_SUCCEED = 1,		// 装备卡片成功
	RESULT_EQUIPCARDS_NO_FOUND_CARD,	// 没有符合条件的卡片
	RESULT_EQUIPCARDS_SRCINVALID,		// 物品无效
	RESULT_EQUIPCARDS_LOCINVALID,		// 位置无效
	RESULT_EQUIPCARDS_FULL,				// 容器已满
	RESULT_EQUIPCARDS_FAILED,			// 失败
};

//卡片操作
enum CONTROL_TYPE						
{
	REPLACE_CARD = 1,   //替换卡片
	UNINSTALL_CARD,		//卸载卡片
	BUILD_CARD			//装载卡片
};


enum RESULT_ADDGOODS
{
	RESULT_ADDGOODS_SUCCEED = 1,		// 添加物品成功
	RESULT_ADDGOODS_SUCCEED_PILE,		// 添加物品成功，但源物品已销毁，已不可用
	RESULT_ADDGOODS_SRCINVALID,			// 物品无效
	RESULT_ADDGOODS_LOCINVALID,			// 位置无效
	RESULT_ADDGOODS_FULL,				// 容器已满
	RESULT_ADDGOODS_FAILED,				// 失败
};

enum RESULT_REMOVEGOODS
{
	RESULT_REMOVEGOODS_SUCCEED = 1,		// 移除成功
	RESULT_REMOVEGOODS_NUMINVALID,		// 数量非法
	RESULT_REMOVEGOODS_SRCINVALID,		// 物品非法
	RESULT_REMOVEGOODS_NONSUPPORT,		// 容器不支持
	RESULT_REMOVEGOODS_FAILED,			// 失败
	RESULT_REMOVEGOODS_CONTAINERVETO	// 容器不允许
};

//物品种类
enum EGOODS
{
	enGoods_Card = 1,		//1 = 装备和卡片
	enGoods_Medicament,		//2 = 药品（可以对某个Thing使用，并产生某种效果）
	enGoods_Materiel,		//3 = 物资（不可以对Thing使用）	
	enGoods_Max				//最大物品种类
};

#define PACKET_OBJECT_MAXCOUNT		20		//一个角色最多包裹物品件数
#define PACKET_KITBAG_SETPOS		44		//包裹保存数据库时，设置的起始位置

#define GOODS_TRADECOUNT_MAX		30		//物品的最大交易次数

//默认包裹1的容量
#define			DEFALUT_PACKET_SIZE		35

//单个包裹最大容量
#define			MAX_PACKET_SIZE			40

#define MAKER_NAME_LEN	18					//物品制造者的名字

#define EQUIPMENT_CARDS_STATUS_MAX	4		//装备的套卡状态ID 最多数

//绑定标志
enum EBIND
{
	enBind_Trade		= 0x01,		//交易（此bit位为1表示不可以：交易、拍卖、给予、邮寄）
	enBind_Sell_NPC		= 0x02,		//出售给NPC（此bit位为1表示不可以：出售给NPC）
	enBind_Clear_NMap	= 0x04,		//为1表示：切换地图物品会消失
	enBind_Max
};

//装备种类（刀、剑等细分类型）
enum EQUIP_KIND
{
	EQUIP_SUBCLASS_UNKNOW		= 0,	//0  = 未知
	EQUIP_SUBCLASS_EARTH		= 1,	//1	 = 地属性卡片
	EQUIP_SUBCLASS_WATER		= 2,	//2	 = 水属性卡片
	EQUIP_SUBCLASS_FIRE			= 3,	//3	 = 火属性卡片
	EQUIP_SUBCLASS_WIND			= 4,	//4	 = 风属性卡片
	EQUIP_SUBCLASS_THUNDER		= 5,	//5	 = 雷属性卡片
	EQUIP_SUBCLASS_CARD_MAX		= 6,	//6	 = 最大卡片类
	EQUIP_SUBCLASS_WEAPON		= EQUIP_SUBCLASS_CARD_MAX + 0,	//6	 = 武器
	EQUIP_SUBCLASS_HEADDPIECE	= EQUIP_SUBCLASS_CARD_MAX + 1,	//7	 = 头盔
	EQUIP_SUBCLASS_ARMOR		= EQUIP_SUBCLASS_CARD_MAX + 2,	//8	 = 衣服
	EQUIP_SUBCLASS_NECK			= EQUIP_SUBCLASS_CARD_MAX + 3,	//9	 = 项链
	EQUIP_SUBCLASS_JADE			= EQUIP_SUBCLASS_CARD_MAX + 4,	//10 = 饰品
	EQUIP_SUBCLASS_FINGER		= EQUIP_SUBCLASS_CARD_MAX + 5,	//11 = 戒指
	EQUIP_SUBCLASS_MAX			= EQUIP_SUBCLASS_CARD_MAX + 6	//12 = 最大
};

//装备激活类型
enum EQUIP_ACTIVE_ID
{
	EQUIP_ACTIVE_ID_ANY			= 0,	// 普通卡片
	EQUIP_ACTIVE_ID_1			= 1,	// 勇者卡片
	EQUIP_ACTIVE_ID_2			= 2,	// 智者卡片
	EQUIP_ACTIVE_ID_3			= 3,	// 嗜血卡片
	EQUIP_ACTIVE_ID_4			= 4,	// 痛苦卡片
	EQUIP_ACTIVE_ID_MAX			= 5,	// 卡片
};

// 药品类子类
enum MEDICAMENT_KIND
{
	LEECHDOM_SUBCLASS_UNKNOW = 0,		//0  = 未知
	LEECHDOM_SUBCLASS_MEDICAMENT,		//1  = 药品
	LEECHDOM_SUBCLASS_SKILLBOOK,		//2  = 技能书
	LEECHDOM_SUBCLASS_CANUSE_TASK,		//3  = 可使用的任务物品
	LEECHDOM_SUBCLASS_MAX,				//4  = 最大
};

// 物资类子类
enum MATERIEL_KIND
{
	MATERIEL_SUBCLASS_UNKNOW	=	0,		//0  = 未知
	MATERIEL_SUBCLASS_TASK,					//1  = 任务
	MATERIEL_SUBCLASS_CARD,					//2  = 卡片
	MATERIEL_SUBCLASS_LUCKYSTONE,			//3  = 幸运石
	MATERIEL_SUBCLASS_STRENGSTONE,			//4  = 强化石
	MATERIEL_SUBCLASS_ALCHEMY,				//5  = 炼金物品
	MATERIEL_SUBCLASS_MAX,					//3  = 最大
};

enum EGoodsBindType
{
	enGoods_No_Bind                             = 0,	// 不绑定
	enGoods_ActorBind_When_PickedUp             = 1,	// 拾取后角色绑定
	enGoods_AccountBind_When_PickedUp           = 2,	// 拾取后账号绑定
	enGoods_ActorBind_When_Used					= 3,	// 使用后角色绑定
	enGoods_AccountBind_When_Used				= 4,	// 使用后账号绑定
	enGoods_ActorBind_When_Traded				= 5,	// 交易后角色绑定
	enGoods_AccountBind_When_Traded				= 6,	// 交易后账号绑定
	enGoods_MaxBindType,
};

//物品创建时指定的配置
enum EGoods_Flag
{
	enGoodsC_BindTrade		= 0x00000001,		//为1表示不可以：交易、拍卖、给予、邮寄
	enGoodsC_BindSell		= 0x00000002,		//为1表示不可以：出售给NPC
	enGoodsC_Clear_NMap		= 0x00000004,		//为1表示：切换地图物品会消失
};

//装备效果索引定义
enum EIndex_E
{
	enIndexE_Base1 = 0,		//0  = 装备脚本配置的效果
	enIndexE_Base2,			//1  = 装备脚本配置的效果
	enIndexE_Base3,			//2  = 装备脚本配置的效果
	enIndexE_Base4,			//3  = 装备脚本配置的效果
	enIndexE_Base5,			//4  = 装备脚本配置的效果
	enIndexE_BaseMax,		//5	 = 装备脚本配置的效果最大值

	enIndexE_Rand1 = enIndexE_BaseMax,		//5  = 装备随机属性的效果
	enIndexE_Rand2,							//6  = 装备随机属性的效果
	enIndexE_Rand3,							//7  = 装备随机属性的效果
	enIndexE_Rand4,							//8  = 装备随机属性的效果
	enIndexE_RandMax,						//9	 = 装备随机属性的效果最大值

	enIndexE_Update1 = enIndexE_RandMax,	//9 = 装备精炼的基础效果
	enIndexE_Update2,						//10 = 装备精炼的灵魂效果
	enIndexE_UpdateMax,						//11 = 装备升级的效果最大值

	enIndexE_Card1 = enIndexE_UpdateMax,	//11 = 镶嵌卡片带来的效果
	enIndexE_Card2,							//12 = 镶嵌卡片带来的效果
	enIndexE_Card3,							//13 = 镶嵌卡片带来的效果
	enIndexE_CardMax,						//14 = 镶嵌卡片带来的效果最大值

	enIndexE_Make1 = enIndexE_CardMax,		//14 = 制造装备时产生的效果（可升级，对应：enIndexE_Update1）
	enIndexE_Make2,							//15 = 制造装备时产生的效果（可升级，对应：enIndexE_Update2）
	enIndexE_Make3,							//16 = 制造装备时产生的效果
	enIndexE_MakeMax,						//17 = 制造装备是产生的效果最大值

	enIndexE_Max = enIndexE_MakeMax			//17
};

//装备影响生物属性的索引定义
enum EIndex_Prop
{
	enIndexP_Add1 = 0,		//0  = 装备附加的属性值（注意不是效果，用于精练）
	enIndexP_Add2,		//1  = 装备附加的属性值（注意不是效果，用于精练）
	enIndexP_Max,		//2  = 装备附加的属性值（注意不是效果，用于精练）
};

enum EEquipTypeInlay
{
	enInvaild = 0,
	enPhyWeapon,	// 物理武器
	enMagicWeapon,	// 法术武器
	enShield,		// 盾牌
	enDefend,		// 防具
};

#define CARD_ITEMID_BGN			500000	// 卡片起始Id

#define WEAPON_FLAG_NO_WEAPON			(0x0001)	// 空手
#define WEAPON_FLAG_SINGLE				(0x0002)	// 单手
#define WEAPON_FLAG_DOUBLE				(0x0004)	// 双手


#define ARMOR_FLAG_NONE					(0x0001)	// 没有护甲（裸体？）
#define ARMOR_FLAG_F					(0x0002)	// 布甲
#define ARMOR_FLAG_L					(0x0004)	// 轻甲
#define ARMOR_FLAG_H					(0x0008)	// 重甲



//#pragma pack(push, 1)

//物品基本属性
struct SGOODS_PROP_BASE
{
	int nGoodsID;					//物品ID
	WORD nNumber;					//数量
	int nBind;						//绑定标志
	char nTradeCount;				//物品可以在玩家间流通的次数(0 ~ 30)。-1为无次数限制
	int nSurviveTime;				//物品存在的游戏时间（单位：秒，-1为无时间限制。可以为现实时间）
	char nSubClass;					//物品的子类型

	SGOODS_PROP_BASE()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define EMPTY_CARD_ID			0x0000
#define INVALID_CARD_ID			0xFFFF

//装备
struct SEQUIPMENT_PROP_PUBLIC : public SGOODS_PROP_BASE
{
	char szMaker[MAKER_NAME_LEN - 3];	//制造者的名字 游戏内角色名最多14字节
	char aEquipedColor[3];			//装备在身上后的显示颜色rgb

	char nSmeltLevel;		//精炼等级（其实是精炼的次数）
	char nUpgradeCount;		//装备的升级次数
	char nHaveIdentify;		//为1表示已鉴定
	char nHaveActive;		//为1表示已激活，仅用于套装

	BYTE byEffectRandActive;				/// 装备随机属性是否激活

	char nSlotMax;							//装备的凹槽上限
	char nSlotLeft;							//可以镶嵌宝石的空凹槽的数量

	int lPMinDamage;					// 增加最小物理伤害
	int lPMaxDamage;					// 增加最大物理伤害
	int lPArmor;						// 增加护甲值

	int lMDamage;						// 增加法术伤害
	int lMPower;						// 增加魔攻
	int lMRes;							// 增加法术抗性

	int lAttackSpeed;					//武器的普通攻击速度，单位：次/千秒

	BYTE nSleight;					//装备的当前熟练度
	BYTE nSleightMax;				//装备的当前熟练度上限

	DWORD dwCardsStatus[EQUIPMENT_CARDS_STATUS_MAX];	//装备的套卡效果

	SEQUIPMENT_PROP_PUBLIC()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SEQUIPMENT_PROP_PRIVATE : public SEQUIPMENT_PROP_PUBLIC
{
};

struct SEQUIPMENT_PROP_ALL : public SEQUIPMENT_PROP_PRIVATE
{
};

//药品
struct SMEDICAMENT_PROP_PUBLIC : public SGOODS_PROP_BASE
{
// 	BYTE byExtend[MEDICA_EXTENDBUF_LEN];		//可扩展的buf，每种子类的所填充的数据不一样
// 
// 	SMEDICAMENT_PROP_PUBLIC()
// 	{
// 		memset(byExtend, 0, sizeof(byExtend));
// 	}
};

struct SMEDICAMENT_PROP_PRIVATE : public SMEDICAMENT_PROP_PUBLIC
{
};

struct SMEDICAMENT_PROP_ALL : public SMEDICAMENT_PROP_PRIVATE
{
};

//物资
struct SMATERIEL_PROP_PUBLIC : public SGOODS_PROP_BASE
{
};

struct SMATERIEL_PROP_PRIVATE : public SMATERIEL_PROP_PUBLIC
{
};

struct SMATERIEL_PROP_ALL : public SMATERIEL_PROP_PRIVATE
{	
};

//背包
struct SKITBAG_PROP_PUBLIC : public SGOODS_PROP_BASE
{
	BYTE nSize;			//背包的容量，即可以存放物品的数量

	SKITBAG_PROP_PUBLIC()
	{
		nSize = 0;
	}
};

struct SKITBAG_PROP_PRIVATE : public SKITBAG_PROP_PUBLIC
{
};

struct SKITBAG_PROP_ALL : public SKITBAG_PROP_PRIVATE
{	
};

//#pragma pack(pop)

#endif//_ITEMDEFINES_H__
