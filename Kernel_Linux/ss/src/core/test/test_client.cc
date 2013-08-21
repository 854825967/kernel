//
// core - client core source code.
//
// $Rev: 5052 $
// $Author: $
// $Date: 2012-02-27 15:39:19 +0800 (周一, 2012-02-27) $
//
// Test code of client.
//

#include "core/test/test_client.h"

#include "core/server_core.h"

/*
#include "core/client_thread_pool.h"
#include "core/core_config.h"
#include "core/event_loop.h"
#include "core/inet_address.h"
#include "core/logic_loop.h"
#include "core/loop_thread.h"
*/

using namespace core;

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "You should run with a argument(configure file directory), just like:" << std::endl << "    $ ./test_client ./configure/core.xml" << std::endl;
    return 0;
  }

  // core::InitializeLogger("./log/client.log", "./log/client.log", "./log/client.log");
  // core::InitializeLogger("./log/info.log", "./log/info.log", "./log/error.log");

  core::CoreConfig::Init(argv[1]);
  if(core::CoreConfig::CheckFinishLoad() == false) {
    std::cout << "load configure file(" << argv[1] << ") error!" << std::endl;
    return 0;
  }

  ServerCore core;
  core.Initialize("./configure/core.xml", "./log/core/test_client.log");

  TestClient client(InetAddress("10.10.10.105", 8888), "TestClient");
  if(core.StartClient(&client)) {
    core.StartLoop();
    core.StopCore();
  }
  std::cout << "client end!!" << std::endl;
/*
  // Main thread loop.
  EventLoop main_loop;
  main_loop.Initialize(true);

  // client.
  TestClient client(&main_loop, InetAddress("127.0.0.1", 8080), "TestServer");

  // Client networkThreadPool.
  ClientThreadPool thread_pool;
  thread_pool.Initialize();

  // Ringqueue between logic thread and main thread, use for logic thread to get tcp task from main thread.
  // Main thread will detection connection's successful.
  BoundlessEntityRingQueue<ConnectionTask> ring(CoreConfig::GetAcceptor()->ring_size_, ring_queue::NONBLOCKING);
  client.Initialize(&thread_pool, &ring);

  // Start thread_pool and client.
  thread_pool.Start();
  client.Start();

  // Logic thread.
  LogicLoop logic_loop;
  logic_loop.Initialize(NULL, client.GetLogicConnectionQueue());
  LoopThread logic_thread(&logic_loop, "LogicThread");
  logic_thread.StartLoop();

  // Start main thread main_loop.
  main_loop.Loop();
*/
  return 0;
}

