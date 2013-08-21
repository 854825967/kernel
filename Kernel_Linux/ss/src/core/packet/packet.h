//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (鍛ㄤ簲, 2011-12-30) $
//
// Define class Packet.
//

#ifndef __PACKET__H
#define __PACKET__H

#include "core/base/byte_buffer_dynamic.h"
#include "core/packet/compress.h"
#include "core/packet/encrypt.h"

namespace core {

class Packet {
 public:
  Packet();
  ~Packet();

  // Get max size of packet/unpacket.
  int GetPacketMaxSize(int size) const;
  int GetUnpacketMaxSize(int size) const;

  // Packet/Unpacket a message.
  // Return >0 : successful.
  // return =0 : with no need for packeting.
  // return <0 : failed.
  int DoPacket(const char *in, int size, char *out, int &max_size);
  int UndoPacket(const char *in, int size, char *out, int &max_size);

  // Set encrypt/compress tools.
  inline void SetEncrypt(Encrypt *encrypt) {
    this->encrypt_ = encrypt;
  }
  inline void SetComress(Compress *compress) {
    this->compress_ = compress;
  }

 private:
  Encrypt *encrypt_;
  Compress *compress_;

  SimpleByteBufferDynamic buffer_;
};

}  // namespace core

#endif  // __PACKET__H

