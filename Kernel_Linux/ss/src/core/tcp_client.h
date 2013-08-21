//
// core - server core source code.
//
// $Rev: 5992 $
// $Author: $
// $Date: 2012-03-15 15:24:40 +0800 (鍛ㄥ洓, 2012-03-15) $
//
// Define class TCPClient.
//

#ifndef __TCP__CLIENT__H
#define __TCP__CLIENT__H

#include <string>

#include "core/core_config.h"
#include "core/inet_address.h"
#include "core/base/boundless_entity_ring_queue.h"
#include "core/base/noncopyable.h"

namespace core {

class Connector;
class EventLoop;
class TCPConnection;
class ConnectionTask;
class ClientThreadPool;

class TCPClient : public Noncopyable {
  typedef BoundlessEntityRingQueue<TCPConnection> RingQueueLogicTCPConnection;

 public:
  TCPClient(const InetAddress &server_address, const std::string &name);
  virtual ~TCPClient();

  bool Initialize(EventLoop *loop, ClientThreadPool *pool, RingQueueLogicTCPConnection *queue);

  void Start();
  void Stop();

  const std::string &GetName() const { return this->name_; }

  RingQueueLogicTCPConnection *GetLogicConnectionQueue() {
    return this->logic_connection_queue_;
  }

  inline void SetConnectionTask(ConnectionTask *task) { this->connection_task_ = task;}
  
  inline ConnectionTask *GetConnectionTask() const { return this->connection_task_; }

 protected:
  virtual ConnectionTask *OnConnectionEstablished() = 0;
  /*
  {
    return new ConnectionTaskSubclass(connection);
  }
  */

  void NewTCPConnection(int sockfd, const InetAddress &local);

  // state of connecting.
  bool connected_;

  std::string name_;
  EventLoop *loop_;

  Connector *connector_;
  TCPConnection *connection_;

  InetAddress server_address_;

  ClientThreadPool *pool_;

  RingQueueLogicTCPConnection *logic_connection_queue_;

  ConnectionTask *connection_task_;
};

}  // namespace core

#endif  // __TCP__CLIENT__H

