//
// core - server core source code.
//
// $Rev: 5992 $
// $Author: $
// $Date: 2012-03-15 15:24:40 +0800 (鍛ㄥ洓, 2012-03-15) $
//
// Define class LogicLoop.
//

#ifndef __LOGIC__LOOP__H
#define __LOGIC__LOOP__H

#include <set>

#include "core/event_loop.h"
#include "core/base/boundless_entity_ring_queue.h"
#include "core/base/byte_buffer_dynamic.h"
#include "core/base/time_tick.h"

namespace core {

class ConnectionTask;

class LogicLoop : public EventLoop {
  typedef std::set<ConnectionTask *> ConnectionList;

 public:
  // typedef BoundlessEntityRingQueue<ConnectionTask> RingQueue;
  typedef BoundlessEntityRingQueue<TCPConnection> RingQueue;

  explicit LogicLoop();
  virtual ~LogicLoop();

  bool Initialize(RingQueue *server_ring_with_schedule, RingQueue *client_ring_with_main);

  inline void SetServerStopCallback(const ServerStopCallback &callback) {
    this->server_stop_callback_ = callback;
  }

  void CheckNewConectionTask();
  void CheckNewClientConectionTask();
  // Move complete verify connections into connections.
  // void CheckCompleteVerify();

  // Read and handle messages.
  void MessageHandler();
  void ClientMessageHandler();

  void RemoveClient(ConnectionTask *task);

 private:
  void OnCloseSignalCallback();

  void QuitLoop();

  // Callback when server stop.
  ServerStopCallback server_stop_callback_;

  RingQueue *server_ring_with_schedule_;
  RingQueue *client_ring_with_main_;

  ConnectionList connection_tasks_;
  ConnectionList client_connection_tasks_;
  // ConnectionList verifys_;

  SimpleByteBufferDynamic buffer_;
};

}  // namespace core

#endif  // __LOGIC__LOOP__H

