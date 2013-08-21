//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (鍛ㄤ簲, 2011-12-30) $
//
// Define class Epoller.
// Simple wrapper of epoll.
//

#ifndef __EPOLLER__H
#define __EPOLLER__H

#include <sys/epoll.h>

#include <vector>

#include "core/base/noncopyable.h"

namespace core {

class EventLoop;
class Channel;

class Epoller : public Noncopyable {
 public:
  typedef std::vector<struct epoll_event> EventList;

  explicit Epoller(EventLoop *loop);
  ~Epoller();

  // Return numbers of event happened.
  int Poll(struct epoll_event *events,
         int max_events, int timeout_milliseconds = -1);
  void AddChannel(Channel *channel);
  void RemoveChannel(Channel *channel);
  void UpdateChannel(Channel *channel);

 private:
  void Update(int operation, Channel *channel);

  EventLoop *loop_;
  int epoll_fd_;
};

}  // namespace core

#endif  // __EPOLLER__H

