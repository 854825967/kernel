/******************************************************************
** 文件名:	DErrorCode.h
** 创建人:	 
** 版  权:	(C) 
** 日  期:	 
** 版  本:	0.1
** 描  述:	错误码定义，服务器发下去的错误码统一由客户端的错误码中心来处理, 
**          这样客户端就不用到处关心错误码处理。可扩展性也好
** 应  用:  服务器，客户端

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef __D_ERROR_CODE_H__
#define __D_ERROR_CODE_H__
#include "GameSys.h"
#include "DMsgKeyRoot.h"

enum eErrorCode
{
		ERROR_CODE_INVALIDUSER	=	1,		// 无此用户
		ERROR_CODE_NOACTOR,					// 无此角色
		ERROR_CODE_KEYERROR,				// 密码错误
		ERROR_CODE_PADLOCK,					// 帐号被禁
		ERROR_CODE_PADLOCKACTOR,			// 角色已被禁止登陆
		ERROR_CODE_LOGINBUSY,				// 登陆服务器忙
		ERROR_CODE_GAMESERVERBUSY,			// 游戏服务器忙
		ERROR_CODE_REPEATER,				// 此账号已登陆
		ERROR_CODE_CREATEFAILED,			// 创建人物失败
		ERROR_CODE_DELETEFAILED,			// 删除人物失败
		ERROR_CODE_DBFAILED,				// 数据库操作失败
		ERROR_CODE_PUTACTORDATA,			// 提交的角色数据不正确
		ERROR_CODE_KICK,					// 服务器主动踢人
		ERROR_CODE_USER_REGISTER,			// 注册帐号失败
		ERROR_CODE_ADD_PP,					// 添加密保资料失败
		ERROR_CODE_GAME_WORLD_EMPTY,		// 没有可登录的游戏世界
		ERROR_CODE_USER_CENTER_DISCONNECT,	// 通知客户端，用户中心断开连接了
		ERROR_CODE_PACKET_FULL,				// 背包满
		ERROR_CODE_CHANNEL,					// 错误透明通道
		ERROR_CODE_CHAT,					// 聊天泡泡通道
		ERROR_CODE_SCROLLTEXT,				// 走马灯通道
    ERROR_CODE_COMMON,        // 通用
};		

#pragma pack(push, 1)	

//错误消息结构
//注意：错误描述只能保存128个字节，建议使用 lstrcpyn() 拷贝错误描述
struct SC_ERRORCODE_MSGFORMAT
{
	u16 m_wKeyRoot;				//CMD_ROOT_ERROR
	u16	m_wSubCode;				//0
	u16 m_wErrorCode;			//错误码（见上面的定义）
	char  m_szErrorDesc[128];		//错误描述

	SC_ERRORCODE_MSGFORMAT(u16 wErrorCode)
	{
		m_wKeyRoot = CMD_ROOT_ERROR;
		m_wSubCode = 0;
		m_wErrorCode = wErrorCode;
		m_szErrorDesc[0] = 0;
	}

	SC_ERRORCODE_MSGFORMAT(void)
	{
		m_wKeyRoot = CMD_ROOT_ERROR;
		m_wSubCode = 0;
		m_wErrorCode = 0;
		m_szErrorDesc[0] = 0;
	}
};

#pragma pack(pop)


#endif //__D_ERROR_CODE_H__
