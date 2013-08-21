//
// core - server core source code.
//
// $Rev: 6033 $
// $Author: $
// $Date: 2012-03-16 14:43:23 +0800 (鍛ㄤ簲, 2012-03-16) $
//
// Define interface BaseLoop, it's the core of reactor and it will be
// ran in a thread.
//

#ifndef __BASE__LOOP__H
#define __BASE__LOOP__H

#include "core/base/noncopyable.h"

namespace core {

class BaseLoop : public Noncopyable {
 public:
  BaseLoop() : looping_(false), quit_(false) {}
  virtual ~BaseLoop() {}

  virtual void Loop() = 0;
  virtual bool Initialize(bool timer = true) { return true; }
  virtual void Stop() {}

  inline bool GetLooping() const { return this->looping_; }
  inline void Quit() { this->quit_ = true; }
  virtual void Wakeup() {}

 protected:
  bool looping_;
  bool quit_;
};

}  // namespace core

#endif  // __BASE__LOOP__H

