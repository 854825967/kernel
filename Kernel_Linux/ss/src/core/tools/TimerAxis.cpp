//
// core - server core source code.
//
// $Rev: 6708 $
// $Author: $
// $Date: 2012-04-12 17:41:05 +0800 (鍛ㄥ洓, 2012-04-12) $
//
// Adopter of Timer.
//

#include "core/tools/TimerAxis.h"

#include <string>

#include "core/event_loop.h"
#include "core/base/logging.h"

TimerAxis::TimerAxis() {}
TimerAxis::~TimerAxis() {}

bool TimerAxis::Initialize(EventLoop *loop) {
  this->loop_ = loop;
  return true;
}

void TimerAxis::Release() { delete this; }

bool TimerAxis::SetTimer(uint32 timerID, uint32 interval, ITimerHandler *handler,
       int callTimes, const char *debugInfo) {
  this->loop_->AddTimer(timerID, interval, callTimes, handler, std::string(debugInfo));
  return true;
}

bool TimerAxis::KillTimer(uint32 timerID, ITimerHandler *handler ) {
  this->loop_->RemoveTimer(timerID, handler);
  return true;
}


