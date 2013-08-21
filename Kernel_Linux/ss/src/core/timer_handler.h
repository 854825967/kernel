//
// core - server core source code.
//
// $Rev: 9911 $
// $Author:  $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Define class TimerHandler.
//

#ifndef __TIMER__HANDLER__H
#define __TIMER__HANDLER__H

#include <map>

#include "core/base/types.h"

namespace core {

class Timer;

class TimerHandler {
 public:
  virtual ~TimerHandler() {}
  typedef std::map<uint32, Timer *> HandlerTimerList;
  
  virtual void OnTimer(uint32 id) = 0;
  
  HandlerTimerList timer_list_;
};

}  // namespace core

#endif  // __TIMER__HANDLER__H

