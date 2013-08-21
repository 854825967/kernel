#include "Header.h"
#include "LibraryDefine.h"
#include "ServerService.h"
#include "ITimeAxis.h"
#include "core/tcp_server.h"

CServerService g_ServerService;


CServerService::CServerService(void)
{
	m_bRunning = FALSE;
}

CServerService::~CServerService(void)
{
	if(this->m_pSocketService) {
		delete this->m_pSocketService;
		this->m_pSocketService = NULL;
	}
	m_ServerKernelCreateHelper.Close();
}

BOOL CServerService::Create(const ServerConfigure &configure)
{
	// 创建内核系统
	if(!m_ServerKernelCreateHelper.Create())
	{
		printf("[ERROR] %s:%d (%s) 创建服务器引擎失败!",
			__FILE__, __LINE__, __FUNCTION__);
		return FALSE;
	}

	return TRUE;
}

BOOL CServerService::StartService(u32 dwSaveTimes, LPCSTR lpszAddr, u32 dwPort, const ServerConfigure &configure, const char *id, const char *db_engine_file)
{
  if( NULL != m_pSocketService || m_bRunning )
  {
    g_pServerLog->TraceErrorLn("m_pSocketService 已经存在不为NULL!");
    return FALSE;
  }
  // 创建ServerScoket
  m_pSocketService = new CSocketService(lpszAddr,dwPort,"DBServer");
  if(NULL == m_pSocketService)
  {
    g_pServerLog->TraceErrorLn("创建网络引擎失败");
    return FALSE;
  }

  // 启动服务器端Socket
  if( !GetServerKernel()->StartServer(m_pSocketService, true))
  {
    g_pServerLog->TraceErrorLn("启动ServerSocket失败! IP = %s 端口= %d", lpszAddr, dwPort);
    return FALSE;
  }

  const char *library_proxy = configure.GetLibrary(DB_LIBRARY_PROXY);
  const char *library_engine = configure.GetLibrary(DB_LIBRARY_ENGINE);

  if(library_proxy == NULL || library_engine == NULL) {
    g_pServerLog->TraceErrorLn("启动ServerSocket失败! 得到动态库proxy或engine失败");
    return FALSE;
  }

  if(!m_DBProxyCreateHelper.Create(dwSaveTimes,(LPSTR)("hs123#iuaj"),
        g_pServerLog,
        m_pTimerAxis,
        m_pSocketService,
        library_proxy, library_engine,
        /*configure.GetDBEngine().c_str(),*/
        db_engine_file,
        configure.GetDBRequest().c_str(),
        (configure.GetDBEngineLog() + id).c_str()))
  {

    g_pServerLog->TraceErrorLn("加载数据代理失败");
    return FALSE;
  }

  g_pServerLog->TraceLn("启动数据库前端成功! IP = %s 端口= %d", lpszAddr, dwPort);

  m_bRunning = TRUE;

  return TRUE;
}

BOOL CServerService::CloseService()
{
	m_DBProxyCreateHelper.Close();
	if(m_pTimerAxis != NULL)
	{
		m_pTimerAxis->Release();
		m_pTimerAxis = NULL;	
	}
	m_bRunning = FALSE;


	return FALSE;
}

// 是否正在运行
BOOL CServerService::IsRunning(void)
{
	return m_bRunning;
}

// 能否停止
BOOL CServerService::CanStop(void)
{ 
	return m_pSocketService->CanStop();
}
