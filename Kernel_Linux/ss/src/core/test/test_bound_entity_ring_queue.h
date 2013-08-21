//
// core - server core source code.
//
// $Rev: 2445 $
// $Author: $
// $Date: 2011-12-15 10:03:34 +0800 (鍛ㄥ洓, 2011-12-15) $
//
// Test code of BoundlessEntityRingQueue.
//

#ifndef __TEST__BOUND__ENTITY__RING__QUEUE__H
#define __TEST__BOUND__ENTITY__RING__QUEUE__H

#include "core/base/thread.h"

namespace core {

class TestTarget;

class Terminal {
 public:
  Terminal(const std::string &name);
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
};

}  // namespace core

#endif  // __TEST__BOUND__ENTITY__RING__QUEUE__H

