#ifndef _SERVERSERVICE_H_
#define _SERVERSERVICE_H_
#include "IServerKernel.h"
#include "IDBProxy.h"
#include "ServerConfigure.h"
#include "SocketService.h"

class CServerService 
{
public:
	// 构造函数
	CServerService(void);

	// 析构函数
	~CServerService(void);

	// 创建DB前端
	BOOL Create(const ServerConfigure &configure);

	// 启动服务
	BOOL StartService(u32 dwSaveTimes, LPCSTR lpszAddr, u32 dwPort, const ServerConfigure &configure, const char *id, const char *db_engine);

	// 关闭服务
	BOOL CloseService();

	// 是否正在运行
	BOOL IsRunning(void);

	// 获取内核指针
	IServerKernel *GetServerKernel(){return  m_ServerKernelCreateHelper.server_kernel_;}

	// 获取时间轴指针
	ITimerAxis *GetTimerAxis(){return m_pTimerAxis;}
	void SetTimerAxis(ITimerAxis *timer){ m_pTimerAxis = timer; }

	// 数据库代理指针
	IDBProxy *GetDBProxy(){return m_DBProxyCreateHelper.m_pDBProxy;}

	// 能否停止
	BOOL CanStop(void);

private:
	CServerKernelCreateHelper	m_ServerKernelCreateHelper;		// 引擎内核加载器
	CDBProxyCreateHelper		m_DBProxyCreateHelper;			// DB代理加载器
	ITimerAxis	*				m_pTimerAxis;					// 定时器指针
	CSocketService*				m_pSocketService;
	BOOL						m_bRunning;
};

extern CServerService g_ServerService;

#endif //_SERVERSERVICE_H_

