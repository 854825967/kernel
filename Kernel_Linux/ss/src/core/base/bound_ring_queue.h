//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (鍛ㄤ簲, 2011-12-30) $
//
// Define class BoundRingQueue.
//

#ifndef __BOUND__RING__QUEUE__H
#define __BOUND__RING__QUEUE__H

#include "core/base/byte_buffer_static.h"
#include "core/base/condition_variable.h"
#include "core/base/mutex.h"
#include "core/base/noncopyable.h"

namespace core {

class BoundRingQueue : public Noncopyable {
  typedef ByteBufferStaticMalloc StaticRingQueue;

 public:
  BoundRingQueue(uint32 max_size, bool blocking = false);
  ~BoundRingQueue();

  // Use only for producer thread.
  // Return bytes added to the queue.
  // Detail to read "core/base/ring_queue_common.h".
  int Add(const char *data, int size);

  // Use only for consumer thread.
  // Return bytes removed from the queue.
  // Detail to read "core/base/ring_queue_common.h".
  int Remove(char *data, int max_size);

  // When producer finish producing, this should be invoked.
  void ProduceCompletely();

  // Check producer finish producing.
  inline bool CheckProduceCompletely() const { return produce_completely_; }
 
 private:
  StaticRingQueue ring_;
  uint32 ring_size_;

  // Write/Read pointers.
  volatile uint32 write_pointer_;
  volatile uint32 read_pointer_;

  // Blocking pattern.
  bool blocking_;

  // Condition variable.
  ConditionVariable condition_not_empty_;
  ConditionVariable condition_not_full_;

  // Mutex
  Mutex mutex_not_empty_;
  Mutex mutex_not_full_;

  volatile bool produce_completely_;
};

}  // namespace core

#endif  // __BOUND__RING__QUEUE__H

