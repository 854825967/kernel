//
// core - server core source code.
//
// $Rev: 6603 $
// $Author: $
// $Date: 2012-04-09 17:12:12 +0800 (鍛ㄤ竴, 2012-04-09) $
//
// Define class BoundlessRingQueue.
//

#ifndef __BOUNDLESS__RING__QUEUE__H
#define __BOUNDLESS__RING__QUEUE__H

#include "core/base/byte_buffer_dynamic.h"
#include "core/base/byte_buffer_static.h"
#include "core/base/condition_variable.h"
#include "core/base/mutex.h"
#include "core/base/noncopyable.h"
#include "core/base/types.h"

namespace core {

class BoundlessRingQueue : public Noncopyable {
  typedef ByteBufferStaticMalloc StaticRingQueue;
  typedef ByteBufferDynamic DynamicQueue;
 public:
  BoundlessRingQueue(uint32 ring_size,
         uint32 dynamic_queue_unit_size, bool blocking = false);
  ~BoundlessRingQueue();

  // Use only for producer thread.
  // Return bytes added to the queue.
  // Detail to read "core/base/ring_queue_common.h".
  int Add(const char *data, int size);

  // Use only for consumer thread.
  // Return bytes removed from the queue.
  // Detail to read "core/base/ring_queue_common.h".
  int Remove(char *data, int max_size);

  // Use only for producer thread.
  // Return flush result.
  // true  : flush completely.
  // false : flush a part of data.
  inline bool Flush() { return Shift2Ring(); }

  // Use for producer thread.
  // Get free bytes of dynamic queue.
  inline uint32 GetDynamicFreeSize() const {
    return this->dynamic_queue_.WriteSize();
  }

  // Use for producer thread.
  // Reduce the size of dynamic queue.
  inline void ReduceDynamicSize() {
    this->dynamic_queue_.ReduceBufferSize();
  }

  // When producer finish producing, this should be invoked.
  void ProduceCompletely();

  // Check producer finish producing.
  inline bool CheckProduceCompletely() const { return produce_completely_; }

  bool CheckEmpty() const {
    return (this->write_pointer_ == this->read_pointer_ ||
        this->dynamic_queue_.ReadSize() == 0);
  }

  // For debug.
  void LogPrint() const;

 private:
  // Use only for producer thread.
  // Shift data(in dynamic queue) to ring queue.
  // Return shift result.
  // true  : shift completely.
  // false : shift a part of data.
  bool Shift2Ring();

  // Try to add data to ring queue.
  // Return add result.
  // true  : add successfully.
  // false : no space to add.
  bool TryAdd(const char *data, int size);

  // ring queue.
  StaticRingQueue ring_;

  // Size of ring queue
  uint32 ring_size_;

  // Write/Read position
  volatile uint32 write_pointer_;
  volatile uint32 read_pointer_;

  // Dynamic Queue
  DynamicQueue dynamic_queue_;

  // Blocking pattern.
  bool blocking_;

  // Condition varialle.
  ConditionVariable condition_not_empty_;

  // Mutex
  Mutex mutex_;

  volatile bool produce_completely_;
};

}  // namespace core

#endif  // __BOUNDLESS__RING__QUEUE__H

