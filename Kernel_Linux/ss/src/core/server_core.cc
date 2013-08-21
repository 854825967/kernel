//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: $
// $Date: 2012-08-28 19:48:18 +0800 (周二, 2012-08-28) $
//
// Wapper of server core.
//

#include "core/server_core.h"

#include <signal.h>

#include "core/client_thread_pool.h"
#include "core/core_config.h"
#include "core/event_loop.h"
#include "core/log_loop.h"
#include "core/logic_log.h"
#include "core/logic_loop.h"
#include "core/loop_thread.h"
#include "core/network_thread_pool.h"
#include "core/tcp_client.h"
#include "core/tcp_server.h"
#include "core/base/logging.h"
#include "core/function/function.h"
#include "core/tools/EventEngine.h"
#include "core/tools/LogTool.h"
#include "core/tools/ScriptLoader.h"
#include "core/tools/TimerAxis.h"

namespace core {

ServerCore::ServerCore()
       : main_loop_(NULL),
         logic_loop_(NULL),
         logic_thread_(NULL),
         log_instance_(NULL),
         log_loop_(NULL),
         log_thread_(NULL),
         client_thread_pool_(NULL),
         network_thread_pool_(NULL),
         server_ring_(NULL),
         client_ring_(NULL),
         server_(NULL) {}

ServerCore::~ServerCore() {
  this->StopLogLoop();

  if(this->client_thread_pool_) delete this->client_thread_pool_;
  if(this->network_thread_pool_) delete this->network_thread_pool_;
  if(this->server_ring_) {
    delete this->server_ring_;
  }
  if(this->client_ring_) delete this->client_ring_;
  if(this->logic_loop_) delete this->logic_loop_;
  if(this->logic_thread_) delete this->logic_thread_;
  if(this->log_instance_) delete this->log_instance_;
  if(this->log_loop_) delete this->log_loop_;
  if(this->log_thread_) delete this->log_thread_;
  if(this->main_loop_) delete this->main_loop_;
}

bool ServerCore::Initialize(const std::string &core_config_file, const std::string &core_log_file, bool daemon_flag) {
  InitializeLogger(core_log_file, core_log_file, core_log_file);

  if(daemon_flag == true) {
    if(daemon(1, 1) != 0) {
      std::cout << "failed to daemon." << std::endl;
      return false;
    }
  }

  core::CoreConfig::Init(core_config_file);
  if(core::CoreConfig::CheckFinishLoad() == false) {
    std::cout << "load configure file(" << core_config_file << ") error!" << std::endl;
    return false;
  }

  // Main loop
  this->main_loop_ = new EventLoop();
  if(this->main_loop_ == NULL || this->main_loop_->Initialize(true) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize EventLoop.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Ring queue.
  this->server_ring_ = new RingQueueLogic(
         CoreConfig::GetAcceptor()->ring_size_, NONBLOCKING);
  this->client_ring_ = new RingQueueLogic(
         CoreConfig::GetAcceptor()->ring_size_, NONBLOCKING);

  // Initialize client thread pool.
  this->client_thread_pool_ = new ClientThreadPool();
  if(this->client_thread_pool_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate CientThreadPool.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  if(this->client_thread_pool_->Initialize() == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize CientThreadPool.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Initialize logic loop.
  this->logic_loop_ = new LogicLoop();
  if(this->logic_loop_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate LogicLoop.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  if(this->logic_loop_->Initialize(this->server_ring_, this->client_ring_) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize LogicLoop.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Initialize logic thread.
  this->logic_thread_ = new LoopThread(this->logic_loop_, "LogicThread");
  if(this->logic_thread_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate logic thread.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Initialize log 
  this->log_instance_ = new LogicLog();
  if(this->log_instance_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate LogicLog.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  if(this->log_instance_->Initialize(".log") == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize LogicLog.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Initialize log loop.
  this->log_loop_ = new LogLoop();
  if(this->log_loop_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate LogLoop.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  if(this->log_loop_->Initialize(this->log_instance_) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize LogLoop.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Initialize log thread.
  this->log_thread_ = new LoopThread(this->log_loop_, "LogThread");
  if(this->log_thread_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate log thread.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // this->main_loop_->Signal(SIGTERM, function::Bind(&ServerCore::Stopping, this));

  this->log_thread_->StartLoop();

  return true;
}

bool ServerCore::StartServer(TCPServer *server, bool daemon_flag) {
  // Initialize tcp server.
  if(server->Initialize(this->main_loop_, this->server_ring_) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize TCPServer.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Initialize network thread pool.
  this->network_thread_pool_ = new NetworkThreadPool(server);
  if(this->network_thread_pool_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate NetworkThreadPool.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  if(this->network_thread_pool_->Initialize() == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize NetworkThreadPool.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Start network thread pool and server.
  this->network_thread_pool_->Start();
  if(server->Start() == false) {
    this->Stopping();
    return false;
  }

  this->server_ = server;

  return true;
}

bool ServerCore::StartClient(TCPClient *client) {
  // Initialize client.
  if(client->Initialize(this->main_loop_, this->client_thread_pool_, this->client_ring_) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize client.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  // Start client.
  client->Start();

  return true;
}

void ServerCore::StartLoop() {
  this->client_thread_pool_->Start();

  this->logic_loop_->SetServerStopCallback(function::Bind(&TCPServer::OnStop, this->server_));
  this->logic_thread_->StartLoop();
  this->main_loop_->Loop();
}

EventLoop *ServerCore::GetServerEventLoop() {
  return this->main_loop_;
}

bool ServerCore::CreateTimerAxis(ITimerAxis **ppTimerAxis) {
  *ppTimerAxis = new TimerAxis;
  if(*ppTimerAxis == NULL) return false;
  return ((TimerAxis *)(*ppTimerAxis))->Initialize(this->logic_loop_);
}

bool ServerCore::CreateEventEngine(IEventEngine **ppEventEngine) {
  *ppEventEngine = new CEventEngine;
  if(*ppEventEngine == NULL) return false;
  return true;
}

bool ServerCore::CreateScriptLoader(IScriptLoader** ppScriptLoader) {
  *ppScriptLoader = new CScriptLoader;
  if(*ppScriptLoader == NULL) return false;
  return true;
}

bool ServerCore::CreateLog(ILog** ppLog, const std::string &log_file) {
  this->log_instance_->SetFileName(LOG_TYPE_COMMON, log_file);
  *ppLog = new LogTool;
  if(*ppLog == NULL) return false;
  return ((LogTool *)(*ppLog))->Initialize(this->log_instance_);
}

bool ServerCore::CreateDetailLog(const std::string &instance, const std::string &train,
    const std::string &battle, const std::string &item) {
  this->log_instance_->SetFileName(LOG_TYPE_INSTANCE, instance);
  this->log_instance_->SetFileName(LOG_TYPE_TRAIN, train);
  this->log_instance_->SetFileName(LOG_TYPE_BATTLE, battle);
  this->log_instance_->SetFileName(LOG_TYPE_GOODS, item);
  return true;
}

void ServerCore::Stopping() {
  // this->main_loop_->Unsignal(SIGTERM);
  CoreLog(INFO, "%s:%d (%s) Server core stopped.", __FILE__, __LINE__, __FUNCTION__);
  if(this->server_) this->server_->Stop();
  this->main_loop_->Quit();
  // this->logic_thread_->StopLoop();
}

void ServerCore::StopCore() {
  if(this->logic_thread_) {
    this->logic_thread_->StopLoop();
  }
  if(this->logic_loop_) {
    delete this->logic_loop_;
    this->logic_loop_ = NULL;
  }

  // After logic thread stop, callback OnStop().
  // if(this->server_) this->server_->OnStop();

  this->StopLogLoop();

  if(this->network_thread_pool_) {
    this->network_thread_pool_->Stop();
  }
  if(this->client_thread_pool_) {
    this->client_thread_pool_->Stop();
  }
}

void ServerCore::StopLogLoop() {
  if(this->log_thread_) {
    this->log_thread_->StopLoop(true);
    if(this->log_loop_) {
      this->log_loop_->Stop();
      if(this->log_instance_) this->log_instance_->Stop();
      delete this->log_loop_;
      this->log_loop_ = NULL;
    }
    delete this->log_thread_;
    this->log_thread_ = NULL;
  }
}

void ServerCore::StopClient(core::TCPClient *client) {
  this->logic_loop_->RemoveClient(client->GetConnectionTask());
  client->Stop();
}

uint32 ServerCore::GetTickCount() const {
  return this->logic_loop_->GetTimeTick().GetSmallSystemMsec();
}

}  // namespace core

extern "C" bool CreateServerKernel(IServerKernel **server_kernel) {
  *server_kernel = new ServerCore;
  if(*server_kernel == NULL) return false;
  else return true;
}


