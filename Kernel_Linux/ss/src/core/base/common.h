//
// core - server core source code.
//
// $Rev: 2917 $
// $Author: $
// $Date: 2012-01-01 17:12:06 +0800 (鍛ㄦ棩, 2012-01-01) $
//
// common define.
//

#ifndef __COMMON__h
#define __COMMON__h

namespace core {


// ------------------------------------------
// disallow copy and assignment.
//
// to use as the follow example:
//
// class Foo {
//  public:
//   Foo();
//  private:
//   DISALLOW_COPY_AND_ASSIGN(Foo);
// };
// ------------------------------------------
#define DISALLOW_COPY_AND_ASSIGN(TypeName)      \
  TypeName(const TypeName&);                    \
  void operator=(const TypeName&)

// Convert to upper.
char *strupr(char *str);

}  // namespace core

#endif  // __COMMON__h

