//
// core - server core source code.
//
// $Rev: 11427 $
// $Author: $
// $Date: 2012-11-27 12:14:07 +0800 (鍛ㄤ簩, 2012-11-27) $
//
// Define class TimeTick.
// TimeTick gives some methods to get serval kinds of time.
// This is not thread-safe class.
//

#ifndef __TIME__TICK__H
#define __TIME__TICK__H

#include <time.h>

#include "core/base/thread.h"
#include "core/base/types.h"
#include "util/Util.h"

namespace core {

class TimeTick {
 public:
  TimeTick() {}
  ~TimeTick() {}

  TimeTick(const TimeTick &time_tick) {
    this->real_time_ = time_tick.real_time_;
    this->progress_time_ = time_tick.progress_time_;
    this->thread_time_ = time_tick.thread_time_;
    this->system_time_ = time_tick.system_time_;
  }

  // Update all times.
  void Update() {
    clock_gettime(CLOCK_REALTIME, &this->real_time_);
    clock_gettime(CLOCK_MONOTONIC, &this->system_time_);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->progress_time_);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &this->thread_time_);

    util::UpdateTickCount(&this->system_time_);
    util::UpdateUnixTime(this->GetRealSec());
  }

  // Nano seconds From 1970-1-1 0:0:0 to now.
  inline timespec GetRealTime() const {
    return this->real_time_;
  }
  // Seconds
  inline time_t GetRealSec() const {
    return this->real_time_.tv_sec;
  }
  // Small Seconds.
  inline uint32 GetSmallRealSec() const {
    return (uint32)this->real_time_.tv_sec;
  }

  // Progress count(progress cpu count).
  inline timespec GetProgressTime() const {
    return this->progress_time_;
  }
  inline time_t GetProgressSec() const {
    return this->progress_time_.tv_sec;
  }
  inline uint32 GetSmallProgressSec() const {
    return (uint32)this->progress_time_.tv_sec;
  }

  // Thread count(thread cpu count).
  inline timespec GetThreadTime() const {
    return this->thread_time_;
  }
  inline time_t GetThreadSec() const {
    return this->thread_time_.tv_sec;
  }
  inline uint32 GetSmallThreadSec() const {
    return (uint32)this->thread_time_.tv_sec;
  }

  // System count(from start system to now).
  inline timespec GetSystemTime() const {
    return this->system_time_;
  }
  inline time_t GetSystemSec() const {
    return this->system_time_.tv_sec;
  }
  inline uint32 GetSmallSystemSec() const {
    return (uint32)this->system_time_.tv_sec;
  }
  inline uint32 GetSmallSystemMsec() const {
    return (uint32)(this->system_time_.tv_sec * 1000 + this->system_time_.tv_nsec / 1000000);
  }
  inline uint64 GetBigSystemMsec() const {
    return (uint64)(this->system_time_.tv_sec * 1000 + this->system_time_.tv_nsec / 1000000);
  }

 private:
  // Nanoseconds From 1970-1-1 0:0:0 to now.
  timespec real_time_;
  // Progress count.
  timespec progress_time_;
  // Thread count.
  timespec thread_time_;
  // System count.
  timespec system_time_;
};


// This is a max-length 49 days timestamp.
// Modify from uint32 to uint64, so timestamp can be deemed to a unlimited value.
class TimestampMillisecond {
 public:
  TimestampMillisecond() : timestamp_(0){}
  explicit TimestampMillisecond(const TimeTick &time_tick) {
    this->Stamp(time_tick);
  }
  ~TimestampMillisecond() {}

  inline void Stamp() {
    timespec time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
    // millisecond.
    this->timestamp_ = time.tv_sec * 1000 + time.tv_nsec / 1000000;
  }
  inline void Stamp(const TimeTick &time_tick) {
    this->timestamp_ = time_tick.GetBigSystemMsec();
  }

  inline uint64 GetStamp() const {
    return this->timestamp_;
  }

  inline uint32 GetSmallStamp() const {
    return this->timestamp_;
  }

  // Attendion, the parameter must be the later one.
  // This distance will get a wrong value if any timestamp return to zero twice.
  uint64 Distance(const TimestampMillisecond &bigger) const {
    // overflow.
    if(bigger.GetStamp() < this->timestamp_) {
      return kuint64max - (this->timestamp_ - bigger.GetStamp());
    }
    return bigger.GetStamp() - this->timestamp_;
  }

  // Absolute distance will return a distance no matter witch one is bigger.
  uint64 AbsoluteDistance(const TimestampMillisecond &timestamp) const {
    if(timestamp.GetStamp() < this->timestamp_) {
      return this->timestamp_ - timestamp.GetStamp();
    }
    return timestamp.GetStamp() - this->timestamp_;
  }

  const TimestampMillisecond &operator = (const TimestampMillisecond &timestamp) {
    this->timestamp_ = timestamp.timestamp_;
    return *this;
  }

  const TimestampMillisecond *operator = (uint64 timestamp) {
    this->timestamp_ = timestamp;
    return this;
  }

 private:
  // milisecond.
  uint64 timestamp_;
};

}  // namespace core

#endif  // __TIME__TICK__H

