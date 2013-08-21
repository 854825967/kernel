//
// core - server core source code.
//
// $Rev: 3061 $
// $Author: $
// $Date: 2012-01-04 15:02:58 +0800 (鍛ㄤ笁, 2012-01-04) $
//
// Define class LogLoop.
//

#ifndef __LOG__LOOP__H
#define __LOG__LOOP__H

#include "core/base_loop.h"
#include "core/logic_log.h"

namespace core {

class LogicLog;

class LogLoop : public BaseLoop {
 public:
  LogLoop();
  virtual ~LogLoop();

  bool Initialize(LogicLog *log);
  virtual void Stop() { this->log_->Stop(); }

  virtual void Loop();

 private:
  LogicLog *log_;
};

}  // namespace core

#endif  // __LOG__LOOP__H

