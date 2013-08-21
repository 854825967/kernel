//
// core - server core source code.
//
// $Rev: 6647 $
// $Author: $
// $Date: 2012-04-10 20:26:21 +0800 (周二, 2012-04-10) $
//
// Define class BoundRingQueue.
//

#include "core/base/bound_ring_queue.h"

#include "core/base/auto_mutex.h"
#include "core/base/logging.h"
#include "core/base/ring_queue_common.h"
#include "core/base/types.h"

namespace core {

using namespace ring_queue;

BoundRingQueue::BoundRingQueue(uint32 max_size, bool blocking)
       : ring_(max_size + 1),
         ring_size_(max_size),
         write_pointer_(0),
         read_pointer_(0),
         blocking_(blocking),
         produce_completely_(false) {
  if(this->ring_size_ == 0)
    CoreLog(ERROR, "%s:%d (%s) Error size allocation in BoundRingQueue.",
           __FILE__, __LINE__, __FUNCTION__);
}

BoundRingQueue::~BoundRingQueue() {}

int BoundRingQueue::Add(const char *data, int size) {
  // Save the read pointer, in case consumer thread altering.
  uint32 read_pointer = this->read_pointer_;
  uint32 need_size = sizeof(RingQueueElement) + size;
  uint32 free_size = 0;
  
  // Get the free size.
  RING_QUEUE_FREE_SIZE(this->ring_size_, read_pointer,
         this->write_pointer_, free_size);

  // Separate blocking/non-blocking pattern to check ring's full.
  if(this->blocking_ == true) {
    AutoMutex auto_mutex(&this->mutex_not_full_);
    while(free_size < need_size) {
      this->condition_not_full_.Wait(&this->mutex_not_full_);
      read_pointer = this->read_pointer_;
      RING_QUEUE_FREE_SIZE(this->ring_size_, read_pointer,
             this->write_pointer_, free_size);
    }
  } else {
    if(free_size < need_size) return kErrorCodeFull;
  }

  // Get the real pointer of ring.
  char *ring_pointer = (char *)this->ring_.BufferPointer();
  // Get the free size after write_pointer_.
  uint32 after_write_pointer_size = 0;
  RING_QUEUE_FREE_SIZE_AFTER_WRITE_POINTER(
         this->ring_size_, read_pointer,
         this->write_pointer_, after_write_pointer_size);
	
  if(after_write_pointer_size >= need_size) {
    // Give the size of data at the begin position.
    RingQueueElement *temp_data
	       = (RingQueueElement *)(&(ring_pointer[this->write_pointer_]));
    temp_data->data_size_ = size;
    memcpy(temp_data->data_pointer_, data, size);
    // This position write_pointer_'s altering must behind the copying.
    this->write_pointer_ += need_size;
  } else {
    // Not enough, copy to the end position and copy the left to the begin position.
    if(after_write_pointer_size >= sizeof(RingQueueElement)) {
      // The size after the write position have enough space to hold the size of data.
      RingQueueElement *temp_data =
             (RingQueueElement *)(&(ring_pointer[this->write_pointer_]));
      temp_data->data_size_ = size;
      after_write_pointer_size -= sizeof(RingQueueElement);
      memcpy(temp_data->data_pointer_, data, after_write_pointer_size);
      uint32 second_part_size = size - after_write_pointer_size;
      memcpy(ring_pointer, &data[after_write_pointer_size], second_part_size);
      this->write_pointer_ = second_part_size;
    } else {
      // Not enough, copy the first part of "size" to the write position, then copy the
      // second part to the begin position, at last, copy the data.
      memcpy(&(ring_pointer[this->write_pointer_]),
             (char *)(&size), after_write_pointer_size);
      uint32 second_part_size = sizeof(RingQueueElement) - after_write_pointer_size;
      memcpy(ring_pointer, &(((char *)(&size))[after_write_pointer_size]),
             second_part_size);
      memcpy(&ring_pointer[second_part_size], data, size);
      // This position write_pointer_'s altering must behind the copying action.
      this->write_pointer_ = need_size - after_write_pointer_size;
    }
  }
  
  // Blocking pattern.
  if(this->blocking_ == true) {
    AutoMutex auto_mutex(&this->mutex_not_empty_);
    this->condition_not_empty_.Signal();
  }

  return size;
}

int BoundRingQueue::Remove(char *data, int max_size) {
  // Save the write pointer, in case producer thread altering.
  uint32 write_pointer = this->write_pointer_;
  uint32 can_read_size = 0;

  RING_QUEUE_READ_SIZE(this->ring_size_, this->read_pointer_,
         write_pointer, can_read_size);

  // Separate blocking/non-blocking pattern to check ring's empty.
  if(this->blocking_ == true) {
    AutoMutex auto_mutex(&this->mutex_not_empty_);
    while(can_read_size == 0) {
      if(this->CheckProduceCompletely() == true) {
        return kErrorCodeComplete;
      }
      this->condition_not_empty_.Wait(&this->mutex_not_empty_);
      write_pointer = this->write_pointer_;
      // Get the can read size again.
      RING_QUEUE_READ_SIZE(this->ring_size_, this->read_pointer_,
         write_pointer, can_read_size);
    }
  } else {
    if(can_read_size == 0) {
      if(this->CheckProduceCompletely() == true)
        return kErrorCodeComplete;
      else
        return kErrorCodeEmpty;
    }
  }

  if(can_read_size < sizeof(RingQueueElement)) {
    CoreLog(ERROR, "%s:%d (%s) Error, read size(%d)", __FILE__, __LINE__, __FUNCTION__, can_read_size);
    return kErrorCodeUnknown;
  }
  
  // Get real pointer of ring.
  char *ring_pointer = (char *)this->ring_.BufferPointer();
	
  // Get the read size after read_pointer_.
  uint32 after_read_pointer_size = 0;
  RING_QUEUE_READ_SIZE_AFTER_READ_POINTER(
        this->ring_size_, this->read_pointer_,
        write_pointer, after_read_pointer_size);

		 
  if(after_read_pointer_size >= sizeof(RingQueueElement)) {
    RingQueueElement *temp_data
           = (RingQueueElement *)(&(ring_pointer[this->read_pointer_]));
    // Check size is enough.
    if(temp_data->data_size_ > (uint32)max_size) {
      return kErrorCodeErrorSize;
    }
    // Save the size, should do it before change read_pointer_.
    uint32 data_size = temp_data->data_size_;
    uint32 read_size = data_size + sizeof(RingQueueElement);
    // Check valid
    if(read_size > can_read_size || data_size > (uint32)max_size) {
      CoreLog(ERROR, "%s:%d (%s) Error size, read_size(%d), can_read_size(%d), max_size(%d)",
             __FILE__, __LINE__, __FUNCTION__, read_size, can_read_size, max_size);
      return kErrorCodeUnknown;
    }
    // Read data.
    if(after_read_pointer_size > read_size) {
      // All this data data after read_pointer_.
      memcpy(data, temp_data->data_pointer_, data_size);
      this->read_pointer_ += read_size;
    } else if(after_read_pointer_size == read_size) {
      memcpy(data, temp_data->data_pointer_, data_size);
      if(write_pointer > this->read_pointer_) {
        this->read_pointer_ += read_size;
      } else {
        // If read to the end, set read_pointer_ 0 value.
        this->read_pointer_ = 0;
      }
    } else {
      // Copy the data from ring queue, when copy the first part of data, we should
      // filter the head size.
      uint32 first_part_size = after_read_pointer_size - sizeof(RingQueueElement);
      // first part.
      memcpy(data, temp_data->data_pointer_, first_part_size);
      uint32 second_part_size = read_size - after_read_pointer_size;
      // second part.
      memcpy(&data[first_part_size], ring_pointer, second_part_size);
      this->read_pointer_ = second_part_size;
    }

    // Blocking pattern.
    if(this->blocking_ == true) {
      AutoMutex auto_mutex(&this->mutex_not_full_);
      this->condition_not_full_.Signal();
    }

    return data_size;
	
  } else {
    // The read size after read_pointer is less than an head size.
    RingQueueElement temp_data;
    char* head = (char *)(&temp_data);
    uint32 second_part_size = sizeof(RingQueueElement) - after_read_pointer_size;
    // Divide into 2 parts to copy a head.
    memcpy(head, &(ring_pointer[this->read_pointer_]), after_read_pointer_size);
    memcpy(&head[after_read_pointer_size], ring_pointer, second_part_size);
    // Check size is enough.
    if(temp_data.data_size_ > (uint32)max_size) {
      return kErrorCodeErrorSize;
    } 
    if(can_read_size < temp_data.data_size_ + sizeof(RingQueueElement)) {
      CoreLog(ERROR, "%s:%d (%s) Error size, read size is too small, can_read_size(%d), need_size(%d)",
             __FILE__, __LINE__, __FUNCTION__, can_read_size, temp_data.data_size_ + sizeof(RingQueueElement));
      return kErrorCodeUnknown;
    }
    // Copy the data directly.
    memcpy(data, &ring_pointer[second_part_size], temp_data.data_size_);
    this->read_pointer_ = temp_data.data_size_ + second_part_size;

    // Blocking pattern.
    if(this->blocking_ == true) {
      AutoMutex auto_mutex(&this->mutex_not_full_);
      this->condition_not_full_.Signal();
    }

    return temp_data.data_size_;
  }
}

void BoundRingQueue::ProduceCompletely() {
  // First update variable.
  this->produce_completely_ = true;

  if(this->blocking_ == true) {
    AutoMutex auto_mutex(&this->mutex_not_empty_);
    this->condition_not_empty_.Signal();
  }
}

}  // namespace core

