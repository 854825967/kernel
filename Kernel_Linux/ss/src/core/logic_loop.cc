//
// core - server core source code.
//
// $Rev: 6603 $
// $Author: $
// $Date: 2012-04-09 17:12:12 +0800 (周一, 2012-04-09) $
//
// Define class LogicLoop.
//

#include "core/logic_loop.h"

#include <signal.h>

#include "core/connection_task.h"
#include "core/core_config.h"
#include "core/tcp_connection.h"
#include "core/base/logging.h"
#include "core/function/function.h"

namespace core {

LogicLoop::LogicLoop()
       : EventLoop(1) {}

LogicLoop::~LogicLoop() {
/*
  ConnectionList::iterator iterator = this->connection_tasks_.begin();
  for(; iterator != this->connection_tasks_.end(); ++iterator) {
    // (*iterator)->SetRecycle();
    (*iterator)->OnCloseConnection();
  }
  iterator = this->client_connection_tasks_.begin();
  for(; iterator != this->client_connection_tasks_.end(); ++iterator) {
    // (*iterator)->SetRecycle();
    (*iterator)->OnCloseConnection();
  }
*/
}

bool LogicLoop::Initialize(LogicLoop::RingQueue *server_ring_with_schedule,
       LogicLoop::RingQueue *client_ring_with_main) {
  if(EventLoop::Initialize(true) == false) return false;

  this->buffer_.PreWrite(CoreConfig::GetTcpConnection()->buffer_unit_size_);

  this->server_ring_with_schedule_ = server_ring_with_schedule;
  this->client_ring_with_main_ = client_ring_with_main;

  this->QuitInCallback(function::Bind(&LogicLoop::QuitLoop, this));

  // this->Signal(SIGINT, function::Bind(&LogicLoop::OnCloseSignalCallback, this));
  // this->LoopInCallback(function::Bind(&LogicLoop::CheckCompleteVerify, this), true);
  if(this->server_ring_with_schedule_) {
    this->LoopInCallback(function::Bind(&LogicLoop::CheckNewConectionTask, this), true);
    this->LoopInCallback(function::Bind(&LogicLoop::MessageHandler, this), false);
  }
  if(this->client_ring_with_main_) {
    this->LoopInCallback(function::Bind(&LogicLoop::CheckNewClientConectionTask, this), true);
    this->LoopInCallback(function::Bind(&LogicLoop::ClientMessageHandler, this), false);
  }
  return true;
}

void LogicLoop::CheckNewConectionTask() {
  TCPConnection *connection = NULL;

  while(this->server_ring_with_schedule_->Remove(connection) == ring_queue::kErrorCodeSuccess) {
    // CoreLog(INFO, "%s:%d (%s) New server connection task", __FILE__, __LINE__, __FUNCTION__);
    // Create a connection task.
    ConnectionTask *task = connection->connection_callback_();
    if(task) {
      task->Initialize(connection);
      task->OnConnectionOK();
      this->connection_tasks_.insert(task);
    } else {
      connection->SetLogicRecycled();
    }
  }
}

void LogicLoop::CheckNewClientConectionTask() {
  TCPConnection *connection = NULL;
  while(this->client_ring_with_main_->Remove(connection) == ring_queue::kErrorCodeSuccess) {
    // CoreLog(INFO, "%s:%d (%s) New client connection task", __FILE__, __LINE__, __FUNCTION__);
    // Create a connection task.
    ConnectionTask *task = connection->connection_callback_();
    if(task) {
      task->Initialize(connection);
      task->OnConnectionOK();
      this->client_connection_tasks_.insert(task);
    } else {
      connection->SetLogicRecycled();
    }
  }
}

/*
void LogicLoop::CheckNewConectionTask() {
  ConnectionTask *task = NULL;
  int retcode = 0;
  while(this->server_ring_with_schedule_->Remove(task) == ring_queue::kErrorCodeSuccess) {
    CoreLog(INFO, "LogicLoop::CheckNewConectionTask new task!!");
    this->verifys_.push_back(task);
  }
}
void LogicLoop::CheckCompleteVerify() {
  ConnectionList::iterator iterator = this->verifys_.begin();
  for(; iterator != this->verifys_.end();) {
    if((*iterator)->CheckVerify()) {
      this->connection_tasks_.push_back(*iterator);
      iterator = this->verifys_.erase(iterator);
    }
  }
}
*/
void LogicLoop::MessageHandler() {
  ConnectionTask *task = NULL;
  ConnectionList::iterator iterator = this->connection_tasks_.begin();
  for(; iterator != this->connection_tasks_.end();) {
    task = *iterator;
    // To check connecting state.
    if(task->CheckDisconnecting() == true) {
      this->connection_tasks_.erase(iterator++);
      task->CloseConnection();
      task->OnCloseConnection();
    } else {
      // Recieve message.
      task->Recieve(this->buffer_.HeadPointer(), this->buffer_.GetCapacitySize());
      ++iterator;
    }
  }
}

void LogicLoop::ClientMessageHandler() {
  ConnectionTask *task = NULL;
  ConnectionList::iterator iterator = this->client_connection_tasks_.begin();
  for(; iterator != this->client_connection_tasks_.end();) {
    task = *iterator;
    // To check connecting state.
    if(task->CheckDisconnecting() == true) {
      this->client_connection_tasks_.erase(iterator++);
      task->CloseConnection();
      task->OnCloseConnection();
    } else {
      // Recieve message.
      task->Recieve(this->buffer_.HeadPointer(), this->buffer_.GetCapacitySize());
      ++iterator;
    }
  }
}

void LogicLoop::RemoveClient(ConnectionTask *task) {
  ConnectionList::iterator iterator = this->client_connection_tasks_.find(task);
  if(iterator != this->client_connection_tasks_.end()) {
    ConnectionTask *task = *iterator;
    this->client_connection_tasks_.erase(iterator);
  }
}

void LogicLoop::OnCloseSignalCallback() {
  
}

void LogicLoop::QuitLoop() {
  ConnectionTask *task = NULL;
  bool quit = false;
  while(!quit) {
    // sleep(1);
    // check server's connection close.
    ConnectionList::iterator iterator = this->connection_tasks_.begin();
    for(; iterator != this->connection_tasks_.end();) {
      task = *iterator;
      this->connection_tasks_.erase(iterator++);
      task->CloseConnection();
      task->OnCloseConnection(true);
    }

    // check client's connection close.
    iterator = this->client_connection_tasks_.begin();
    for(; iterator != this->client_connection_tasks_.end();) {
      task = *iterator;
      this->client_connection_tasks_.erase(iterator++);
      task->CloseConnection();
      task->OnCloseConnection(true);
    }

    quit = this->connection_tasks_.empty() && this->client_connection_tasks_.empty();
  }

  if(this->server_stop_callback_) {
    this->server_stop_callback_();
  }
}

}  // namespace core

