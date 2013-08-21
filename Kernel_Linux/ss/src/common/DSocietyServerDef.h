/*******************************************************************
** 文件名:  DSocietyServerDef.h
** 版  权:	(C)  
** 创建人:	廖怀富
** 日  期:	2010/5/5
** 版  本:	1.0
** 描  述:	社会服宏定义
** 应  用:  服务器
** 备  注:
********************************************************************/

#ifndef _DSOCIETYSERVERDEF_H__
#define _DSOCIETYSERVERDEF_H__

//////////////////////////////////////////////////////////////////////////
enum
{
	LEN_MAX_ACTOR_NAME			= 13,	// 角色名长度
	LEN_MAX_SVR_NAME			= 32,	// 服务器名字
	LEN_MAX_ACTOR_LIST_UPDATE	= 100,	// 一次更新角色列表的最大个数 
	LEN_MAX_SOCIETY_SVR_DESC	= 128,	// 社会服描述长度
	LEN_MAX_SERVER_IP			= 16,	// ip长度

	SOCIETY_INVALID_ACTORID		= 0,	// 无效角色ID

	// 服务器类型定义
	SOCIETY_ST_LOGIN			= 0,	// 登录服
	SOCIETY_ST_GATEWAY			= 1,	// 网关服
	SOCIETY_ST_ROOM				= 2,	// 房间服
	SOCIETY_ST_SOCIETY			= 3,	// 社会服
	SOCIETY_ST_CENTER			= 4,	// 中心服 
	SOCIETY_ST_LOBBY			= 5,	// 大厅服
};

#endif//_DSOCIETYSERVERDEF_H__

