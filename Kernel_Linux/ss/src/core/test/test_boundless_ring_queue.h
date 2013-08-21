//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (鍛ㄤ簲, 2011-12-30) $
//
// Test code of BoundlessRingQueue.
//

#ifndef __TEST__BOUNDLESS__RING__QUEUE__H
#define __TEST__BOUNDLESS__RING__QUEUE__H

#include "core/base/boundless_ring_queue.h"
#include "core/base/thread.h"

namespace core {

class Terminal {
 public:
  Terminal(const std::string &name, BoundlessRingQueue *queue);
  ~Terminal();

  void Consume();
  void Produce();

  void SetConsumer() {
    this->thread_.SetThreadFunction(function::Bind(&Terminal::Consume, this));
  }

  void SetProducer() {
    this->thread_.SetThreadFunction(function::Bind(&Terminal::Produce, this));
  }

  inline void Start() { thread_.Start(); }

  inline void Join() { thread_.Join(); }

  static int producer_sleep_;

 private:
  Thread thread_;
  BoundlessRingQueue *queue_;
};

}  // namespace core

#endif  // __TEST__BOUNDLESS__RING__QUEUE__H

