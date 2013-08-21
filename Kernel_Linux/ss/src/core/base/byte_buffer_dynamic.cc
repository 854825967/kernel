//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (周五, 2011-12-30) $
//
// Define class ByteBufferDynamic.
//
// This is a dynamic length buffer, using for socket to receive/send data.
// This buffer contains two pointers, you can use these pointers to read/write
// data from/to it. Before you write any data to buffer, you should check the
// buffer is enough using function - "PreWrite" (this function can reallocate
// the buffer when the buffer is not enough), After reading/writing, you should
// shift the buffer using the function - "ReadShift/WriteShift".
// This ByteBufferDynamic supports ordering read and random read, but only
// supports ordering write.
// If need, compile with "_BYTE_BUFFER_DYNAMIC_CHECK", this will check buffer
// overflow.
//

#include <string.h>

#include "core/base/byte_buffer_dynamic.h"

#include "core/base/logging.h"

namespace core {

bool ByteBufferDynamic::PreWrite(const int size) {
  if(this->WriteSize() < size) {
    // allocate the minimum multiples of the unit_buffer_size_
    int multiple = (size + this->unit_buffer_size_) / this->unit_buffer_size_;
#ifdef _BYTE_BUFFER_DYNAMIC_CHECK
    if(this->max_count_ - multiple < this->allocate_count_) {
      return false;
    }
#endif

    CoreLog(INFO, "%s:%d (%s) Resize ByteBufferDynamic, buffer_size_=[%u], write_size=[%u], prewrite size=[%u]",
           __FILE__, __LINE__, __FUNCTION__, this->buffer_size_, this->WriteSize(), size);

    int add_size = this->unit_buffer_size_ * multiple;
    this->buffer_size_ += add_size;

#ifdef _CORE_DEBUG
    static int prewrite_count = 0;
    CoreLog(INFO, "%s:%d (%s) Resize ByteBufferDynamic prewrite_count=%u, add_size=%u, buffer_size_=%u",
           __FILE__, __LINE__, __FUNCTION__, ++prewrite_count, add_size, this->buffer_size_);
#endif

    this->buffer_.resize(this->buffer_size_);

#ifdef _BYTE_BUFFER_DYNAMIC_CHECK
    this->allocate_count_ += multiple;
#endif
  }
  return true;
}

void ByteBufferDynamic::ReduceBufferSize() {
  int write_size = this->WriteSize();

  if(write_size > this->unit_buffer_size_ << 1) {
    int multiples = write_size >> 1;
    // Up to multiples of unit_buffer_size_.
    multiples = (multiples + this->unit_buffer_size_) / this->unit_buffer_size_;
    this->buffer_size_ -= write_size;
    this->buffer_size_ += this->unit_buffer_size_ * multiples;
    this->buffer_.resize(this->buffer_size_);

#ifdef _CORE_DEBUG
    CoreLog(INFO, "%s:%d (%s) Reduce buffer size [%u]",
           __FILE__, __LINE__, __FUNCTION__, write_size - this->unit_buffer_size_ * multiples);
#endif
  }
}

void ByteBufferDynamic::ReadShift(int size) {
  this->Shift(size, 0);
}

void ByteBufferDynamic::WriteShift(int size) {
  this->Shift(0, size);
}

void ByteBufferDynamic::RandomReadShift(int position, int size) {
  memmove(&this->buffer_[position], &this->buffer_[position + size], size);
  this->write_index_ -= size;
}

void ByteBufferDynamic::Shift(int read_size, int write_size) {
  this->read_index_ += read_size;
  this->write_index_ += write_size;

  if(this->read_index_ > 0) {
    int shift_size = this->write_index_ - this->read_index_;
    if(shift_size != 0) {
      memmove(&this->buffer_[0], &this->buffer_[this->read_index_], shift_size);
      this->read_index_ = 0;
      this->write_index_ = shift_size;
    } else {
      this->read_index_ = 0;
      this->write_index_ = 0;
    }
  }
}

}  // namespace amz

