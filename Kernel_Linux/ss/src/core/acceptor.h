//
// core - server core source code.
//
// $Rev: 4642 $
// $Author: $
// $Date: 2012-02-17 15:54:15 +0800 (鍛ㄤ簲, 2012-02-17) $
//
// Define class Acceptor.
// This acceptor uses non-blocking pattern.
//

#ifndef __ACCEPTOR__H
#define __ACCEPTOR__H

#include "core/tcp_socket.h"
#include "core/base/noncopyable.h"
#include "core/base/time_tick.h"
#include "core/function/function.h"

namespace core {

class InetAddress;
class Channel;
class EventLoop;

class Acceptor : public Noncopyable {
  typedef function::Function2<void, int, const InetAddress &> NewConnectionCallback;

 public:
  explicit Acceptor(const InetAddress &listen_address, EventLoop *loop);
  ~Acceptor();

  // Callback.
  inline void SetNewConnectionCallback(const NewConnectionCallback &callback) {
    this->callback_ = callback;
  }

  // Listen and accept.
  bool Listen();
  void Accept(const TimeTick &time_tick);

  inline InetAddress &GetAddress() { return this->local_address_; }

  inline EventLoop *GetEventLoop() { return this->loop_; }

 private:
  TCPSocket socket_;
  NewConnectionCallback callback_;
  InetAddress local_address_;
  EventLoop *loop_;
  Channel *channel_;
};

}  // namespace core

#endif  // __ACCEPTOR__H

