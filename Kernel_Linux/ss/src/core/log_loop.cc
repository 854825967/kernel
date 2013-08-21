//
// core - server core source code.
//
// $Rev: 6775 $
// $Author: $
// $Date: 2012-04-13 17:11:45 +0800 (周五, 2012-04-13) $
//
// Define class LogLoop.
//

#include "core/log_loop.h"

#include "core/base/logging.h"

namespace core {

LogLoop::LogLoop() : log_(NULL) {}
LogLoop::~LogLoop() {}

bool LogLoop::Initialize(LogicLog *log) {
  this->log_ = log;
  return true;
}

void LogLoop::Loop() {
  this->looping_ = true;
  if(this->log_) {
    while(this->quit_ == false) {
      this->log_->Logger();
    }
  } else {
    CoreLog(ERROR, "%s:%d (%s) Failed to loop, log_ is NULL.",
           __FILE__, __LINE__, __FUNCTION__);
  }
  this->looping_ = false;
}

}  // namespace core

