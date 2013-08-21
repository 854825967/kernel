/*******************************************************************
** 文件名:  DGameEventDef.h  
** 版  权:	(C)
** 创建人:	Zipher
** 日  期:	2012/03/17
** 版  本:	1.0
** 描  述:	游戏事件消息码和结构体定义
** 应  用:  
	
**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef _DGAMEEVENTDEF_H__
#define _DGAMEEVENTDEF_H__


// 发送邮件的金钱最大值为500万
#define EMAILMONEYMAX	100000000

// 发送5万金币以上 那么给个提示
#define EMAILMONEYMSG	50000
#define MAX_GAME_M_HOLD  99999999999

#define MAX_GAMEEVENT		999

enum
{
	sc_eGameEvent_Msg = 5,	//  事件消息
	cs_eGameEvent_List,		//	获取事件列表请求	
	sc_eGameEvent_List,		//	获取事件列表返回	
	cs_eGameEvent_Update,	//	事件奖励领取请求
	sc_eGameEvent_Update,	//	事件奖励领取返回
	sc_eGameEvent_Del,		//	返回事件删除
};

enum em_MsgType
{
	em_Msg_GetListRet     = 0,   //没有邮件
	em_Msg_GetListStart   = 1,
	em_Msg_GetListIng     = 2,
	em_Msg_GetListEnd     = 3,
	em_Msg_Open = 5,			// 打开
	em_Msg_Send,
	em_Msg_Update,				// 更新
	em_Msg_Delete,				// 删除
	em_Msg_Back,
	em_Msg_GetEmailMoney		// 获取全部的金币邮件
};

#pragma pack(push, 1)


// 游戏事件的消息头
struct SGameEventMsgHeader
{
	u16	sSubCmdId;	//  子消息码
	s16	sRet;		//  返回码   
	s32	lActorID;	//  请求消息的用户id

	SGameEventMsgHeader()
	{
		memset(this,0,sizeof(*this));
	}
};

struct  SGameEventMsg
{
	SGameEventMsgHeader msgHead;
	s32					nGameEventID;
	char				msgDesz[128];

	SGameEventMsg()
	{
		memset(this,0,sizeof(*this));
	}
};

// 游戏事件的基本信息结构体
struct SGameEvent 
{
	s32		lGameEventID;			// 游戏事件ID
	s32		lSendActorID;			// 发送游戏事件的角色ID  小于零是系统事件
	char	szEventDesz[256];		// 事件描述
	char	szTime[20];				// 发送时间
	u8		byGameEventState;		// 游戏事件状态  0没有奖励领取 1未领取 2已领取
	s32		lLeftTime;				// 剩余保存天数
	char	szGoodsBuffer[36];		// 6个物品(4字节lGoodsID + 2字节lGoodsNum)
	
	SGameEvent()
	{
		memset(this,0,sizeof(*this));
	}
};

// 请求GameEvent列表
struct SGameEventList 
{
	SGameEventMsgHeader head;
	s32					lActorID;

	SGameEventList()
	{
		memset(this,0,sizeof(*this));
	}
};

// 游戏事件列表返回
// 60天以前发送未查看的和3天前已经查看过的删除
struct SGameEventListRes 
{
	SGameEventMsgHeader head;
	SGameEvent			sGameEvent;

	SGameEventListRes()
	{
		memset(this,0,sizeof(*this));
	}
};

// 更新游戏事件 只有领取之后才更新 ，DB要把钱和物品删除了
// 可以在正文上写 领取日至(哦) 在重新把数据物品数据输出
struct SGameEventUpdate 
{
	SGameEventMsgHeader head;
	s32					lGameEventID;				// 游戏事件ID

	SGameEventUpdate()
	{
		memset(this,0,sizeof(*this));
	}
};

// 更新返回
struct SGameEventUpdateRes 
{
	SGameEventMsgHeader head;
	s32					lGameEventID;				// 游戏事件ID

	SGameEventUpdateRes()
	{
		memset(this,0,sizeof(*this));
	}
};

// 删除一个游戏事件
struct  SGameEventDel
{
	SGameEventMsgHeader head;
	s32		lGameEventID;			// 游戏事件ID

	SGameEventDel()
	{
		memset(this,0,sizeof(*this));
	}
};

struct	SGameEventInfo
{
	s32		lGameEventID;			// 游戏事件ID
	u8		byGameEventState;		// 游戏事件状态  0没有奖励领取 1未领取 2已领取
	s32		lLeftTime;				// 剩余保存天数
	char	szGoodsBuffer[36];		// 36个物品(4字节lGoodsID + 2字节lGoodsNum)

	SGameEventInfo()
	{
		memset(this,0,sizeof(*this));
	}
};

struct	SGameEventGoodsInfo
{
	s32		lGoodsID;				// 物品ID
	u16		lGoodsNum;				// 物品数量

	SGameEventGoodsInfo()
	{
		memset(this,0,sizeof(*this));
	}
};


#pragma pack(pop)

typedef std::vector<SGameEvent>	 VEC_GAMEEVENT;	

#endif // _DGAMEEVENTDEF_H__
