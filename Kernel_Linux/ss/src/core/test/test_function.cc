//
// core - server core source code.
//
// $Rev: 2645 $
// $Author: $
// $Date: 2011-12-28 17:47:24 +0800 (周三, 2011-12-28) $
//
// Test of core::function::Function.
//

#include <iostream>
#include <string>

#include "core/function/function.h"

class Test1 {
 public:
  ~Test1() { std::cout << "~Test1()" << std::endl; }
  void Callback0() { std::cout << "Test1::Callback0()" << std::endl; }
  void Callback1(int _1) { std::cout << "Test1::Callback1(" << _1 << ")" << std::endl; }
  void Callback2(int _1, int _2) { std::cout << "Test1::Callback2(" << _1 << ", " << _2 << ")" << std::endl; }
  int Callback3(int _1, int _2, int _3) { std::cout << "Test1::Callback3(" << _1 << ", " << _2 << ", " << _3 << ")" << std::endl; return 0; }
  void Callback4(int _1, int _2, int _3, int _4) { std::cout << "Test1::Callback4(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ")" << std::endl; }
  std::string Callback5(int _1, int _2, int _3, int _4, const char *_5) { std::cout << "Test1::Callback5(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", "<< _5 << ")" << std::endl; return std::string("aaaaa"); }
  void Callback6(int _1, int _2, int _3, int _4, const char *_5, std::string _6) { std::cout << "Test1::Callback6(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", " << _5 << ", " << _6 << ")" << std::endl; }
};

class Test2 {
 public:
  virtual void Callback00() { std::cout << "Test2::Callback00()" << std::endl; }
  void Callback11(int _1) { std::cout << "Test2::Callback11(" << _1 << ")" << std::endl; }
  void Callback22(int _1, int _2) { std::cout << "Test2::Callback22(" << _1 << ", " << _2 << ")" << std::endl; }
  int Callback33(int _1, int _2, int _3) { std::cout << "Test2::Callback33(" << _1 << ", " << _2 << ", " << _3 << ")" << std::endl; return 0; }
  void Callback44(int _1, int _2, int _3, int _4) { std::cout << "Test2::Callback44(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ")" << std::endl; }
  std::string Callback55(int _1, int _2, int _3, int _4, const char *_5) { std::cout << "Test2::Callback55(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", "<< _5 << ")" << std::endl; return std::string("aaaaa"); }
  void Callback66(int _1, int _2, int _3, int _4, const char *_5, std::string _6) { std::cout << "Test2::Callback66(" << _1 << ", " << _2 << ", " << _3 << ", " << _4 << ", " << _5 << ", " << _6 << ")" << std::endl; }
};

class Test3 : public Test2 {
 public:
  virtual void Callback00() { std::cout << "Test3::Callback00()" << std::endl; }
};

using namespace core::function;

int main() {
  Test1 test1;
  Test2 test2;
  Test3 test3;
  Test2 *test22 = &test3;

  // Use Like boost::function<void()>, boost::function<void(int)>, boost::function<void(int, int)> ...
  // Without use typelist, so, different numbers of parameter use different name of "core::function::Function".
  Function0<void> function0;
  Function1<void, int> function1;
  Function2<void, int, int> function2;
  Function3<int, int, int, int> function3;
  Function4<void, int, int, int, int> function4;
  Function5<std::string, int, int, int, int, const char *> function5;
  Function6<void, int, int, int, int, const char*, std::string> function6;

  // like boost::bind(&Test1::Callback0, &test1), boost::bind(&Test1::Callback1, &test1, _1) ...
  function0 = Bind(&Test1::Callback0, &test1);
  function1 = Bind(&Test1::Callback1, &test1);
  function2 = Bind(&Test1::Callback2, &test1);
  function3 = Bind(&Test1::Callback3, &test1);
  function4 = Bind(&Test1::Callback4, &test1);
  function5 = Bind(&Test1::Callback5, &test1);
  function6 = Bind(&Test1::Callback6, &test1);

  // like boost invoke
  function0();
  function1(1);
  function2(1, 2);
  function3(1, 2, 3);
  function4(1, 2, 3, 4);
  function5(1, 2, 3, 4, "string_5");
  function6(1, 2, 3, 4, "string_5", "string_6");

  function0();
  function1(11);
  function2(11, 22);
  function3(11, 22, 33);
  function4(11, 22, 33, 44);
  function5(11, 22, 33, 44, "string_55");
  function6(11, 22, 33, 44, "string_55", "string_66");

  function0 = Bind(&Test2::Callback00, test22);
  function1 = Bind(&Test2::Callback11, &test2);
  function2 = Bind(&Test2::Callback22, &test2);
  function3 = Bind(&Test2::Callback33, &test2);
  function4 = Bind(&Test2::Callback44, &test2);
  function5 = Bind(&Test2::Callback55, &test2);
  function6 = Bind(&Test2::Callback66, &test2);

  function0();
  function1(1);
  function2(1, 2);
  function3(1, 2, 3);
  function4(1, 2, 3, 4);
  function5(1, 2, 3, 4, "string_5");
  function6(1, 2, 3, 4, "string_5", "string_6");

  function0();
  function1(11);
  function2(11, 22);
  function3(11, 22, 33);
  function4(11, 22, 33, 44);
  function5(11, 22, 33, 44, "string_55");
  function6(11, 22, 33, 44, "string_55", "string_66");

  return 0;
}

