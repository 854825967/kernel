//
// core - server core source code.
//
// $Rev: 6708 $
// $Author: $
// $Date: 2012-04-12 17:41:05 +0800 (周四, 2012-04-12) $
//
// Define class ScheduleLoop.
//

#include "core/schedule_loop.h"

#include "core/network_thread_pool.h"
#include "core/tcp_server.h"
#include "core/tcp_connection.h"
#include "core/base/bound_entity_ring_queue.h"

namespace core {

ScheduleLoop::ScheduleLoop(NetworkThreadPool *pool) 
       : pool_(pool) {}
ScheduleLoop::~ScheduleLoop() {}

void ScheduleLoop::Loop() {
  // Allocate tcp client according to configure file.
  // Connect and relate to a client loop.
  // ...

  this->looping_ = true;
  TCPServer *server = this->pool_->GetTCPServer();

  BoundEntityRingQueue<TCPConnection> *connection_queue = server->GetConnectionQueue();
  while(this->quit_ == false) {
    this->time_tick_.Update();

    if(server->CheckStoping() == false) {
      // Handle recycle.
      server->CheckRecycle(TimestampMillisecond(this->time_tick_));
      server->Recycle();

      // Get connection from main thread.
      TCPConnection *connection = NULL;
      while(true) {
        int ret = connection_queue->Remove(connection);
        if(ret == ring_queue::kErrorCodeSuccess) {
          server->InsertConnection(connection);
          // Get a connection, balance to verify threads.
          // EventLoop *loop = this->pool_->GetNextVerifyLoop();
          EventLoop *loop = this->pool_->GetNextMessageLoop();
          connection->SetEventLoop(loop);
          // Start connection communication.
          connection->OnConnectionStart(this->time_tick_);
          server->GetLogicConnectionQueue()->Add(connection);
        } else if(ret == kErrorCodeComplete) {
          // Main thread complete, trigger stopping server.
          server->Stop();
          break;;
        } else {
          server->GetLogicConnectionQueue()->Flush();
          break;
        }
      }
    } else {
      server->RecycleAll();
      this->quit_ = server->Recycle();
    }
    usleep(20000);
  }

  this->looping_ = false;
}

}  // namespace core

