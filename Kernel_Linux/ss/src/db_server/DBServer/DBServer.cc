#include "Header.h"
#include "ServerConfigure.h"
#include "ServerService.h"

int main(int argc, char *argv[]) 
{
	// 配置选项
	char szOptionName[256];
	char server_configure[256];
	s32 server_id = 1;

	if(argc == 5) {
		if(strncmp(argv[1], "-configure", 10) == 0 &&
				strncmp(argv[3], "-auto", 5) == 0) {
			strncpy(server_configure, argv[2], sizeof(server_configure));
			server_id = atoi(argv[4]);
		} else if(strncmp(argv[3], "-configure", 10) == 0 &&
				strncmp(argv[1], "-auto", 5) == 0) {
			strncpy(server_configure, argv[4], sizeof(server_configure));
			server_id = atoi(argv[2]);
		} else {
			std::cout << "Bad argument, run it like this: " << 
				"./your_binary -auto 1 -configure ./configure/server.xml" << std::endl;
			return 0;
		}
	} else {
		std::cout << "Bad argument, run it like this: " << 
			"./your_binary -auto 1 -configure ./configure/server.xml" << std::endl;
		return 0;
	}

	ServerConfigure configure;
	if(configure.Load(server_configure) == false) 
	{
		printf("[ERROR] Load configure file error!!");
		return 0;
	}

  char id[10];
  snprintf(id, sizeof(id), "_%d", server_id);

	strncpy(LogFileName, (configure.GetLogicLog() + id).c_str(), sizeof(LogFileName));

	// 创建ServerService
	if( !g_ServerService.Create(configure) )
	{
		printf("[ERROR] ServerService Create error!!");
		return 0;
	}

	IServerKernel* pServerKernel = g_ServerService.GetServerKernel();
	if(pServerKernel == NULL) 
	{
		printf("[ERROR] GetServerKernel error!!");
		return 0;
	}


	// 初始化内核系统
	if(!pServerKernel->Initialize(configure.GetCoreDir(), configure.GetCoreLog() + id, configure.CheckDeamon())) 
	{
		printf("[ERROR] %s:%d (%s) 服务器引擎初始化失败!\n",
			__FILE__, __LINE__, __FUNCTION__);
		return 0;
	}

	if(pServerKernel->CreateLog(&g_pServerLog, configure.GetLogicLog() + id) == false) 
	{
		printf("[ERROR] CreateLog error!!\n");
		return 0;
	}

	ITimerAxis *timer = NULL;

	// 创建时间轴管理器
	if(pServerKernel->CreateTimerAxis(&timer) == false) {
		g_pServerLog->TraceErrorLn("[ERROR] %s:%d (%s) 创建时间轴失败!",
			__FILE__, __LINE__, __FUNCTION__);
		return FALSE;
	}

  g_ServerService.SetTimerAxis(timer);

  std::string server_ip;
  u16 server_port;
  u32 save_time;
  std::string db_engine;
  if(configure.GetLocalServerInfo(server_id, server_ip, server_port, save_time, db_engine) == false) {
		g_pServerLog->TraceErrorLn("[ERROR] Error server id(%d)", server_id);
		return 0;
	}

	if(g_ServerService.StartService(save_time, server_ip.c_str(), server_port, configure, id, db_engine.c_str()))
	{
		g_pServerLog->TraceLn("StartService %s \n", server_ip.c_str());
		pServerKernel->StartLoop();
		pServerKernel->StopCore();
	}

	// g_ServerService.CloseService();
	g_pServerLog->Release();

	return 0;
}

