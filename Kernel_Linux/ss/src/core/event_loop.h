//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Define class EventLoop, It's a reactor.
// With Epoll, EventLoop uses to dispose a large number of channel(I/O event)
// in a thread.
//

#ifndef __EVENT__LOOP__h
#define __EVENT__LOOP__h

#include <sys/epoll.h>

#include <string>
#include <vector>

#include "core/base_loop.h"
#include "core/callbacks.h"
#include "core/base/byte_buffer_dynamic.h"
#include "core/base/mutex.h"
#include "core/base/time_tick.h"
#include "core/function/function.h"
#include "core/packet/packet.h"

namespace core {

class Channel;
class Epoller;
class SignalSet;
class TimingWheel;
class TimerHandler;

class EventLoop : public BaseLoop {
 public:
  // like boost::function<void()>.
  typedef function::Function0<void> Functor;
  typedef std::vector<Functor> FunctorList;
  typedef std::vector<struct epoll_event> ChannelList;

  typedef function::Function1<void, const TimeTick &> FunctorAttachTimeTick;
  typedef std::vector<FunctorAttachTimeTick> FunctorAttachTimetickList;

  EventLoop(int poll_timeout_sec = -1);
  virtual ~EventLoop();

  virtual bool Initialize(bool timer);
  virtual void Loop();

  // Wakeup.
  virtual void Wakeup();

  inline void SetPollTimeoutSec(int poll_timeout_sec = -1) { this->poll_timeout_sec_ = poll_timeout_sec; }

  // Timer.
  void AddTimer(uint32 id, uint32 msecs, int call_times,
         TimerHandler *handler, const std::string &debug);
  void RemoveTimer(uint32 id, TimerHandler *handler);
/*
  // Signal.
  bool Signal(int signal_number, const SignalCallback &callback);
  bool Unsignal(int signal_number);
*/
  // Let epoll related to a channel.
  void AddChannel(Channel* channel);
  void RemoveChannel(Channel* channel);
  void UpdateChannel(Channel* channel);

  // Push back(thread-safe).
  // Attention: this callback should be effective during EventLoop's life cycle.
  void LoopInCallback(const Functor &callback, bool before);

  void LoopInCallbackAttachTimeTick(const FunctorAttachTimeTick &callback);

  // Push back to callback once(thread-safe).
  void LoopInOnceCallback(const Functor &callback);

  // Push back.
  // Attention: this callback should be effective during EventLoop's life cycle.
  void QuitInCallback(const Functor &callback);

  // Wakeup and callback.
  void WakeupCallback(const Functor &callback);

  // Set/Get packet.
  inline void SetPacket(Encrypt *encrypt, Compress *compress) {
    this->packet_.SetEncrypt(encrypt);
    this->packet_.SetComress(compress);
  }
  Packet* GetPacket() { return &this->packet_; }

  // Get temp buffer.
  SimpleByteBufferDynamic *GetTempBuffer() { return &this->buffer_; }
  SimpleByteBufferDynamic *GetPacketBuffer() { return &this->packet_buffer_; }

  // Get time.
  inline const TimeTick &GetTimeTick() const { return this->time_; }

  // Get wakeup data.
  void HandleRead(const TimeTick &time);

 private:
  void DoBeforeCallbacks();
  void DoAfterCallbacks();
  void DoAttachTimetickCallbacks(const TimeTick &time_tick);
  void DoAfterOnceCallbacks();
  void DoQuitCallbacks();

  void DoWakeupCallbacks();

  // Epoller.
  Epoller *epoller_;
  // Epoll gives active I/O channels.
  ChannelList active_channels_;

  // Run at the start of loop.
  FunctorList loop_before_callbacks_;
  // Run at the end of loop.
  FunctorList loop_after_callbacks_;
  // Run at the end of loop.
  FunctorAttachTimetickList loop_callbacks_attach_timetick_;
  // Run once at the end of loop.
  FunctorList loop_after_once_callbacks_;
  // Run before loop quit.
  FunctorList quit_callbacks_;

  // Run once at the end of loop.
  FunctorList wakeup_callbacks_;

  // Mutex.
  Mutex mutex_;

  // Time tick.
  TimeTick time_;

  // Packet.
  Packet packet_;

  // Signal list.
  // SignalSet *signals_;

  // For socket, temp buffer.
  SimpleByteBufferDynamic buffer_;
  SimpleByteBufferDynamic packet_buffer_;

  TimingWheel *wheel_;

  int poll_timeout_sec_;

  // wakeup.
  int wakeup_fd_[2];
  Channel *wakeup_channel_;
};

}  // namespace core

#endif  // __EVENT__LOOP__h

