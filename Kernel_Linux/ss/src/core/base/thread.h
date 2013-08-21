//
// core - server core source code.
//
// $Rev$
// $Author$
// $Date$
//
// Wrapper of pthread.
//

#ifndef __THREAD__H
#define __THREAD__H

#include <pthread.h>

#include <string>

#include "core/base/condition_variable.h"
#include "core/base/mutex.h"
#include "core/base/noncopyable.h"
#include "core/base/types.h"
#include "core/function/function.h"

namespace core {

enum ThreadState {
  THREAD_STATE_CREATE = 0,
  THREAD_STATE_ALIVE,
  THREAD_STATE_TERMINAL,
};

class Thread : public Noncopyable {
 public:
  typedef function::Function0<void> Threadfunction;

  Thread(const std::string &name, const Threadfunction &callback, bool joinable = true);
  ~Thread();

  void SetThreadFunction(const Threadfunction &callback);

  bool Start();
  void Join();

  inline pthread_t GetTid() const { return this->tid_; }

  inline bool CheckJoinable() const { return this->joinable_; }
  inline bool CheckAlive() const { return this->state_ == THREAD_STATE_ALIVE; }
  inline bool CheckTerminal() const { return this->state_ == THREAD_STATE_TERMINAL; }

  inline void Alive() { this->state_ = THREAD_STATE_ALIVE; }
  inline void Terminal() { this->state_ = THREAD_STATE_TERMINAL; }

  inline std::string GetName() const { return this->name_; }

 private:
  static void *StartThread(void *parameter);

  Threadfunction callback_;

  pthread_t tid_;
  std::string name_;
  uint8 state_;
  bool joinable_;

  Mutex mutex_;
  ConditionVariable condition_variable_;
};

}  // namespace core

#endif  // __LOOP__THREAD__H

