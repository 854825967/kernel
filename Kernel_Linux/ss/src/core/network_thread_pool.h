//
// core - server core source code.
//
// $Rev: 2873 $
// $Author: $
// $Date: 2011-12-31 18:22:57 +0800 (鍛ㄥ叚, 2011-12-31) $
//
// Define class NetworkThreadPool.
//

#ifndef __NETWORK__THREAD__POOL__h
#define __NETWORK__THREAD__POOL__h

#include "core/event_loop_thread_group.h"
#include "core/loop_thread.h"
#include "core/base/noncopyable.h"

namespace core {

class ScheduleLoop;
class TCPServer;

class NetworkThreadPool : public Noncopyable {
  
 public: 
  NetworkThreadPool(TCPServer *server);
  ~NetworkThreadPool();

  bool Initialize();
  void Start();
  void Stop();

  inline LoopThread *GetScheduleThread() { return this->schedule_thread_; }
  inline ScheduleLoop *GetScheduleLoop() { return this->schedule_loop_; }

  // inline LoopThread *GetNextVerifyThread() { return this->verify_threads_.GetNextLoopThread(); }
  // inline EventLoop *GetNextVerifyLoop() { return this->verify_threads_.GetNextLoop(); }

  inline LoopThread *GetNextMessageThread() { return this->message_threads_.GetNextLoopThread(); }
  inline EventLoop *GetNextMessageLoop() { return this->message_threads_.GetNextLoop(); }

  inline TCPServer *GetTCPServer() { return this->server_; }

 private:
  LoopThread *schedule_thread_;
  ScheduleLoop *schedule_loop_;

  // EventLoopThreadGroup verify_threads_;
  EventLoopThreadGroup message_threads_;

  TCPServer *server_;
};

}  // namespace core

#endif  // __NETWORK__THREAD__POOL__h

