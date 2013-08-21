#ifndef _ICONNECTSINK_H__
#define _ICONNECTSINK_H__
#include "DErrorCode.h"

#define MAX_CONNECT_NUM		10200	//每个场景服支持的最大客户端连接数

//玩家客户端连接状态
enum CONN_STATE
{
	enConnState_Login	= 0,				// 登录态
	enConnState_Running,					// 运行态	
	enConnState_Logout,						// 退出存盘态
	enConnState_Max
};

//连接槽消息
enum
{
	enConnSink_UserLogin_V		= 0,		// 帐号登陆，已通过验证
	enConnSink_UserLogout,					// 角色下线
	enConnSink_NextWorld,					// 切换地图
	enConnSink_NextZone,					// 跨进程切换地图
	enConnSink_Select,						// 角色小退
	enConnSink_AgainSelectSceneSvr,			// 重新选择场景服
	enConnSink__Max
};

//关闭与玩家客户端的连接的原因
enum CLOSE_CONN
{
	enClose_Conn_Max,						//待添加
};

//连接sink接口的定义
struct IConnectSink
{
	virtual ~IConnectSink() {}

	//取得当前的连接状态
	virtual u8 GetConnectSinkState(void) = 0;

	//取得此客户端连接对应的游戏服Id
	virtual u32 GetGameID(void) = 0;	

	//////////////////////////////////////////////////////////////////////////
	// 描  述：启用本对象实例
	// 输  入：dwSocketID为连接的Socket ID，
	//         dwConnectIndex为连接序号（由CConnectSinkManager分配）
	// 返回值：成功返回TRUE
	//////////////////////////////////////////////////////////////////////////
	virtual BOOL StartConnectSink(u32 dwConnectIndex) = 0;

	//对象实例回收时，清除现有的数据
	virtual BOOL Clean(BOOL bSink) = 0;

	//返回TRUE表示此对象实例已被使用
	virtual BOOL IsHaveUsed(void) = 0;

	//通知玩家出错（ErrorMsg为错误消息），并断开与玩家的连接（dwSocketID为玩家连接的SocketID）
	virtual	BOOL KickUser(SC_ERRORCODE_MSGFORMAT &ErrorMsg) = 0;

	//给玩家客户端发送数据
	virtual void SendData(LPCSTR pData, s32 nDataLen) = 0;

	//消息
	virtual void OnMessage(u32 dwMessage, LPCSTR pData, s32 nDataLen) = 0;	

	//关闭与玩家客户端的连接
	virtual BOOL CloseConnects(CLOSE_CONN enReason) = 0;

	//获取客户端的IP和端口信息
	virtual BOOL GetClientInfo(LPSTR szIP, u16 &wPort) = 0;

	//nIndex: 请求流水号
	//nRetCode 取值于 EN_VESTIBULE_RET
	virtual	void OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID, LPSTR pOutData,
               s32 nOutDataLen, LPSTR pInData = NULL, s32 nInDataLen = 0) = 0;
};

#endif //_ICONNECTSINK_H__

