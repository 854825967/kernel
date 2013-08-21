//
// core - server core source code.
//
// $Rev: 7087 $
// $Author: $
// $Date: 2012-04-29 08:44:23 +0800 (鍛ㄦ棩, 2012-04-29) $
//
// Define class Channel
// A channel describes a I/O event with a fd(file descriptor), this fd can be
// a socket, a timer fd or a signal fd.
//

#ifndef __CHANNEL__H
#define __CHANNEL__H

#include <string>

#include "core/base/noncopyable.h"
#include "core/function/function.h"

namespace core {

class EventLoop;
class TimeTick;

class Channel : public Noncopyable {
 public:
  // Return true means this channel is not available.
  typedef function::Function0<void> CommonEventCallback;
  // Return true means this channel is not available.
  typedef function::Function1<void, const TimeTick &> ReadEventCallback;

  Channel(EventLoop *loop, int fd);
  ~Channel();

  inline bool CheckEventHanding() const { return this->event_handling_; }

  // Handle happend event.
  void HandleEvent(const TimeTick &timetick);

  // Set callback handle.
  inline void SetReadCallback(const ReadEventCallback &callback) {
    this->read_callback_ = callback;
  }
  inline void SetWriteCallback(const CommonEventCallback &callback) {
    this->write_callback_ = callback;
  }
  inline void SetCloseCallback(const CommonEventCallback &callback) {
    this->close_callback_ = callback;
  }
  inline void SetErrorCallback(const CommonEventCallback &callback) {
    this->error_callback_ = callback;
  }

  // Event.
  inline int GetEvent() const { return this->event_; }
  inline bool CheckNoneEvent() const { return this->event_ == kNoneEvent_; }
  inline bool CheckReadEvent() const { return this->event_ & kReadEvent_; }
  inline bool CheckWriteEvent() const { return this->event_ & kWriteEvent_; }
  // Enable event.
  inline void EnableRead() { this->event_ |= kReadEvent_; this->UpdateEvent(); }
  inline void EnableWrite() { this->event_ |= kWriteEvent_; this->UpdateEvent(); }
  inline void EnableAll() { this->event_ = kReadEvent_ | kWriteEvent_; this->UpdateEvent(); }
  // Disable event.
  inline void DisableAll() { this->event_ = kNoneEvent_; this->UpdateEvent(); }
  inline void DisableRead() { this->event_ &= ~kReadEvent_; this->UpdateEvent(); }
  inline void DisableWrite() { this->event_ &= ~kWriteEvent_; this->UpdateEvent(); }

  inline void IgnoreWrite() { this->event_ &= ~kWriteEvent_; }

  // In HandleEvent, invoke to get happened event.
  inline int GetHappenedEvent() const { return this->happened_event_; }
  // After epoll_wait, invoke to set happened event.
  inline void SetHappendEvent(int event) { this->happened_event_ = event; }

  inline int GetFd() const { return this->fd_; }
  inline EventLoop *GetEventLoop() const { return this->loop_; }
  inline void SetEventLoop(EventLoop *loop) { this->loop_ = loop; }

  // State.
  inline bool CheckStateInit() const { return this->state_ == kStateInit; }
  inline bool CheckStateAdded() const { return this->state_ == kStateAdded; }
  inline bool CheckStateDeleted() const { return this->state_ == kStateDeleted; }
  //
  inline void SetStateAdded() { this->state_ = kStateAdded; }
  inline void SetStateDeleted() { this->state_ = kStateDeleted; }

  // For debug
  std::string SerializeString() const;

 private:
  // Update event to epoller.
  void UpdateEvent();

  // Event type.
  static const int kReadEvent_;
  static const int kWriteEvent_;
  static const int kNoneEvent_;

  // Event file describes.
  int fd_;

  // Concerned event and happened event.
  int event_;
  int happened_event_;

  // State for epoller.
  int state_;

  // State type.
  static const int kStateInit;
  static const int kStateAdded;
  static const int kStateDeleted;

  // Read callback deliver a timetick parameter.
  // this will gives a TCP heartbeat time.
  ReadEventCallback read_callback_;
  CommonEventCallback write_callback_;
  CommonEventCallback close_callback_;
  CommonEventCallback error_callback_;

  // Running in this loop.
  EventLoop *loop_;

  bool event_handling_;
};

}  // namespace core

#endif  // __CHANNEL__H

