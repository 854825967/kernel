//
// core - server core source code.
//
// $Rev: 5305 $
// $Author: $
// $Date: 2012-03-05 17:00:56 +0800 (鍛ㄤ竴, 2012-03-05) $
//
// Define class TCPServer.
//

#ifndef __TCP__SERVER__H
#define __TCP__SERVER__H

#include <list>
#include <map>
#include <string>

#include "core/inet_address.h"
#include "core/base/noncopyable.h"
#include "core/base/bound_entity_ring_queue.h"
#include "core/base/boundless_entity_ring_queue.h"
#include "core/base/time_tick.h"
#include "core/base/types.h"

namespace core {

class EventLoop;
class Acceptor;
class TCPConnection;
class ConnectionTask;
class NetworkThreadPool;
class ScheduleLoop;
class LogicLoop;
class LoopThread;

class TCPServer : public Noncopyable {
  typedef std::map<std::string, TCPConnection *> ConnectionList;
  typedef std::list<TCPConnection *> RecycleList;
  typedef BoundEntityRingQueue<TCPConnection> RingQueueTCPConnection;
  typedef BoundlessEntityRingQueue<TCPConnection> RingQueueLogicTCPConnection;

 public:
  TCPServer(const InetAddress &address, const std::string &name);
  virtual ~TCPServer();

  bool Initialize(EventLoop *accept_loop, RingQueueLogicTCPConnection *ring);

  bool Start();
  void Stop();

  virtual void OnStop() {}

  // Set/Check stoping flag.
  inline void SetStoping() { this->state_ = CLOSING; }
  inline bool CheckStoping() const { return this->state_ == CLOSING; }

  // ----------------------------------------------
  // For Schedule thread.
  // Travel the recycle list, and recycle the connection.
  bool Recycle();
  // Recycle all connection.
  void RecycleAll();
  // Travel the connection list, and move the one which need recycle to the recycle list.
  void CheckRecycle(const TimestampMillisecond &timestamp);
  // Insert a new connection.
  void InsertConnection(TCPConnection *connection);
  // ----------------------------------------------

  inline RingQueueTCPConnection *GetConnectionQueue() { return this->connection_queue_; }
  inline RingQueueLogicTCPConnection *GetLogicConnectionQueue() { return this->logic_connection_queue_; }

  inline const InetAddress *GetLocalAddress() { return &this->local_address_; }

 protected:
  enum { INITIALIZE, STARTING, RUNNING, CLOSING, CLOSED, };

  virtual ConnectionTask *OnConnectionEstablished() = 0;
  /*
  {
    return new ConnectionTaskSubclass(connection);
  }
  */

  // When a connection arrived.
  void NewTCPConnection(int sockfd, const InetAddress &peer);

  std::string name_;
  uint8 state_;

  // EventLoop *loop_;
  // ScheduleLoop *loop_;
  Acceptor *acceptor_;

  // Communicate between main thread and schedule thread.
  RingQueueTCPConnection *connection_queue_;
  // Communicate between logic thread and schedule thread.
  RingQueueLogicTCPConnection *logic_connection_queue_;

  // Local address.
  InetAddress local_address_;

  // Connection list and recycle list.
  ConnectionList connections_;
  RecycleList recycles_;

  // Delay release list, this is to delay to release.
  RecycleList delay_releases_;

  // NetworkThreadPool *network_thread_pool_;

  // LoopThread *logic_thread_;
  // LogicLoop *logic_loop_;
};

}  // namespace core

#endif  // __TCP__SERVER__H

