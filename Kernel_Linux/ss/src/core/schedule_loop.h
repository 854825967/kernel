//
// core - server core source code.
//
// $Rev: 3059 $
// $Author: $
// $Date: 2012-01-04 14:38:27 +0800 (鍛ㄤ笁, 2012-01-04) $
//
// Define class ScheduleLoop.
//

#ifndef __SCHEDULE__LOOP__H
#define __SCHEDULE__LOOP__H

#include "core/base_loop.h"
#include "core/base/time_tick.h"

namespace core {

class NetworkThreadPool;
class TCPConnection;

class ScheduleLoop : public BaseLoop {
 public:
  explicit ScheduleLoop(NetworkThreadPool *pool);
  virtual ~ScheduleLoop();

  virtual void Loop();

 private:
  NetworkThreadPool *pool_;
  TimeTick time_tick_;
};

}  // namespace core

#endif  // __SCHEDULE__LOOP__H

