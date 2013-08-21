//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: $
// $Date: 2012-08-28 19:48:18 +0800 (周二, 2012-08-28) $
//
// Define class TimingWheel.
//

#include "core/timing_wheel.h"

#include <assert.h>

#ifdef __CORE_TIMERFD__
#include <sys/timerfd.h>
#else  // __CORE_TIMERFD__
#include "core/event_loop.h"
#endif  // __CORE_TIMERFD__

#include "core/timer.h"
#include "core/base/logging.h"

namespace core {

TimingWheel::TimingWheel(uint32 tick_msec, EventLoop *loop)
       : tick_msec_(tick_msec),
         loop_(loop)
#ifndef __CORE_TIMERFD__
         { this->patch_timer_ = 0; }
#else  // __CORE_TIMERFD__
        , channel_(NULL) {
  int timer_fd = ::timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
  if(timer_fd == -1) {
    CoreLog(ERROR, "%s:%d (%s) timerfd_create error.",
           __FILE__, __LINE__, __FUNCTION__);
  } else if((this->channel_ = new Channel(this->loop_, timer_fd)) == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed to allocate channel.",
           __FILE__, __LINE__, __FUNCTION__);
    ::close(timer_fd);
  }
}
#endif  // __CORE_TIMERFD__

TimingWheel::~TimingWheel() {
  this->TimerRelease();
#ifdef __CORE_TIMERFD__
  if(this->channel_) {
    this->channel_->DisableAll();
    ::close(this->channel_->GetFd());
    delete this->channel_;
  }
#endif  // __CORE_TIMERFD__
}

bool TimingWheel::Start(const TimestampMillisecond &now) {
#ifdef __CORE_TIMERFD__
  if(this->channel_ == NULL) return false;

  this->channel_->SetReadCallback(function::Bind(&TimingWheel::OnSchedule, this));
  this->channel_->EnableRead();
#else  // __CORE_TIMERFD__
  this->loop_->LoopInCallbackAttachTimeTick(function::Bind(&TimingWheel::OnSchedule, this));
#endif  // __CORE_TIMERFD__

  this->timestamp_ = now;

  this->base_.Initialize(this);
  this->group_[0].Initialize(this, 0);
  this->group_[1].Initialize(this, 1);
  this->group_[2].Initialize(this, 2);
  this->group_[3].Initialize(this, 3);

  return this->ResetTimer();
}

void TimingWheel::Schedule(uint32 id, uint32 tick_count, int call_times, TimerHandler *handler, const std::string &debug) {
  if(handler->timer_list_.find(id) != handler->timer_list_.end()) {
    // Reschedule to delete previous one.
    this->Unschedule(id, handler);
  }
  Timer *timer = new Timer(id, tick_count, call_times, handler, debug);
  if(timer == NULL) {
    return ;
  }
  if(this->ScheduleImplement(timer, tick_count) == false) {
    delete timer;
  }
}

bool TimingWheel::ScheduleImplement(Timer *timer, uint32 tick_count) {
  if(tick_count < TIMING_BASE_SIZE) {
    timer->timing_group_id_ = -1;
    this->base_.Schedule(timer, tick_count);
  } else if(tick_count < (1 << (TIMING_BASE_BIT + TIMING_GROUP_BIT))) {
    timer->left_base_tick_count_ = tick_count % TIMING_BASE_SIZE;
    timer->timing_group_id_ = 0;
    this->group_[0].Schedule(timer, tick_count);
    timer->left_base_tick_count_ += this->base_.GetCurrentTick();
  } else if(tick_count < (1 << (TIMING_BASE_BIT + 2 * TIMING_GROUP_BIT))) {
    timer->left_base_tick_count_ = tick_count % (TIMING_BASE_SIZE * TIMING_GROUP_SIZE);
    timer->timing_group_id_ = 1;
    this->group_[1].Schedule(timer, tick_count);
    timer->left_base_tick_count_ += this->group_[0].GetCurrentTick() * TIMING_BASE_SIZE;
  } else if(tick_count < (1 << (TIMING_BASE_BIT + 3 * TIMING_GROUP_BIT))) {
    timer->left_base_tick_count_ = tick_count % (TIMING_BASE_SIZE * TIMING_GROUP_SIZE * TIMING_GROUP_SIZE);
    timer->timing_group_id_ = 2;
    this->group_[2].Schedule(timer, tick_count);
    timer->left_base_tick_count_ += this->group_[1].GetCurrentTick() * TIMING_BASE_SIZE *
           TIMING_GROUP_SIZE;
  } else {
    timer->left_base_tick_count_ = tick_count % (TIMING_BASE_SIZE * 
           TIMING_GROUP_SIZE * TIMING_GROUP_SIZE * TIMING_GROUP_SIZE);
    timer->timing_group_id_ = 3;
    this->group_[3].Schedule(timer, tick_count);
    timer->left_base_tick_count_ += this->group_[2].GetCurrentTick() * TIMING_BASE_SIZE *
           TIMING_GROUP_SIZE * TIMING_GROUP_SIZE;
  }
  // Insert into the handler's timer list.
  timer->handler_->timer_list_.insert(std::make_pair(timer->id_, timer));
  return true;
}

void TimingWheel::Unschedule(uint32 id, TimerHandler *handler) {
  // Find timer by id.
  TimerHandler::HandlerTimerList::iterator iterator = handler->timer_list_.find(id);
  if(iterator != handler->timer_list_.end()) {
    Timer *timer = iterator->second;
    // Unschedule, so delete from handler's timer list.
    handler->timer_list_.erase(iterator);
    this->releases_.push_back(timer);
    timer->releasing_ = true;
  }
}

void TimingWheel::OnSchedule(const TimeTick &now) {
  uint64_t read_value;
  TimestampMillisecond timestamp(now);

#ifdef __CORE_TIMERFD__
  ::read(this->channel_->GetFd(), &read_value, sizeof(read_value));
  // Calculate timeout to compensate callback.
  uint64 distance = this->timestamp_.Distance(timestamp);
#else
  // Calculate timeout to compensate callback.
  uint64 distance = this->timestamp_.Distance(timestamp) + this->patch_timer_;
#endif  // __CORE_TIMERFD__

  uint32 count = distance / this->tick_msec_;

#ifdef _CORE_DEBUG
  if(count > 1)
    CoreLog(ERROR, "TimingWheel::OnSchedule count[%u]", count);
#endif  // _CORE_DEBUG

#ifdef __CORE_TIMERFD__
  if(count == 0) {
    count = 1;
  }
  this->timestamp_ = timestamp;
#else
  if(count > 0) {
    this->patch_timer_ = distance - count * this->tick_msec_;
    this->timestamp_ = timestamp;
  }
#endif  // __CORE_TIMERFD__

  while(count-- > 0) {
    if(this->base_.OnSchedule() == true) {
      // Turn around, to make a carry.
      for(size_t pos = 0; pos < 4; ++pos) {
        if(this->group_[pos].OnSchedule() == false) break;
      }
    }
  }
  this->TimerRelease();
}

bool TimingWheel::Forward(int group_id, Timer *timer) {
  return this->ScheduleImplement(timer, timer->left_base_tick_count_);
}

bool TimingWheel::ResetTimer() {
  struct itimerspec newValue;
  bzero(&newValue, sizeof newValue);
  newValue.it_value.tv_sec = 1;
  newValue.it_interval.tv_sec = this->tick_msec_ / 1000;
  newValue.it_interval.tv_nsec = (this->tick_msec_ % 1000) * 1000000;

#ifdef __CORE_TIMERFD__
  if(::timerfd_settime(this->channel_->GetFd(), 0, &newValue, NULL) != 0) {
    CoreLog(ERROR, "%s:%d (%s) timerfd_settime error.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
#else  // __CORE_TIMERFD_
  this->loop_->SetPollTimeoutSec(this->tick_msec_ / 4);
#endif  // __CORE_TIMERFD__

  CoreLog(INFO, "%s:%d (%s) tick_msec_ is %d.",
      __FILE__, __LINE__, __FUNCTION__, this->tick_msec_);

  return true;
}

void TimingWheel::TimerRelease() {
  TimerReleaseList::iterator iterator = this->releases_.begin();
  for(; iterator != this->releases_.end(); ++iterator) {
    Timer *timer = *iterator;
    assert(timer);
    if(timer->timing_group_id_ == -1) {
      // In base, erase it.
      Timer::TimerList &bucket = base_.GetBucket(timer->timing_bucket_id_);
      if(timer->iterator_ != bucket.end())
        bucket.erase(timer->iterator_);
    } else if(timer->timing_group_id_ < 4) {
      // In group, erase it.
      Timer::TimerList &bucket = group_[timer->timing_group_id_].GetBucket(timer->timing_bucket_id_);
      if(timer->iterator_ != bucket.end())
        bucket.erase(timer->iterator_);
    } else {
      CoreLog(ERROR, "%s:%d (%s) Error timer(debug=[%s]) timing_group_id_.",
             __FILE__, __LINE__, __FUNCTION__, timer->debug_.c_str());
    }
    delete timer;
  }
  this->releases_.clear();
}

}  // namespace core

