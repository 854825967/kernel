 /*******************************************************************
** 文件名:	DMsgKeyRoot.h
** 版  权:	(C)  
** 创建人:	庄雪锋
** 日  期:	2011/07/19
** 版  本:	1.0
** 描  述:	主消息码的定义
** 应  用:  服务器，客户端
** 备  注:  该消息码 包括登陆主消息码，选择角色相关息码 等一切通信的主消息码
**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef __D_MSGKEY_MAIN_H__
#define __D_MSGKEY_MAIN_H__


//////////////////////////////////////////////////////////////////////////
///////////////// 登陆主消息码（根：CMD_ROOT_LOGIN） /////////////////////
// 用户登录
#define ROOTLOGIN_SC_MAIN_USERLOGIN			1
#define ROOTLOGIN_CS_MAIN_USERLOGIN			1

// 调至选择人物态
#define ROOTLOGIN_SC_MAIN_TURNSELECT		2
#define ROOTLOGIN_CS_MAIN_TURNSELECT		2

// 队列位置，从0开始
#define ROOTLOGIN_SC_MAIN_LISTNUM			3
#define ROOTLOGIN_CS_MAIN_LISTNUM			3

// 发送客户端版本号
#define ROOTLOGIN_SC_MAIN_CLIENTVER			4
#define ROOTLOGIN_CS_MAIN_CLIENTVER			4

// 发送登录随机数
#define ROOTLOGIN_SC_MAIN_ENTERCODE			5
#define ROOTLOGIN_CS_MAIN_ENTERCODE			5

// 需要验证矩阵卡
#define ROOTLOGIN_SC_MAIN_SUPERCARD			7
#define ROOTLOGIN_CS_MAIN_SUPERCARD			7

// 玩家游戏世界角色分布情况
#define ROOTLOGIN_SC_MAIN_ACTOR_NUM			8

// 游戏世界当前在线人数分布情况
#define ROOTLOGIN_SC_MAIN_WORLD_ONLINE		9

// 登录中心通知客户端发送账号密码
#define ROOTLOGIN_SC_NOTICE_LOGIN			10


//////////////////////////////////////////////////////////////////////////
///////////// 选择角色主消息码（根：CMD_ROOT_SELECTACTOR） ///////////////
// 选择人物
#define ROOTSELECTACTOR_SC_MAIN_SELECT			1
#define ROOTSELECTACTOR_CS_MAIN_SELECT			1

// 将调到运行态
#define ROOTSELECTACTOR_SC_MAIN_TURNRUN			2
#define ROOTSELECTACTOR_CS_MAIN_TURNRUN			2

// 创建角色
#define ROOTSELECTACTOR_SC_MAIN_CREATEACTOR		3
#define ROOTSELECTACTOR_CS_MAIN_CREATEACTOR		3

// 删除角色
#define ROOTSELECTACTOR_SC_MAIN_DELETEACTOR		4
#define ROOTSELECTACTOR_CS_MAIN_DELETEACTOR		4

// 发送登录随机数
#define ROOTSELECTACTOR_SC_MAIN_ENTERCODE		5
#define ROOTSELECTACTOR_CS_MAIN_ENTERCODE		5

// 发送MAC
#define ROOTSELECTACTOR_SC_MAIN_MAC				6
#define ROOTSELECTACTOR_CS_MAIN_MAC				6

// 已登录玩家跳转服务器 开始 
#define ROOTSELECTACTOR_SC_MAIN_JUMP_START		7
#define ROOTSELECTACTOR_CS_MAIN_JUMP_START		7

//逻辑对像行为事件，如移动、攻击、伤害、动作、消失等
#define ROOTTHING_SC_MAIN_ACTION				4
#define ROOTTHING_CS_MAIN_ACTION				4

//////////////////////////////////////////////////////////////////////////
///////////// 选择角色主消息码（根：CMD_ROOT_ENTITY） ///////////////

#endif //__D_MSGKEY_MAIN_H__

