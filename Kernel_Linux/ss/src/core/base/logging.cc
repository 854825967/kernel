//
// core - server core source code.
//
// $Rev: 6708 $
// $Author: $
// $Date: 2012-04-12 17:41:05 +0800 (周四, 2012-04-12) $
//
// Define class logger.
//

#include "core/base/logging.h"

#include <stdlib.h>
#include <time.h>

#include "core/base/auto_mutex.h"
#include "core/base/mutex.h"
#include "core/base/variable_parameter.h"

namespace core {


std::ofstream Logger::info_log_file_;
std::ofstream Logger::warn_log_file_;
std::ofstream Logger::erro_log_file_;

void InitializeLogger(const std::string& info_log_filename,
                      const std::string& warn_log_filename,
                      const std::string& erro_log_filename) {
  Logger::info_log_file_.open(info_log_filename.c_str());
  Logger::warn_log_file_.open(warn_log_filename.c_str());
  Logger::erro_log_file_.open(erro_log_filename.c_str());
}

/*static*/
std::ostream& Logger::GetStream(LogSeverity severity) {
  return (severity == INFO) ?
      (info_log_file_.is_open() ? info_log_file_ : std::cout) :
      (severity == WARNING ?
       (warn_log_file_.is_open() ? warn_log_file_ : std::cerr) :
       (erro_log_file_.is_open() ? erro_log_file_ : std::cerr));
}

/*static*/
std::ostream& Logger::Start(LogSeverity severity)/*,
                            const std::string& file,
                            int line,
                            const std::string& function)*/ {
  time_t tm;
  time(&tm);
  char time_string[128];
  ctime_r(&tm, time_string);
/*
  return GetStream(severity) //<< time_string
                             << " [" << kServrityString[severity] << "] " << file << ":" << line
                             << " (" << function << ") " << std::flush;
*/
  return GetStream(severity) << time_string << " [" << kServrityString[severity] << "] " << std::flush;
}

Logger::~Logger() {
  GetStream(severity_) << "\n" << std::flush;

  if (severity_ == FATAL) {
    info_log_file_.close();
    warn_log_file_.close();
    erro_log_file_.close();
    abort();
  }
}

void CoreLog(LogSeverity level, const char *content, ...) {
  static Mutex mutex;
  static const uint32 kMaxLogLength = 10240;

  AutoMutex auto_mutex(&mutex);
  char log[kMaxLogLength + 1];
  memset(log, 0, sizeof(log));
  GET_VARIABLE_PARAMETERS(log, sizeof(log), content);

  LOG(level) << log;
}


}  // namespace core

