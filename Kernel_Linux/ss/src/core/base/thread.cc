//
// core - server core source code.
//
// $Rev$
// $Author$
// $Date$
//
// Wrapper of pthread.
//

#include "core/base/thread.h"

#include <signal.h>

#include "core/base/logging.h"

namespace core {

Thread::Thread(const std::string &name, const Threadfunction &callback, bool joinable)
       : callback_(callback),
         tid_(0),
         name_(name),
         state_(THREAD_STATE_CREATE), 
         joinable_(joinable) {}

Thread::~Thread() {}

void Thread::SetThreadFunction(const Threadfunction &callback) {
  this->callback_ = callback;
}

bool Thread::Start() {
  CoreLog(INFO, "%s:%d (%s) thread [%s] start...", __FILE__, __LINE__, __FUNCTION__, this->name_.c_str());

  if(this->CheckAlive() == true) {
    CoreLog(ERROR, "%s:%d (%s) Failed to start, thread is alive.", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  pthread_attr_t attr;
  ::pthread_attr_init(&attr);
  if(this->CheckJoinable() == false) {
    ::pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  }
  
  // Create a thread and let it executes the method - "ThreadFunction".
  if(::pthread_create(&this->tid_, &attr, Thread::StartThread, this) != 0) {
    CoreLog(ERROR, "%s:%d (%s) Failed to start, pthread_create error!", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  ::pthread_attr_destroy(&attr);

  // Block it, until alive state.
  this->mutex_.Lock();
  while(this->CheckAlive() == false) {
    // Not alive, wait for it. The method "ThreadFuction" will change state
    // into alive in it's thread.
    this->condition_variable_.Wait(&this->mutex_);
  }
  this->mutex_.Unlock();

  return true;
}

void Thread::Join() {
  if(this->GetTid() && this->CheckJoinable()) {
    this->mutex_.Lock();
    if(this->CheckAlive()) {
      this->condition_variable_.Wait(&this->mutex_);
    }
    this->mutex_.Unlock();
    ::pthread_join(this->tid_, NULL);
    this->tid_ = 0;
  }
}

void* Thread::StartThread(void *parameter) {
Thread *thread = static_cast<Thread *>(parameter);

  // Alive.
  thread->mutex_.Lock();
  thread->Alive();
  thread->condition_variable_.Signal();
  thread->mutex_.Unlock();

  sigset_t sig_mask;
  sigfillset(&sig_mask);
  pthread_sigmask(SIG_SETMASK, &sig_mask, NULL);

  // Callback.
  thread->callback_();

  // Terminal.
  thread->mutex_.Lock();
  thread->Terminal();
  thread->condition_variable_.Broadcast();
  thread->mutex_.Unlock();

  CoreLog(INFO, "%s:%d (%s) Thread[%s] terminal.", __FILE__, __LINE__, __FUNCTION__, thread->name_.c_str());

  return thread;
}

}  // namespace core

