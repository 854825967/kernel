//
// core - server core source code.
//
// $Rev: 2431 $
// $Author: $
// $Date: 2011-12-12 21:41:44 +0800 (鍛ㄤ竴, 2011-12-12) $
//
// Noncopyable.
//

#ifndef __NONCOPYABLE__H
#define __NONCOPYABLE__H

namespace core {

namespace noncopyable_ {

class Noncopyable {
 protected:
  Noncopyable() {}
  ~Noncopyable() {}

 private:
  Noncopyable(const Noncopyable&);
  const Noncopyable& operator=(const Noncopyable&);
};

}  // namespace noncopyable_

typedef noncopyable_::Noncopyable Noncopyable;

}  // namespace core

#endif  // __NONCOPYABLE__H

