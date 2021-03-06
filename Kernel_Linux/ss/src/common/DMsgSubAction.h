/******************************************************************
** 文件名:	DMsgSubAction.h
** 创建人:
** 版  权:	(C)  	 
** 日  期:	 
** 版  本:	0.1
** 描  述:	实体行为事件的子消息码，
**          即，这些消息码的主码是ROOTTHING_SC_MAIN_ACTION（或者ROOTTHING_CS_MAIN_ACTION）
** 应  用:  服务器、客户端
** 备  注:   
**
**  消息码的流通类型如下：
**  CSC: 服务器与客户端相互通信的消息码。
**
**  BCM: 服务器各功能与逻辑对像通知广播的消息码。（只会用在服务器）
**  SS: 服务器各功能相互通信的消息码。（只会用在服务器）
**
**  CC: 客户端各功能相互通信的消息码。（只会用在客户端）
**  IC: 客户端输入设备与客户端功能模块通信的消息码。（只会用在客户端）
**
**  CSC_S: 服务器发给服务器模块的CSC类型，相当于模拟客户端发的CSC消息（只会用在服务器）
**  CSC_C: 客户端发给客户端模块的CSC类型，相当于模拟服务器发的CSC消息（只会用在客户端）
**  IC_C: 客户端发给客户端模块的IC类型，相当于模拟输入设备发的IC消息（只会用在客户端）

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef __DMSG_SUBACTION_H__
#define __DMSG_SUBACTION_H__

// 事件类型ID定义
enum emEventType
{
	SRC_TYPE_ID_ROOT		= 0,	// 根
	SRC_TYPE_ID_SYSTEM,				// 系统
	SRC_TYPE_ID_ACTOR,				// 玩家
	SRC_TYPE_ID_MONSTER,			// 怪物 
	SRC_TYPE_ID_ITEM,				// 物品
	SRC_TYPE_ID_CONTAINER,			// 容器
	SRC_TYPE_ID_CHAT,				// 聊天 
	SRC_TYPE_ID_BOX,				// 盒子
	SRC_TYPE_ID_DUMMY,				// 假人
	SRC_TYPE_ID_TEAM,				// 组队
	SRC_TYPE_ID_GAMEOBJ,			// 场景物件
	SRC_TYPE_ID_UNION,				// 家族
	SRC_TYPE_ID_HERO,				// 英雄
	SRC_TYPE_ID_BATTLE,				// 战场
	SRC_TYPE_ID_SCRIPT_EVENT,		// 脚本事件
	SRC_TYPE_ID_RANK,				// 大赛排名
	SRC_TYPE_ID_MAX
};


//CIRCULTYPE：流通类型（4位）
//ACTIONID：行为事件的子消息码（8位）
#define MAKE_MSGID(CIRCULTYPE, ACTIONID)	(CIRCULTYPE << 8 | ACTIONID)

//获取消息的CIRCULTYPE（流通类型）
#define PARSE_CIRCULTYPE(MSGID)				(MSGID >> 8)

//获取消息的ACTIONID（行为事件子消息码）
#define PARSE_ACTIONID(MSGID)				(MSGID & 0xFF)


//////////////////////////////////////////////////////////////////////////
///////////////////////////// 消息流通类型 ///////////////////////////////
//[CSC]:  服务器与客户端相互通信的消息码。
#define MAINACTION_CIRCULTYPE_CSC						1

//[BCM]:  服务器各功能与逻辑对像通知广播的消息码（只会用在服务器）
#define MAINACTION_CIRCULTYPE_BCM						2

//[SS]:  服务器各功能相互通信的消息码（只会用在服务器）
#define MAINACTION_CIRCULTYPE_SS						3

//[CC]:  客户端各功能相互通信的消息码（只会用在客户端）
#define MAINACTION_CIRCULTYPE_CC						4

//[IC]:  客户端输入设备与客户端功能模块通信的消息码（只会用在客户端）
#define MAINACTION_CIRCULTYPE_IC						5

//[CSC_S]:  服务器发给服务器模块的CSC类型，相当于模拟客户端发的CSC消息（只会用在服务器）
#define MAINACTION_CIRCULTYPE_CSC_S						6

//[CSC_C]:  客户端发给客户端模块的CSC类型，相当于模拟服务器发的CSC消息（只会用在客户端）
#define MAINACTION_CIRCULTYPE_CSC_C						7

//[IC_C]:  客户端发给客户端模块的IC类型，相当于模拟输入设备发的IC消息（只会用在客户端）
#define MAINACTION_CIRCULTYPE_IC_C						8

#define MAINACTION_MAX									MAINACTION_CIRCULTYPE_IC_C

//////////////////////////////////////////////////////////////////////////
/////////////////////// 战场事件的子消息码 ///////////////////////////
enum MAINACTION_BATTLE_EVENT
{
	EVENT_GAME_BIG_ROUND_BEGIN			= 1, 	// 大回合开始
	EVENT_GAME_SMALL_ROUND_BEGIN,				// 小回合开始
	EVENT_GAME_BIG_ROUND_END, 					// 大回合结束
	EVENT_GAME_SMALL_ROUND_END,					// 小回合结束
	EVENT_GAME_ROOM_PREPARE,					// 房间游戏开始
};

//////////////////////////////////////////////////////////////////////////
///////////////////// 大赛排名类子消息吗 /////////////////////////////////
enum MAINACTION_RANK_EVENT
{
	EVENT_RANK_PLAYER_LEVELUP			= 1,	// 玩家升级
};

//////////////////////////////////////////////////////////////////////////
// EVENT_RANK_PLAYER_LEVELUP
struct SEventRankPlayerLevelUp_S
{
	s64	qwUserID;	// 账号ID
	s32	lLevel;		// 等级

	SEventRankPlayerLevelUp_S()
	{
		memset(this, 0, sizeof(*this));
	}
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/////////////////////// 实体行为事件的子消息码 ///////////////////////////
enum MAINACTION_MSGID
{
 
	/////////////////////////////////////////////////////////
	//描        述：场景服登录或者登出中心服
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CS_LOGINOUT,
 
	// 逻辑对象创建 
	MAINACTION_MSGID_CREATE ,

	// 逻辑对象销毁
	MAINACTION_MSGID_DESTORY,

	// 移动
	MAINACTION_MSGID_MOVE,

	// 站立
	MAINACTION_MSGID_STOPHERE,

	// 死亡
	MAINACTION_MSGID_DIE,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_RELIVE
	//描        述：人物复活
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_RELIVE,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_RELIVE_TIME
	//描        述：更新复活时间
	//支持流通类型：CSC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_RELIVE_TIME,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_CLOSERELIVEMSGBOX
	//描        述：关闭复活对话框
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CLOSERELIVEMSGBOX,

	// 技能攻击
	MAINACTION_MSGID_SKILL_ATTACK,

	// 传送
	MAINACTION_MSGID_NEW_WORLD,

	/////////////////////////////////////////////////////////
	//描        述：点击完成任务
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_FINISHTASK,

	// 商店NPC的物品列表
	MAINACTION_MSGID_LIST_INVENTORY,


	// 服务器启动成功事件
	MAINACTION_MSGID_START_OK,

	// 玩家登录成功
	MAINACTION_MSGID_PLAYERLOGIN,

	// 玩家登出成功
	MAINACTION_MSGID_PLAYERLOGOUT,

	// 登录数据库返回，通知其他模块加载数据库
	MAINACTION_MSGID_PLAYERLOADDATABASE,

	// 玩家定时保存数据
	MAINACTION_MSGID_PLAYERSAVE,

	// 物品销毁
	MAINACTION_MSGID_DESTROY,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_OPENBOX
	//描        述：盒子相关的操作消息
	//支持流通类型：CSC, SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_OPENBOX,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_RESBOX
	//描        述：资源盒子相关的操作消息
	//支持流通类型：CSC, SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_RESBOX,

	// 创建容器
	MAINACTION_MSGID_CONTAINER,

	// 背包发生变化
	MAINACTION_MSGID_BAGS_CHG,

	// 可以存放物品
	MAINACTION_MSGID_BAG_VALIDE,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_RELEASE
	//描        述：对像释放
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_RELEASE,

	// 属性更新
	MAINACTION_MSGID_UPDATEPROP,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_CLEAN_SHOW
	//描        述：刷新外观
	//支持流通类型：CSC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CLEAN_SHOW,

	/////////////////////////////////////////////////////////
	//描        述：装备栏中装备的耐久发生变化
	//支持流通类型：CSC
	///////////////////////////////////////////////////////// 
	MAINACTION_MSGID_ENDURE,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_LOOK_ACTOR_EQUIP
	//描        述：观察玩家装备
	//支持流通类型：CSC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_LOOK_ACTOR_EQUIP,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_SYSTEMMESSAGE
	//描        述：系统消息
	//支持流通类型：SS, CSC，BCM
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SYSTEMMESSAGE,

	/////////////////////////////////////////////////////////
	//描        述：生物显示状态改变
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CRT_STATE_CHG,

	/////////////////////////////////////////////////////////
	//描        述：逻辑->UI 技能准备
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_PREPARE,

	/////////////////////////////////////////////////////////
	//描        述：逻辑->UI 技能释放
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_CAST_OUT,

	/////////////////////////////////////////////////////////
	//描        述：逻辑->UI 释放闪电链技能的消息
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_CHAIN_OUT,

	/////////////////////////////////////////////////////////
	//描        述：逻辑->UI 技能中断
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_BREAK,

	/////////////////////////////////////////////////////////
	//描        述：取消技能
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_CANCEL_UL,
	MAINACTION_MSGID_SKILL_CANCEL_LU,

	/////////////////////////////////////////////////////////
	//描        述：技能初始化
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_INIT,

	/////////////////////////////////////////////////////////
	//描        述：升级技能
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_UPGRADE_UL,
	MAINACTION_MSGID_SKILL_UPGRADE_LU,
	MAINACTION_MSGID_SKILL_UPGRADE_PET_UL,
	MAINACTION_MSGID_SKILL_UPGRADE_PET_LU,

	/////////////////////////////////////////////////////////
	//描        述：遗忘技能
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_FORGET_PET_UL,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_UPGRADE_EXP
	//描        述：升级功勋等级
	//支持流通类型：CSC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_UPGRADE_EXP,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_OSS_TASK
	//描        述：OOS 任务监控消息
	//支持流通类型：CSC
	MAINACTION_MSGID_OSS_TASK,


	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_MURDEROUS
	//描        述：杀手对敌人造成死亡
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_MURDEROUS,

	/////////////////////////////////////////////////////////
	//描        述：更新CD时间
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_COLD_UPDATA_LU,
	MAINACTION_MSGID_COLD_UPDATA_PET_LU,

	/////////////////////////////////////////////////////////
	//描        述：变更名字颜色
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PKNAMECOLOR,

	/////////////////////////////////////////////////////////
	//描        述：切换PK模式
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SWITCHPKMODE,

	MAINACTION_MSGID_OPENSHOP,

	/////////////////////////////////////////////////////////
	//描        述：显示箱子中所有物品
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SHOWITEMS_INBOX,

	/////////////////////////////////////////////////////////
	//描        述：升级通知
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_LEVELUP,

	/////////////////////////////////////////////////////////
	//描        述：攻击
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ATTACK,

	/////////////////////////////////////////////////////////
	//描        述：被攻击
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BE_ATTACK,

	/////////////////////////////////////////////////////////
	//描        述：改变战斗状态
	//支持流通类型：MAINACTION_CIRCULTYPE_CSC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGE_FIGHT_STATUS,

	/////////////////////////////////////////////////////////
	//描        述：更新技能点
	//支持流通类型：MAINACTION_CIRCULTYPE_CSC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_UPDATA_POINT,

	/////////////////////////////////////////////////////////
	//描        述：更新NPC头顶标识
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_NPCHEADFLAG,

	/////////////////////////////////////////////////////////
	//描        述：切换状态
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SWITCHSTATE,

	/////////////////////////////////////////////////////////
	//描        述：服务器使用道具(使用药品)
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_USEGOODS,

	/////////////////////////////////////////////////////////
	//描        述：开始读进度条
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_STARTPROGRESSBAR,

	/////////////////////////////////////////////////////////
	//描        述：进度条结束
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ENDPROGRESSBAR,

	/////////////////////////////////////////////////////////
	//描        述：播放音效
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PLAYSOUND,

	/////////////////////////////////////////////////////////
	//描        述：使用药品结果
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_USELEECHDOMRESULT,

	/////////////////////////////////////////////////////////
	//消  息    码：MAINACTION_MSGID_TRANSMAP
	//描        述：切换地图，EntityServer发出这个消息
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRANSMAP,

	/////////////////////////////////////////////////////////
	//描        述：错误码通道
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ERRORCODECHUNNEL,

	/////////////////////////////////////////////////////////
	//描        述：技能改变位置
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGELOCATIONFORSKILL,

	/////////////////////////////////////////////////////////
	//描        述：链接社会服成功事件
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SOCIETYSVRLOGINED,

	/////////////////////////////////////////////////////////
	//描        述：断开与社会的链接服事件
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SOCIETYSVRLOGOUTED,

	/////////////////////////////////////////////////////////
	//描        述：副本逻辑处理
	//支持流通类型：场景服->中心服
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CENTER_ECTYPE_PROCESS,

	/////////////////////////////////////////////////////////
	//描        述：客户端交易请求事件
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_REQUEST,

	/////////////////////////////////////////////////////////
	//描        述：交易开始
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_GO,

	////////////////////////////////////////////////////////
	//描        述：取消交易
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_CANCEL,

	////////////////////////////////////////////////////////
	//描        述：金钱数目改变
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_UPDATE_MONEY,

	////////////////////////////////////////////////////////
	//描        述：改变交易栏中物品(己交蚨苑�)
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_UPDATE_ITEMS,


	////////////////////////////////////////////////////////
	//描        述：加锁或者解锁
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_LOCK,

	////////////////////////////////////////////////////////
	//描        述：点了确定
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_CONFIRM,

	////////////////////////////////////////////////////////
	//描        述：交易完成
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TRADE_FINISH,

	////////////////////////////////////////////////////////
	//描        述：玩家切换地图
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ACTOR_CHANGE_MAP,

	////////////////////////////////////////////////////////
	//描        述：复活询问
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ASK_RELIVE,

	/////////////////////////////////////////////////////////
	// 描	   述：重置副本
	// 支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_RESET_ECTYPE,

	////////////////////////////////////////////////////////
	//描        述：组队情况变更
	//支持流通类型：SS
	//数据结构：STeamChangeInfo_SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TEAM_CHANGE,

	////////////////////////////////////////////////////////
	//描        述：技能释放结束
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ATTACK_FINISH,

	////////////////////////////////////////////////////////
	//描        述：复活倒计时
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGEACTOR_INTERVAL,

	////////////////////////////////////////////////////////
	//描        述：同步非九宫格内所有的NPC
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SYNC_NPCINFO,

	////////////////////////////////////////////////////////
	//描        述：任务数据加载ok
	//支持流通类型：任务系统
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_TASK_DATA_LOADED_OK,

	////////////////////////////////////////////////////////
	//描        述：更新AI模式
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CALL_ANIMAL_AIMODE,

	/////////////////////////////////////////////////////////
	//描        述：服务器使用道具(穿装备)
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ONEQUIP,

	/////////////////////////////////////////////////////////
	//描        述：服务器使用道具(卸装备)
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_UNEQUIP,

	/////////////////////////////////////////////////////////
	//描        述：进入战斗状态
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ENTER_FIGHT_STATUS,

	/////////////////////////////////////////////////////////
	//描        述：脱离战斗状态
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_LEAVE_FIGHT_STATUS,

	/////////////////////////////////////////////////////////
	//描        述：服务器登录/登出事件
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SERVER_LOGIN_LOGOUT,

	/////////////////////////////////////////////////////////
	//描        述：服务器更新人数
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SERVER_ONLINE_UPDATE,

	////////////////////////////////////////////////////////
	//描        述：上马换外观
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_RIDE_MOUNT,

	////////////////////////////////////////////////////////
	//描        述：下马换外观
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_DOWN_MOUNT,

	/////////////////////////////////////////////////////////
	//描        述：选择目标
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SELECT_TARGET,

	/////////////////////////////////////////////////////////
	//描        述：鼠标移动玩家
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_MOUSE_MOVE_PLAYER,

	/////////////////////////////////////////////////////////
	//描        述：客户端改变配置参数
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGE_OPTION,

	/////////////////////////////////////////////////////////
	//描        述：客户端移除所有对象
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BEFORE_REMOVE_ALL_OBJECT,

	/////////////////////////////////////////////////////////
	//描        述：客户端技能预判断
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SKILL_CAN_USE,

	/////////////////////////////////////////////////////////
	//描        述：吟唱结束
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PREPARE_END,

	/////////////////////////////////////////////////////////
	//描        述： 任务完成监控事件消息
	//支持流通类型：SS
	MAINACTION_MSGID_TASK_SYS_TASK_FINISH,

	/////////////////////////////////////////////////////////
	//描        述： 打开仓库界面
	//支持流通类型：CC
	MAINACTION_MSGID_OPEN_STORAGE,

	////////////////////////////////////////////////////////
	//描        述：变身
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGE_MODEL,

	////////////////////////////////////////////////////////
	//描        述：合体
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_MERGE_MODEL,

	////////////////////////////////////////////////////////
	//描        述：自定义快捷栏更新
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_DEFINE_BAR_UPDATA,

	////////////////////////////////////////////////////////
	//描        述：沉默效果
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SLIENT_EFFECT,

	/////////////////////////////////////////////////////////
	//描        述： 获得商城每个Tab页上商品的最大数量
	//支持流通类型：CC
	MAINACTION_MSGID_GET_TAB_MAX_NUM,

	/////////////////////////////////////////////////////////
	//描        述： 获得商品列表
	//支持流通类型：CC
	MAINACTION_MSGID_GET_MALL_GOODS_LIST,

	/////////////////////////////////////////////////////////
	//描        述： 再次确认购买商品
	//支持流通类型：CC
	MAINACTION_MSGID_RES_BUY_MIND_GOODS,

	/////////////////////////////////////////////////////////
	//描        述： 购买商品结果
	//支持流通类型：CC
	MAINACTION_MSGID_RESULT_BUY_MIND_GOODS,

	/////////////////////////////////////////////////////////
	//描        述： 账户余额查询结果
	//支持流通类型：CC
	MAINACTION_MSGID_PAY_INFO_QUERY,

	////////////////////////////////////////////////////////
	//描        述：服务器广播留言
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_CHAT_MSG_REPLY,

	////////////////////////////////////////////////////////
	//描        述：服务器广播关仗�
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_CLOSE_REPLY,

	////////////////////////////////////////////////////////
	//描        述：摊位状态
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_STATUS_REPLY,

	////////////////////////////////////////////////////////
	//描        述：摊位名
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_NAME_REPLY,

	////////////////////////////////////////////////////////
	//描        述：放入物品回复
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_PUTONGOODS_REPLY,

	////////////////////////////////////////////////////////
	//描        述：取下物品回复
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_PUTOFFGOODS_REPLY,

	////////////////////////////////////////////////////////
	//描        述：修改物品回复
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_MODIFYGOODS_REPLY,

	////////////////////////////////////////////////////////
	//描        述：购买物品回复
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_BUYGOODS_REPLY,

	////////////////////////////////////////////////////////
	//描        述：通知顾客增加一个物品
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_CUSTOMER_ADD_GOODS_REPLY,

	////////////////////////////////////////////////////////
	//描        述：通知顾客移除一个物品
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOOTH_CUSTOMER_REMOVE_GOODS_REPLY,

	////////////////////////////////////////////////////////
	//描        述：改变名字
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGE_NAME,

	////////////////////////////////////////////////////////
	//描        述：移动事件（隐身专用）
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGE_LOC_HIDE_USE,

	////////////////////////////////////////////////////////
	//描        述：不具有反隐能力
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_NOT_HAS_SHOW_EFFECT,

	////////////////////////////////////////////////////////
	//描        述：宝石更新目标反隐引用计数
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_UPDATA_TARGET_UNHIDE_REF,

	////////////////////////////////////////////////////////
	//描        述：是否看不见
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_IS_CAN_NOT_SEE,

	////////////////////////////////////////////////////////
	//描        述：更新自己的状态
	//支持流通类型：SS、CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_UPDATA_HIDE_STATUS,

	////////////////////////////////////////////////////////
	//描        述：隐身
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_HIDE_MODEL,

	////////////////////////////////////////////////////////
	//描        述：玩家批量数据更新
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MSG_PLAYER_BATCH_UPDATE,

	////////////////////////////////////////////////////////
	//描        述：宠物列表
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PETLIST_UPDATE,

	////////////////////////////////////////////////////////
	//描        述：宠物操作
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PET_OPERATE,

	////////////////////////////////////////////////////////
	//描        述：宠物装备更换
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PET_CHANGE_EQUIP,

	////////////////////////////////////////////////////////
	//描        述：宠物改名(自己的宠物,针对界面)
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PET_CHANGENAME,

	////////////////////////////////////////////////////////
	//描        述：宠物改名(针对场景宠物,不一定是自己的)
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PET_CHANGENAME_ALL,

	////////////////////////////////////////////////////////
	//描        述：设置宠物AI
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PET_SETAI,

	////////////////////////////////////////////////////////
	//描        述：宠物实体创建成功
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PET_ENTITY_CREATE,

	////////////////////////////////////////////////////////
	//描        述：t制造套装备结果
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_RESULT_MAKESUIT,
	/////////////////////////////////////////////////////////
	//描        述：战场逻辑处理
	//支持流通类型：场景服->社会服
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SOCIETY_BATTLE_PROCESS,

	////////////////////////////////////////////////////////
	//描        述：打开制造套装备结果
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_OPEN_MAKESUIT,

	// 宠物使用技能
	MAINACTION_MSGID_SKILL_USE_PET,

	////////////////////////////////////////////////////////
	//描        述：变身刷新事件
	//支持流通类型：CC
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CHANGE_MODEL_RESHOW,

	////////////////////////////////////////////////////////
	//描        述：战场模块.战场事件
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BATTLE_EVENT,

	////////////////////////////////////////////////////////
	//描        述：地图更新事件
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_MAP_UPDATE_EVENT,

	////////////////////////////////////////////////////////
	//描        述：玩家切换地图(完成即玩家已经进入地图)
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ACTOR_CHANGE_MAP_FINISH,

	////////////////////////////////////////////////////////
	//描        述：玩家合体
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ACTOR_MERGE,

	////////////////////////////////////////////////////////
	//描        述：lua打断进度条
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_LUA_BREAK,

	////////////////////////////////////////////////////////
	//描        述：交换宝石
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_SWAP_GEM,

	////////////////////////////////////////////////////////
	//描        述：实体回合结束
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_ENTITY_ROUND_END,

	////////////////////////////////////////////////////////
	//描        述：实体回合结束
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BUFF_ROUND_END,

	/////////////////////////////////////////////////////////
	//描        述：关卡进度
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_INSTANCE_UPDATA,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_BATTLE_END
	//描        述：战斗结束
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BATTLE_END,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_STRENGTHEN_CARD
	//描        述：合成
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_STRENGTHEN_CARD,

	////////////////////////////////////////////////////////
	//描        述：实体开始战斗
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BUFF_BATTLE_BEGIN,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_PVP_TRAIN_END
	//描        述：战斗结束
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PVP_TRAIN_END,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_FRIEND_TRAIN_END
	//描        述：好友切磋结束
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_FRIEND_TRAIN_END,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_INSTANCE_FINISH
	//描        述：关卡通关
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_INSTANCE_FINISH,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_COMB_INFO
	//描        述：连击信息
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_COMB_INFO,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_BOMB_INFO
	//描        述：炸弹信息
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_BOMB_INFO,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_PRODUCE_LEVELUP
	//描        述：铁匠铺升级事件
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_PRODUCE_LEVELUP,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_FRIEND_COLLECT
	//描        述：好友收集结束
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_FRIEND_COLLECT,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_CLIENT_FINISH
	//描        述：客户端触发完成
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_CLIENT_FINISH,

	/////////////////////////////////////////////////////////
	//消  息    MAINACTION_MSGID_INSTANCE_COLLEC
	//描        述：关卡征收完成
	//支持流通类型：SS
	/////////////////////////////////////////////////////////
	MAINACTION_MSGID_INSTANCE_COLLECT,


	// 最大子消息码
	MAINACTION_MSGID_MAX,
};

enum MAINCONTAINER_MSGID
{
	// 打开容器
	MAINCONTAINER_CSC_OPEN,

	// 关闭容器
	MAINCONTAINER_CSC_CLOSE,

	// 往容器添加物品
	MAINCONTAINER_CSC_ADD,

	// 从容器删除物品
	MAINCONTAINER_CSC_REMOVE,

	// 通知客户端更新
	MAINCONTAINER_CSC_UPDATE,

	// 通知服务器拆分物品
	MAINCONTAINER_CSC_SPLIT,

	// 物品数量改变
	MAINCONTAINER_SS_NUM_CHG
};

enum MAINSKEP_MSGID
{
	// 改变虚拟物品栏的容量
	MSG_SKEP_CHANGESIZE,

	// 同步虚拟物品栏权限
	MSG_SKEP_SYNCPOPEDOM,

	// 同步虚拟物品栏中物品的位置
	MSG_SKEP_SYNC,

	// 销毁虚拟物品栏
	MSG_SKEP_DESTORYSKEP,

	MSG_SKEP_LINK,

	MSG_SKEP_SPLIT,

	MSG_SKEP_USE,

	MSG_SKEP_OBSERVER,
};

enum MAINTRADE_MSGID
{
	// 取消交易
	MSG_TRADE_CANCEL,

	// 请求交易
	MSG_TRADE_REQUEST,

	// 接受交易
	MSG_TRADE_ACCEPT,

	// 接受交易回复
	MSG_TRADE_GO,

	// 拒绝交易
	MSG_TRADE_REFUSE,

	// 锁定交易
	MSG_TRADE_LOCK,

	// 取消锁定
	MSG_TRADE_UNLOCK,

	// 改变金钱
	MSG_TRADE_UPDATE_MONEY,

	// 放入交易物品
	MSG_TRADE_SET_ITEM,

	// 移除交易物品
	MSG_TRADE_CLEAR_ITEM,

	// 确认交易
	MSG_TRADE_CONFIRM,

	// 交易结束
	MSG_TRADE_FINISH,

	// 玩家属性更新
	MSG_PROPERTY_UPDATE,
};

enum ENUMMAIN_MIND
{
	// 请求每个Tab页上商品的最大数量(客户端->服务器)
	MSG_MIND_GET_TAB_MAX_NUM,

	// 请求商品列表(客户端->服务器)
	MSG_MIND_GET_MIND_GOODS_LIST,

	// 请求购买商品(客户端->服务器)
	MSG_MIND_BUY_MIND_GOODS,

	// 请求购买商品回复(服务器->客户端)
	MSG_MIND_RES_BUY_MIND_GOODS,

	// 确认购买或取消(客户端->服务器)
	MSG_MIND_CONFIRM_BUY,

	// 购买商品结果(服务器->客户端)
	MSG_MIND_RESULT_BUY_MIND_GOODS,

	// 账号余额查询(客户端->服务器 或 服务器->客户端)
	MSG_MIND_PAY_INFO_QUERY,
};

/// 家族事件消息码
enum ENUM_MAIN_UNION
{
	/// 主角色加入家族，接到家族信息（客户端->客户端）
	MAINUNION_MSGID_MAINPLAYER_JOINUNION = 0,

	/// 主角色离开家族（客户端->客户端）
	MAINUNION_MSGID_MAINPLAYER_LEAVEUNION,
};


//最大消息码（通过 MAKE_MSGID(CIRCULTYPE, ACTIONID) 获得）
#define MAIN_ACTION_MSG_MAX					MAKE_MSGID(MAINACTION_MAX, MAINACTION_MSGID_MAX)


#pragma pack(push,1)

// 登录中心服成功
#define EVENT_LOGIN_CENTER										8
struct SEventLoginCenter_S
{

};

// 移动完成
#define EVENT_CREATURE_DONEMOVE									9
// 场景服
struct SEventCreatureDoneMove_S
{

};

// 创建实体
#define EVENT_ENTITY_CREATEENTITY								11
// 场景服
struct SEventEntityCreateEntity_S
{
	LONGLONG		uidEntity;		// 实体uid
};

// 怪物或者玩家死亡
#define EVENT_CREATURE_DIE										12
// 场景服
struct SEventCreatureDie_S
{
	LONGLONG		uidMurderer;		// 谋杀者的uid
};

// 删除实体
#define EVENT_ENTITY_DESTROYENTITY								13
// 场景服
struct SEventEntityDestroryEntity_S
{
	LONGLONG		uidEntity;		// 实体uid
};
// 客户端
struct SEventEntityDestroryEntity_C
{
	LONGLONG		uidEntity;		// 实体uid
};


// 实体添加BUFF
#define EVENT_CREATURE_ADDBUFF									14
// 场景服（vote/execute）
struct SEventCreatureAddBuff_S
{
	DWORD			dwBuffID;		// buff id
	LONGLONG		uidAdd;			// 本buff的添加者
};
// 客户端
struct SEventCreatureAddBuff_C
{
	DWORD			dwIndex;		// buff index
	DWORD			dwFlashID;		// 光效ID
	DWORD			dwRandFlashID;	// 随机效果光效
};

// 实体移除BUFF
#define EVENT_CREATURE_REMOVEBUFF								15
// 场景服（vote/execute）
struct SEventCreatureRemoveBuff_S
{
	DWORD			dwBuffID;		// buff id
	LONGLONG		uidRemove;		// 移除者
};

// 客户端
struct SEventCreatureRemoveBuff_C
{
	DWORD			dwIndex;		// buff index
};

// 点击NPC
#define EVENT_PERSON_MEETNPC									16
// 场景服
struct SEventPersonMeetNpc_S
{
	LONGLONG		uidMaster;		// 谁点的NPC
	LONGLONG		uidNPC;			// 何个NPC
};

// 实体攻击
#define EVENT_CREATURE_USE_SKILL								17
struct SEventUseSkill_S
{
	LONGLONG		uidUnit;		  // 对象
	s32     		nSkillID;			// 技能id
  s32         nSkillType;   // (1~5：地水火风雷)
};


// 实体被攻击
#define EVENT_CREATURE_BE_USE_SKILL								18
// struct SEventUseSkill_S

// 实体位置变更
#define EVENT_CREATURE_CHANGELOC								19
// 场景服
struct SEventCreatureChangeLoc_S
{
	DWORD			dwOldRoomID;	// 旧场景ID
	POINT			ptOldTile;		// 旧Tile
	DWORD			dwNewRoomID;	// 新场景ID
	POINT			ptNewTile;		// 新Tile
	bool			bSameServer;	// 旧场景与新场景是否为同服务器
};
// 客户端
struct SEventCreatureChangeLoc_C
{
	POINT			ptOldTile;		// 旧Tile
	POINT			ptNewTile;		// 新Tile
};

// 实体被伤害
#define EVENT_CREATURE_INJURED									20
struct SEventCreatureInjured_S
{
	LONGLONG		uidMurderer;			// 凶手
	DWORD			dwHPDamage;				// HP伤害
	DWORD			dwMPDamage;				// MP伤害
	s32				nAttackType;			// 攻击类型
};

// 实体开始移动
#define EVENT_CREATURE_STARTMOVE								21

// 实体攻击结束
#define EVENT_CREATURE_USE_SKILLFINISHED							22

// 实体主动伤害
#define EVENT_CREATURE_HARM										23
struct SEventCreatureHarm_S
{
	LONGLONG		uidCasualty;			// 被攻击者
	DWORD			dwHPDamage;				// HP伤害
	DWORD			dwMPDamage;				// MP伤害
	s32				nAttackType;			// 攻击类型
};

// 人物进度条状态开始事件
#define EVENT_PERSON_PROGRESSBARSTART							24
// 场景服（vote/execute）
struct SEventPersonProgressBarStart_S
{
	BYTE byBarType;					// 进度条类型
	int nTime;						// 持续时间
	char szName[32];				// 进度条的名字
};

// 人物进度条状态结束事件
#define EVENT_PERSON_PROGRESSBAREND								25
// 场景服（vote/execute）
struct SEventPersonProgressBarEnd_S
{
	enum
	{
		PB_INVALID = 0,
		PB_WORK_SKILL,				// 工作技能进度条
		PB_OPEN_DOOR,				// 打开场景物件门进度条
		PB_STAND_FLAG,				// 打开场景物件占领点进度条
		PB_OPEN_BOX,				// 打开场景盒子进度条
		PB_RIDE_STATE,				// 骑马状态
		PB_TREASURE_IDENTIFY,		// 藏宝图鉴定进度条
		PB_TREASURE_USE,			// 藏宝图使用进度条
		PB_RUNLUAFUNCTION,			// 运行LUA函数
		PB_PET_OUT,					// 宠物出战
	};

	int			nEndReason;			// 结束原因
	LONGLONG	uidMaster;			// 进度条部件的主人
	char		userData[128];		// 第一个字节用于放进度条类型
	int			nDataLen;
};

// 骑马进度条上下文
struct SRideProgressBarContext_S
{
	SRideProgressBarContext_S()
	{
		nBufferID = 0;
		uidGoodsID = 0;
		byBufferLv = 0;
	}
	int			nBufferID;			// buffer ID
	LONGLONG	uidGoodsID;			// 物品的guid
	BYTE		byBufferLv;			// buffer 等级
};

// 鉴定进度条上下文
struct STreasureIdentifyProgressBarContext
{
	LONGLONG uidTreasure;

	STreasureIdentifyProgressBarContext()
	{
		memset( this, 0, sizeof(*this) );
	}
};

// 藏宝图使用进度条上下文
struct STreasureUseProgressBarContext
{
	LONGLONG uidTreasure;

	STreasureUseProgressBarContext()
	{
		memset( this, 0, sizeof(*this) );
	}
};

struct SRunLuaFunctionProgressBarContext_S
{
	LONGLONG uidGoods;
	char	 szLuaFunctionname[64];
	SRunLuaFunctionProgressBarContext_S()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 切换地图
struct SS_TANSMAP_ACTION_CONTEXT
{
	enum TANSMAP_MODE
	{
		TANSMAP_MODE_NEXTROOM = 0,
	};
	int	lTansMode;
	int	lTargetMapID;
	POINT	ptTargetPos;
	SS_TANSMAP_ACTION_CONTEXT()
	{
		memset( this, 0, sizeof(*this) );
	}
};

#define EVENT_PERSON_SWITCHSTATE								26

// 实体允许使用技能
#define EVENT_ALOW_USE_SKILL									27

/// 宠物从场景删除，收回到玩家
#define EVENT_PET_DEL_SCENE										28


// 怪物或者玩家死亡
#define EVENT_CREATURE_KILL										29
// 场景服
struct SEventCreatureKill_S
{
	LONGLONG		uidDie;		// 被杀者的uid
};

// HP更新
#define EVENT_CREATURE_HP_UPDATA								30
// MP更新
#define EVENT_CREATURE_MP_UPDATA								31

/***************************************************************/
///////////////////////// 系统事件码 ////////////////////////////
/***************************************************************/
// 构建了场景
#define EVENT_SYSTEM_BUILDROOM									1
// 场景服（vote / execute）
struct SEventSystemBuildRoom_S
{
	DWORD			dwMapID;		// 地图ID
	DWORD			dwRoomID;		// 场景ID
};

// 客户端
struct SEventSystemBuildRoom_C
{
	DWORD			dwMapID;		// 地图ID
	DWORD			dwRoomID;		// 场景ID
};

// 销毁了场景
#define EVENT_SYSTEM_DESTORYROOM								2
// 场景服（vote / execute）
struct SEventSystemDestoryRoom_S
{
	DWORD			dwMapID;		// 地图ID
	DWORD			dwRoomID;		// 场景ID
};

// 客户端
struct SEventSystemDestoryRoom_C
{

};
// 弹出系统消息
#define MSG_SYSTEM_CLIENT_MSGCENTER_POP							3

// 玩家/怪物死亡消息
#define MSG_SYSTEM_CREATURE_DIE									4
struct SEventSystemCreatureDie_S
{
	LONGLONG	uiDieID;			// 死者的uid
	LONGLONG	uiMurderID;			// 谋杀者的uid
};

//////////////////////////////////////////////////////////////////////////
////////////////////////////////容器类事件////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define	MSG_C_CREATE											1
#define MSG_C_RELEASE											2
struct SC_MSG_CONTAINER
{
	int nCMD;			// 容器类子命令
	int nContainerID;	// 容器Id
	int nCSize;			// 容器大小
	int nLocation;		// 容器位置
};

//////////////////////////////////////////////////////////////////////////
/////////////////////////////虚拟物品栏类事件/////////////////////////////
//通知客户端创建虚拟物品栏
struct SBuildBoxExtendContext
{
	LONGLONG	uidBox;
};
struct SBuildShopmallExtendContext
{
	LONGLONG	uidNPC;
};
//同步虚拟物品栏最大容量
struct SMsgSkepChangeSize_SC
{
	WORD	wMaxSize;	// 虚拟物品栏最大容量
};

//同步虚拟物品栏权限
struct SMsgSkepSyncPopedom_SC
{
	DWORD	dwPopedom;	// 虚拟物品栏权限
};

struct SSyncSkepGoods
{
	int			nPlace;			// 物品在虚拟物品栏中的位置
	LONGLONG	uidGoods;		// 虚拟栏中物品的uid
	DWORD		dwRelaySkepID;	// 交互的虚拟物品篮Id
	BYTE		byLink;			// 真实物品是否已链接(0:否 1:是)
};

struct SMsgSkepLink_CS
{
	DWORD		dwSrcSkepID;	// 源虚拟物品栏Id
	int			nSrcPlace;		// 源位置
	int			nTrgContainId;	// 目标容器Id
	int			nTrgPlace;		// 新位置
};

struct SMsgSkepObserver_CS
{
	BYTE		byOpen;			// (0:关闭 1:打开)
};

struct SMsgSkepSplit_CS
{
	int			nSplitNum;		// 数量
	LONGLONG	uidGoods;		// 物品uid
	int			nPlace;			// 虚拟物品栏中的位置
};

struct SMsgSkepUse_CS
{
	LONGLONG	uidGoods;		// 物品uid
	int			nPlace;			// 虚拟物品栏中的位置
};

/***************************************************************/
/////////////////// 通用物品篮事件码 ////////////////////////////
/***************************************************************/
// 向通用物品篮添加物品
#define EVENT_SKEP_ADDSKEPGOODS									1
// 场景服（vote / execute）
/* 只有凭空添加物品时，才会触发此事件，比如从商店里买进一个物品就
会触发此事件，从一个物品篮转移到另一个物品篮是不会触发此事件，比
如从仓库拖物品到包裹栏。也就只有实在通用物品栏才会触发//*/
struct SEventSkepAddSkepGoods_S
{
	LONGLONG		uidOperater;	// 操作者
	LONGLONG		uidGoods;		// 物品UID
	int				nPlace;			// 添加位置
};

// 向通用物品篮删除物品
#define EVENT_SKEP_REMOVESKEPGOODS								2
// 场景服（vote / execute）
/* 只有凭空移除物品时，才会触发此事件，比如任务NPC从包裹栏收走任务
物品。也就只有实在通用物品栏才会触发//*/
struct SEventSkepRemoveSkepGoods_S
{
	LONGLONG		uidOperater;	// 操作者
	LONGLONG		uidGoods;		// 物品UID	
	int				nPlace;			// 移除位置
};

// 通用物品篮内要释放了
#define EVENT_SKEP_DESTORYSKEP									3
// 服务器
struct SEventSkepDestorySkep_S
{
	DWORD			dwSkepID;		// 物品篮ID
}; 

// 客户端
// 内部不负责释放客户端skep，因为担心外部很多地方
// 保存了它的指针，让他的管理者来释放，比如物品篮
// 的skep，让物品篮来释放
struct SEventSkepDestorySkep_C
{
	DWORD			dwSkepID;		// 物品篮ID
};

// 清空通用物品篮
#define EVENT_SKEP_CLEANSASHSKEP								4
// 场景服（vote / execute）
/* 外部调用ISkep::Clean清空物品篮时，会触发此事件，不论链接物品篮还
是实在物品篮都会触发//*/
struct SEventSkepCleanSashSkep_S
{
	LONGLONG		uidOperater;	// 操作者
};

// 链接物品
#define EVENT_SKEP_LINKSKEPGOODS								5
// 场景服（vote / execute）
/* 链接物品栏：将当物品从一个物品篮拖到链接物品栏时，在做真正执行操
作时，触发否决事件。执行操作有以下几种结果：
1、将本物品栏的物品从一个位置移动到别的位置
2、将其他实在物品栏链接到本物品栏
实在物品栏：将当物品从一个物品栏拖到实在物品栏时，在做真正执行操
作时，触发否决事件，执行操作有以下几种结果：
1、如果是链接物品，则还原物品链接关系，使本物品篮不
再链接了。成功后，发EVENT_SKEP_LINKSKEPGOODS事件
2、如果是实在物品，并且目标位置没有物品，则转移此物
品从本物品篮至本物品篮，比如从仓库拖到物品栏，成
功后发EVENT_SKEP_LINKSKEPGOODS.
3、如果是实在物品，并且目标位置有物品，则有可能需要
触发合并事件，当触发EVENT_SKEP_UNITESKEPGOODS事件，
则表示合并成功，也就是全部合并成功
4、如果不能合并，就会在两个实在物品栏之间交换物品，
先发EVENT_SKEP_EXCHANGESKEPGOODS投票事件，如果没
有否决则会执行交换事件，再发
EVENT_SKEP_EXCHANGESKEPGOODS执行事件。不再发
EVENT_SKEP_LINKSKEPGOODS事件了
//*/
struct SEventSkepLinkSkepGoods_S
{
	LONGLONG		uidOperater;	// 操作者
	LONGLONG		uidGoods;		// 物品UID

	DWORD			dwSrcSkepID;	// 源物品篮
	DWORD			dwSrcPlace;		// 源位置

	int				nTargetSkepID;	// 目标物品篮
	int				nTargetPlace;	// 目标位置
};

// 客户端（vote）
struct SEventSkepLinkSkepGoods_C
{	
	LONGLONG		uidGoods;		// 物品UID

	DWORD			dwSrcSkepID;	// 源物品篮
	DWORD			dwSrcPlace;		// 源位置

	DWORD			dwTargetSkepID;	// 目标物品篮
	int				nTargetPlace;	// 目标位置
};

// 交换物品
#define EVENT_SKEP_EXCHANGESKEPGOODS							6
// 场景服（vote / execute）
struct SEventSkepExchangeSkepGoods_S
{
	LONGLONG		uidOperater;	// 操作者

	//////////////////////////////////////////////
	DWORD			dwSkepID1;		// 物品篮1
	int				nSkepPlace1;	// 物品篮1位置
	LONGLONG		uidGoods1;		// 物品UID

	//////////////////////////////////////////////
	DWORD			dwSkepID2;		// 物品篮2
	int				nSkepPlace2;	// 物品篮2位置
	LONGLONG		uidGoods2;		// 物品UID
};

// 合并物品（只适用于全部合并）
#define EVENT_SKEP_UNITESKEPGOODS								7
// 场景服（execute）
struct SEventSkepUniteSkepGoods_S
{
	LONGLONG		uidOperater;	// 操作者
	LONGLONG		uidGoods;		// 物品UID

	DWORD			dwSkepID;		// 物品篮
	int				nPlace;			// 物品篮位置

	int				nUniteQty;		// 合并数量

	bool			bAddTime;		// 是否为添加时

	bool			bLinkTime;		// 是否为链接时
	DWORD			dwSrcSkepID;	// 链接时的源物品篮
};

// 通用物品篮拆分物品
#define EVENT_SKEP_SPLITGOODS									8
// 场景服（vote / execute）
struct SEventSkepSplitGoods_S
{
	LONGLONG		uidOperator;	// 操作者
	LONGLONG		uidGoods;		// 物品UID

	DWORD			dwSkepID;		// 物品篮ID
	DWORD			dwPlace;		// 位置	

	DWORD			dwSplitNum;		// 拆分数量	

	LONGLONG		uidNewGoods;	// 拆分后物品
};

// 客户端
struct SEventSkepSplitGoods_C
{
	LONGLONG		uidGoods;		// 物品UID

	DWORD			dwSkepID;		// 物品篮ID
	DWORD			dwPlace;		// 位置	

	DWORD			dwSplitNum;		// 拆分数量		
};

// 通用物品篮内某位置发生了变化
#define EVENT_SKEP_PLACECHANGE									9
// 客户端
struct SEventSkepPlaceChange_C
{
	DWORD			dwSkepID;		// 物品篮ID
	DWORD			dwPlace;		// 位置
};
struct SEventSkepGoods_C
{
	LONGLONG		uidGoods;		// 物品uid
	DWORD			dwPlace;		// 位置
};

// 通用物品篮内修改了容量
#define EVENT_SKEP_CHANGESIZE									10
// 客户端
struct SEventSkepChangeSize_C
{
	DWORD			dwSkepID;		// 物品篮ID
	DWORD			dwMaxSize;		// 大小
};

// 使用药品
#define EVENT_ENTITY_USELEECHDOM								11
// 客户端
struct SEventEntityUseLeechdom_C
{
	LONGLONG	uidGoods;			// 物品UID
	DWORD		dwSkepID;			// 物品篮ID
	DWORD		dwPlace;			// 物品位置
};

//场景服 组队情况变更
//子消息码 MAINACTION_MSGID_TEAM_CHANGE
struct STeamChangeInfo_SS
{
	enum
	{
		STC_Join,
		STC_Leave,
		STC_Kick,
		STC_CaptainChange,
	};

	BYTE bChangeType;     //变更类型 见上面枚举
	DWORD dwTeamID;       //队伍ID
	DWORD dwMemberID;     //变更成员ID
};

// 中心服 系统内发送服务器登录登出事件
struct SServerLoginLogout_SS
{
	enum
	{
		TYPE_INVALID = 0,
		TYPE_LOGIN,
		TYPE_LOGOUT,
		TYPE_NUM,
	};

	BYTE	byOpType;	// 操作类型，登录/登出
	BYTE	bySvrType;	// 服务器类型 ；见"DCenterServerMsg.h"的定义
	char	szIP[20];
	WORD	wPort;
	DWORD	dwParam;	// 备用参数

	SServerLoginLogout_SS()
	{
		memset(this,0,sizeof(SServerLoginLogout_SS));
	}
};

// 上马
struct SClientRideMount_CC
{
	int nHorseResID;	// 马的资源ID
	int nActionIndex; // 使用第几套动作

	SClientRideMount_CC()
	{
		memset(this,0,sizeof(SClientRideMount_CC));
	}
};

struct SChangeOption_CC
{
	int optType;	  // 配置参数
	int value; // 修改后的值

	SChangeOption_CC()
	{
		memset(this,0,sizeof(SChangeOption_CC));
	}
};

// 完成任务事件
struct SFinishTask_SS
{
	int	lActorID;	// 角色ID
	int	lTaskID;	// 任务ID
	
	SFinishTask_SS()
	{
		memset(this,0,sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////////////
// 商城相关结构体

// MSG_MIND_GET_TAB_MAX_NUM
struct SMsgActionGetTabMaxNumInfo_SC
{
	BYTE			byTotalTabNum;	// Tab页总数量

	//////////////////////////////////////////////////////////////////////////
	//...byTotalTabNum个BYTE，每个BYTE表示每个Tab页中商品的总数量
};

// MSG_MIND_GET_MIND_GOODS_LIST
struct SMsgActionGetMindGoodsList_CS
{
	BYTE			byTabIndex;		// 标签页下标
	BYTE			byBgnGoodsIdx;	// 从第几个开始
	BYTE			byPageGoodsNum;	// 请求个数
};

// MSG_MIND_GET_MIND_GOODS_LIST
struct SMsgActionMindGoodsInfoList_SC
{
	BYTE			byTabIndex;		// 标签页下标
	BYTE			byBgnGoodsIdx;	// 从第几个开始
	BYTE			byPageGoodsNum;	// 请求个数
	BYTE			byGoodsNum;		// 商品个数
};

struct SMsgActionMindGoodsInfo
{
	int			lGoodsId;			// 物品Id
	BYTE			byIsBind;			// 是否强制绑定(1:购买后强制绑定, 0:根据绑定字段决定)
	BYTE			byIsCircle;			// 是否循环(1:根据配置的上下架时间循环执行, 0:不循环)
	int			lServerTime;		// 服务器时间
	int			lUpTime;			// 上架时间(0:始终处于上架状态；限时上架格式：年+月+日+时+分+秒)
	int			lDownTime;			// 下架时间(0:始终处于上架状态；限时下架格式：年+月+日+时+分+秒)
	int			lPrice;				// 元宝原价
	int			lRebatePrice;		// 元宝折后价
	int			lBindPrice;			// 绑定元宝原价
	int			lBindRebatePrice;	// 绑定元宝折后价
};

// MSG_MIND_BUY_MIND_GOODS
struct SMsgActionBuyMindGoods_CS
{
	BYTE			byTabIndex;		// 标签页下标
	BYTE			byGoodsIndex;	// 第几个物品
	BYTE			byGoodsNum;		// 购买物品数量
	BYTE			byMoneyType;	// 使用货币类型(0:元宝,1:绑定元宝)
};

// MSG_MIND_RES_BUY_MIND_GOODS
struct SMindMoneyInfo
{
	BYTE			byMoneyType;	// 使用货币类型(0:元宝,1:绑定元宝)
	int			lMoneyNum;		// 货币数量
};
struct SMsgActionResBuyMindGoods_SC
{
	int			lGoodsId;		// 物品Id
	BYTE			byGoodsNum;		// 物品数量
	SMindMoneyInfo	sNeedMoney;		// 需要多少商城货币
};

// MSG_MIND_CONFIRM_BUY
struct SMsgActionConfirmBuy_CS
{
	BYTE			byResult;		// 是否购买(0:取消, 1:确认)
};

// MSG_MIND_RESULT_BUY_MIND_GOODS
struct SMsgActionResultBuyMindGoods_SC
{
	BYTE			byResult;		// 购买结果
	//////////////////////////////////////////////////////////////////////////
	// 如果购买成功, 带上剩余商城货币(元宝或绑定元宝)
};

// MSG_MIND_PAY_INFO_QUERY
struct SMsgActionPayInfoQuery_SC
{
	int		lPayNum;				// 返回剩余元宝数量
};

// MAINACTION_MSGID_MAP_UPDATE_EVENT
// 中心服地图/场景更新信息
struct SMapUpdateContext
{
	BOOL	bLogin;		// 是否为登录
	DWORD	dwMapID;	// 地图编号

	SMapUpdateContext()
	{
		memset(this,0,sizeof(*this));
	}
	SMapUpdateContext(BOOL bLogin_,DWORD dwMapID_)
	{
		bLogin = bLogin_;
		dwMapID = dwMapID_;
	}
};

// MAINACTION_MSGID_FRIEND_COLLECT
struct SEventFriendCollect_S
{
	s32	nFriendID;		// 好友ID

	SEventFriendCollect_S()
	{
		nFriendID = 0;
	}
};

// MAINACTION_MSGID_INSTANCE_COLLECT
struct SEventInstanceCollect_S
{
	s32	lType;		// 0:普通征收, 1:强制征收

	SEventInstanceCollect_S()
	{
		lType = 0;
	}
};

// MAINACTION_MSGID_BATTLE_END
struct SEventBattleResult_S
{
	s32	nInstanceID;		// 关卡ID
	s32	nCreatureID;		// 怪物ID
	s32	nRoundCount;		// 回合数
	BOOL bWin;				// 是否胜利

	SEventBattleResult_S()
	{
		nInstanceID = 0;
		nCreatureID = 0;
		nRoundCount = 0;
		bWin = FALSE;
	}
};

// MAINACTION_MSGID_STRENGTHEN_CARD
struct SEventStrengthenResult_S
{
	s32	nGoodID;			    // 产物
	s32	nType;				    // 合成类型
	s32	nSubType;			    // 合成子类型
	s32	nStrengthLevel;		// 配方等级
	BOOL bIsOK;				    // 是否成功

	SEventStrengthenResult_S()
	{
		nGoodID = 0;
    nType = 0;
    nSubType = 0;
    nStrengthLevel = 0;
		bIsOK = FALSE;
	}
};

// MAINACTION_MSGID_INSTANCE_FINISH
struct SEventInstanceFinish_S
{
	s32	nInstanceID;		// 关卡ID
	s32	nHardType;		// 难度

	SEventInstanceFinish_S()
	{
		nInstanceID = 0;
		nHardType = 0;
	}
};

// MAINACTION_MSGID_PRODUCE_LEVELUP
struct SEventProduceLevelUp_S
{
	s32	nSubType;			// 合成子类型

  SEventProduceLevelUp_S()
	{
    nSubType = 0;
	}
};

#pragma pack(pop)

#endif //__DMSG_SUBACTION_H__
