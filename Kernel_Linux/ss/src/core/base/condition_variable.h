//
// core - server core source code.
//
// $Rev: 5010 $
// $Author: $
// $Date: 2012-02-23 20:17:14 +0800 (鍛ㄥ洓, 2012-02-23) $
//
// Define class ConditionVariable.
//

#ifndef __CONDITION__VARIABLE__H
#define __CONDITION__VARIABLE__H

#include <sys/time.h>

#include "core/base/logging.h"
#include "core/base/mutex.h"
#include "core/base/noncopyable.h"

namespace core {

class ConditionVariable : public Noncopyable {
 public:
  ConditionVariable() {
    pthread_condattr_t attr;
    pthread_condattr_init(&attr);
    pthread_cond_init(&this->condition_, &attr);
    pthread_condattr_destroy(&attr);
  }
  ~ConditionVariable() {
    pthread_cond_destroy(&this->condition_);
  }

  void Wait(Mutex *mutex) {
    pthread_cond_wait(&this->condition_, &(mutex->mutex_));
  }

  // timeout_in_msecs < 0: wait forever
  // timeout_in_msecs >= 0: wait timeout_in_msecs msec
  bool Wait(Mutex *mutex, int timeout_in_msecs) {
    if(timeout_in_msecs < 0) {
      this->Wait(mutex);
      return true;
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);

    // add timeout
    tv.tv_sec += timeout_in_msecs / 1000;
    tv.tv_usec += (timeout_in_msecs % 1000) * 1000;

    int million = 1000000;
    if(tv.tv_usec >= million) {
      tv.tv_sec += tv.tv_usec / million;
      tv.tv_usec %= million;
    }   

    // convert timeval to timespec
    struct timespec ts;
    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;
    int return_code = pthread_cond_timedwait(&this->condition_, &mutex->mutex_, &ts);

    if(return_code != 0) {
      CoreLog(ERROR, "%s:%d (%s) Failed in ConditionVariable::Wait, returncode=%d",
             __FILE__, __LINE__, __FUNCTION__, return_code);
      return false;
    }

    return true;
  }

  void Signal() {
    pthread_cond_signal(&this->condition_);
  }

  void Broadcast() {
    pthread_cond_broadcast(&this->condition_);
  }

 private:
  pthread_cond_t condition_;
};

}  // namespace core

#endif  // __CONDITION__VARIABLE__H

