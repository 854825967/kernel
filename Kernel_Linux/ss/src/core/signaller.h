//
// core - server core source code.
//
// $Rev: 2494 $
// $Author: $
// $Date: 2011-12-20 16:19:50 +0800 (鍛ㄤ簩, 2011-12-20) $
//
// Define class Signaller.
//

#ifndef __SIGNALLER__H
#define __SIGNALLER__H

#include "core/function/function.h"

namespace core {

class Signaller {
  typedef function::Function0<void> SignalFunctor;
 public:
  explicit Signaller(const SignalFunctor &callback) : number_(0), callback_(callback) {}
  ~Signaller() {}

  inline void Run() {
    this->callback_();
  }

  inline int GetNumber() const { return this->number_; }

 private:
  int number_;
  SignalFunctor callback_;
};

}  // namespace core

#endif  // __SIGNALLER__H

