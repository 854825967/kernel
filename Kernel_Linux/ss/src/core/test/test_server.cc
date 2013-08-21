//
// core - server core source code.
//
// $Rev: 5052 $
// $Author: $
// $Date: 2012-02-27 15:39:19 +0800 (周一, 2012-02-27) $
//
// Test code of server.
//

#include "core/test/test_server.h"

#include "core/core_config.h"
#include "core/server_core.h"
/*
#include "core/event_loop.h"
#include "core/inet_address.h"
#include "core/network_thread_pool.h"
#include "core/logic_loop.h"
#include "core/loop_thread.h"
*/

using namespace core;

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "You should run with a argument(configure file directory), just like:" << std::endl << "    $ ./test_server ./configure/core.xml" << std::endl;
    return 0;
  }

  //core::InitializeLogger("./log/server.log", "./log/server.log", "./log/servererror.log");
  //core::InitializeLogger("./log/info.log", "./log/info.log", "./log/error.log");

  core::CoreConfig::Init(argv[1]);
  if(core::CoreConfig::CheckFinishLoad() == false) {
    std::cout << "load configure file(" << argv[1] << ") error!" << std::endl;
    return 0;
  }

  ServerCore core;
  core.Initialize("./configure/core.xml", "./log/core/test_server.log");

  core.CreateLog(&logger, "./logic.log");

  TestServer server(InetAddress("10.10.10.105", 8888), "TestServer");
  if(core.StartServer(&server, false)) {
    core.StartLoop();
    // Stop logic model
    // notify core stop logic model.
    core.StopCore();
    // Othrers.
  } else {
    std::cout << "start server error!!" << std::endl;
  }
/*
  // Main thread loop.
  EventLoop main_loop;
  main_loop.Initialize(true);

  // Initialize tcp server.
  TestServer server(&main_loop, InetAddress("127.0.0.1", 8080), "TestServer");
  server.Initialize();

  // Initialize server networkThreadPool.
  NetworkThreadPool thread_pool(&server);
  thread_pool.Initialize();

  // Start thread_pool and server.
  thread_pool.Start();
  server.Start();

  // Logic thread.
  LogicLoop logic_loop;
  logic_loop.Initialize(server.GetLogicConnectionQueue(), NULL);
  LoopThread logic_thread(&logic_loop, "LogicThread");
  logic_thread.StartLoop();

  // Start main thread main_loop.
  main_loop.Loop();
*/ 
  return 0;
}

