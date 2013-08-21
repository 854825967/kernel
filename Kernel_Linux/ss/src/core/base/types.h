//
// core - server core source code.
//
// $Rev: 2353 $
// $Author: $
// $Date: 2011-12-08 18:05:59 +0800 (鍛ㄥ洓, 2011-12-08) $
//
// Types define.
//

#ifndef __TYPES__H
#define __TYPES__H

#include <stdint.h>

namespace core {

// ===================================================================
// from google3/base/port.h
// We modify some micro names.

typedef unsigned int uint;

#ifdef _MSC_VER
typedef __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
#else
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
#endif

// long long macros to be used because gcc and vc++ use different suffixes,
// and different size specifiers in format strings
#undef CORE_LONGLONG
#undef CORE_ULONGLONG
#undef CORE_LL_FORMAT

#ifdef _MSC_VER
#define CORE_LONGLONG(x) x##I64
#define CORE_ULONGLONG(x) x##UI64
#define CORE_LL_FORMAT "I64"  // As in printf("%I64d", ...)
#else
#define CORE_LONGLONG(x) x##LL
#define CORE_ULONGLONG(x) x##ULL
#define CORE_LL_FORMAT "ll"  // As in "%lld". Note that "q" is poor form also.
#endif

static const int32 kint32max = 0x7FFFFFFF;
static const int32 kint32min = -kint32max - 1;
static const int64 kint64max = CORE_LONGLONG(0x7FFFFFFFFFFFFFFF);
static const int64 kint64min = -kint64max - 1;
static const uint32 kuint32max = 0xFFFFFFFFu;
static const uint64 kuint64max = CORE_ULONGLONG(0xFFFFFFFFFFFFFFFF);

// ===================================================================

}  // namespace core

#endif  // __TYPES__H

