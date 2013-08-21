//
// core - server core source code.
//
// $Rev: 4466 $
// $Author: $
// $Date: 2012-02-09 13:04:59 +0800 (鍛ㄥ洓, 2012-02-09) $
//
// Define class TimingBase.
//

#ifndef __TIMING__BASE__H
#define __TIMING__BASE__H

#include "core/timer.h"

namespace core {

class TimingWheel;

class TimingBase {
 public:
  explicit TimingBase();
  ~TimingBase();

  inline uint32 GetCurrentTick() const { return this->current_tick_; }

  inline void Initialize(TimingWheel *wheel) {
    this->wheel_ = wheel;
  }

  inline void Schedule(Timer *timer, uint32 tick_count) {
    timer->timing_bucket_id_ = (tick_count + this->current_tick_) % TIMING_BASE_SIZE;
    timer->iterator_ = this->bucket_[timer->timing_bucket_id_].insert(
           this->bucket_[timer->timing_bucket_id_].end(), timer);
  }


  inline Timer::TimerList &GetBucket(uint32 id) {
    return this->bucket_[id];
  }

  bool OnSchedule();

 private:
  uint32 current_tick_;
  Timer::TimerList bucket_[TIMING_BASE_SIZE];
  TimingWheel *wheel_;
};

}  // namespace core

#endif  // __TIMING__BASE__H

