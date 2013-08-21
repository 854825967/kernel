//
// core - server core source code.
//
// $Rev: 6033 $
// $Author: $
// $Date: 2012-03-16 14:43:23 +0800 (周五, 2012-03-16) $
//
// Define class NetworkThreadPool.
//

#include "core/network_thread_pool.h"

#include "core/core_config.h"
#include "core/schedule_loop.h"
#include "core/tcp_server.h"
#include "core/base/logging.h"

namespace core {

NetworkThreadPool::NetworkThreadPool(TCPServer *server)
       : schedule_loop_(NULL), server_(server) {}

NetworkThreadPool::~NetworkThreadPool() {
  if(this->schedule_thread_ != NULL) {
    delete this->schedule_thread_;
    this->schedule_thread_ = NULL;
  }
  if(this->schedule_loop_ != NULL) {
    delete this->schedule_loop_;
    this->schedule_loop_ = NULL;
  }
}

bool NetworkThreadPool::Initialize() {
  // Schedule thread.
  this->schedule_loop_ = new ScheduleLoop(this);
  if(this->schedule_loop_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate schedule_loop_", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  if(this->schedule_loop_->Initialize() == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize schedule_loop_", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  this->schedule_thread_ = new LoopThread(this->schedule_loop_, "ScheduelThread");
  if(this->schedule_loop_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate schedule_thread_", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
/*
  // Verify thread group.
  if(this->verify_threads_.Initialize(CoreConfig::GetThread()->verify_number_, "VerifyThread") == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize verify_threads_", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
*/
  // Message thread group.
  if(this->message_threads_.Initialize(CoreConfig::GetThread()->message_number_, "MessageThread", false) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize message_threads_", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  return true;
}

void NetworkThreadPool::Start() {
  this->schedule_thread_->StartLoop();
  // this->verify_threads_.Start();
  this->message_threads_.Start();
}

void NetworkThreadPool::Stop() {
  // this->message_threads_.Stop();
  // Not force quit, let schedule thread complete to quit.
  this->schedule_thread_->StopLoop(false);
  this->message_threads_.Stop();
}

}  // namespace core

