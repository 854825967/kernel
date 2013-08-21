//
// core - server core source code.
//
// $Rev: 6456 $
// $Author:  $
// $Date: 2012-04-01 14:34:33 +0800 (周日, 2012-04-01) $
//
// Define class Acceptor.
// This acceptor uses non-blocking pattern.
//

#include "core/acceptor.h"

#include <errno.h>

#include "core/channel.h"
#include "core/inet_address.h"
#include "core/base/logging.h"

namespace core {

Acceptor::Acceptor(const InetAddress &listen_address, EventLoop *loop)
       : local_address_(listen_address), loop_(loop), channel_(NULL) {
  if(this->socket_.CreateSocket() == false ||
         this->socket_.SetNonblock() == false ||
         this->socket_.Bind(this->local_address_) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed to create socket or bind address.",
           __FILE__, __LINE__, __FUNCTION__);
  } else {
    this->channel_ = new Channel(this->loop_, this->socket_.GetSockfd());
    if(this->channel_ == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Failed to allocate a channel_",
             __FILE__, __LINE__, __FUNCTION__);
    } else {
      this->channel_->SetReadCallback(function::Bind(&Acceptor::Accept, this));
    }
  }
}

Acceptor::~Acceptor() {
  if(this->channel_)
    delete this->channel_;
}

bool Acceptor::Listen() {
  if(this->socket_.Listen(SOMAXCONN) == true) {
    this->channel_->EnableRead();
    return true;
  }
  return false;
}

void Acceptor::Accept(const TimeTick &time_tick) {
  CoreLog(INFO, "Acceptor::Accept()");
  InetAddress peer;
  int peer_sockfd = this->socket_.Accept(peer);
  if(peer_sockfd >= 0) {
    if(this->callback_)
      this->callback_(peer_sockfd, peer);
    else
      ::close(peer_sockfd);
  } else {
    if(errno == EMFILE) {
      // Ignore.
      int ignore_fd = accept(this->socket_.GetSockfd(), NULL, NULL);
      close(ignore_fd);
    }
    CoreLog(ERROR, "%s:%d (%s) Failed to accept",
           __FILE__, __LINE__, __FUNCTION__);
  }
}

}  // namespace core

