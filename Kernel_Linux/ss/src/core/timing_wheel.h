//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Define class TimingWheel.
//

#ifndef __TIMING__WHEEL__H
#define __TIMING__WHEEL__H

#include <vector>

#include "core/channel.h"
#include "core/version.h"
#include "core/timing_base.h"
#include "core/timing_group.h"
#include "core/base/time_tick.h"
#include "core/base/types.h"
#include "core/function/function.h"

namespace core {

class Timer;
class TimerHandler;
class EventLoop;

class TimingWheel {
  // typedef std::set<Timer *> TimerReleaseList;
  typedef std::vector<Timer *> TimerReleaseList;

 public:
  TimingWheel(uint32 tick_msec, EventLoop *loop);
  ~TimingWheel();

  // Start and set the timestamp.
  bool Start(const TimestampMillisecond &now);

  // Schedule for user.
  void Schedule(uint32 id, uint32 tick_count, int call_times,
         TimerHandler *handler, const std::string &debug);
  
  // Schedule for TimingWheel/TimingBase/TimingGroup.
  bool ScheduleImplement(Timer *timer, uint32 tick_count);
  
  // Unschedule for user.
  void Unschedule(uint32 id, TimerHandler *handler);
  
  // Callback.
  void OnSchedule(const TimeTick &now);
  
  // Forwrad to previous group.
  bool Forward(int group_id, Timer *timer);

  bool ResetTimer();

  // Release the memory
  void TimerRelease();

 private:
  TimingBase base_;
  TimingGroup group_[4];
  
  uint32 tick_msec_;
  TimestampMillisecond timestamp_;

  EventLoop *loop_;

#ifdef __CORE_TIMERFD__
  int timer_fd_;
  Channel *channel_;
#else
  uint32 patch_timer_;
#endif  // __CORE_TIMERFD__

  TimerReleaseList releases_;
};

}  // namespace core

#endif  // __TIMING__WHEEL__H

