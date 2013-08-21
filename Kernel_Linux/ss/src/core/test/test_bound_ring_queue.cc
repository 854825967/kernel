//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (周五, 2011-12-30) $
//
// Test code of BoundRingQueue.
//

#include "core/test/test_bound_ring_queue.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include "core/base/logging.h"
#include "core/base/ring_queue_common.h"
#include "core/base/types.h"

namespace core {

int Terminal::producer_sleep_ = 0;
static int max_value = kint32max;

Terminal::Terminal(const std::string &name, BoundRingQueue *queue)
       : thread_(name, function::Bind(&Terminal::Consume, this), true), queue_(queue) {}

Terminal::~Terminal() {}

void Terminal::Consume() {
  sleep(1);
  CoreLog(INFO, "consumer(%s) begin...", this->thread_.GetName().c_str());

  char buffer[102400];
  int size = 0;
  while(true) {
    CoreLog(INFO, "consumer loop...");
    size = this->queue_->Remove(buffer, sizeof(buffer));
    if(size == ring_queue::kErrorCodeComplete) {
      break;
    } else if(size > 0){
      buffer[size] = '\0';
      CoreLog(WARNING, "%s", buffer);
    }
    // usleep(1);
  }
}

void Terminal::Produce() {
  sleep(1);
  CoreLog(INFO, "producer(%s) begin...", this->thread_.GetName().c_str());

  int iterator = 0;
  int random = rand() % 1024;
  int value = 0;
  while(true) {
    CoreLog(INFO, "producer loop...");
    random = rand() % 1024;
    value = max_value - iterator;
    std::ostringstream oss;
    if(value < random) {
      for(; iterator < max_value; ++iterator) {
         oss << iterator << " ";
      }
      oss << iterator << ".";
      this->queue_->Add(oss.str().c_str(), oss.str().length());
      CoreLog(INFO, "producer [%d], iterator(%d) and finished", value, iterator);
      break;
    } else {
      random += iterator;
      for(; iterator < random; ++iterator) {
         oss << iterator << " ";
      }
      this->queue_->Add(oss.str().c_str(), oss.str().length());
      CoreLog(INFO, "producer [%d], iterator(%d)", random, iterator);
    }
    usleep(Terminal::producer_sleep_);
  }
  this->queue_->ProduceCompletely();
  CoreLog(INFO, "producer end...");
}

}  // namespace core

int main(int argc, char* argv[]) {

  if(argc == 4) {
    core::Terminal::producer_sleep_ = atoi(argv[1]);
    core::max_value = atoi(argv[2]);

    srand(time(NULL));
    core::InitializeLogger("./log/info.log", "./log/warn.log", "./log/error.log");

    bool blocking = argv[3] == 0;
    core::BoundRingQueue ring(102400, blocking);


    core::Terminal producer("producer", &ring);
    producer.SetProducer();

    producer.Start();


    core::Terminal consumer("consumer", &ring);
    consumer.SetConsumer();

    consumer.Start();

    producer.Join();
    consumer.Join();
  } else {
    std::cout << "You should run with 2 argument2 to give a sleep time(microseconds), a max value and blocking pattern, just like the follow: " << std::endl << " ./test_bound_ring_queue 10 99999 0" << std::endl;
  }

  return 0;
}

