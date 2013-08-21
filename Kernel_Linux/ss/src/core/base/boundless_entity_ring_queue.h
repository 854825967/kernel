//
// core - server core source code.
//
// $Rev: 5322 $
// $Author: $
// $Date: 2012-03-05 19:49:49 +0800 (鍛ㄤ竴, 2012-03-05) $
//
// Define class BoundlessEntityRingQueue.
//

#ifndef __BOUNDLESS__ENTITY__RING__QUEUE__H
#define __BOUNDLESS__ENTITY__RING__QUEUE__H

#include <deque>
#include <queue>
#include <ext/pool_allocator.h>

#include "core/base/auto_mutex.h"
#include "core/base/condition_variable.h"
#include "core/base/logging.h"
#include "core/base/types.h"
#include "core/base/ring_queue_common.h"
#include "core/base/noncopyable.h"

namespace core {

using namespace ring_queue;

template <typename Type>
class BoundlessEntityRingQueue : public Noncopyable {
  typedef std::pair<bool, Type *> ValuePair;
  typedef __gnu_cxx::__pool_alloc<ValuePair> PoolAllocator;
  typedef std::queue<Type *, std::deque<Type *, PoolAllocator> > DynamicQueue;

 public:
  explicit BoundlessEntityRingQueue(uint32 ring_capacity, uint8 blocking_pattern);
  ~BoundlessEntityRingQueue();

  // Use only for producer thread.
  // When successful, return 0, When an error occurs return
  // value to read in "core/base/ring_queue_common.h".
  int Add(Type *element);
  // Use only for consumer thread.
  // When successful, return 0, When an error occurs return
  // value to read in "core/base/ring_queue_common.h".
  int Remove(Type *&element);

  // Flush to ring queue.
  // Use only for producer thread.
  inline bool Flush();

  // When producer finish producing, this should be invoked.
  inline void ProduceCompletely();

  // Check producer finish producing.
  inline bool CheckProduceCompletely() const { return produce_completely_; }

 private:
  // Shift element into ring queue.
  // Use only for producer thread.
  bool Shift2Ring();

  void Signal();

  inline bool CheckBlocking() const { return this->blocking_pattern_ != NONBLOCKING; }

  // Dynamic queue.
  DynamicQueue dynamic_queue_;
  // Ring queue.
  ValuePair *ring_;

  // Write/Read pointer.
  volatile uint32 write_pointer_;
  volatile uint32 read_pointer_;

  // Condition variable.
  ConditionVariable condition_not_empty_;
  // Mutex.
  Mutex mutex_;

  // Capacity of ring.
  uint32 ring_capacity_;

  // complete flag.
  volatile bool produce_completely_;

  uint8 blocking_pattern_;
};

template <typename Type>
BoundlessEntityRingQueue<Type>::BoundlessEntityRingQueue(
       uint32 ring_capacity, uint8 blocking_pattern)
       : write_pointer_(0),
         read_pointer_(0),
         ring_capacity_(ring_capacity),
         produce_completely_(false),
         blocking_pattern_(blocking_pattern) {
  CoreLog(INFO, "%s:%d (%s) ring_capacity_=[%u].",
         __FILE__, __LINE__, __FUNCTION__, this->ring_capacity_);
  this->ring_ = new ValuePair[this->ring_capacity_];
  // Initialize.
  uint32 pos = 0;
  for(; pos < ring_capacity_; ++pos) {
    this->ring_[pos].first = false;
  }
}

template <typename Type>
BoundlessEntityRingQueue<Type>::~BoundlessEntityRingQueue() {
  delete [] this->ring_;
  this->ring_ = NULL;
}

template <typename Type>
int BoundlessEntityRingQueue<Type>::Add(Type *element) {
  if(this->Shift2Ring() && this->ring_[this->write_pointer_].first == false) {
    this->ring_[this->write_pointer_].second = element;
    this->ring_[this->write_pointer_].first = true;
    this->write_pointer_ = ++this->write_pointer_ % this->ring_capacity_;
    this->Signal();
  } else {
    this->dynamic_queue_.push(element);
#ifdef _CORE_DEBUG
    CoreLog(INFO, "%s:%d (%s) dynamic_queue_ size=[%u].",
           __FILE__, __LINE__, __FUNCTION__, this->dynamic_queue_.size());
#endif
  }

  return kErrorCodeSuccess;
}

template <typename Type>
int BoundlessEntityRingQueue<Type>::Remove(Type *&element) {
  if(this->CheckBlocking() == true) {
    // Blocking pattern.
    AutoMutex auto_mutex(&this->mutex_);
    while(this->ring_[this->read_pointer_].first == false) {
      if(this->CheckProduceCompletely() == true) {
        return kErrorCodeComplete;
      } else {
        this->condition_not_empty_.Wait(&this->mutex_);
      }
    }
  } else {
    // Non-blocking pattern.
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

  return kErrorCodeSuccess;
}

template <typename Type>
bool BoundlessEntityRingQueue<Type>::Flush() {
  return this->Shift2Ring();
}

template <typename Type>
bool BoundlessEntityRingQueue<Type>::Shift2Ring() {
  bool shift_all = true;
  // A optimizion, signal once.
  bool signal = ((this->ring_[this->write_pointer_].first == false)
         && (this->dynamic_queue_.empty() == false));
  while(this->dynamic_queue_.empty() == false) {
    if(this->ring_[this->write_pointer_].first == false) {
      // Have space to write.
      this->ring_[this->write_pointer_].second = this->dynamic_queue_.front();
      this->ring_[this->write_pointer_].first = true;
      this->write_pointer_ = ++this->write_pointer_ % this->ring_capacity_;
      // Shift one, pop it.
      this->dynamic_queue_.pop();
    } else {
      shift_all = false;
      break;
    }
  }

  if(signal == true) this->Signal();

  return shift_all;
}

template <typename Type>
void BoundlessEntityRingQueue<Type>::ProduceCompletely() {
  this->produce_completely_ = true;
  this->Signal();
}

template <typename Type>
void BoundlessEntityRingQueue<Type>::Signal() {
  if(this->CheckBlocking() == true) {
    AutoMutex auto_mutex(&this->mutex_);
    this->condition_not_empty_.Signal();
  }
}

}  // namespace core

#endif  // __BOUNDLESS__ENTITY__RING__QUEUE__H

