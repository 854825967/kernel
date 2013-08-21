//
// core - server core source code.
//
// $Rev: 9885 $
// $Author: $
// $Date: 2012-08-27 18:14:28 +0800 (鍛ㄤ竴, 2012-08-27) $
//
// Define class TCPConnection.
//

#ifndef __TCP__CONNECTION__H
#define __TCP__CONNECTION__H

#include <string>

#include "core/callbacks.h"
#include "core/channel.h"
#include "core/core_config.h"
#include "core/tcp_socket.h"
#include "core/base/boundless_ring_queue.h"
#include "core/base/byte_buffer_dynamic.h"
#include "core/base/mutex.h"
#include "core/base/noncopyable.h"
#include "core/base/types.h"
#include "core/base/time_tick.h"

namespace core {

class EventLoop;
class InetAddress;

class TCPConnection : public Noncopyable {
 public:
  TCPConnection(int sockfd, EventLoop *loop, const std::string & name, 
         const InetAddress &local, const InetAddress &peer);
  virtual ~TCPConnection();

  bool Initialize(bool need_gw_forward_received, bool need_gw_forward_send);

  inline void SetConnectionEstablishedCallback(
         const ConnectionEstablishedCallback &callback) {
    this->connection_callback_ = callback;
  }

  inline void SetEventLoop(EventLoop *loop) {
    this->channel_->SetEventLoop(loop);
    this->loop_ = loop;
  }

  // Callback.
  void OnReadCallback(const TimeTick &time);
  void OnWriteCallback();
  void OnCloseCallback();
  void OnErrorCallback();
  // Connection start.
  void OnConnectionStart(const TimeTick &time);

  // Check state is disconnected.
  inline bool CheckDisconnecting() const { return this->state_ == DISCONNECTING; }

  // ----------------------------------------------
  // Only for schedule thread(recycle thread).
  // Check logic and network recycled flag.
  // For client, this invoke is for logic thread.
  inline bool CheckCanRecycle() const {
    return this->recycle_logic_ && this->recycle_network_;
  }
  inline bool CheckLogicRecycle() const {
    return this->recycle_logic_;
  }
  inline bool CheckNetworkRecycle() const {
    return this->recycle_network_;
  }
  // ----------------------------------------------

  // ----------------------------------------------
  // Only for Logic thread.
  // Set flag of logic recycled
  inline void SetLogicRecycled() { this->recycle_logic_ = true; }
  // ----------------------------------------------

  // ----------------------------------------------
  // Only for network thread.
  // Set flag of network recycled
  inline void SetNetworkRecycled() { this->recycle_network_ = true; }
  // ----------------------------------------------

  // Name.
  const std::string &GetName() const {
    return this->name_;
  }

  // Address.
  const InetAddress &GetLocalAddress() const { return this->local_address_; }
  const InetAddress &GetPeerAddress() const { return this->peer_address_; }

  // Require to shutdown.
  void RequireShutdown();

  // Send/Recieve for logic.
  void SendMessage(const char *message, int size);
  int RecieveMessage(char *message, int max_size);

  // Check timeout for kick.
  inline bool CheckTimeout(const TimestampMillisecond &timestamp) const {
    return this->timeout_.AbsoluteDistance(timestamp) >
           static_cast<uint32>(CoreConfig::GetTcpConnection()->kick_timeout_);
  }

  // Check delay release.
  inline bool CheckDelayRelease() const { return this->delay_release_; }

  // For logic thread to notify network thread.
  inline void SendCompletely() { this->send_queue_.ProduceCompletely(); }

  // Connection callback.
  ConnectionEstablishedCallback connection_callback_;

  // Shut down write.
  void Shutdown();

 protected:
  enum { CONNECTING = 0, CONNECTED, DISCONNECTING, DISCONNECTED, };
  enum { FLUSH_COMPLETE = 0, FLUSH_EMPTY, FLUSH_ERROR,  };

  // FlushMessageBuffer Will move all the message in the ring to buffer(to socket).
  int FlushMessageBuffer();
  // FlushMessageRing will move all the message in the buffer to ring(to logic).
  int FlushMessageRing();

  // SetState.
  inline void SetState(uint8 state) { this->state_ = state; }

  // Send/Recieve for network.
  void Send();
  bool Recieve();

  inline void UpdateTimeout(const TimeTick &time_tick) {
    this->timeout_.Stamp(time_tick);
  }

  // Close connection.
  void Disconnecting();

  // Packet/Unpacket
  bool PacketMessage(const char *data, int size);
  bool UnpacketMessage(const char *packet, int size);

  // Loop, channel and socket.
  EventLoop *loop_;
  Channel *channel_;
  TCPSocket socket_;

  // Name.
  std::string name_;

  // Recycle flag.
  // Schedule thread uses 2 flag to ensure thread-safe recycle tcp connection.
  bool recycle_logic_;
  bool recycle_network_;
  // CONNECTED, DISCONNECTING, DISCONNECTED.
  uint8 state_;

  // For logic check verifyed.
  // bool verified_;

  // Address.
  InetAddress local_address_;
  InetAddress peer_address_;

  // Buffer.
  ByteBufferDynamic send_buffer_;
  ByteBufferDynamic recieve_buffer_;

  // Ring queue.
  BoundlessRingQueue send_queue_;
  BoundlessRingQueue recieve_queue_;

  // 
  TimestampMillisecond timeout_;

  mutable Mutex mutex_;

  // delay release flag.
  bool delay_release_;

  // 
  bool communicating_;

  // has received tencent gateway's forward package.
  bool need_gw_forward_receive_;
  bool need_gw_forward_send_;

  static const char kCRLF[];
  static const char kDoubleCRLF[];
};

}  // namespace core

#endif  // __TCP__CONNECTION__H

