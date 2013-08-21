#ifndef __DLOGINSERVERMSG_H__
#define __DLOGINSERVERMSG_H__

#define USER_NAME_MAX_LEN		33
#define PASSWORD_MAX_LEN		41
#define ACTOR_NAME_MAX_LEN		13

#pragma pack(push, 1)

// 版本号
struct WS_VERSION			
{
	union
	{	
		struct
		{
			s16 sV4,sV3,sV2,sV1;	// sV1(最大)->sV4(最小)
		}data_sep;

		s64 data_com;
	};

	WS_VERSION()
	{
		data_com = 0;
	}
};

// 登录现场(C->S)
struct SSUserLoginContext
{
	s64		lSessionID;		// 会话ID
	char	szSerialNO[20];	// 网卡序列号

	SSUserLoginContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 客户端发送账号密码到登录中心
struct SSUserLoginContextEx
{
	char			szUserName[USER_NAME_MAX_LEN];	// 用户名
	char			szPassword[41];	
	s64			nVerificationCode;				// 验证码
	WS_VERSION	sVersion;						// 客户端版本号

	SSUserLoginContextEx()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 登录随机数现场(S->C)
struct SSEnterCodeContext
{
	u32		dwEnterCode;	// [0,99]
	char		RandStrBuf[32];	// 随机串

	SSEnterCodeContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 创建角色现场(C->S)
struct SSActorCreateContext
{
	char		szName[ACTOR_NAME_MAX_LEN];		// 角色名
	u8		byIconID;						// 角色头像
	u8		bySex;							// 性别

	SSActorCreateContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 玩家申请了矩阵卡(S->C)
struct SSuperCardPos_SC
{
	s32		lPos_1;				// 位置1
	s32		lPos_2;				// 位置2
	s32		lPos_3;				// 位置3

	SSuperCardPos_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 矩阵卡的值(C->S)
struct SSuperCardValue_CS
{
	char		szValue_1[81];		// 密码字符串1
	char		szValue_2[81];		// 密码字符串2
	char		szValue_3[81];		// 密码字符串3

	SSuperCardValue_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 用户登录返回(S->C)
struct SSUserLoginRes
{
	s64	 	qwUserID;			// 用户ID
	s32	 	lActorNum;			// 角色数目
	s32		lPromptFlag;		// 默认值返回0，返回1表示要弹出提示信息的窗口，具体内容会通过lPromptMsg提供
	char		lPromptMsg[256];	// 提示信息
	u32		m_dwVersion;		// 服务器版本，见VERSION_NUMBER定义

	SSUserLoginRes()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 角色信息现场(S->C)
struct SSActorInfo
{
	char		szName[13];			// 角色名
	s32		lActorID;			// 角色ID
	char		szServerIP[33];		// 所在服务器IP
	u16		wPort;				// 所在服务器端口
	u8		lKillFlag;			// 封号标志，0：正常，1：封号

	SSActorInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 删除角色现场(C->S)
struct SSActorDeleteContext
{
	s32		lActorID;	// 角色ID
	char		szKeyMD5[PASSWORD_MAX_LEN];	// 二级密码的 MD5

	SSActorDeleteContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 排队位置现场
struct SSListLocationContext
{
	s32		 nLocation;	// 位置

	SSListLocationContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ROOTSELECTACTOR_CS_MAIN_JUMP_START
// 已登录玩家服务器跳转开始(进入场景前) - 输入结构体
struct SLoginUserJumpStartContext
{
	s64		qwUserID;		// 用户ID
	char	 	szRandBuf[128];	// 客户端标示串Buffer

	SLoginUserJumpStartContext()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ROOTSELECTACTOR_SC_MAIN_JUMP_START
// 已登录玩家服务器跳转开始(进入场景前) - 输出结构体
struct SLoginUserJumpStartRes
{
	s32		lReturn;			// 返回值 1 成功
	s64		qwUserID;			// UserID
	u32		ValidationCode[4];	// 验证码
	char		szRand[16];			// 客户端标示串

	SLoginUserJumpStartRes()
	{
		memset(this, 0, sizeof(*this));
	}
};

#pragma pack(pop)

#endif // __DLOGINSERVERMSG_H__
