//
// core - server core source code.
//
// $Rev: 2704 $
// $Author: $
// $Date: 2011-12-30 11:58:08 +0800 (鍛ㄤ簲, 2011-12-30) $
//
// Define class Logger.
//

#ifndef __BASE__LOGGING__H
#define __BASE__LOGGING__H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "core/base/mutex.h"
#include "core/base/types.h"

namespace core {

void InitializeLogger(const std::string& info_log_filename = "~/tmp/core_info.log",
                      const std::string& warn_log_filename = "~/tmp/core_warn.log",
                      const std::string& erro_log_filename = "~/tmp/core_error.log");

enum LogSeverity { INFO, WARNING, ERROR, FATAL, MAX, };
static std::string kServrityString[MAX] = { "INFO", "WARNING", "ERROR", "FATAL" };

class Logger {
  friend void InitializeLogger(const std::string& info_log_filename,
                               const std::string& warn_log_filename,
                               const std::string& erro_log_filename);
public:
  Logger(LogSeverity s) : severity_(s) {}
  ~Logger();

  static std::ostream& GetStream(LogSeverity severity);
  static std::ostream& Start(LogSeverity severity);/*,
                             const std::string& file,
                             int line,
                             const std::string& function);*/

private:
  static std::ofstream info_log_file_;
  static std::ofstream warn_log_file_;
  static std::ofstream erro_log_file_;
  LogSeverity severity_;
};

// initialize log directorys and file names.
// InitializeLogger("/log/info.log", "/log/warn.log", "/log/error.log");


// The basic mechanism of logging.{h,cc} is as follows:
//  - LOG(severity) defines a Logger instance, which records the severity.
//  - LOG(severity) then invokes Logger::Start(), which invokes Logger::Stream
//    to choose an output stream, outputs a message head into the stream and
//    flush.
//  - The std::ostream reference returned by LoggerStart() is then passed to
//    user-specific output operators (<<), which writes the log message body.
//  - When the Logger instance is destructed, the destructor appends flush.
//    If severity is FATAL, the destructor causes SEGFAULT and core dump.
//
// It is important to flush in Logger::Start() after outputing message
// head.  This is because that the time when the destructor is invoked
// depends on how/where the caller code defines the Logger instance.
// If the caller code crashes before the Logger instance is properly
// destructed, the destructor might not have the chance to append its
// flush flags.  Without flush in Logger::Start(), this may cause the
// lose of the last few messages.  However, given flush in Start(),
// program crashing between invocations to Logger::Start() and
// destructor only causes the lose of the last message body; while the
// message head will be there.
//
#define LOG(severity)                                                   \
  Logger(severity).Start(severity)
//, __FILE__, __LINE__, __FUNCTION__)

void CoreLog(LogSeverity level, const char *content, ...);

}  // namespace core

#endif // __BASE__LOGGING__H

