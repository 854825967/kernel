//
// core - server core source code.
//
// $Rev: 3059 $
// $Author: $
// $Date: 2012-01-04 14:38:27 +0800 (鍛ㄤ笁, 2012-01-04) $
//
// Adopter of Timer.
//

#ifndef __TIMER__AXIS__H
#define __TIMER__AXIS__H

#include "include/ITimeAxis.h"
#include "core/base/types.h"

namespace core {

class EventLoop;

}  // namespace core

using namespace core;

class TimerAxis : public ITimerAxis {
 public:
  TimerAxis();
  virtual ~TimerAxis();

  bool Initialize(EventLoop *loop);

  virtual void Release();
  virtual bool SetTimer(uint32 timerID, uint32 interval, ITimerHandler *handler,
         int callTimes, const char *debugInfo);
  virtual bool KillTimer(uint32 timerID, ITimerHandler *handler );

 private:
  EventLoop *loop_;
};

#endif  // __TIMER__AXIS__H

