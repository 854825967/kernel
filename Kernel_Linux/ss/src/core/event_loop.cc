//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: $
// $Date: 2012-08-28 19:48:18 +0800 (周二, 2012-08-28) $
//
// Define class EventLoop, It's a reactor.
// With Epoll, EventLoop uses to dispose a large number of channel(I/O event)
// in a thread.
//

#include "core/event_loop.h"

#include <errno.h>
// #include <sys/eventfd.h>

#ifdef _CORE_DEBUG
#include <sys/time.h>
#endif

#include "core/channel.h"
#include "core/core_config.h"
#include "core/epoller.h"
#include "core/event_pipe.h"
#include "core/signal_set.h"
#include "core/timing_wheel.h"
#include "core/timer_handler.h"
#include "core/base/logging.h"
#include "core/base/auto_mutex.h"

namespace core {

namespace {
/*
int CreateEventfd() {
  int evtfd = folly::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evtfd < 0) {
    CoreLog(FATAL, "%s:%d (%s) Failed in eventfd",
           __FILE__, __LINE__, __FUNCTION__);
    abort();
  }
  return evtfd;
}
*/

}  // namespace

EventLoop::EventLoop(int poll_timeout_sec) : epoller_(NULL),
       /*signals_(NULL), */wheel_(NULL), poll_timeout_sec_(poll_timeout_sec),
       wakeup_channel_(NULL) {
  CreateEventPipe(this->wakeup_fd_);
  this->wakeup_channel_ = new Channel(this, EventPipeReadfd(this->wakeup_fd_));
  if(this->wakeup_channel_ == NULL) {
    CoreLog(FATAL, "%s:%d (%s) Failed to create wakeup_channel_",
           __FILE__, __LINE__, __FUNCTION__);
  }
}

EventLoop::~EventLoop() {
  if(this->wheel_) {
    delete this->wheel_;
    this->wheel_ = NULL;
  }
/*
  if(this->signals_) {
    delete this->signals_;
    this->signals_ = NULL;
  }
*/
  if(this->epoller_) {
    delete this->epoller_;
    this->epoller_ = NULL;
  }
  if(wakeup_channel_) {
    delete this->wakeup_channel_;
    this->wakeup_channel_ = NULL;
  }
  CloseEventPipe(this->wakeup_fd_);
}

bool EventLoop::Initialize(bool timer) {
  // Update time.
  this->time_.Update();

  // Resize the active channel.
  this->active_channels_.resize(128);

  // Allocate heap of epoll, signal and timing-wheel.
  this->epoller_ = new Epoller(this);
  if(this->epoller_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate epoller_.", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
/*
  this->signals_ = new SignalSet(this);
  if(this->signals_ == NULL || this->signals_->Start() == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate signals_ or start error.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
*/
  if(timer) {
    this->wheel_ = new TimingWheel(CoreConfig::GetTimer()->unit_interval_msec_, this);
    if(this->wheel_ == NULL || this->wheel_->Start(TimestampMillisecond(this->time_)) == false) {
      CoreLog(ERROR, "%s:%d (%s) Failed in allocate wheel_ or start error.",
             __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
  }

  // Initialize the size of buffer_.
  this->buffer_.PreWrite(CoreConfig::GetTcpConnection()->buffer_unit_size_);
  this->packet_buffer_.PreWrite(CoreConfig::GetTcpConnection()->buffer_unit_size_);

  this->wakeup_channel_->SetReadCallback(
         function::Bind(&EventLoop::HandleRead, this));
  this->wakeup_channel_->EnableRead();

  return true;
}

void EventLoop::Loop() {
  this->looping_ = true;
  this->quit_ = false;

  int events_number = 0;
  int msec_sleep = 0;
  const int kWriteEventHit = 3;
  const int kWriteEventSleepMsec = 5;
  const int kReadEventSleepMsec = 5;
  int write_event_loop_time = 1;
  bool handle_write_event = false;

  int poll_timeout_sec = this->poll_timeout_sec_;
  int sleep_msec = 0;

  while(this->quit_ == false) {
    // Get time.
    // this->time_.Update();

    this->DoBeforeCallbacks();

    events_number = this->epoller_->Poll(&this->active_channels_[0],
           this->active_channels_.size(), poll_timeout_sec);
    if(events_number < 0) {
      CoreLog(ERROR, "%s:%d (%s) Poll return -1 erron(%d).",
             __FILE__, __LINE__, __FUNCTION__, errno);
      continue;
    }
    if((size_t)events_number == this->active_channels_.size()) {
      // Allocate 2 multiples of size.
      this->active_channels_.resize(this->active_channels_.size() * 2);
    }
    // Update time.
    this->time_.Update();

    // Check handle write event.
    if(write_event_loop_time++ == kWriteEventSleepMsec) {
      write_event_loop_time = 1;
      handle_write_event = true;
    } else {
      handle_write_event = false;
    }

    int pos = 0;
    for(; pos < events_number; ++pos) {
      if(this->active_channels_[pos].data.fd == 0 || this->active_channels_[pos].events == 0) continue;
      Channel *channel = static_cast<Channel *>(this->active_channels_[pos].data.ptr);
      assert(channel);
      channel->SetHappendEvent(this->active_channels_[pos].events);
      // Check not handle write, disable write.
      if(handle_write_event == false) {
        channel->IgnoreWrite();
      }
      // Callback.
      channel->HandleEvent(this->time_);
    }
    // After callback once.
    this->DoAfterOnceCallbacks();
    // After callback.
    this->DoAfterCallbacks();
    // Callback with timetick.
    this->DoAttachTimetickCallbacks(this->time_);
    // Wakeup callback.
    this->DoWakeupCallbacks();

    // For debug.
    if(handle_write_event == true) {
      sleep_msec = kWriteEventSleepMsec;
    } else {
      sleep_msec = kReadEventSleepMsec;
    }
    ::usleep(sleep_msec * 1000);

    if(this->poll_timeout_sec_ >= sleep_msec) {
      poll_timeout_sec = this->poll_timeout_sec_ - sleep_msec;
    }
  }

  this->DoQuitCallbacks();

  this->quit_ = true;
  this->looping_ = false;
}

void EventLoop::AddTimer(uint32 id, uint32 msecs, int call_times,
       TimerHandler *handler, const std::string &debug) {
  this->wheel_->Schedule(id, msecs / CoreConfig::GetTimer()->unit_interval_msec_,
         call_times, handler, debug);
}

void EventLoop::RemoveTimer(uint32 id, TimerHandler *handler) {
  this->wheel_->Unschedule(id, handler);
}
/*
bool EventLoop::Signal(int signal_number, const SignalCallback &callback) {
  return this->signals_->Insert(signal_number, callback);
}

bool EventLoop::Unsignal(int signal_number) {
  return this->signals_->Remove(signal_number);
}
*/
void EventLoop::AddChannel(Channel* channel) {
  assert(channel);
  this->epoller_->AddChannel(channel);
}

void EventLoop::RemoveChannel(Channel* channel) {
  assert(channel);
  if(this->GetLooping()) {
    CoreLog(INFO, "EventLoop::RemoveChannel");
    this->epoller_->RemoveChannel(channel);
  } else {
    CoreLog(ERROR, "EventLoop RemoveChannel is not looping state.");
  }
}

void EventLoop::UpdateChannel(Channel* channel) {
  assert(channel);
  this->epoller_->UpdateChannel(channel);
}

void EventLoop::LoopInCallback(const Functor &callback, bool before) {
  if(before == false) {
    AutoMutex auto_mutex(&this->mutex_);
    this->loop_before_callbacks_.push_back(callback);
  } else {
    AutoMutex auto_mutex(&this->mutex_);
    this->loop_after_callbacks_.push_back(callback);
  }
}

void EventLoop::LoopInCallbackAttachTimeTick(const FunctorAttachTimeTick &callback) {
  AutoMutex auto_mutex(&this->mutex_);
  this->loop_callbacks_attach_timetick_.push_back(callback);
}

void EventLoop::LoopInOnceCallback(const Functor &callback) {
  AutoMutex auto_mutex(&this->mutex_);
  this->loop_after_once_callbacks_.push_back(callback);
}

void EventLoop::QuitInCallback(const Functor &callback) {
  AutoMutex auto_mutex(&this->mutex_);
  this->quit_callbacks_.push_back(callback);
}

void EventLoop::WakeupCallback(const Functor &callback) {
  this->Wakeup();
  AutoMutex auto_mutex(&this->mutex_);
  this->wakeup_callbacks_.push_back(callback);
}

void EventLoop::HandleRead(const TimeTick &time) {
  uint64 data = 1;
  ssize_t n = ::read(EventPipeReadfd(this->wakeup_fd_), &data, sizeof(data));
  if(n != sizeof(data)) {
     CoreLog(ERROR, "%s:%d (%s) wakeup and read [%u] bytes data.",
           __FILE__, __LINE__, __FUNCTION__, n);
  }
}

void EventLoop::Wakeup() {
  uint64 data = 1;
  ssize_t n = ::write(EventPipeWritefd(this->wakeup_fd_), &data, sizeof(data));
  if(n != sizeof(data)) {
     CoreLog(ERROR, "%s:%d (%s) wakeup and write [%u] bytes data.",
           __FILE__, __LINE__, __FUNCTION__, n);
  }
}

void EventLoop::DoBeforeCallbacks() {
  // Shorten the time of lock.
  this->mutex_.Lock();
  FunctorList callbacks(this->loop_before_callbacks_);
  this->mutex_.Unlock();

  FunctorList::iterator iter = callbacks.begin();
  for(; iter != callbacks.end(); ++iter) {
    (*iter)();
  }
}

void EventLoop::DoAfterCallbacks() {
  // Shorten the time of lock.
  this->mutex_.Lock();
  FunctorList callbacks(this->loop_after_callbacks_);
  this->mutex_.Unlock();

  FunctorList::iterator iter = callbacks.begin();
  for(; iter != callbacks.end(); ++iter) {
    (*iter)();
  }
}

void EventLoop::DoAttachTimetickCallbacks(const TimeTick &time_tick) {
  // Shorten the time of lock.
  this->mutex_.Lock();
  FunctorAttachTimetickList callbacks(this->loop_callbacks_attach_timetick_);
  this->mutex_.Unlock();

  FunctorAttachTimetickList::iterator iter = callbacks.begin();
  for(; iter != callbacks.end(); ++iter) {
    (*iter)(time_tick);
  }
}

void EventLoop::DoAfterOnceCallbacks() {
  // Shorten the time of lock.
  this->mutex_.Lock();
  FunctorList callbacks(this->loop_after_once_callbacks_);
  this->loop_after_once_callbacks_.clear();
  this->mutex_.Unlock();

  FunctorList::iterator iter = callbacks.begin();
  for(; iter != callbacks.end(); ++iter) {
    (*iter)();
  }
}

void EventLoop::DoQuitCallbacks() {
  // Shorten the time of lock.
  this->mutex_.Lock();
  FunctorList callbacks(this->quit_callbacks_);
  this->mutex_.Unlock();

  FunctorList::iterator iter = callbacks.begin();
  for(; iter != callbacks.end(); ++iter) {
    (*iter)();
  }
}

void EventLoop::DoWakeupCallbacks() {
  // Shorten the time of lock.
  this->mutex_.Lock();
  FunctorList callbacks(this->wakeup_callbacks_);
  this->wakeup_callbacks_.clear();
  this->mutex_.Unlock();

  FunctorList::iterator iter = callbacks.begin();
  for(; iter != callbacks.end(); ++iter) {
    (*iter)();
  }
}

}  // namespace core

