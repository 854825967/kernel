//
// core - server core source code.
//
// $Rev$
// $Author$
// $Date$
//
// Define shared_ptr, it is not thread-safe implement.
//

#ifndef __SHARED__PTR__H
#define __SHARED__PTR__H

namespace core {

template <class Type>
class shared_ptr {
  typedef unsigned int uint32;

 public:
  shared_ptr() : ptr_(NULL), reference_count_(NULL) {}
  shared_ptr(const shared_ptr &copy) { 
    if(this->ptr_ != copy.ptr_) {
      this->ptr_ = copy.ptr_;
      this->reference_count_ = copy.reference_count_;
      if(this->reference_count_) ++(*this->reference_count_);
    }
  }

  template <class A>
  explicit shared_ptr(A *ptr) : ptr_(ptr), reference_count_(0) {
    if(this->ptr_ != NULL) {
      this->reference_count_ = new uint32;
      *(this->reference_count_) = 1;
    }
  }

  ~shared_ptr() { this->Release(); }

  inline shared_ptr<Type>& operator=(const shared_ptr<Type> &p) {
    if(this->ptr_ == p.ptr_) {
      return *this;
    }

    this->Release();
    this->ptr_ = p.ptr_;
    this->reference_count_ = p.reference_count_;
    if(this->reference_count_) ++(*this->reference_count_);

    return *this;
  }

  inline Type& operator*() const {
    return *(this->ptr_);
  }
  inline Type *operator->() const {
    return this->ptr_;
  }
  inline Type *GetPtr() const { return this->ptr_; }

  inline bool IsNull() const { return this->ptr_ == NULL; }
  inline uint32 ReferenceCount() const {
    if(this->reference_count_ == NULL) return 0;
    return *reference_count_;
  }

  inline void Release() {
    if(this->reference_count_ != NULL) {
      if(--(*this->reference_count_) == 0) {
        delete this->reference_count_;
        delete this->ptr_;
      }
      this->reference_count_ = NULL;
      this->ptr_ = NULL;
    }
  }

 private:
  Type *ptr_;
  uint32 *reference_count_;
};

}  // namespace core

#endif  // __SHARED__PTR__H

