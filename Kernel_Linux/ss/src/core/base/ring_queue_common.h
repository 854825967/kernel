//
// core - server core source code.
//
// $Rev: 6219 $
// $Author: $
// $Date: 2012-03-25 18:45:54 +0800 (鍛ㄦ棩, 2012-03-25) $
//
// Ring queue's common define.
//

#ifndef __RING__QUEUE__COMMON__H
#define __RING__QUEUE__COMMON__H


namespace core {

namespace ring_queue {

// the structure defines element in the RingQueueInterface.
struct RingQueueElement {
  uint32 data_size_;
  char data_pointer_[0];
};

const static int kBlockingAllPattern = 0;
const static int kBlockingConsumerPattern = 1;
const static int kBlockingProducerPattern = 2;
const static int kNonblockingPattern = 3;

// Blocking pattern.
enum BlockingPattern {
  NONBLOCKING = 0x0,
  BLOCKING_ALL = 0x1, 
  BLOCKING_CONSUMER = 0x2,
  BLOCKING_PRODUCER = 0x4,
};

// Sucessful.
const static int kErrorCodeSuccess = 0;

// Only in non-blocking pattern.
const static int kErrorCodeFull = -1;
const static int kErrorCodeEmpty = -1;
const static int kErrorCodeAllocate = -2;

// Either blocking/non-blocking pattern.
const static int kErrorCodeComplete = -2;
const static int kErrorCodeErrorSize = -3;
const static int kErrorCodeUnknown = -4;

}  // namespace ring_queue

// check is empty.
#define RING_QUEUE_EMPTY(read_pointer, write_pointer) \
  ((read_pointer) == (write_pointer))
  
// check is full.
#define RING_QUEUE_FULL(max_size, read_pointer, write_pointer) \
  (((write_pointer + 1) % (max_size + 1)) == (read_pointer))
  
// get free size.
#define RING_QUEUE_FREE_SIZE(max_size, read_pointer, write_pointer, free_size) \
  do { \
    if(RING_QUEUE_EMPTY(read_pointer, write_pointer)) { \
      free_size = max_size; \
    } else if(read_pointer > write_pointer) { \
      free_size = read_pointer - write_pointer - 1; \
    } else { \
      free_size = max_size - (write_pointer - read_pointer); \
    } \
  } while(false)
  
// This is some error
// The size after write_pointer.
#define RING_QUEUE_FREE_SIZE_AFTER_WRITE_POINTER(max_size, read_pointer, write_pointer, free_size_after_write_pointer) \
  do { \
    if(read_pointer == write_pointer) \
      free_size_after_write_pointer = max_size - write_pointer + 1;\
    else if(read_pointer > write_pointer) \
      free_size_after_write_pointer = read_pointer - write_pointer - 1; \
    else \
      if(read_pointer == 0) \
        free_size_after_write_pointer = max_size - write_pointer; \
      else \
        free_size_after_write_pointer = max_size - write_pointer + 1; \
  } while(false)
  
// The size you can read from ring queue.
#define RING_QUEUE_READ_SIZE(max_size, read_pointer, write_pointer, read_size) \
  do { \
    RING_QUEUE_FREE_SIZE(max_size, read_pointer, write_pointer, read_size); \
    read_size = max_size - read_size; \
  } while(false)
  
// The read size after read_pointer.
#define RING_QUEUE_READ_SIZE_AFTER_READ_POINTER(max_size, read_pointer, write_pointer, read_size_after_read_pointer) \
  do { \
    if(write_pointer == read_pointer) \
      read_size_after_read_pointer = 0; \
    else if(write_pointer > read_pointer) \
      read_size_after_read_pointer = write_pointer - read_pointer; \
    else \
      read_size_after_read_pointer = max_size - read_pointer + 1; \
  } while(false)

}  // namespace core

#endif  // __RING__QUEUE__COMMON__H

