/******************************************************************
** 文件名:	TeamDef.h
** 版  权:	(C)  
** 创建人:	庄雪锋
** 日  期:	2011-08-18
** 版  本:	1.0
** 描  述:	组队模块用到的类型和定义
** 应  用:  社会服 组队模块

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef _TEAMDEF_H__
#define _TEAMDEF_H__

#include "DServerDef.h"

#pragma pack(push, 1)

const int TEAM_MEMBERS_MIN = 1;		// 组队需要的最少成员
const int TEAM_MEMBERS_MAX = 3;		// 组队可以达到的最多成员
const int TEAM_INVALID_ID = 0;		// 无效的队伍ID

enum TEAM_RESULT
{	
	TEAM_OPPOSE,			// 反对
	TEAM_AGREE,				// 同意
	TEAM_NO,				// 否
	TEAM_YES,				// 是
	TEAM_CREATING,			// 正在创建
	TEAM_CREATED,			// 已经创建
};

enum TeamSet
{
	TEAM_NONE = 0,      //没有队伍
	TEAM_MEMBER,        //有队伍
	TEAM_CAPTAIN,       //是队长
};


// 组队模块的消息码(请求,应答,通知)
enum TEAM_CMD
{
	// 邀请玩家组队(C->S S->C)
	TR_INVITE = 0,
	// 被邀请玩家应答 (C->S S->C)
	TA_INVITE,

	// 申请加入队伍
	TR_APPLY,
	TA_APPLY,

	// 离开队伍
	TR_LEAVE,
	TN_LEAVE,

	// 改变队长
	TR_CHANGE_CAPTAIN,
	TN_CHANGE_CAPTAIN,

	// 队员列表
	TN_MEMBER_LIST,	

	// 玩家加入
	TN_JOINED,

	// 查询是否组队
	TR_QUERY,
	TA_QUERY,

	// 数据转发
	TR_FORWARD,

	// 队员登入登出
	TN_LOGINOUT,

	// 队伍解散
	TN_DISBAND,

	// UID改变
	TN_UIDCHANGED,

	// 组队的操作消息
	TN_MESSAGE,

	// 请求更新组队信息
	TR_UPDATE,

	// 组队更新通知
	TN_UPDATE,

	// 邀请组队2
	TR_INVITE2,

	TR_APPLY2,  // 申请2

    TR_TEAMATEDATA,   //队友数据请求
	TN_TEAMATEDATA,   //队友数据下发

	TR_TEAMATEPOS,   //队友位置数据请求
	TN_TEAMATEPOS,   //队友位置数据下发
};

// 队友信息
struct STeammate
{
	u32		dwId;			// 角色ID
	UID		uid;			// UID
	char	szName[13];		// 名称	
	BOOL	bOnline;		// 是否在线
	STeammate()
	{
		memset(this,0,sizeof(*this));
	}
};

struct STeamDataRequest
{
	u8		nCmd;
	u32		dwActorID;               // 请求者id
	u32		dwTeammateID;            // 需要请求数据的队友ID

	STeamDataRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

// 请求更新队友属性信息
struct STeammateData
{
	u8		nCmd;
	u32		dwRequesterID;  // 请求者ID
    u32		dwID;			// 队友ID
	s32		iLevel;			// 当前等级

	STeammateData()
	{
		memset(this,0,sizeof(*this));
	}

};

// 请求更新队友属性信息
struct STeammatePosition
{
	u8		nCmd;
	u32		dwRequesterID;  // 请求者ID
	u32		dwID;			// 队友ID
	s32		nPositon;		// 队友位置

	STeammatePosition()
	{
		memset(this,0,sizeof(*this));
	}
};

//------------------------------------------------------------------

// 组队模块的邀请玩家请求
struct STeamInviteRequest
{
	u8		nCmd;							// 命令
	u32		dwInvitorId;					// 邀请者ID
	s32		nInvitorHead;					// 邀请者头像
	s8		szInvitorName[13];				// 邀请者名称
	u32		dwInviteeId;					// 被邀请者ID
	STeamInviteRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的邀请玩家请求
struct STeamInviteRequest2
{
	BYTE nCmd;							// 命令
	DWORD dwInvitorId;					// 邀请者ID
	int nInvitorHead;					// 邀请者头像
	char szInvitorName[32];				// 邀请者名称
	char szInviteeName[32];				// 被邀请者名字
	STeamInviteRequest2()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的申请加入请求
struct STeamApplyRequest
{
	BYTE nCmd;							// 命令
	DWORD dwApplicantId;				// 申请者ID
	int nApplicantHead;					// 申请者头像
	char szApplicantName[32];			// 申请者名称
	DWORD dwTargetId;					// 接受者ID	
	STeamApplyRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的踢除玩家请求
struct STeamKickRequest
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	DWORD dwKickedId;					// 被踢者ID
	DWORD dwKickerId;                   // 踢人者ID
	STeamKickRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的玩家离开请求
struct STeamLeaveRequest
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	DWORD dwLeaveId;					// 离开者ID
	STeamLeaveRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的更改队长请求
struct STeamChangeCaptainRequest
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	DWORD dwNewCaptainId;				// 新队长的ID
	DWORD dwRequestActorId;             // 发出请求的玩家ID
	STeamChangeCaptainRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的查询玩家是否组队请求
struct STeamQueryRequest
{
	BYTE nCmd;							// 命令
	DWORD dwSenderId;					// 发送者ID
	DWORD dwQueryId;					// 要查询的玩家ID
	DWORD dwCampID;						// 阵营ID
	STeamQueryRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的转发请求
struct STeamForward
{
	BYTE nCmd;							// 命令
	DWORD dwReceiverId;					// 接收者ID
	STeamForward()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块更新队伍信息请求
struct STeamUpdateRequest
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	STeamUpdateRequest()
	{
		memset(this,0,sizeof(*this));
	}
};

//------------------------------------------------------------------

// 组队模块的邀请玩家应答
struct STeamInviteAnswer
{
	BYTE nCmd;							// 命令		
	STeammate invitor;					// 邀请者
	STeammate invitee;					// 被邀请者
	BYTE nResult;						// 结果
	STeamInviteAnswer()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的申请加入应答
struct STeamApplyAnswer
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	STeammate applicant;				// 申请者
	BYTE nResult;						// 结果
	STeamApplyAnswer()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的更改分配方式应答
struct STeamChangeAllotModeAnswer
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	DWORD dwPlayerId;					// 应答者ID	
	BYTE nNewAllotMode;					// 分配方式
	BYTE nResult;						// 结果
	STeamChangeAllotModeAnswer()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的查询玩家是否组队应答
struct STeamQueryAnswer
{
	BYTE nCmd;							// 命令
	DWORD dwQueryId;					// 被查询玩家的ID
	BYTE nResult;						// 结果
	DWORD dwCampID;						// 阵营ID
	STeamQueryAnswer()
	{
		memset(this,0,sizeof(*this));
	}
};

//------------------------------------------------------------------

// 组队模块的队员列表通知
struct STeamMemberListNotice
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	BYTE nTeamState;					// 队伍状态
	DWORD dwCaptainId;					// 队长ID	
	BYTE nMemberCount;					// 队员个数
	STeammate members[1];				// 队员列表
	STeamMemberListNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的玩家加入通知
struct STeamJoinedNotice
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	STeammate joined;					// 加入者	
	STeamJoinedNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的玩家登入登出通知
struct STeamLoginoutNotice
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	STeammate member;					// 队员
	STeamLoginoutNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的踢除玩家通知
struct STeamKickNotice
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	DWORD dwKickedId;					// 被踢者ID
	STeamKickNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的玩家离开通知
struct STeamLeaveNotice
{
	BYTE nCmd;							// 命令
	DWORD dwTeamId;						// 队伍ID
	DWORD dwLeaveId;					// 离开者ID
	STeamLeaveNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的改变队长通知
struct STeamChangeCaptainNotice
{
	BYTE nCmd;							// 命令	
	DWORD dwTeamId;						// 队伍ID
	DWORD dwNewCaptainId;				// 新队长ID	
	STeamChangeCaptainNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的解散队伍通知
struct STeamDisbandNotice
{
	BYTE nCmd;							// 命令	
	DWORD dwTeamId;						// 队伍ID
	STeamDisbandNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// UID改变通知
struct STeamUidChangedNotice
{
	BYTE nCmd;							// 命令	
	DWORD dwTeamId;						// 队伍ID
	DWORD dwPlayerId;					// 玩家ID
	UID uidPlayer;						// 玩家新的UID
	STeamUidChangedNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

////////////////////////////////////////////////////////////////////////////
//寻求组队
// 寻求组队设置
struct SRecruitTeamSetUp
{
	BYTE  nCmd;							// 设置		
	DWORD dwActorId;                    // 自己Id
	BYTE  bInvite;					    // 组队邀请设置
	BYTE  bApply;						// 入队申请设置
	SRecruitTeamSetUp()
	{
		memset(this,0,sizeof(*this));
	}
};

// 队伍信息,用于直接显示
struct STeamMessage
{
	BYTE nCmd;							// 命令	
	WORD wLength;						// 信息长度
	char szText[1];						// 信息文本
	STeamMessage()
	{
		memset(this,0,sizeof(*this));
	}
};

// 队伍信息,用于直接显示
struct STeamMessageNew
{
	BYTE nCmd;							// 命令	
	int dwPlayerId;					// 接收信息的角色ID
	WORD wLength;						// 信息长度
	char szText[1];						// 信息文本
	STeamMessageNew()
	{
		memset(this,0,sizeof(*this));
	}
};

// 发送给客户端的组队更新通知,这个主要用在客户端发送根其他关心队伍改变的模块
struct STeamUpdateNotice
{
	BYTE nLastMemberCount;   // 上次队伍的成员个数
	UID  uidLastMembers[TEAM_MEMBERS_MAX];  // 上次队伍成员的UID
	BYTE nCurMemberCount;    // 当前队伍成员的个数
	UID  uidCurMembers[TEAM_MEMBERS_MAX];   // 当前队伍成员的UID
	STeamUpdateNotice()
	{
		memset(this,0,sizeof(*this));
	}
};

// 组队模块的申请加入请求
struct STeamApplyRequest2
{
	BYTE nCmd;							// 命令
	DWORD dwApplicantId;				// 申请者ID
	int nApplicantHead;					// 申请者头像
	int  nClass;                        // 职业
	int  nLevel;                        // 等级
	char szApplicantName[32];			// 申请者名称
	DWORD dwTeamId;					    // 接受的队伍ID

	STeamApplyRequest2()
	{
		memset(this,0,sizeof(*this));
	}
};

#pragma pack(pop)

#endif // _TEAMDEF_H__
