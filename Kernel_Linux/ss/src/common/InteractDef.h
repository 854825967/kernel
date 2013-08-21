#ifndef	_INTERACTDEF_H__
#define	_INTERACTDEF_H__

// 通常的交互信息消息码
#define INTERACT_MSG_COMMON					0

// 任务交互结果
#define INTERACT_MSG_RESULT					1

// 更新任务
#define INTERACT_MSG_TASK_UPDATA			2

// 接受任务
#define INTERACT_MSG_TASK_ACCEPT			3

// 删除任务
#define INTERACT_MSG_TASK_DELETE			4

// 添加公告任务
#define INTERACT_MSG_RANDOM_TASK_ADD		5

// 删除公告任务
#define INTERACT_MSG_RANDOM_TASK_DELETE		6

// 请求刷新公告任务
#define INTERACT_MSG_RANDOM_TASK_REFRESH	7

// 请求挑战任务怪物
#define INTERACT_MSG_TASK_REQ_BATTLE		8

// 领取任务奖励
#define INTERACT_MSG_TASK_GET_PRIZE			9

// 放弃任务
#define INTERACT_MSG_TASK_GIVEUP			10

// 初始化图鉴
#define INTERACT_MSG_CARDBOOK_INIT			11

// 初始化关卡
#define INTERACT_MSG_INSTANCE_INIT			12

// 隐藏任务箭头
#define INTERACT_MSG_TASK_HIDE_ARROW		13

// 隐藏任务Icon
#define INTERACT_MSG_TASK_HIDE_ICON			14

// 领取每日任务奖励
#define INTERACT_MSG_DAYTASK_GET_PRIZE		15

// 更新任务条件完成数量
#define INTERACT_MSG_TASK_UPDATA_NUM		16

// 客户端触发完成任务
#define INTERACT_MSG_TASK_CLIENT_FINISH			17

// 初始化搜集领取标志
#define INTERACT_MSG_INSTANCE_PRIZE_INIT	18

// 搜集碎片奖励标识更新
#define INTERACT_MSG_INSTANCE_PRIZE_UPDATE	19



//////////////////// S_CS_ROOT_MSGKEY_INTERACT //////////////////////
//////////////////// CS_S_ROOT_MSGKEY_INTERACT //////////////////////
#define	S_CS_INTERACT_MAIN_INT		1	//设置数值
#define CS_S_INTERACT_MAIN_INT		1

#define	S_CS_INTERACT_MAIN_STR		2	//设置字符串
#define CS_S_INTERACT_MAIN_STR		2

#pragma pack(push, 1)

// 更新任务
struct STaskUpdate
{
	int	nTaskID;			// 任务ID
	u8	bState;				// 任务状态

	STaskUpdate()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 请求刷新公告任务
struct SRandomTaskRefresh
{
	int	nTaskID[5];			// 任务ID
	s8	nLeftCount;			// 剩余次数

	SRandomTaskRefresh(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

// 领取任务奖励
struct STaskGetPrize
{
	int	nTaskID;			// 任务ID
	u8	bSelectIndex;		// 选择第几个物品

	STaskGetPrize()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 请求刷新公告任务
struct SRandomTaskRemove
{
	int	nTaskID;			// 任务ID
	s8	nLeftCount;			// 剩余次数

	SRandomTaskRemove(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

// 更新任务
struct STaskUpdateNum
{
	int	nTaskID;			// 任务ID
	int	nCount;				// 完成条件数量

	STaskUpdateNum()
	{
		memset(this, 0, sizeof(*this));
	}
};
 

//交互系统主消息码，场景服和中心服通讯时使用
struct INTERACT_MainKey
{
	BYTE byKeyMain;			//见上面的定义

	INTERACT_MainKey(void)
	{
		byKeyMain = 0;
	}
};

//设置的结构
struct S_CS_InteractSet : public INTERACT_MainKey
{
	WORD wServerID;			//发出消息的服务器ID

	int nTypeID;			//
	int nMainID;			//
	int nOwnerID;			//

	BOOL bSaveDB;			//是否保存DB

	DWORD dwKey;			//Key

	S_CS_InteractSet()
	{
		memset(this, 0, sizeof(*this));
	}
};

//设置数值的结构
struct S_CS_InteractSet_Int : public S_CS_InteractSet
{
	int nValue;				//值

	S_CS_InteractSet_Int()
	{
		byKeyMain = S_CS_INTERACT_MAIN_INT;
		nValue = 0;
	}
};

//设置字符串的结构
struct S_CS_InteractSet_Str : public S_CS_InteractSet
{
	int nStrlen;				//字符串的长度

	//... nStrlen 个字节的字符

	S_CS_InteractSet_Str()
	{
		byKeyMain = S_CS_INTERACT_MAIN_STR;
		nStrlen = 0;
	}
};

// 任务交互结果
struct S_CS_TaskInteractResult
{
	int nTaskId;			// 任务id
	int nType;				// 类型：接任务成功、失败；提交任务成功、失败；放弃任务成功、失败。具体枚举值见lua脚本
	int nParam1;			// 备用参数1
	int nParam2;			// 备用参数2

	S_CS_TaskInteractResult()
	{
		memset(this,0,sizeof(S_CS_TaskInteractResult));
	}
};

struct S_CS_CanAcceptTask
{
	enum
	{
		TYPE_INVALID = 0,
		TYPE_ADD,
		TYPE_REMOVE,
	};

	BYTE byType; // [TYPE_INVALID,TYPE_REMOVE]	
	int  nData;	 // 当byType = ADD，nData 为：添加可接任务的数量，当byType = DELETE，nData 为 任务编号
	//...
};

struct S_SC_InstancePrizeUpdate
{
	s32	nPrizeID;	// 该奖励ID已经领取
};

#pragma pack(pop)

#endif // _INTERACTDEF_H__
