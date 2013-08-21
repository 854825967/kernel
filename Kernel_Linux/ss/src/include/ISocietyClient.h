/*******************************************************************
** 文件名:  ISocietyClient.h
** 版  权:	(C)  
** 创建人:	庄雪锋
** 日  期:	2011/08/17
** 版  本:	1.0
** 描  述:	社会服客户端接口
** 应  用:  该接口用于其他服务器(目前是游戏服务器)连接社会服务器，提供相应相关服务
********************************************************************/

#ifndef _ISOCIETYCLIENT_H__
#define _ISOCIETYCLIENT_H__
#include "GameSys.h"
#include "IOsApi.h"
#include "DSocietyServerMsg.h"

struct ITimerAxis;
struct ILog;
struct IServerKernel;

// ISocietyClient接口宿主者需要实现的接口
struct ISocietyClientOwner
{
  virtual ~ISocietyClientOwner() {}
	// 获取应用服务器信息
	// nLen为szName缓冲区的大小
	// nType参考 DCenterServerMsg.h 的定义
	virtual BOOL GetOwnerInfo(LPSTR szName, s32 nLen, u32 &nID, u8 &nType, u16 &wPort) = 0;

	// 应用服务器登录处理
	// bResult, TRUE表示登录成功; FALSE表示登录失败
	// szDesc, 登录失败时的描述信息
	virtual void OnSocietySvrLogin(BOOL bResult, LPCSTR szDesc) = 0;
	
	// 应用服务器退出处理
	virtual void OnSocietySvrLogout(void) = 0;

	// 发给某个角色数据的处理
	virtual void OnSocietySvrSendToActor(s32 lActorID, LPCSTR pBuf, s32 nLen) = 0;
	
	// 全服务器广播数据的处理
	virtual void OnSocietySvrBroadcastData(LPCSTR pBuf, s32 nLen) = 0;

	// 发给某个房间数据的处理
	virtual void OnSocietySvrSendDataToRoom(s32 lRoomID, LPCSTR pBuf, s32 nLen) = 0;

	// 接收数据处理(数据来源:社会服)
	virtual void OnRecvFromSocietySvr(LPCSTR pBuf, s32 nLen) = 0;
};

// 社会服客户端接口
struct ISocietyClient
{
  virtual ~ISocietyClient() {}
	// 关闭客户端
	virtual void Close() = 0;

	// 销毁社会服客户端
	virtual void Release(void) = 0;

	// 角色更新列表, 应用服务器登录成功后，需要调用此方法进行更新
	// bFirst 用于分批次更新时，表明是否第一批更新
	virtual BOOL ActorUpdateList(u16 wNum, PActorBaseInfoEx pActorList, u8 byFirst) = 0;
	
	// 角色登录 opType = 0：上线登陆，1：跨游戏服登陆 
	virtual BOOL ActorLogin(s32 lActorID, LPCSTR szActorName, u8 opType, s32 nReserve) = 0;

	// 角色退出 opType = 1：登出，2：登出（跨游戏服的情况）
	virtual BOOL ActorLogout(s32 lActorID, u8 opType, s32 nReserve) = 0;
	
	// 向全世界广播消息
	virtual BOOL BroadcastData(LPCSTR pBuf, s32 nLen) = 0;
	
	// 向插件模块发送消息
	virtual BOOL SendToPlugin(u16 wEventID, u8 bSrcTypeID, LPCSTR pBuf, s32 nLen) = 0;

	// 获取所有服务器总在线人数
	virtual int GetTotalOnlineNum(void) = 0;
	
	// 获取服务器的在线人数
	virtual int GetServerOnlineNum(SServerKey &Key) = 0;

	// 角色属性更新
	virtual BOOL ActorPropertyUpdate(SActorPropertyUpdatePacket &packet) = 0;
};

// 创建社会服客户端(输出函数)
extern "C" BOOL CreateSocietyClient(ISocietyClient **ppSocietyClient,
	ISocietyClientOwner *pAppServer, ITimerAxis *pTimeAxis, ILog *pLog, IServerKernel *pServerKernel,
	LPCSTR szSocietyServerIP, u16 wSocietyServerPort);

typedef BOOL (*ProcCreateSocietyClient)(ISocietyClient **ppSocietyClient, 
	ISocietyClientOwner *pAppServer, ITimerAxis *pTimeAxis, ILog *pLog, IServerKernel *pServerKernel,
	LPCSTR sSocietyServerIP, WORD wSocietyServerPort);
// 社会服客户端创建辅助类
class CSocietyClientHelper
{
public:
	// 构造函数
	CSocietyClientHelper()
	{
		m_pSocietyClient = NULL;
	}

	// 析构函数
	~CSocietyClientHelper()
	{
		Close();
	}

	// 创建社会服客户端
	BOOL Create(ISocietyClientOwner *pAppServer, ITimerAxis *pTimeAxis,ILog *pLog,
		IServerKernel *pServerKernel,LPCSTR sSocietyServerIP, WORD wSocietyServerPort,
    const char *so)
	{
    if(this->m_DynamicLoader.LoadLibrary(so) == FALSE)
    {
      return FALSE;
    }

    ProcCreateSocietyClient proc = NULL;
    proc = (ProcCreateSocietyClient)(this->m_DynamicLoader.GetProcAddress("CreateSocietyClient"));
    if(proc == NULL)
      return FALSE;

    return proc(&(this->m_pSocietyClient), pAppServer, pTimeAxis, pLog, pServerKernel,
			sSocietyServerIP, wSocietyServerPort);
	}

	// 释放社会服客户端
	void Close(void)
	{
		if (m_pSocietyClient != NULL)
		{
			m_pSocietyClient->Release();
			m_pSocietyClient = NULL;
		}

		m_DynamicLoader.FreeLibrary();
	}

public:
	ISocietyClient	*m_pSocietyClient;	// 社会服客户端指针

private:
	CDynamicLoader	m_DynamicLoader;	// 动态库加载
};

#endif//_ISOCIETYCLIENT_H__
