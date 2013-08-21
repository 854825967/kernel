//
// core - server core source code.
//
// $Rev: 5421 $
// $Author: $
// $Date: 2012-03-06 20:03:28 +0800 (鍛ㄤ簩, 2012-03-06) $
//
// Define class SignalSet.
// This is not thread-safe, so uses it in a single thread.
//

#ifndef __SIGNAL__SET__H
#define __SIGNAL__SET__H

#include <signal.h>

#include <map>

#include "core/callbacks.h"
#include "core/base/noncopyable.h"
#include "core/base/time_tick.h"

namespace core {

class Channel;
class EventLoop;
class Signaller;

class SignalSet : public Noncopyable {
 public:
  typedef std::pair<Signaller, sigset_t> SignallerInfo;
  typedef std::map<int, SignallerInfo> SignallerList;

  SignalSet(EventLoop *loop);
  ~SignalSet();

  bool Start();

  bool Insert(int key, const SignalCallback &callback);
  bool Remove(int key);

  inline void Run(int key);

  void OnReadCallback(const TimeTick &time_tick);

 private:
  SignallerList signallers_;
  Channel *channel_;
  EventLoop *loop_;

  sigset_t sig_mask_;
};

}  // namespace core

#endif  // __SIGNAL__SET__H

