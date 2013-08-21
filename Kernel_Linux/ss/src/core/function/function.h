//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (鍛ㄤ簲, 2011-12-30) $
//
// Define function, just like boost::function and boost::bind.
//

#ifndef __FUNCTION__H
#define __FUNCTION__H

// #include <memory>

#include "core/base/shared_ptr.h"

namespace core {

namespace function {

// ------------------------------------------------------------------------------
//
// Use as the follow:
//
// #include <string>
//
// #include "core/function/function.h"
//
// class Test1 {
//  public:
//   void Callback0() { std::cout << "Test1::Callback0()" << std::endl; }
//   void Callback1(int _1) { std::cout << "Test1::Callback1(" << _1 << ")" << std::endl; }
//   void Callback2(int _1, int _2) { std::cout << "Test1::Callback2(" << _1 << ", " << _2 << ")" << std::endl; }
//   int Callback3(int _1, int _2, int _3) { std::cout << "Test1::Callback3(" << _1 << ", " << _2 << ", " << _3 << ")" << std::endl; return 0; }
//   void Callback4(int _1, int _2, int _3, int _4) { std::cout << "Test1::Callback4(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ")" << std::endl; }
//   std::string Callback5(int _1, int _2, int _3, int _4, char *_5) { std::cout << "Test1::Callback5(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", "<< _5 >> ")" << std::endl; return std::string("aaaaa"); }
//   void Callback6(int _1, int _2, int _3, int _4, char *_5, std::string _6) { std::cout << "Test1::Callback6(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", " << _5 << ", " << _6 << ")" << std::endl; }
// };
//
// class Test2 {
//   void Callback00() { std::cout << "Test2::Callback00()" << std::endl; }
//   void Callback11(int _1) { std::cout << "Test2::Callback11(" << _1 << ")" << std::endl; }
//   void Callback22(int _1, int _2) { std::cout << "Test2::Callback22(" << _1 << ", " << _2 << ")" << std::endl; }
//   int Callback33(int _1, int _2, int _3) { std::cout << "Test2::Callback33(" << _1 << ", " << _2 << ", " << _3 << ")" << std::endl; return 0; }
//   void Callback44(int _1, int _2, int _3, int _4) { std::cout << "Test2::Callback44(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ")" << std::endl; }
//   std::string Callback55(int _1, int _2, int _3, int _4, char *_5) { std::cout << "Test2::Callback55(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", "<< _5 >> ")" << std::endl; return std::string("aaaaa"); }
//   void Callback66(int _1, int _2, int _3, int _4, char *_5, std::string _6) { std::cout << "Test2::Callback66(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", " << _5 << ", " << _6 << ")" << std::endl; }
// };
//
// using namespace core::function;
// int main() {
//   Test1 test1;
//   Test2 test2;
//
//   // Use Like boost::function<void()>, boost::function<void(int)>, boost::function<void(int, int)> ...
//   // Without use typelist, so, different numbers of parameter use different name of "core::function::Function".
//   Function0<void> function0;
//   Function1<void, int> function1;
//   Function2<void, int, int> function2;
//   Function3<int, int, int, int> function3;
//   Function4<void, int, int, int, int> function4;
//   Function5<std::string, int, int, int, int, char *> function5;
//   Function6<void, int, int, int, int, int, std::string> function6;
//
//   // like boost::bind(&Test1::Callback0, &test1), boost::bind(&Test1::Callback1, &test1, _1) ...
//   function0 = Bind(&Test1::Callback0, &test1);
//   function1 = Bind(&Test1::Callback1, &test1);
//   function2 = Bind(&Test1::Callback2, &test1);
//   function3 = Bind(&Test1::Callback3, &test1);
//   function4 = Bind(&Test1::Callback4, &test1);
//   function5 = Bind(&Test1::Callback5, &test1);
//   function6 = Bind(&Test1::Callback6, &test1);
//
//   // like boost invoke
//   function0();
//   function1(1);
//   function2(1, 2);
//   function3(1, 2, 3);
//   function4(1, 2, 3, 4);
//   function5("string_1", 2, 3, 4, "string_5");
//   function6(1, 2, 3, 4, 5, "string_6");
//
//   function0();
//   function1(11);
//   function2(11, 22);
//   function3(11, 22, 33);
//   function4(11, 22, 33, 44);
//   function5("string_11", 22, 33, 44, "string_55");
//   function6(11, 22, 33, 44, 55, "string_66");
//
//   function0 = Bind(&Test2::Callback00, &test2);
//   function1 = Bind(&Test2::Callback11, &test2);
//   function2 = Bind(&Test2::Callback22, &test2);
//   function3 = Bind(&Test2::Callback33, &test2);
//   function4 = Bind(&Test2::Callback44, &test2);
//   function5 = Bind(&Test2::Callback55, &test2);
//   function6 = Bind(&Test2::Callback66, &test2);
//
//   function0();
//   function1(1);
//   function2(1, 2);
//   function3(1, 2, 3);
//   function4(1, 2, 3, 4);
//   function5("string_1", 2, 3, 4, "string_5");
//   function6(1, 2, 3, 4, 5, "string_6");
//
//   function0();
//   function1(11);
//   function2(11, 22);
//   function3(11, 22, 33);
//   function4(11, 22, 33, 44);
//   function5("string_11", 22, 33, 44, "string_55");
//   function6(11, 22, 33, 44, 55, "string_66");
//
//   return 0;
// }
//
// ------------------------------------------------------------------------------



// ------------------------------------------------------------------------------
//
// Functor pointer, support 6 parameters at most
//
// ------------------------------------------------------------------------------
template <typename ObjectType, typename ReturnType>
struct FunctorPointer0 {
  typedef ReturnType (ObjectType::*FunctionPointer)();

  FunctorPointer0() : object_pointer_(NULL) {}
  ReturnType operator() () {
    return (this->object_pointer_->*(this->function_pointer_))();
  }

  ObjectType *object_pointer_;
  FunctionPointer function_pointer_;
};

template <typename ObjectType, typename ReturnType, typename P1>
struct FunctorPointer1 {
  typedef ReturnType (ObjectType::*FunctionPointer)(P1);

  FunctorPointer1() : object_pointer_(NULL) {}
  ReturnType operator() (P1 _1) {
    return (this->object_pointer_->*(this->function_pointer_))(_1);
  }

  ObjectType *object_pointer_;
  FunctionPointer function_pointer_;
};

template <typename ObjectType, typename ReturnType, typename P1, typename P2>
struct FunctorPointer2 {
  typedef ReturnType (ObjectType::*FunctionPointer)(P1, P2);

  FunctorPointer2() : object_pointer_(NULL) {}
  ReturnType operator() (P1 _1, P2 _2) {
    return (this->object_pointer_->*(this->function_pointer_))(_1, _2);
  }

  ObjectType *object_pointer_;
  FunctionPointer function_pointer_;
};

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3>
struct FunctorPointer3 {
  typedef ReturnType (ObjectType::*FunctionPointer)(P1, P2, P3);

  FunctorPointer3() : object_pointer_(NULL) {}
  ReturnType operator() (P1 _1, P2 _2, P3 _3) {
    return (this->object_pointer_->*(this->function_pointer_))(_1, _2, _3);
  }

  ObjectType *object_pointer_;
  FunctionPointer function_pointer_;

};

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4>
struct FunctorPointer4 {
  typedef ReturnType (ObjectType::*FunctionPointer)(P1, P2, P3, P4);

  FunctorPointer4() : object_pointer_(NULL) {}
  ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4) {
    return (this->object_pointer_->*(this->function_pointer_))(_1, _2, _3, _4);
  }

  ObjectType *object_pointer_;
  FunctionPointer function_pointer_;

};

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5>
struct FunctorPointer5 {
  typedef ReturnType (ObjectType::*FunctionPointer)(P1, P2, P3, P4, P5);

  FunctorPointer5() : object_pointer_(NULL) {}
  ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4, P5 _5) {
    return (this->object_pointer_->*(this->function_pointer_))(_1, _2, _3, _4, _5);
  }

  ObjectType *object_pointer_;
  FunctionPointer function_pointer_;

};

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
struct FunctorPointer6 {
  typedef ReturnType (ObjectType::*FunctionPointer)(P1, P2, P3, P4, P5, P6);

  FunctorPointer6() : object_pointer_(NULL) {}
  ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4, P5 _5, P6 _6) {
    return (this->object_pointer_->*(this->function_pointer_))(_1, _2, _3, _4, _5, _6);
  }

  ObjectType *object_pointer_;
  FunctionPointer function_pointer_;

};


// ------------------------------------------------------------------------------
//
// Functor object, support 6 parameters at most
//
// ------------------------------------------------------------------------------
template <typename ReturnType>
class Functor0 {
 public:
  Functor0() {}
  virtual ~Functor0() {}

  virtual ReturnType operator() () = 0;
};

template <typename ReturnType, typename P1>
class Functor1 {
 public:
  Functor1() {}
  virtual ~Functor1() {}

  virtual ReturnType operator() (P1) = 0;
};

template <typename ReturnType, typename P1, typename P2>
class Functor2 {
 public:
  Functor2() {}
  virtual ~Functor2() {}

  virtual ReturnType operator() (P1, P2) = 0;
};

template <typename ReturnType, typename P1, typename P2, typename P3>
class Functor3 {
 public:
  Functor3() {}
  virtual ~Functor3() {}

  virtual ReturnType operator() (P1, P2, P3) = 0;
};

template <typename ReturnType, typename P1, typename P2, typename P3, typename P4>
class Functor4 {
 public:
  Functor4() {}
  virtual ~Functor4() {}

  virtual ReturnType operator() (P1, P2, P3, P4) = 0;
};

template <typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5>
class Functor5 {
 public:
  Functor5() {}
  virtual ~Functor5() {}

  virtual ReturnType operator() (P1, P2, P3, P4, P5) = 0;
};

template <typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Functor6 {
 public:
  Functor6() {}
  virtual ~Functor6() {}

  virtual ReturnType operator() (P1, P2, P3, P4, P5, P6) = 0;
};

// ------------------------------------------------------------------------------
//
// Functor implement object, support 6 parameters at most
//
// ------------------------------------------------------------------------------
template <typename ObjectType, typename ReturnType>
class FunctorImplement0 : public Functor0<ReturnType> {
 public:
  FunctorImplement0() {}
  virtual ~FunctorImplement0() {}

  virtual ReturnType operator() () {
    return this->object_();
  }

  FunctorPointer0<ObjectType, ReturnType> object_;
};

template <typename ObjectType, typename ReturnType, typename P1>
class FunctorImplement1 : public Functor1<ReturnType, P1> {
 public:
  FunctorImplement1() {}
  virtual ~FunctorImplement1() {}

  virtual ReturnType operator() (P1 _1) {
    return this->object_(_1);
  }

  FunctorPointer1<ObjectType, ReturnType, P1> object_;
};

template <typename ObjectType, typename ReturnType, typename P1, typename P2>
class FunctorImplement2 : public Functor2<ReturnType, P1, P2> {
 public:
  FunctorImplement2() {}
  virtual ~FunctorImplement2() {}

  virtual ReturnType operator() (P1 _1, P2 _2) {
    return this->object_(_1, _2);
  }

  FunctorPointer2<ObjectType, ReturnType, P1, P2> object_;
};

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3>
class FunctorImplement3 : public Functor3<ReturnType, P1, P2, P3> {
 public:
  FunctorImplement3() {}
  virtual ~FunctorImplement3() {}

  virtual ReturnType operator() (P1 _1, P2 _2, P3 _3) {
    return this->object_(_1, _2, _3);
  }

  FunctorPointer3<ObjectType, ReturnType, P1, P2, P3> object_;
};

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4>
class FunctorImplement4 : public Functor4<ReturnType, P1, P2, P3, P4> {
 public:
  FunctorImplement4() {}
  virtual ~FunctorImplement4() {}

  virtual ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4) {
    return this->object_(_1, _2, _3, _4);
  }

  FunctorPointer4<ObjectType, ReturnType, P1, P2, P3, P4> object_;
};

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5>
class FunctorImplement5 : public Functor5<ReturnType, P1, P2, P3, P4, P5> {
 public:
  FunctorImplement5() {}
  virtual ~FunctorImplement5() {}

  virtual ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4, P5 _5) {
    return this->object_(_1, _2, _3, _4, _5);
  }

  FunctorPointer5<ObjectType, ReturnType, P1, P2, P3, P4, P5> object_;
};
template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class FunctorImplement6 : public Functor6<ReturnType, P1, P2, P3, P4, P5, P6> {
 public:
  FunctorImplement6() {}
  virtual ~FunctorImplement6() {}

  virtual ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4, P5 _5, P6 _6) {
    return this->object_(_1, _2, _3, _4, _5, _6);
  }

  FunctorPointer6<ObjectType, ReturnType, P1, P2, P3, P4, P5, P6> object_;
};

// ------------------------------------------------------------------------------
//
// Function, support 6 parameters at most
//
// ------------------------------------------------------------------------------
template <typename ReturnType>
class Function0 {
 public:
  Function0() {}
  Function0(const Function0<ReturnType> &function) {
    this->functor_ = function.functor_;
  }
  explicit Function0(Functor0<ReturnType> *functor) : functor_(functor) {}

  Function0<ReturnType> &operator=
         (const Function0<ReturnType> &function) {
    this->functor_ = function.functor_;
    return *this;
  }

  ReturnType operator() () {
    return (*this->functor_)();
  }

  operator bool() {
    if(this->functor_.GetPtr() != NULL) return true;
    else return false;
  }

 private:
  shared_ptr<Functor0<ReturnType> > functor_;
};

template <typename ReturnType, typename P1>
class Function1 {
 public:
  Function1() {}
  Function1(const Function1<ReturnType, P1> &function) {
    this->functor_ = function.functor_;
  }
  explicit Function1(Functor1<ReturnType, P1> *functor) : functor_(functor) {}

  Function1<ReturnType, P1> &operator=
         (const Function1<ReturnType, P1> &function) {
    this->functor_ = function.functor_;
    return *this;
  }

  ReturnType operator() (P1 _1) {
    return (*this->functor_)(_1);
  }

  operator bool() {
    if(this->functor_.GetPtr() != NULL) return true;
    else return false;
  }

 private:
  shared_ptr<Functor1<ReturnType, P1> > functor_;
};

template <typename ReturnType, typename P1, typename P2>
class Function2 {
 public:
  Function2() {}
  Function2(const Function2<ReturnType, P1, P2> &function) {
    this->functor_ = function.functor_;
  }
  explicit Function2(Functor2<ReturnType, P1, P2> *functor) : functor_(functor) {}

  Function2<ReturnType, P1, P2> &operator=
         (const Function2<ReturnType, P1, P2> &function) {
    this->functor_ = function.functor_;
    return *this;
  }

  ReturnType operator() (P1 _1, P2 _2) {
    return (*this->functor_)(_1, _2);
  }

  operator bool() {
    if(this->functor_.GetPtr() != NULL) return true;
    else return false;
  }

 private:
  shared_ptr<Functor2<ReturnType, P1, P2> > functor_;
};

template <typename ReturnType, typename P1, typename P2, typename P3>
class Function3 {
 public:
  Function3() {}
  Function3(const Function3<ReturnType, P1, P2, P3> &function) {
    this->functor_ = function.functor_;
  }
  explicit Function3(Functor3<ReturnType, P1, P2, P3> *functor) : functor_(functor) {}

  Function3<ReturnType, P1, P2, P3> &operator=
         (const Function3<ReturnType, P1, P2, P3> &function) {
    this->functor_ = function.functor_;
    return *this;
  }

  ReturnType operator() (P1 _1, P2 _2, P3 _3) {
    return (*this->functor_)(_1, _2, _3);
  }

  operator bool() {
    if(this->functor_.GetPtr() != NULL) return true;
    else return false;
  }

 private:
  shared_ptr<Functor3<ReturnType, P1, P2, P3> > functor_;
};

template <typename ReturnType, typename P1, typename P2, typename P3, typename P4>
class Function4 {
 public:
  Function4() {}
  Function4(const Function4<ReturnType, P1, P2, P3, P4> &function) {
    this->functor_ = function.functor_;
  }
  explicit Function4(Functor4<ReturnType, P1, P2, P3, P4> *functor) : functor_(functor) {}

  Function4<ReturnType, P1, P2, P3, P4> &operator=
         (const Function4<ReturnType, P1, P2, P3, P4> &function) {
    this->functor_ = function.functor_;
    return *this;
  }

  ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4) {
    return (*this->functor_)(_1, _2, _3, _4);
  }

  operator bool() {
    if(this->functor_.GetPtr() != NULL) return true;
    else return false;
  }

 private:
  shared_ptr<Functor4<ReturnType, P1, P2, P3, P4> > functor_;
};

template <typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5>
class Function5 {
 public:
  Function5() {}
  Function5(const Function5<ReturnType, P1, P2, P3, P4, P5> &function) {
    this->functor_ = function.functor_;
  }
  explicit Function5(Functor5<ReturnType, P1, P2, P3, P4, P5> *functor) : functor_(functor) {}

  Function5<ReturnType, P1, P2, P3, P4, P5> &operator=
         (const Function5<ReturnType, P1, P2, P3, P4, P5> &function) {
    this->functor_ = function.functor_;
    return *this;
  }

  ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4, P5 _5) {
    return (*this->functor_)(_1, _2, _3, _4, _5);
  }

  operator bool() {
    if(this->functor_.GetPtr() != NULL) return true;
    else return false;
  }

 private:
  shared_ptr<Functor5<ReturnType, P1, P2, P3, P4, P5> > functor_;
};

template <typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Function6 {
 public:
  Function6() {}
  Function6(const Function6<ReturnType, P1, P2, P3, P4, P5, P6> &function) {
    this->functor_ = function.functor_;
  }
  explicit Function6(Functor6<ReturnType, P1, P2, P3, P4, P5, P6> *functor) : functor_(functor) {}

  Function6<ReturnType, P1, P2, P3, P4, P5, P6> &operator=
         (const Function6<ReturnType, P1, P2, P3, P4, P5, P6> &function) {
    this->functor_ = function.functor_;
    return *this;
  }

  ReturnType operator() (P1 _1, P2 _2, P3 _3, P4 _4, P5 _5, P6 _6) {
    return (*this->functor_)(_1, _2, _3, _4, _5, _6);
  }

  operator bool() {
    if(this->functor_.GetPtr() != NULL) return true;
    else return false;
  }

 private:
  shared_ptr<Functor6<ReturnType, P1, P2, P3, P4, P5, P6> > functor_;
};

// ------------------------------------------------------------------------------
//
// Bind, support 6 parameters at most
//
// ------------------------------------------------------------------------------
template <typename ObjectType, typename ReturnType>
Function0<ReturnType> Bind(ReturnType (ObjectType::*pointer)(), ObjectType *object) {
  FunctorPointer0<ObjectType, ReturnType> function_pointer;
  function_pointer.object_pointer_ = object;
  function_pointer.function_pointer_ = pointer;

  FunctorImplement0<ObjectType, ReturnType> *functor_implement
         = new FunctorImplement0<ObjectType, ReturnType>;
  functor_implement->object_ = function_pointer;

  Function0<ReturnType> function(static_cast<Functor0<ReturnType>*>(functor_implement));
  return function;
}

template <typename ObjectType, typename ReturnType, typename P1>
Function1<ReturnType, P1> Bind(ReturnType (ObjectType::*pointer)(P1), ObjectType *object) {
  FunctorPointer1<ObjectType, ReturnType, P1> function_pointer;
  function_pointer.object_pointer_ = object;
  function_pointer.function_pointer_ = pointer;

  FunctorImplement1<ObjectType, ReturnType, P1> *functor_implement
         = new FunctorImplement1<ObjectType, ReturnType, P1>;
  functor_implement->object_ = function_pointer;

  Function1<ReturnType, P1> function(static_cast<Functor1<ReturnType, P1>*>(functor_implement));
  return function;
}

template <typename ObjectType, typename ReturnType, typename P1, typename P2>
Function2<ReturnType, P1, P2> Bind(ReturnType (ObjectType::*pointer)(P1, P2), ObjectType *object) {
  FunctorPointer2<ObjectType, ReturnType, P1, P2> function_pointer;
  function_pointer.object_pointer_ = object;
  function_pointer.function_pointer_ = pointer;

  FunctorImplement2<ObjectType, ReturnType, P1, P2> *functor_implement
         = new FunctorImplement2<ObjectType, ReturnType, P1, P2>;
  functor_implement->object_ = function_pointer;

  Function2<ReturnType, P1, P2> function(static_cast<Functor2<ReturnType, P1, P2>*>(functor_implement));
  return function;
}

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3>
Function3<ReturnType, P1, P2, P3> Bind(ReturnType (ObjectType::*pointer)(P1, P2, P3), ObjectType *object) {
  FunctorPointer3<ObjectType, ReturnType, P1, P2, P3> function_pointer;
  function_pointer.object_pointer_ = object;
  function_pointer.function_pointer_ = pointer;

  FunctorImplement3<ObjectType, ReturnType, P1, P2, P3> *functor_implement
         = new FunctorImplement3<ObjectType, ReturnType, P1, P2, P3>;
  functor_implement->object_ = function_pointer;

  Function3<ReturnType, P1, P2, P3> function(static_cast<Functor3<ReturnType, P1, P2, P3>*>(functor_implement));
  return function;
}

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4>
Function4<ReturnType, P1, P2, P3, P4> Bind(ReturnType (ObjectType::*pointer)(P1, P2, P3, P4), ObjectType *object) {
  FunctorPointer4<ObjectType, ReturnType, P1, P2, P3, P4> function_pointer;
  function_pointer.object_pointer_ = object;
  function_pointer.function_pointer_ = pointer;

  FunctorImplement4<ObjectType, ReturnType, P1, P2, P3, P4> *functor_implement
         = new FunctorImplement4<ObjectType, ReturnType, P1, P2, P3, P4>;
  functor_implement->object_ = function_pointer;

  Function4<ReturnType, P1, P2, P3, P4> function(static_cast<Functor4<ReturnType, P1, P2, P3, P4>*>(functor_implement));
  return function;
}

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5>
Function5<ReturnType, P1, P2, P3, P4, P5> Bind(ReturnType (ObjectType::*pointer)(P1, P2, P3, P4, P5), ObjectType *object) {
  FunctorPointer5<ObjectType, ReturnType, P1, P2, P3, P4, P5> function_pointer;
  function_pointer.object_pointer_ = object;
  function_pointer.function_pointer_ = pointer;

  FunctorImplement5<ObjectType, ReturnType, P1, P2, P3, P4, P5> *functor_implement
         = new FunctorImplement5<ObjectType, ReturnType, P1, P2, P3, P4, P5>;
  functor_implement->object_ = function_pointer;

  Function5<ReturnType, P1, P2, P3, P4, P5> function(static_cast<Functor5<ReturnType, P1, P2, P3, P4, P5>*>(functor_implement));
  return function;
}

template <typename ObjectType, typename ReturnType, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
Function6<ReturnType, P1, P2, P3, P4, P5, P6> Bind(ReturnType (ObjectType::*pointer)(P1, P2, P3, P4, P5, P6), ObjectType *object) {
  FunctorPointer6<ObjectType, ReturnType, P1, P2, P3, P4, P5, P6> function_pointer;
  function_pointer.object_pointer_ = object;
  function_pointer.function_pointer_ = pointer;

  FunctorImplement6<ObjectType, ReturnType, P1, P2, P3, P4, P5, P6> *functor_implement
         = new FunctorImplement6<ObjectType, ReturnType, P1, P2, P3, P4, P5, P6>;
  functor_implement->object_ = function_pointer;

  Function6<ReturnType, P1, P2, P3, P4, P5, P6> function(static_cast<Functor6<ReturnType, P1, P2, P3, P4, P5, P6>*>(functor_implement));
  return function;
}

}  // namespace function

}  // namespace core

#endif  // __FUNCTION__H

