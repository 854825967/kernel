//
// core - server core source code.
//
// $Rev: 9885 $
// $Author: $
// $Date: 2012-08-27 18:14:28 +0800 (周一, 2012-08-27) $
//
// Define class TCPConnection.
//

#include "core/tcp_connection.h"

#include <algorithm>

#include "core/core_config.h"
#include "core/event_loop.h"
#include "core/inet_address.h"
#include "core/protocol.h"
#include "core/base/auto_mutex.h"
#include "core/base/ring_queue_common.h"
#include "core/base/logging.h"

namespace core {

#ifdef _CORE_PERFORM_TEST
uint64 kSendTotal = 0;
uint64 kSendSocketTotal = 0;
#endif

const char TCPConnection::kCRLF[] = "\r\n";
const char TCPConnection::kDoubleCRLF[] = "\r\n\r\n";

TCPConnection::TCPConnection(int sockfd, EventLoop *loop,
         const std::string & name, 
         const InetAddress &local, const InetAddress &peer)
         : loop_(loop), channel_(NULL),
           socket_(sockfd), name_(name),
           recycle_logic_(false), recycle_network_(false),
           state_(CONNECTING), /*verified_(false),*/
           local_address_(local), peer_address_(peer),
           send_buffer_(CoreConfig::GetTcpConnection()->buffer_unit_size_),
           recieve_buffer_(CoreConfig::GetTcpConnection()->buffer_unit_size_),
           send_queue_(CoreConfig::GetTcpConnection()->ring_queue_size_,
                  CoreConfig::GetTcpConnection()->ring_queue_unit_size_),
           recieve_queue_(CoreConfig::GetTcpConnection()->ring_queue_size_,
                  CoreConfig::GetTcpConnection()->ring_queue_unit_size_),
           delay_release_(false) , need_gw_forward_receive_(false), need_gw_forward_send_(false) {}

bool TCPConnection::Initialize(bool need_gw_forward_receive, bool need_gw_forward_send) {
  this->need_gw_forward_receive_ = need_gw_forward_receive;
  this->need_gw_forward_send_ = need_gw_forward_send;
  this->channel_ = new Channel(this->loop_, this->socket_.GetSockfd());
  if(this->channel_ == NULL) {
    CoreLog(INFO, "%s:%d (%s) Failed to allocate channel.", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }
  this->channel_->SetReadCallback(function::Bind(&TCPConnection::OnReadCallback, this));
  this->channel_->SetWriteCallback(function::Bind(&TCPConnection::OnWriteCallback, this));
  this->channel_->SetCloseCallback(function::Bind(&TCPConnection::OnCloseCallback, this));
  this->channel_->SetErrorCallback(function::Bind(&TCPConnection::OnErrorCallback, this));
  return true;
}

TCPConnection::~TCPConnection() {
  if(this->channel_) {
    delete this->channel_;
    this->channel_ = NULL;
  }
  CoreLog(INFO, "TCPConnection::~TCPConnection() this=[%p]", this);
#ifdef _CORE_PERFORM_TEST
  CoreLog(INFO, "send=[%lu], send to socket=[%lu]", kSendTotal, kSendSocketTotal);
#endif
}

void TCPConnection::OnReadCallback(const TimeTick &time) {
  // Update timeout.
  this->UpdateTimeout(time);

  if(this->state_ == CONNECTED) {
    // Recieve from socket.
    if(this->Recieve() == true) {
      if(this->need_gw_forward_receive_) {
        const char *double_crlf = std::search(this->recieve_buffer_.ReadPointer(),
            static_cast<const char *>(this->recieve_buffer_.WritePointer()),
            kDoubleCRLF, kDoubleCRLF + 4);
        if(double_crlf < this->recieve_buffer_.WritePointer()) {
          this->recieve_buffer_.ReadShift(double_crlf + 4 - this->recieve_buffer_.ReadPointer());
          this->need_gw_forward_receive_ = false;
          CoreLog(INFO, "Recieve gw forwad package.");
        } else {
          CoreLog(INFO, "Need gw forwad_receive_ recieve_buffer_.ReadSize()=%d.",
              this->recieve_buffer_.ReadSize());
          return ;
        }
      }
      // Flush all message to recieve ring queue.
      this->FlushMessageRing();
    }
  }
}

void TCPConnection::OnWriteCallback() {
  // CoreLog(INFO, "%s:%d (%s) connection can write.", __FILE__, __LINE__, __FUNCTION__);
  // Flush all message to send ring queue.
  int flush = this->FlushMessageBuffer();
  if(flush == FLUSH_EMPTY) {
    // Send to socket.
    this->Send();
  } else if(flush == FLUSH_ERROR) {
    // Error occur, RequireShutdown.
    CoreLog(ERROR, "%s:%d (%s) Error occured, return FLUSH_ERROR.", __FILE__, __LINE__, __FUNCTION__);
    this->RequireShutdown();
  } else if(flush == FLUSH_COMPLETE) {
    this->Send();
    if(this->send_buffer_.ReadSize() <= 0) {
      // Send complete, no data to write, and logic thread must stop
      // the connection, so close the connectin.
      CoreLog(INFO, "%s:%d (%s) complete occrued FLUSH_COMPLETE.", __FILE__, __LINE__, __FUNCTION__);
      this->RequireShutdown();
    }
  }
}

void TCPConnection::OnCloseCallback() {
  CoreLog(INFO, "%s:%d (%s) Close occured.", __FILE__, __LINE__, __FUNCTION__);
  this->RequireShutdown();
}

void TCPConnection::OnErrorCallback() {
  CoreLog(INFO, "%s:%d (%s) Error occured.", __FILE__, __LINE__, __FUNCTION__);
  this->RequireShutdown();
}

void TCPConnection::OnConnectionStart(const TimeTick &time) {
  if(this->channel_ && this->state_ == CONNECTING) {
    // CoreLog(INFO, "%s:%d (%s) Connection starting.", __FILE__, __LINE__, __FUNCTION__);

    this->UpdateTimeout(time);

    this->SetState(CONNECTED);

    // Initialize buffer's capacity.
    this->send_buffer_.PreWrite(CoreConfig::GetTcpConnection()->buffer_init_size_);
    this->recieve_buffer_.PreWrite(CoreConfig::GetTcpConnection()->buffer_init_size_);

    this->channel_->EnableAll();

    if(this->need_gw_forward_send_) {
      this->socket_.Send(kDoubleCRLF, 4);
      this->need_gw_forward_send_ = false;
      CoreLog(INFO, "Send gw forward package");
    }

    // this->connection_callback_(this);
  }
}

void TCPConnection::Shutdown() {
  if(this->state_ == DISCONNECTING) {
    CoreLog(INFO, "%s:%d (%s) Shutdown!!", __FILE__, __LINE__, __FUNCTION__);
    this->SetState(DISCONNECTED);
    this->socket_.Close();
  } 
}

void TCPConnection::Disconnecting() {
  CoreLog(INFO, "%s:%d (%s) Disconnecting!!", __FILE__, __LINE__, __FUNCTION__);
  this->channel_->DisableAll();
  this->recycle_network_ = true;
}

void TCPConnection::RequireShutdown() {
  this->mutex_.Lock();
  if(this->state_ == CONNECTED) {
    this->SetState(DISCONNECTING);
    this->loop_->WakeupCallback(function::Bind(&TCPConnection::Disconnecting, this));
  }
  this->mutex_.Unlock();
}

void TCPConnection::SendMessage(const char *message, int size) {
  if(this->send_queue_.Add(message, size) != size) {
    CoreLog(ERROR, "%s:%d (%s) Failed to add to send ring queue.",
        __FILE__, __LINE__, __FUNCTION__);
  }
  // CoreLog(INFO, "Send data [size=%d]", size);
}

int TCPConnection::RecieveMessage(char *message, int max_size) {
  if(this->send_queue_.CheckEmpty() == false) {
    // Flush send queue.
    this->send_queue_.Flush();
  }

  return this->recieve_queue_.Remove(message, max_size);
}

bool TCPConnection::PacketMessage(const char *data, int size) {
  SimpleByteBufferDynamic *packet = this->loop_->GetPacketBuffer();
  int max_size = packet->GetCapacitySize();
  // Packet.
  int ret = this->loop_->GetPacket()->DoPacket(data, size,
         protocol::GetProtocolData(packet->HeadPointer()), max_size);
  if(ret == 1) {
    // Set size of the packet.
    protocol::SetProtocolHead(packet->HeadPointer(), max_size);
    max_size += protocol::kProtocolHeadSize;
    if(this->send_buffer_.PreWrite(max_size) == true) {
      memcpy(this->send_buffer_.WritePointer(), packet->HeadPointer(), max_size);
      this->send_buffer_.WriteShift(max_size);
    } else {
      CoreLog(ERROR, "%s:%d (%s) PreWrite error.", __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
    return true;

  } else if(ret == 0) {
    // Not need packet, first, copy the head.
    // memcpy(this->send_buffer_.WritePointer(), &size, protocol::kProtocolHeadSize);
    if(this->send_buffer_.PreWrite(size + protocol::kProtocolHeadSize) == true) {
      *protocol::ProtocolHeadCast(this->send_buffer_.WritePointer()) = size;
      // Second, copy the data.
      memcpy(protocol::GetProtocolData(this->send_buffer_.WritePointer()), data, size);
      this->send_buffer_.WriteShift(size + protocol::kProtocolHeadSize);
    } else {
      CoreLog(ERROR, "%s:%d (%s) PreWrite error.", __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
    return true;
  } else {
    CoreLog(ERROR, "%s:%d (%s) DoPacket error.", __FILE__, __LINE__, __FUNCTION__);
  }

  return false;
}

bool TCPConnection::UnpacketMessage(const char *packet, int size) {
  SimpleByteBufferDynamic *buffer = this->loop_->GetTempBuffer();
  int max_size = buffer->GetCapacitySize();
  int ret = this->loop_->GetPacket()->UndoPacket(packet,
         size, buffer->HeadPointer(), max_size);
  if(ret == 1) {
    if(this->recieve_queue_.Add(buffer->HeadPointer(), max_size) != max_size) {
      CoreLog(ERROR, "%s:%d (%s) recieve_queue_ Add error.", __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
    return true;
  } else if(ret == 0) {
    if(this->recieve_queue_.Add(packet, size) != size) {
      CoreLog(ERROR, "%s:%d (%s) recieve_queue_ Add error.", __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
    return true;
  }
  return false;
}

int TCPConnection::FlushMessageBuffer() {
  SimpleByteBufferDynamic *buffer = this->loop_->GetTempBuffer();
  int size = 0;
  while(true) {
    // CoreLog(INFO, "%s:%d (%s) Try to send message.", __FILE__, __LINE__, __FUNCTION__);
    size = this->send_queue_.Remove(buffer->HeadPointer(), buffer->GetCapacitySize());
    if(size >= 0) {
      if(this->PacketMessage(buffer->HeadPointer(), size) == false) return FLUSH_ERROR;
    } else {
      if(size == ring_queue::kErrorCodeEmpty) return FLUSH_EMPTY;
      else if(size == ring_queue::kErrorCodeComplete) return FLUSH_COMPLETE;
      else {
        CoreLog(ERROR, "%s:%d (%s) send_queue Remove error.", __FILE__, __LINE__, __FUNCTION__);
        return FLUSH_ERROR;
      }
    }
  }
}

int TCPConnection::FlushMessageRing() {
  SimpleByteBufferDynamic *packet = this->loop_->GetPacketBuffer();
  int packet_size = 0;
  while((uint32)(this->recieve_buffer_.ReadSize()) > protocol::kProtocolHeadSize) {
    packet_size = protocol::GetPacketSize(this->recieve_buffer_.ReadPointer());
    if(packet_size > this->recieve_buffer_.ReadSize()) return FLUSH_COMPLETE;
    memcpy(packet->HeadPointer(), this->recieve_buffer_.ReadPointer(), packet_size);

    if(this->UnpacketMessage(protocol::GetProtocolData(packet->HeadPointer()),
           packet_size - protocol::kProtocolHeadSize) == true) {
      this->recieve_buffer_.ReadShift(packet_size);
      // CoreLog(INFO, "%s:%d (%s) Success flushing message to ring.", __FILE__, __LINE__, __FUNCTION__);
    } else {
      return FLUSH_ERROR;
      CoreLog(ERROR, "%s:%d (%s) Failed to flush message.", __FILE__, __LINE__, __FUNCTION__);
    }
  }
  return FLUSH_COMPLETE;
}

void TCPConnection::Send() {
  int size = this->send_buffer_.ReadSize();
  if(size > 0) {
    int ret = this->socket_.Send(this->send_buffer_.ReadPointer(),
        size);
    if(ret > 0) {
#ifdef _CORE_PERFORM_TEST
      kSendSocketTotal += ret;
#endif
      // CoreLog(INFO, "Send data to socket [size=%d]", ret);
      this->send_buffer_.ReadShift(ret);
    } else if(ret < 0) {
      this->OnErrorCallback();
    }
  }
}

bool TCPConnection::Recieve() {
  // Ensure could recieve 1 message.
  this->recieve_buffer_.PreWrite(CoreConfig::GetTcpConnection()->buffer_unit_size_);
  int ret = this->socket_.Recieve(this->recieve_buffer_.WritePointer(),
         this->recieve_buffer_.WriteSize());
  if(ret > 0) {
    CoreLog(INFO, "TCPConnection::Recieve() size=%d this=%p", ret, this);
    // CoreLog(INFO, "%s:%d (%s) Recieve data from socket [size=%d]", __FILE__, __LINE__, __FUNCTION__, ret);
    // Every time recieving complete, PreWrite will enlarge the capacity of buffer,
    // this enlarging will reach a balance situation in maybe servral times(this
    // depends on the communication speed).
    this->recieve_buffer_.PreWrite(CoreConfig::GetTcpConnection()->buffer_unit_size_);
    // Shift write pointer.
    this->recieve_buffer_.WriteShift(ret);
  }
  else if(ret == 0) {
    this->OnCloseCallback();
  } else {
    this->OnErrorCallback();
    return false;
  }

  return true;
}

}  // namespace core

