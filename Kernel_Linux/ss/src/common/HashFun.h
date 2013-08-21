//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 3464 $
// $Author: than $
// $Date: 2012-01-10 16:07:38 +0800 (鍛ㄤ簩, 2012-01-10) $
//
// Define hash function.
//

#ifndef __HASH__FUN__H
#define __HASH__FUN__H

namespace hash {

template <class _Key>
struct Hash { };

inline size_t HashString(const char *__s) {
  unsigned long __h = 0;
  for ( ; *__s; ++__s)
    __h = 5 * __h + *__s;
  return size_t(__h);
}

template <>
struct Hash<char *> {
  size_t operator()(const char *__s) {
    return HashString(__s);
  }
};

template <>
struct Hash<const char *> {
  size_t operator()(const char *__s) {
    return HashString(__s);
  }
};

}  // namespace hash

#endif  // __HASH__FUN__H

