//
// core - server core source code.
//
// $Rev: 5305 $
// $Author: $
// $Date: 2012-03-05 17:00:56 +0800 (鍛ㄤ竴, 2012-03-05) $
//
// Define class Connector.
// This Connector uses non-blocking pattern and must run in a EventLoop.
// Not a thread-safe version.
//

#ifndef __CONNECTOR__H
#define __CONNECTOR__H

#include "core/inet_address.h"
#include "core/tcp_socket.h"
#include "core/timer_handler.h"
#include "core/function/function.h"
#include "core/base/noncopyable.h"
#include "core/base/types.h"

namespace core {

class EventLoop;
class Channel;

class Connector : public Noncopyable, public TimerHandler {
  typedef function::Function2<void, int, const InetAddress &> NewConnectionCallback;

 public:
  Connector(EventLoop *loop, const InetAddress &server_address, int retry_msec);
  ~Connector();

  virtual void OnTimer(uint32 id);

  // Callback.
  inline void SetNewConnectionCallback(const NewConnectionCallback &callback) {
    this->callback_ = callback;
  }

  // Start and stop.
  void Start();
  void Stop();

  // Support retry timeout.
  void Restart();

 private:
  enum { DISCONNECTED = 0, CONNECTING, CONNECTED, };

  // Connect to server.
  void Connect();

  // Remove channel.
  void RemoveChannel();

  // Delay to remove channel(safe mode).
  void DelayRemoveChannel();

  // Connect complete or error occupy.
  void OnComplete();
  void OnError();

  // Server address.
  InetAddress address_;
  // Socket.
  TCPSocket socket_;
  // Callback.
  NewConnectionCallback callback_;
  // Event loop and channel.
  EventLoop *loop_;
  Channel *channel_;
  // state
  uint8 state_;

  int retry_msec_;

  bool retry_flag_;
};

}  // namespace core

#endif  // __CONNECTOR__H

