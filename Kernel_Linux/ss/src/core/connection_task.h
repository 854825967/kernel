//
// core - server core source code.
//
// $Rev: 6165 $
// $Author: $
// $Date: 2012-03-23 14:00:53 +0800 (鍛ㄤ簲, 2012-03-23) $
//
// Define class ConnectionTask.
//

#ifndef __CONNECTION__TASK__H
#define __CONNECTION__TASK__H

#include "core/tcp_connection.h"
#include "core/inet_address.h"

namespace core {

class ConnectionTask {
 public:
  ConnectionTask() : connection_(NULL), state_(DISCONNECTED) {}
  virtual ~ConnectionTask() {}

  // Initialize.
  void Initialize(TCPConnection *connection) {
    this->connection_ = connection;
    this->peer_address_ = this->connection_->GetPeerAddress();
    this->local_address_ = this->connection_->GetLocalAddress();
    this->state_ = CONNECTED;
  }

  // Invoke by LogicLoop.  
  // OnRecieve is a interface, implement by inheritance class.
  virtual void OnRecieve(const char *message, int size) = 0;
  // On connection ok callback. 
  virtual void OnConnectionOK() = 0;
  // Invoke by logic loop when closing connection.
  virtual void OnCloseConnection(bool force = false) = 0;

  // This SendHandler is a interface, use for inheritance class.
  void Send(const char *message, int size) {
    if(this->CheckConnected())
      this->connection_->SendMessage(message, size);  
  }

  // Invoke by logic loop.
  void Recieve(char *buffer, int max_size) { 
    int size = 0; 
    while(this->CheckConnected() &&
           (size = this->connection_->RecieveMessage(buffer, max_size)) > 0) {
      this->OnRecieve(buffer, size);
    }
  }

  inline bool CheckDisconnecting() const {
    if(this->CheckConnected())
      return this->connection_->CheckDisconnecting();
    return true;
  }

  // Close the connection.
  inline void CloseConnection() {
    this->Disconnect();
  }

  inline bool CheckDisconnected() const { return this->state_ == DISCONNECTED; }

  // Get address.
  const InetAddress &GetPeerAddress() const { return this->peer_address_; } 
  const InetAddress &GetLocalAddress() const { return this->local_address_; } 

  // Get address string.
  std::string GetPeerString() const { return this->peer_address_.GetString(); }
  std::string GetLocalString() const { return this->local_address_.GetString(); }

  inline bool CheckConnected() const { return this->state_ == CONNECTED; }

 private:
  enum { CONNECTED, DISCONNECTED, };

  inline void Disconnect() {
    if(this->CheckConnected()) {
      this->connection_->SendCompletely();
      this->connection_->SetLogicRecycled();
      this->connection_ = NULL;
      this->state_ = DISCONNECTED;
    }
  }

  TCPConnection *connection_;

  InetAddress peer_address_;
  InetAddress local_address_; 

  uint8 state_;
};

}  // namespace core

#endif  // __CONNECTION__TASK__H

