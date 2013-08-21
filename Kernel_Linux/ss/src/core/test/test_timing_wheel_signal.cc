//
// core - server core source code.
//
// $Rev: 6708 $
// $Author: $
// $Date: 2012-04-12 17:41:05 +0800 (周四, 2012-04-12) $
//
// Define class TestTimingWheelSignal.
//

#include <signal.h>

#include <iostream>
#include <stdlib.h>

#include "core/core_config.h"
#include "core/event_loop.h"
#include "core/timer_handler.h"
#include "core/base/logging.h"

namespace core {

std::string time_info[6] = {
  "timer1----1000", 
  "timer2----2000",
  "timer3----3000",
  "timer4----10000",
  "timer5----30000",
  "timer6----300*1000"
};

static void print_elapsed_time(void)
{
  static struct timespec start;
  struct timespec curr;
  static int first_call = 1;
  int secs, nsecs;

  if (first_call) {
    first_call = 0;
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
      printf("clock_gettime");
  }

  if (clock_gettime(CLOCK_MONOTONIC, &curr) == -1)
    printf("clock_gettime");

  secs = curr.tv_sec - start.tv_sec;
  nsecs = curr.tv_nsec - start.tv_nsec;
  if (nsecs < 0) {
    secs--;
    nsecs += 1000000000;
  }
  printf("%d.%03d: ", secs, (nsecs + 500000) / 1000000);
}

class Test : public TimerHandler {
 public:
  Test(EventLoop *loop) : loop_(loop) {}

  void Signal_SIGINT() {
    std::cout << "Recieve SIGINT!!!" << std::endl;
    CoreLog(INFO, "Recieve SIGINT!!!");
    exit(EXIT_SUCCESS);
  }

  virtual void OnTimer(uint32 id) {
    print_elapsed_time();
    // std::cout << "Recieve timer[" << id << "----" << time_info[id-1] << "]!!!" << std::endl;
    CoreLog(INFO, "Recieve timer[%u]!!", id);
    if(id == 1 || id == 2) {
      // this->loop_->RemoveTimer(id, this);
      if(id == 1) {
//        this->loop_->AddTimer(3, 3000, 10, this, "timer3");
      }
    }
  }

 private:
  EventLoop *loop_;
};

}  // namespace core

using namespace core;

int main(int argc, char* argv[]) {
  core::InitializeLogger("./log/info.log", "./log/warn.log", "./log/error.log");

  if(argc != 2) {
    std::cout << "You should run with a argument(configure file directory), just like:" << std::endl << "    $ ./test_timing_wheel_signal ./configure/core.xml" << std::endl;
    return 0;
  }

  core::CoreConfig::Init(argv[1]);
  if(core::CoreConfig::CheckFinishLoad() == false) {
    std::cout << "load configure file(" << argv[1] << ") error!" << std::endl;
    return 0;
  }

  EventLoop loop;

  Test test(&loop);

  loop.Initialize(true);

  loop.Signal(SIGINT, function::Bind(&Test::Signal_SIGINT, &test));

  // loop.AddTimer(1, 1000, -1, &test, "timer1");
  // loop.AddTimer(2, 2000, 5, &test, "timer2");
  // loop.AddTimer(4, 10000, -1, &test, "timer4");
  // loop.AddTimer(5, 30000, -1, &test, "timer5");
  // loop.AddTimer(6, 300 * 1000, -1, &test, "timer6");

  char buff[20];

  for(int i = 1; i <= 1; i++) {
    sprintf(buff, "timer%d", i);
    loop.AddTimer(i, 120 * 1000, -1, &test, buff);
  }

  print_elapsed_time();
  std::cout << "Timer start." << std::endl;

  loop.Loop();

  return 0;
}


