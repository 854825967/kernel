//
// core - server core source code.
//
// $Rev: 2873 $
// $Author: $
// $Date: 2011-12-31 18:22:57 +0800 (鍛ㄥ叚, 2011-12-31) $
//
// Define class EventLoopThreadGroup.
//

#ifndef __EVENT__LOOP__THREAD__GROUP__H
#define __EVENT__LOOP__THREAD__GROUP__H

#include <string>
#include <vector>

#include "core/base/noncopyable.h"
#include "core/base/types.h"

namespace core {

class LoopThread;
class EventLoop;

class EventLoopThreadGroup : public Noncopyable {
  typedef std::vector<EventLoop *> LoopGroup;
  typedef std::vector<LoopThread *> ThreadGroup;
 public:
  EventLoopThreadGroup();
  ~EventLoopThreadGroup();

  bool Initialize(uint32 thread_number, const std::string &name = "", bool timer = false);

  void Start();
  void Stop();

  inline EventLoop *GetNextLoop() {
    return this->loops_[this->hash_++ % this->loops_.size()];
  }
  inline LoopThread *GetNextLoopThread() {
    return this->threads_[this->hash_++ % this->threads_.size()];
  }

 private:
  ThreadGroup threads_;
  LoopGroup loops_;
  uint32 hash_;
};

}  // namespace core

#endif  // __EVENT__LOOP__THREAD__GROUP__H

