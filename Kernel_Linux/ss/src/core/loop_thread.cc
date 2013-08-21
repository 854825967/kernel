//
// core - server core source code.
//
// $Rev: 8717 $
// $Author: $
// $Date: 2012-06-27 11:57:44 +0800 (周三, 2012-06-27) $
//
// Define class LoopThread.
//

#include "core/loop_thread.h"

#include "core/base/logging.h"

namespace core {

LoopThread::LoopThread(BaseLoop *loop, const std::string &name, bool joinable)
       : loop_(loop),
         thread_(name, function::Bind(&LoopThread::Loop, this), joinable) {
//  function::Function0<void> callback;
//  callback = function::Bind(&LoopThread::StartLoop, this);
//  thread_.SetThreadFunction(callback);
}

LoopThread::~LoopThread() {}

void LoopThread::StartLoop() {
  this->thread_.Start();
}

void LoopThread::StopLoop(bool force_quit) {
  if(this->loop_->GetLooping()) {
    if(force_quit) this->GetLoop()->Quit();
    this->loop_->Stop();
    this->loop_->Wakeup();
    this->thread_.Join();
  } else {
    this->thread_.Join();
  }
}

}  // namespace core

