//
// core - server core source code.
//
// $Rev: 2353 $
// $Author: $
// $Date: 2011-12-08 18:05:59 +0800 (鍛ㄥ洓, 2011-12-08) $
//
// ScopedMutex is an auto mutex in it's live socpe.
//

#ifndef __SCOPED__MUTEX__H
#define __SCOPED__MUTEX__H

namespace core {

template <typename MutexType>
class ScopedMutex {
 public:
  explicit ScopedMutex(MutexType *mutex) : mutex_(mutex){
    this->mutex_->Lock();
  }
  ~ScopedMutex() {
    this->mutex_->Unlock();
  }

 private:
  MutexType *mutex_;
};

}  // namespace core

#endif  // __SCOPED__MUTEX__H

