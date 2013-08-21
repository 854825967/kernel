//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 6775 $
// $Author: than $
// $Date: 2012-04-13 17:11:45 +0800 (鍛ㄤ簲, 2012-04-13) $
//
// Define interface ILog.
//

#ifndef __ILOG__H
#define __ILOG__H

#include "include/GameType.h"

enum LogLevel {
  Debug = 0,
  Info,
  Warn,
  Error,
  Fatal,
  LogLevelMax,
};

class ILog {
 public:
  virtual ~ILog() {}

  virtual void Release() = 0;

  // New log version.
  virtual void SetLogLevel(u8 level) = 0;
  virtual void Logger(u8 level, const char *format, ...) = 0;

  // Compat old version.
  virtual void TraceLn(LPCSTR lpszFormat, ...) = 0;
  virtual void TraceErrorLn(LPCSTR lpszFormat, ...) = 0;

  // Detail log.
  virtual void ItemLog(u8 level, const char *format, ...) = 0;
  virtual void InstanceLog(u8 level, const char *format, ...) = 0;
  virtual void TrainLog(u8 level, const char *format, ...) = 0;
  virtual void BattleLog(u8 level, const char *format, ...) = 0;
};

#endif  // __ILOG__H

