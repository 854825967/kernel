//
// core - server core source code.
//
// $Rev: 2925 $
// $Author: $
// $Date: 2012-01-01 19:40:55 +0800 (鍛ㄦ棩, 2012-01-01) $
//
// Define class LoopThread.
//

#ifndef __LOOP__THREAD__H
#define __LOOP__THREAD__H

#include <string>

#include "core/base_loop.h"
#include "core/base/noncopyable.h"
#include "core/base/thread.h"

namespace core {

class LoopThread : public Noncopyable {
 public:
  LoopThread(BaseLoop *loop, const std::string &name = "", bool joinable = true);
  ~LoopThread();

  void StartLoop();
  void StopLoop(bool force_quit = true);
  inline BaseLoop *GetLoop() const { return this->loop_; }

 private:
  inline void Loop() { this->loop_->Loop(); }

  BaseLoop *loop_;
  Thread thread_;
};

}  // namespace core


#endif  // __LOOP__THREAD__H

