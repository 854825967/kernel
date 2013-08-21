//
// core - server core source code.
//
// $Rev: 6033 $
// $Author: $
// $Date: 2012-03-16 14:43:23 +0800 (周五, 2012-03-16) $
//
// Define class ClientThreadPool.
//

#ifndef __CLIENT__THREAD__POOL__h
#define __CLIENT__THREAD__POOL__h

#include "core/event_loop_thread_group.h"
#include "core/loop_thread.h"
#include "core/base/noncopyable.h"

namespace core {

class TCPClient;

class ClientThreadPool : public Noncopyable {
  
 public: 
  ClientThreadPool();
  ~ClientThreadPool();

  bool Initialize();
  void Start();
  void Stop();

  inline LoopThread *GetNextClientThread() { return this->client_threads_.GetNextLoopThread(); }
  inline EventLoop *GetNextClientLoop() { return this->client_threads_.GetNextLoop(); }

 private:
  EventLoopThreadGroup client_threads_;
};

}  // namespace core

#endif  // __CLIENT__THREAD__POOL__h

