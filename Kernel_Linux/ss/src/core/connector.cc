//
// core - server core source code.
//
// $Rev: 6708 $
// $Author: $
// $Date: 2012-04-12 17:41:05 +0800 (周四, 2012-04-12) $
//
// Define class Connector.
// This Connector uses non-blocking pattern and must run in a EventLoop.
//

#include "core/connector.h"

#include <errno.h>

#include "core/channel.h"
#include "core/event_loop.h"
#include "core/base/logging.h"

namespace core {

Connector::Connector(EventLoop *loop,
       const InetAddress &server_address, int retry_msec)
       : address_(server_address), loop_(loop),
         channel_(NULL), state_(DISCONNECTED),
         retry_msec_(retry_msec), retry_flag_(false) {}

Connector::~Connector() {
  if(this->retry_msec_ > 0 && this->retry_flag_ == true) {
    this->loop_->RemoveTimer(1, this);
    this->retry_flag_ = false;
  }
  this->socket_.Close();
  this->RemoveChannel();
}

void Connector::OnTimer(uint32 id) {
  this->loop_->RemoveTimer(1, this);
  this->retry_flag_ = false;

  this->Start();
}

void Connector::Start() {
  if(this->state_ == DISCONNECTED) {
    // To connect.
    this->Connect();
    this->state_ = CONNECTING;
  } else {
    CoreLog(ERROR, "%s:%d (%s) Failed to create socket or bind address.",
           __FILE__, __LINE__, __FUNCTION__);
  }
}

void Connector::Stop() {
  this->socket_.Close();
  this->state_ = DISCONNECTED;
}

void Connector::Restart() {
  this->Stop();
  if(this->retry_msec_ > 0) {
    this->state_ = DISCONNECTED;
    if(this->retry_flag_ == true) {
      this->loop_->RemoveTimer(1, this);
    }
    this->loop_->AddTimer(1, this->retry_msec_, 1, this, __FUNCTION__);
    this->retry_flag_ = true;
  } else {
    CoreLog(ERROR, "%s:%d (%s) Failed to restart, retry_msec_=[%d].",
           __FILE__, __LINE__, __FUNCTION__, this->retry_msec_);
  }
}

void Connector::Connect() {
  CoreLog(INFO, "Connector begin to connect");
  if(this->socket_.CreateSocket() == true && this->socket_.SetNonblock() == true) {
    if(this->socket_.Connect(this->address_) == true) {
      // Channel
      this->channel_ = new Channel(this->loop_, this->socket_.GetSockfd());
      this->channel_->SetWriteCallback(function::Bind(&Connector::OnComplete, this));
      this->channel_->SetErrorCallback(function::Bind(&Connector::OnError, this));
      this->channel_->EnableWrite();
    } else {
      // TODO: Retry timeout.
      this->Restart();
      CoreLog(ERROR, "%s:%d (%s) Failed to connect to address(%s)",
       __FILE__, __LINE__, __FUNCTION__, this->address_.GetString().c_str());
    }
  }
}

void Connector::RemoveChannel() {
  if(this->channel_) {
    this->channel_->DisableAll();
    delete this->channel_;
    this->channel_ = NULL;
  }
}

void Connector::DelayRemoveChannel() {
  this->loop_->LoopInOnceCallback(function::Bind(&Connector::RemoveChannel, this));
}

void Connector::OnComplete() {
  if(this->state_ == CONNECTING) {
    // Remove the retry timer.
    if(this->retry_msec_ > 0 && this->retry_flag_ == true) {
      this->loop_->RemoveTimer(1, this);
      this->retry_flag_ = false;
    }
    this->DelayRemoveChannel();
    this->state_ = CONNECTED;
    // Get peer address.
    struct sockaddr_in local_address;
    memset(&local_address, 0, sizeof(local_address));
    socklen_t addrlen = sizeof(local_address);
    if(::getsockname(this->socket_.GetSockfd(), (struct sockaddr *)(&local_address), &addrlen) < 0)
    {
      CoreLog(ERROR, "%s:%d (%s) Failed to getsockname", __FILE__, __LINE__, __FUNCTION__);
    } else {
      CoreLog(INFO, "Connector connect complete");
      if(this->callback_) {
        this->callback_(this->socket_.GetSockfd(), InetAddress(local_address));
      }
    }
  }
}

void Connector::OnError() {
  int optval;
  socklen_t optlen = sizeof(optval);
  if (::getsockopt(this->socket_.GetSockfd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    optval = errno;

  CoreLog(ERROR, "%s:%d (%s) Error occur error(%d) address(%s)",
       __FILE__, __LINE__, __FUNCTION__, optval, this->address_.GetString().c_str());

  this->DelayRemoveChannel();

  this->Restart();
}

}  // namespace core

