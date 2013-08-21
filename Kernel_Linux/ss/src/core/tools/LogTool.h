//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 6775 $
// $Author: $
// $Date: 2012-04-13 17:11:45 +0800 (鍛ㄤ簲, 2012-04-13) $
//
// Define class LogTool.
//

#ifndef __LOG__TOOL__H
#define __LOG__TOOL__H

#include "include/ILog.h"

namespace core {

class LogicLog;

}  // namespace core

using namespace core;

class LogTool : public ILog {
 public:
  LogTool();
  virtual ~LogTool();

  bool Initialize(LogicLog *log);

  virtual void Release();

  // New log version.
  virtual void SetLogLevel(u8 level) { this->log_level_ = level; }
  virtual void Logger(u8 level, const char * format, ...);

  // Compat old version.
  virtual void TraceLn(LPCSTR lpszFormat, ...);
  virtual void TraceErrorLn(LPCSTR lpszFormat, ...);

  // Detail log.
  virtual void ItemLog(u8 level, const char *format, ...);
  virtual void InstanceLog(u8 level, const char *format, ...);
  virtual void TrainLog(u8 level, const char *format, ...);
  virtual void BattleLog(u8 level, const char *format, ...);

 private:
  u8 log_level_;
  LogicLog *log_;
};

#endif  // __LOG__TOOL__H

