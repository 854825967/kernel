//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7029 $
// $Author: than $
// $Date: 2012-04-24 13:35:39 +0800 (鍛ㄤ簩, 2012-04-24) $
//
// Main of gateway server.
//

#include "GateWayServiceMgr.h"
#include "Header.h"
#include "ServerConfigure.h"
#include "ILog.h"

int main(int argc, char *argv[]) {
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
  if(configure.Load(server_configure) == false) {
    printf("[ERROR] Load configure file error!!");
    return 0;
  }

  strncpy(LogFileName, configure.GetLogicLog().c_str(), sizeof(LogFileName));

  std::string server_ip;
  u16 server_port;
  u32 user_max_number;

  if(configure.GetLocalServerInfo(server_id, server_ip, server_port, user_max_number) == false) {
    printf("[ERROR] Error server id(%d)", server_id);
    return 0;
  }

  g_GateWayServiceMgr = new CGateWayServiceMgr(/*core::InetAddress(*/server_ip.c_str(),
         server_port/*)*/, "GatewayServer");

  if(g_GateWayServiceMgr == NULL) {
    printf("[ERROR] Allocate g_GateWayServiceMgr error!!");
    return 0;
  }

  if(g_GateWayServiceMgr->Initialize(server_id,
         core::InetAddress(configure.GetCenterServerIP(), configure.GetCenterServerPort()),
         user_max_number, configure) == false) {
    printf("[ERROR] Initialize g_GateWayServiceMgr error!!\n");
    return 0;
  }

  IServerKernel *server_kernel = g_GateWayServiceMgr->GetServerKernel();
  g_pServerLog = g_GateWayServiceMgr->GetServerLog();

  if(server_kernel->StartServer(g_GateWayServiceMgr, true)) {
    server_kernel->StartLoop();
    server_kernel->StopCore();
  } else {
    g_pServerLog->TraceErrorLn("[ERROR] StartServer error!!");
    return 0;
  }

  if(g_GateWayServiceMgr) {
    delete g_GateWayServiceMgr;
    g_GateWayServiceMgr = NULL;
  }
}

