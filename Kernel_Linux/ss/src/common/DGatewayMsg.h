#ifndef _DGATEWAYMSGFOMANT_H__
#define _DGATEWAYMSGFOMANT_H__

#include "DMsgKeyRoot.h"
#include "DServerDef.h"

#define	GATEWAY_CSMSG_LOGIN_APPSERVER		1			// 网关登录 应用服
#define GATEWAY_SCMSG_APPSERVERINFO			2			// 应用服信息

#define GATEWAY_CSMSG_SENDTO_SCENE			11			// 网关发送数据场景
#define GATEWAY_SCMSG_SENDTO_SCENE			12			// 场景发送数据到网关

#define GATEWAY_SCBATCHMSG_SENDTO_SCENE		13			// 场景发送数据到网关(转发给多个客户端)
#define GATEWAY_SCBATCHMSG_SENDTO_CLIENT	14			// 向所有的客户端广播一个消息

#define GATEWAY_OR_SCENE_ACTOR_LOGIN		20			//  帐号登陆
#define GATEWAY_OR_SCENE_ACTOR_DATA			21			//  客户端 通过网关转发到场景的数据头
#define GATEWAY_OR_SCENE_ACTOR_LOGOUT		22			//  场景通知 网关关闭客户端 
#define GATEWAY_OR_SCENE_USER_LOGOUT		23			//	网关通知场景服 客户端登出

#define GATEWAY_SCMSG_CHANGE_SCENE_SERVER	24			//	场景服向网关请求切换场景服

#define GATEWAY_SCMSG_AGAIN_SELECT_SECENE	25			//  场景服通知网关为玩家重新选择场景服


#pragma pack(push, 1)

// 网关消息头 
struct SGateWayMsgHead
{
	//  
	BYTE		m_wKeyRoot;
};

// 网关登陆 AppServer
struct SGateWayLoginServer : public SGateWayMsgHead
{
	char	szIP[17];	// IP 地址 
	WORD	wProt;		// 服务端口
	DWORD	nGateWayID; // 网关ID

	SGateWayLoginServer()
	{
		memset(this,0,sizeof(*this));
		m_wKeyRoot = GATEWAY_CSMSG_LOGIN_APPSERVER;
	}
};

// 网关登陆 AppServer
struct SAppServerInfo: public SGateWayMsgHead
{
	BYTE	nType;			// 应用服务器类型 
	DWORD	nAppID;			// 该类型的服务器ID
	char	szAppName[32];	// 服务名
	WORD	Port;			// 端口
	SAppServerInfo()
	{
		memset(this,0,sizeof(*this));
		m_wKeyRoot = GATEWAY_SCMSG_APPSERVERINFO;
	}
};

// 客户端到场景服消息头
struct SC2SMsgHead : public SGateWayMsgHead
{
	ClientID	clientId;	 // 客户端识别ID
	WORD		m_wMainMsg;	 // 主消息码
	WORD		m_wSubMsgId; // 子消息ID 
};

//帐号登陆，已通过验证
struct SUSER_LOGIN_V : public SGateWayMsgHead
{
	ClientID 	lIdenID;		// 客户端识别ID 
	s64		qwUserDBID;		// 帐号DB ID
	int		nActorDBID;		// 角色DB ID
	int		nTurnSType;		// 跳转类型，取值见IVestibule.h的 EN_LOGIN_USER_JUMP_TYPE
	char		RandMac16[16];		// 客户端发送上来的随机串
	char		ipAddress[16];		// 登录Ip地址
	char		szSerialNO[20];		// 网卡MAC
	int		nLobbyServerID;		// 大厅服务器ID(登录或者跳转至大厅服务器，值为0)

	SUSER_LOGIN_V()
	{
		memset(this, 0, sizeof(*this));
		m_wKeyRoot = GATEWAY_OR_SCENE_ACTOR_LOGIN;
	}
};


//struct IActor;


//玩家角色下线
struct SUSER_LOGOUT : public SGateWayMsgHead
{
	ClientID	lIdenID;		// 客户端识别ID 
	WORD		wReason;		// 登出原因
	s64 qwUserDBID;			//帐号DB ID
	int nActorDBID;				//角色DB ID
	//IActor *pMaster;			//玩家角色
	int nTurnSType;				//跳转类型，取值见IVestibule.h的 EN_LOGIN_USER_JUMP_TYPE

	char szIP[16];				//服务器IP
	WORD wPort;				//服务器开放的端口
	DWORD ValidationCode[4];		//验证码

	SUSER_LOGOUT()
	{
		memset(this, 0, sizeof(*this));
		m_wKeyRoot = GATEWAY_OR_SCENE_USER_LOGOUT;
 	}
};


struct SKickoutClient: public SGateWayMsgHead
{
	ClientID 	lIdenID;		// 客户端识别ID 
	DWORD dwReason;

	SKickoutClient()
	{
		memset(this, 0, sizeof(*this));
		m_wKeyRoot = GATEWAY_OR_SCENE_ACTOR_LOGOUT;
	}
};

//玩家角色切换场景服
struct SNextZone : public SGateWayMsgHead
{ 
	s32		dwRoomID;		// 目标房间ID

	SNextZone()
	{
		memset(this, 0, sizeof(*this));
	}
};

//玩家角色切换场景服(场景服->网关)
struct SChangeZone : public SGateWayMsgHead
{
	ClientID 	lIdenID;		// 客户端识别ID 
	s64 qwUserID;		// 账号Id
	char 		szRand[16];		// 客户端标示串
	char		szIP[16];		// 服务器IP
	WORD		wPort;			// 服务器开放的端口
	DWORD		ValidationCode[4];	// 验证码
	int		nLobbyServerID;		// 大厅服务器ID(大厅服跳转至房间服，必须填)

	SChangeZone()
	{
		memset(this, 0, sizeof(*this));
		m_wKeyRoot = GATEWAY_SCMSG_CHANGE_SCENE_SERVER;
	}
};

// 场景服通知网关，为角色重新选择服务器
struct SAgainSelectScene : public SGateWayMsgHead
{
	ClientID 	lIdenID;		// 客户端识别ID 

	SAgainSelectScene()
	{
		memset(this, 0, sizeof(*this));
		m_wKeyRoot = GATEWAY_SCMSG_AGAIN_SELECT_SECENE;
	}
	SAgainSelectScene(ClientID _lIden)
	{
		memset(this, 0, sizeof(*this));
		m_wKeyRoot = GATEWAY_SCMSG_AGAIN_SELECT_SECENE;
		lIdenID = _lIden;
	}
};


struct SBatchMsgToClient: SGateWayMsgHead
{
	WORD	nDataLen;
	char	pData[1];
};


#pragma pack(pop)


#endif // _DGATEWAYMSGFOMANT_H__
