//
// core - server core source code.
//
// $Rev: 5421 $
// $Author: $
// $Date: 2012-03-06 20:03:28 +0800 (周二, 2012-03-06) $
//
// Define class SignalSet.
//

#include "core/signal_set.h"

#include <sys/signalfd.h>

#include "core/channel.h"
#include "core/event_loop.h"
#include "core/signaller.h"
#include "core/base/logging.h"

namespace core {

SignalSet::SignalSet(EventLoop *loop) : channel_(NULL), loop_(loop) {
  ::sigemptyset(&this->sig_mask_);
  int fd = ::signalfd(-1, &this->sig_mask_, 0);
  if(fd == -1) {
    CoreLog(ERROR, "%s:%d (%s) Failed to signalfd.", __FILE__, __LINE__, __FUNCTION__);
  } else if ((this->channel_ = new Channel(this->loop_, fd)) == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed to allocate channel.",
           __FILE__, __LINE__, __FUNCTION__);
    ::close(fd);
  }
}

SignalSet::~SignalSet() {
  if(this->channel_) {
    this->channel_->DisableAll();
    ::close(this->channel_->GetFd());
    delete this->channel_;
  }
}

bool SignalSet::Start() {
  if(this->channel_ == NULL) return false;

  this->channel_->SetReadCallback(function::Bind(&SignalSet::OnReadCallback, this));
  this->channel_->EnableRead();
  
  return true;
}

bool SignalSet::Insert(int key, const SignalCallback &callback) {
  if(this->signallers_.find(key) == this->signallers_.end()) {
    // Save current signal set.
    sigset_t mask;
    ::sigemptyset(&mask);
    ::sigaddset(&this->sig_mask_, key);
    if(::sigprocmask(SIG_BLOCK, &this->sig_mask_, &mask) == -1) {
      CoreLog(ERROR, "%s:%d (%s) Failed to sigprocmask, key=[%d].",
             __FILE__, __LINE__, __FUNCTION__, key);
      return false;
    }
    if(::signalfd(this->channel_->GetFd(), &this->sig_mask_, 0) == -1) {
      CoreLog(ERROR, "%s:%d (%s) Failed to signalfd.", __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
    // Insert to list.
    Signaller signaller(callback);
    this->signallers_.insert(std::make_pair(key, std::make_pair(signaller, mask)));
    return true;
  }

  return false;
}

bool SignalSet::Remove(int key) {
  SignallerList::iterator iterator = this->signallers_.find(key);
  if(iterator != this->signallers_.end()) {
    ::sigdelset(&this->sig_mask_, key);
    // recover signal set.
    if(::sigprocmask(SIG_SETMASK, &iterator->second.second, NULL) == -1) {
      CoreLog(ERROR, "%s:%d (%s) Failed to sigprocmask, key=[%d].",
             __FILE__, __LINE__, __FUNCTION__, key);
      return false;
    }
    if(::signalfd(this->channel_->GetFd(), &this->sig_mask_, 0) == -1) {
      CoreLog(ERROR, "%s:%d (%s) Failed to signalfd.", __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
    // Remove from list.
    this->signallers_.erase(iterator);
    return true;
  }

  return false;
}

void SignalSet::Run(int key) {
  SignallerList::iterator iterator = this->signallers_.find(key);
  if(iterator != this->signallers_.end()) {
    iterator->second.first.Run();
  }
}

void SignalSet::OnReadCallback(const TimeTick &time_tick) {
  struct signalfd_siginfo data;
  ssize_t size = read(this->channel_->GetFd(), &data, sizeof(struct signalfd_siginfo));
  if(size == sizeof(signalfd_siginfo)) {
    this->Run(data.ssi_signo);
  }
}

}  // namespace core

