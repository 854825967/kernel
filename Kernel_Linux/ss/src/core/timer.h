//
// core - server core source code.
//
// $Rev: 2543 $
// $Author: $
// $Date: 2011-12-23 18:37:10 +0800 (鍛ㄤ簲, 2011-12-23) $
//
// Define class Timer.
//

#ifndef __TIMER__H
#define __TIMER__H

#include <list>
#include <string>

#include "core/timer_handler.h"

namespace core {

#define TIMING_BASE_BIT 8
#define TIMING_BASE_SIZE 256
#define TIMING_GROUP_BIT 6
#define TIMING_GROUP_SIZE 64

class Timer {
 public:
  Timer(uint32 id, uint32 tick_count, uint32 call_times, TimerHandler *handler,
         const std::string &debug)
         : id_(id), tick_count_(tick_count), call_timers_(call_times),
           handler_(handler), left_base_tick_count_(0), timing_group_id_(0),
           timing_bucket_id_(0), debug_(debug) , releasing_(false) {}

  typedef std::list<Timer *> TimerList;

  inline uint32 OnSchedule() {
    this->handler_->OnTimer(this->id_);
    if(this->call_timers_ < 0) return 1;
    return --this->call_timers_;
  }

  uint32 id_;
  uint32 tick_count_;
  int call_timers_;
  TimerHandler *handler_;

  uint32 left_base_tick_count_;
  
  int timing_group_id_;				// -1: base, 0~3: group.
  size_t timing_bucket_id_;
  TimerList::iterator iterator_;

  std::string debug_;

  // Check the timer is in the releasing state.
  bool releasing_;
};

}  // namespace core

#endif  // __TIMER__H

