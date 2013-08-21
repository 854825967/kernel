//
// core - server core source code.
//
// $Rev: 9885 $
// $Author: $
// $Date: 2012-08-27 18:14:28 +0800 (周一, 2012-08-27) $
//
// Define class TCPServer.
//

#include "core/tcp_server.h"

#include "core/acceptor.h"
#include "core/core_config.h"
#include "core/event_loop.h"
#include "core/logic_loop.h"
#include "core/network_thread_pool.h"
#include "core/schedule_loop.h"
#include "core/tcp_connection.h"
#include "core/base/logging.h"
#include "core/function/function.h"

namespace core {

TCPServer::TCPServer(const InetAddress &address, const std::string &name) 
       : name_(name), state_(INITIALIZE), acceptor_(NULL),
         connection_queue_(NULL), logic_connection_queue_(NULL),
         local_address_(address)/*, logic_thread_(NULL), logic_loop_(NULL)*/ {}

TCPServer::~TCPServer() {
  RecycleList::iterator iterator = this->delay_releases_.begin();
  for(; iterator != this->delay_releases_.end(); ++iterator) {
    delete *iterator;
  }

  if(this->connection_queue_) {
    delete this->connection_queue_;
    this->connection_queue_ = NULL;
  }

  if(this->acceptor_) {
    delete this->acceptor_;
    this->acceptor_ = NULL;
  }
/*
  if(this->logic_thread_ != NULL) {
    delete this->logic_thread_;
    this->logic_thread_ = NULL;
  }
  if(this->logic_loop_ != NULL) {
    delete this->logic_loop_;
    this->logic_loop_ = NULL;
  }
*/
}

bool TCPServer::Initialize(EventLoop *accept_loop, RingQueueLogicTCPConnection *ring) {
  // Create acceptor and enable read to wait for connection.
  this->acceptor_ = new Acceptor(this->local_address_, accept_loop);
  if(this->acceptor_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate acceptor.",
  	 __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Logic connection queue.
  this->logic_connection_queue_ = ring;

  // Conection queue.
  this->connection_queue_ = new RingQueueTCPConnection(
         CoreConfig::GetAcceptor()->ring_size_, BLOCKING_PRODUCER);
  if(this->connection_queue_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate connection queue.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
/*
  this->logic_loop_ = new LogicLoop();
  if(this->logic_loop_ == NULL || this->logic_loop_->Initialize(this->logic_connection_queue_) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate or Initialize logic loop.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  this->logic_thread_ = new LoopThread(this->logic_loop_, "LogicThread");
  if(logic_thread_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in Initialize logic thread.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
*/
  this->acceptor_->SetNewConnectionCallback(function::Bind(&TCPServer::NewTCPConnection, this));

  return true;
}

bool TCPServer::Start() {
  // Starting state.
  this->state_ = STARTING;

//  this->logic_thread_->StartLoop();

  // Start and listen.
  if(this->acceptor_->Listen() == false) {
     CoreLog(ERROR, "%s:%d (%s) Listen error!!", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  // Running state.
  this->state_ = RUNNING;

  CoreLog(INFO, "%s:%d (%s) Server start!!", __FILE__, __LINE__, __FUNCTION__);

  return true;
}

void TCPServer::Stop() {
  // Travel and broadcast recycle.
 /*
  ConnectionList::iterator iterator = this->connections_.begin();
  while(iterator != this->connections_.end()) {
    TCPConnection *connection = iterator->second;
    // connection->BroatcastRecycle();
    this->connections_.erase(iterator);
    this->recycles_.push_back(connection);
    iterator = this->connections_.begin();
  }
 */

  this->SetStoping();
  CoreLog(INFO, "%s:%d (%s) Server stop!!", __FILE__, __LINE__, __FUNCTION__);
}

void TCPServer::RecycleAll() {
  ConnectionList::iterator iterator = this->connections_.begin();
  while(iterator != this->connections_.end()) {
    TCPConnection *connection = iterator->second;
    // Let network Disconnecing itself, logic will notify network threads.
    connection->RequireShutdown();
    this->connections_.erase(iterator);
    this->recycles_.push_back(connection);
    iterator = this->connections_.begin();
  }
}

bool TCPServer::Recycle() {
  if(this->recycles_.empty()) return true;

  RecycleList::iterator iterator = this->recycles_.begin();
  for(; iterator != this->recycles_.end();) {
    TCPConnection *connection = *iterator;
    if(connection->CheckCanRecycle() == true) {
#ifdef _LOGIC_DEBUG   
      CoreLog(INFO, "TCPServer::Recycle() delete connection=[%p]", connection);
#endif
      connection->Shutdown();
      delete connection;
      iterator = this->recycles_.erase(iterator);
      continue;
    }
    ++iterator;
  }

  return false;
}

void TCPServer::CheckRecycle(const TimestampMillisecond &timestamp) {
  ConnectionList::iterator iterator = this->connections_.begin();
  for(; iterator != this->connections_.end();) {
    TCPConnection *connection = iterator->second;
    if(connection->CheckLogicRecycle()) {
      connection->RequireShutdown();
    } else if(connection->CheckNetworkRecycle()) {
    /*
    if((connection->CheckCanRecycle() == false && connection->CheckLogicRecycle())
      || connection->CheckTimeout(timestamp)) {
      // Require network thread to shutdown connection.
      connection->RequireShutdown();
      */
    } else {
      ++iterator;
      continue;
    }

    this->connections_.erase(iterator++);
    this->recycles_.push_back(connection);
  }
}

void TCPServer::InsertConnection(TCPConnection *connection) {
  this->connections_.insert(std::make_pair(connection->GetName(), connection));
}

void TCPServer::NewTCPConnection(int sockfd, const InetAddress &peer) {
  char buffer[16];
  snprintf(buffer, sizeof(buffer), ":%d", sockfd);
  std::string connection_name = this->name_ + buffer;
  TCPConnection *connection = new TCPConnection(sockfd, NULL, connection_name,
         this->local_address_, peer);
  if(connection == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed to allocate tcp connection.",
  	 __FILE__, __LINE__, __FUNCTION__);
    return ;
  }
  if(connection->Initialize(CoreConfig::GetTcpConnection()->open_tgw_, false) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed to Initialize connection.",
  	 __FILE__, __LINE__, __FUNCTION__);
    delete connection;
    return ;
  }
  connection->SetConnectionEstablishedCallback(
         function::Bind(&TCPServer::OnConnectionEstablished, this));
  // Blocking Add.
  int ret = this->connection_queue_->Add(connection);
  if(ret != ring_queue::kErrorCodeSuccess) {
    CoreLog(ERROR, "%s:%d (%s) Failed to add connection to queue.",
  	 __FILE__, __LINE__, __FUNCTION__);
    delete connection;
    return ;
  }
}

}  // namespace core

