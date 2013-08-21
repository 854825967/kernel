//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (周五, 2011-12-30) $
//
// Test code of BoundlessEntityRingQueue.
//

#include "core/test/test_boundless_entity_ring_queue.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include "core/base/boundless_entity_ring_queue.h"
#include "core/base/logging.h"
#include "core/base/ring_queue_common.h"
#include "core/base/types.h"

namespace core {

typedef BoundlessEntityRingQueue<core::TestTarget> BoundlessEntityRingQueueImp;
static BoundlessEntityRingQueueImp *queue = NULL;

class TestTarget {
 public:
  TestTarget() : data_(0) {}
  ~TestTarget() {}

  inline void Set(int64 data) { this->data_ = data; }
  inline int64 Get() const { return this->data_; }

 private:
  int64 data_;
};


int Terminal::producer_sleep_ = 0;
static int max_value = kint32max;

Terminal::Terminal(const std::string &name)
       : thread_(name, function::Bind(&Terminal::Consume, this), true) {}

Terminal::~Terminal() {}

void Terminal::Consume() {
  sleep(1);
  CoreLog(INFO, "consumer(%s) begin...", this->thread_.GetName().c_str());

  int size = 0;
  while(true) {
    CoreLog(INFO, "consumer loop...");

    TestTarget *target = NULL;
    size = queue->Remove(target);

    if(size == ring_queue::kErrorCodeComplete) {
      break;
    } else if(size == ring_queue::kErrorCodeSuccess) {
      CoreLog(WARNING, "%llu", target->Get());
      delete target;
    }
    // usleep(Terminal::producer_sleep_);
  }
}

void Terminal::Produce() {
  sleep(1);
  CoreLog(INFO, "producer(%s) begin...", this->thread_.GetName().c_str());

  int64 iterator = 0;
  int random = rand() % 1024;
  int value = 0;
  while(true) {
    CoreLog(INFO, "producer loop...");
    random = rand() % 1024;
    value = max_value - iterator;
    if(value < random) {
      for(; iterator < max_value; ++iterator) {
        TestTarget *target = new TestTarget();
        if(target) {
          target->Set(iterator);
          queue->Add(target);
        }
      }
      CoreLog(INFO, "producer [%d], iterator(%d) and finished", value, iterator);
      break;
    } else {
      random += iterator;
      for(; iterator < random; ++iterator) {
        TestTarget *target = new TestTarget();
        target->Set(iterator);
        queue->Add(target);
      }
      CoreLog(INFO, "producer [%d], iterator(%d)", random, iterator);
    }
    usleep(Terminal::producer_sleep_);
  }

  CoreLog(INFO, "producer flush...");

  while(true) {
    if(queue->Flush() == true) {
      queue->ProduceCompletely();
      break;
    }
    usleep(Terminal::producer_sleep_ * 5);
  }
  CoreLog(INFO, "producer end...");
}

}  // namespace core

int main(int argc, char* argv[]) {

  if(argc == 5) {
    core::Terminal::producer_sleep_ = atoi(argv[1]);
    core::max_value = atoi(argv[2]);

    srand(time(NULL));
    core::InitializeLogger("./log/info.log", "./log/warn.log", "./log/error.log");

    core::uint8 blocking = atoi(argv[3]);
    int ring_size = atoi(argv[4]);
    core::queue = new core::BoundlessEntityRingQueueImp(ring_size, blocking);

    core::Terminal producer("producer");
    producer.SetProducer();

    producer.Start();


    core::Terminal consumer("consumer");
    consumer.SetConsumer();

    consumer.Start();

    producer.Join();
    consumer.Join();
  } else {
    std::cout << "You should run with 2 argument2 to give a sleep time(microseconds), a max value and ring size, just like the follow: " << std::endl << " ./test_boundless_entity_ring_queue 10 99999 1024" << std::endl;
  }

  return 0;
}

