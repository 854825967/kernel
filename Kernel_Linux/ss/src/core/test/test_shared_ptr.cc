//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (周五, 2011-12-30) $
//
// Test code.
//

#include <iostream>
#include <vector>

#include "core/base/logging.h"
#include "core/base/shared_ptr.h"
#include "core/base/types.h"

class Test {
 public:
  Test() { std::cout << "Test()" << std::endl; }
  ~Test() { std::cout << "~Test()" << std::endl; }

  void Run() { std::cout << "Run()" << std::endl; }
};

int main() {
  core::CoreLog(core::INFO, "%s:%d (%s) test log %d", __FILE__, __LINE__, __FUNCTION__, 1);

  std::vector<core::uint32> vec;
  vec.resize(10);
  core::CoreLog(core::INFO, "%s:%d (%s) vec size(%u)", __FILE__, __LINE__, __FUNCTION__, vec.size());

  vec.resize(5);
  core::CoreLog(core::INFO, "%s:%d (%s) vec size(%u)", __FILE__, __LINE__, __FUNCTION__, vec.size());


  // shared_ptr(A *ptr)
  core::shared_ptr<Test> ptr1(new Test);
  // shared_ptr(const shared_ptr &copy)
  core::shared_ptr<Test> ptr2 = ptr1;
  // shared_ptr()
  core::shared_ptr<Test> ptr3(new Test);

  std::cout << "1111111111111"<< std::endl;

  ptr1->Run();
  (*ptr1).Run();

  std::cout << "2222222222222"<< std::endl;

  // operator=
  ptr2 = ptr3;
  ptr1 = ptr3;

  // print ~Test()

  // Release
  ptr3.Release();

  std::cout << "3333333333333"<< std::endl;

  // GetPtr
  Test *test = ptr2.GetPtr();
  test->Run();

  std::cout << "4444444444444"<< std::endl;

  // IsNull
  if(ptr1.IsNull()) {
    std::cout << "1.IsNull()" << std::endl;
  } else {
    std::cout << "1.Not IsNull()" << std::endl;
  }
  if(ptr3.IsNull()) {
    std::cout << "2.IsNull()" << std::endl;
  } else {
    std::cout << "2.Not IsNull()" << std::endl;
  }

  std::cout << "5555555555555"<< std::endl;

  ptr2.Release();

  std::cout << "6666666666666"<< std::endl;

  ptr1.Release();

  // print ~Test()

  std::cout << "7777777777777"<< std::endl;

  ptr3.Release();

  std::cout << "7777777777777"<< std::endl;

  ptr3.Release();
  ptr3.Release();
  ptr3.Release();

  return 0;
}
