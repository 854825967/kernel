//
// core - server core source code.
//
// $Rev: 2353 $
// $Author: $
// $Date: 2011-12-08 18:05:59 +0800 (鍛ㄥ洓, 2011-12-08) $
//
// Define class ByteBufferStatic.
//
// This is a fixed length buffer.
//

#ifndef __BYTE__BUFFER__STATIC
#define __BYTE__BUFFER__STATIC

#include "core/base/logging.h"

namespace core {

// Use stack memory.
template <int BufferSize>
class ByteBufferStatic {
 public:
  ByteBufferStatic() {}
  ~ByteBufferStatic() {}

  inline uint8 *BufferPointer() const { return this->buffer_; }

 private:
  uint8 buffer_[BufferSize];
};

// Use heap memory.
class ByteBufferStaticMalloc {
 public:
  explicit ByteBufferStaticMalloc(uint32 buffer_size) : buffer_(NULL) {
	this->buffer_ = new uint8[buffer_size];
	if(this->buffer_ == NULL) {
	  LOG(FATAL) << "Not enough memory for ByteBufferStatic2";
	}
  }
  ~ByteBufferStaticMalloc() {
    if(this->buffer_) {
	  delete [] this->buffer_;
	  this->buffer_ = NULL;
	}
  }

  inline uint8 *BufferPointer() const { return this->buffer_; }

 private:
  uint8 *buffer_;
};

}  // namespace core

#endif  // __BYTE__BUFFER__STATIC

