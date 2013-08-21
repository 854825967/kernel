//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (鍛ㄤ簲, 2011-12-30) $
//
// Define class BoundEntityRingQueue.
//

#ifndef __BOUND__ENTITY__RING__QUEUE__H
#define __BOUND__ENTITY__RING__QUEUE__H

#include <deque>
#include <queue>
#include <ext/pool_allocator.h>

#include "core/base/auto_mutex.h"
#include "core/base/condition_variable.h"
#include "core/base/logging.h"
#include "core/base/noncopyable.h"
#include "core/base/ring_queue_common.h"
#include "core/base/types.h"

namespace core {

using namespace ring_queue;

template <typename Type>
class BoundEntityRingQueue : public Noncopyable {
  typedef std::pair<bool, Type *> ValuePair;

 public:
  explicit BoundEntityRingQueue(uint32 ring_capacity, uint8 blocking_pattern);
  ~BoundEntityRingQueue();

  // Use only for producer thread.
  // When successful, return 0, When an error occurs return
  // value to read in "core/base/ring_queue_common.h".
  int Add(Type *element);
  // Use only for consumer thread.
  // When successful, return 0, When an error occurs return
  // value to read in "core/base/ring_queue_common.h".
  int Remove(Type *&element);

  // When producer finish producing, this should be invoked.
  inline void ProduceCompletely();

  // Check producer finish producing.
  inline bool CheckProduceCompletely() const { return produce_completely_; }

 private:
  // Ring queue.
  ValuePair *ring_;

  // Write/Read pointer.
  volatile uint32 write_pointer_;
  volatile uint32 read_pointer_;

  // Condition variable.
  ConditionVariable condition_not_empty_;
  ConditionVariable condition_not_full_;

  // Mutex.
  Mutex mutex_not_empty_;
  Mutex mutex_not_full_;

  // Capacity of ring.
  uint32 ring_capacity_;

  // complete flag.
  volatile bool produce_completely_;

  uint8 blocking_pattern_;
};

template <typename Type>
BoundEntityRingQueue<Type>::BoundEntityRingQueue(uint32 ring_capacity, uint8 blocking_pattern)
       : write_pointer_(0),
         read_pointer_(0),
         ring_capacity_(ring_capacity),
         produce_completely_(false),
         blocking_pattern_(blocking_pattern) {
  this->ring_ = new ValuePair[this->ring_capacity_];
  // Initialize.
  uint32 pos = 0;
  for(; pos < ring_capacity; ++pos) {
    this->ring_[pos].first = false;
  }
}

template <typename Type>
BoundEntityRingQueue<Type>::~BoundEntityRingQueue() {
  delete [] this->ring_;
}

template <typename Type>
int BoundEntityRingQueue<Type>::Add(Type *element) {
  if(this->blocking_pattern_ & BLOCKING_PRODUCER) {
    // Blocking Pattern.
    AutoMutex auto_mutex(&this->mutex_not_full_);
    while(this->ring_[this->write_pointer_].first == true) {
      this->condition_not_full_.Wait(&this->mutex_not_full_);
    }
  } else {
    // Non-blocking pattern.
    if(this->ring_[this->write_pointer_].first == true) {
      return kErrorCodeFull;
    }
  }

  // Lock-free here.
  this->ring_[this->write_pointer_].second = element;
  this->ring_[this->write_pointer_].first = true;
  this->write_pointer_ = ++this->write_pointer_ % this->ring_capacity_;

  // Signal.
  if(this->blocking_pattern_ & BLOCKING_CONSUMER) {
    AutoMutex auto_mutex(&this->mutex_not_full_);
    this->condition_not_empty_.Signal();
  }

  return kErrorCodeSuccess;
}

template <typename Type>
int BoundEntityRingQueue<Type>::Remove(Type *&element) {
  if(this->blocking_pattern_ & BLOCKING_CONSUMER) {
    // Blocking Pattern.
    AutoMutex auto_mutex(&this->mutex_not_empty_);
    while(this->ring_[this->read_pointer_].first == false) {
      if(this->CheckProduceCompletely() == true)
        return kErrorCodeComplete;
      else
        this->condition_not_empty_.Wait(&this->mutex_not_empty_);
    }
  } else {
    // Non-blocking Pattern.
    if(this->ring_[this->read_pointer_].first == false) {
      if(this->CheckProduceCompletely() == true)
        return kErrorCodeComplete;
      else
        return kErrorCodeEmpty;
    }
  }

  // Lock-free here.
  element = this->ring_[this->read_pointer_].second;
  this->ring_[this->read_pointer_].first = false;
  this->read_pointer_ = ++this->read_pointer_ % this->ring_capacity_;

  // Signal.
  if(this->blocking_pattern_ & BLOCKING_PRODUCER) {
    AutoMutex auto_mutex(&this->mutex_not_empty_);
    this->condition_not_full_.Signal();
  }

  return kErrorCodeSuccess;
}

template <typename Type>
void BoundEntityRingQueue<Type>::ProduceCompletely() {
  this->produce_completely_ = true;
  if(this->blocking_pattern_ & BLOCKING_PRODUCER) {
    AutoMutex auto_mutex(&this->mutex_not_empty_);
    this->condition_not_full_.Signal();
  }
}

}  // namespace core

#endif  // __BOUND__ENTITY__RING__QUEUE__H

