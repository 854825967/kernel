//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (周五, 2011-12-30) $
//
// Define class Packet.
//

#include "core/packet/packet.h"

#include "core/base/logging.h"

namespace core {

Packet::Packet() : encrypt_(NULL), compress_(NULL) {}
Packet::~Packet() {}

int Packet::GetPacketMaxSize(int size) const {
  if(this->encrypt_) {
    size = this->encrypt_->GetMaxEncryptSize(size);
    if(this->compress_) return this->compress_->GetMaxCompressSize(size);
  } else {
    if(this->encrypt_) {
      return this->compress_->GetMaxCompressSize(size);
    }
  }
  return size;
}

int Packet::GetUnpacketMaxSize(int size) const {
  if(this->compress_) {
    size = this->compress_->GetMaxUncompressSize(size);
    if(this->encrypt_) this->encrypt_->GetMaxDecryptSize(size);
  } else {
    if(this->encrypt_) this->encrypt_->GetMaxDecryptSize(size);
  }
  return size;
}

int Packet::DoPacket(const char *in, int size, char *out, int &max_size) {
  if(this->encrypt_) {
    this->buffer_.PreWrite(max_size);
    int temp_size = max_size;
    if(this->encrypt_->DoEncrypt(in, size, this->buffer_.HeadPointer(), temp_size) == false) {
      CoreLog(ERROR, "%s:%d (%s) Failed to Encrypt.", __FILE__, __LINE__, __FUNCTION__);
      return -1;
    }
    if(this->compress_) {
      if(this->compress_->DoCompress(this->buffer_.HeadPointer(), temp_size, out, max_size) == false) {
        CoreLog(ERROR, "%s:%d (%s) Failed to Compress.", __FILE__, __LINE__, __FUNCTION__);
        return -1;
      }
    }
    return 1;
  } else {
    if(this->compress_) {
      if(this->compress_->DoCompress(in, size, out, max_size) == false) {
        CoreLog(ERROR, "%s:%d (%s) Failed to Compress.", __FILE__, __LINE__, __FUNCTION__);
        return -1;
      }
      return 1;
    }
    return 0;
  }
}

int Packet::UndoPacket(const char *in, int size, char *out, int &max_size) {
  if(this->compress_) {
    this->buffer_.PreWrite(max_size);
    int temp_size = max_size;
    if(this->compress_->UnDocompress(in, size, this->buffer_.HeadPointer(), temp_size) == false) {
      CoreLog(ERROR, "%s:%d (%s) Failed to Unompress.", __FILE__, __LINE__, __FUNCTION__);
      return -1;
    }
    if(this->encrypt_) {
      if(this->encrypt_->DoDecrypt(this->buffer_.HeadPointer(), temp_size, out, max_size) == false) {
        CoreLog(ERROR, "%s:%d (%s) Failed to Decrypt.", __FILE__, __LINE__, __FUNCTION__);
        return -1;
      }
    }
    return 1;
  } else {
    if(this->encrypt_) {
      if(this->encrypt_->DoDecrypt(in, size, out, max_size) == false) {
        CoreLog(ERROR, "%s:%d (%s) Failed to Decrypt.", __FILE__, __LINE__, __FUNCTION__);
        return -1;
      }
      return 1;
    }
    return 0;
  }
}

}  // namespace core

