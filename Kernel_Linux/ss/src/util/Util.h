//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 11427 $
// $Author: $
// $Date: 2012-11-27 12:14:07 +0800 (鍛ㄤ簩, 2012-11-27) $
//
// Util.
//

#ifndef __UTIL__H
#define __UTIL__H

#include <assert.h>
#include <pthread.h>

namespace util {

void UpdateTickCount(struct timespec *tm);
void UpdateUnixTime(time_t time);

time_t GetUnixTime();
unsigned int GetTickCount();
unsigned int GetTickCountUs();

time_t GetTomorrowZeroTime();
time_t GetTodayZeroTime();

template <typename _Ty>
static void Construct(_Ty* _Ptr) {
  ::new (_Ptr) _Ty();
}

template <typename _Ty>
static void Construct(_Ty* _Ptr, const _Ty& _Val) {
  ::new (_Ptr) _Ty(_Val);
}

namespace current_thread {

struct timespec *_t_GetTimeSpec();

}  // namespace current_thread

}  // namespace util

#endif // __UTIL__H

