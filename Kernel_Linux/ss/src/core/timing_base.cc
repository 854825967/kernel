//
// core - server core source code.
//
// $Rev: 6313 $
// $Author: $
// $Date: 2012-03-28 15:21:03 +0800 (周三, 2012-03-28) $
//
// Define class TimingBase.
//


#include "core/timing_wheel.h"

namespace core {

TimingBase::TimingBase() : current_tick_(0), wheel_(NULL) {}
TimingBase::~TimingBase() {}

bool TimingBase::OnSchedule() {
  Timer::TimerList::iterator iterator = this->bucket_[this->current_tick_].begin();
  for(; iterator != this->bucket_[this->current_tick_].end();) {
    Timer *timer = *iterator;
    iterator = this->bucket_[this->current_tick_].erase(iterator);
    timer->iterator_ = this->bucket_[this->current_tick_].end();
    if(timer->releasing_)
      continue;
    // Timer callback.
    if(timer->OnSchedule() > 0) {
      // If need reschedule, first to check timer's valid(OnSchedule maybe Unschedule timer)
      if(timer->releasing_ == false) {
        this->wheel_->ScheduleImplement(timer, timer->tick_count_);
      }
    }
  }
  if(++this->current_tick_ >= TIMING_BASE_SIZE) {
    this->current_tick_ = 0;
    return true;
  }
  return false;
}

}  // namespace core

