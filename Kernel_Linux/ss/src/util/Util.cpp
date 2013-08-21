//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 11427 $
// $Author: $
// $Date: 2012-11-27 12:14:07 +0800 (鍛ㄤ簩, 2012-11-27) $
//
// Util.
//


#include "Util.h"

#include <stdarg.h>
#include <time.h>

namespace util {

namespace current_thread {

__thread struct timespec _t_ts;
__thread time_t _t_unix_time;

struct timespec *_t_GetTimeSpec() {
  return &_t_ts;
}

time_t _t_GetUnixTime() {
  return _t_unix_time;
}

}  // namespace current_thread

void UpdateTickCount(struct timespec *tm) {
  assert(tm);
  current_thread::_t_ts.tv_sec = tm->tv_sec ;
  current_thread::_t_ts.tv_nsec = tm->tv_nsec;
}

void UpdateUnixTime(time_t time) {
  current_thread::_t_unix_time = time;
}

time_t GetUnixTime() {
  return current_thread::_t_GetUnixTime();
}

unsigned int GetTickCount() {
/*
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
*/
  struct timespec *ts = current_thread::_t_GetTimeSpec();
  if(ts) {
    return (ts->tv_sec*1000 + ts->tv_nsec/(1000*1000));
  }
  return 0;
}

unsigned int GetTickCountUs() {
/*
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (ts.tv_sec*1000*1000 + ts.tv_nsec/1000);
*/
  struct timespec *ts = current_thread::_t_GetTimeSpec();
  if(ts) {
    return (ts->tv_sec*1000*1000 + ts->tv_nsec/1000);
  }
  return 0;
}

time_t GetTomorrowZeroTime() {
  time_t now = time(NULL);
  time_t tomorrow = now + 24 * 60 * 60;
  struct tm *tm_time = localtime(&tomorrow);
  tm_time->tm_hour = 0;
  tm_time->tm_min = 0;
  tm_time->tm_sec = 0;
  return mktime(tm_time);
}

time_t GetTodayZeroTime() {
  time_t now = time(NULL);
  struct tm *tm_time = localtime(&now);
  tm_time->tm_hour = 0;
  tm_time->tm_min = 0;
  tm_time->tm_sec = 0;
  return mktime(tm_time);
}

}  // namespace util

