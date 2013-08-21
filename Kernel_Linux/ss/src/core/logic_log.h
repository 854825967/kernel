//
// core - server core source code.
//
// $Rev: 6775 $
// $Author: $
// $Date: 2012-04-13 17:11:45 +0800 (鍛ㄤ簲, 2012-04-13) $
//
// Define class LogicLog.
//

#ifndef __LOGIC__LOG__H
#define __LOGIC__LOG__H

#include <string>

#include "core/base/boundless_entity_ring_queue.h"
#include "core/base/noncopyable.h"

namespace core {

enum LogicLogType {
  LOG_TYPE_COMMON = 0,
  LOG_TYPE_INSTANCE,
  LOG_TYPE_TRAIN,
  LOG_TYPE_BATTLE,
  LOG_TYPE_GOODS,

  LOG_TYPE_MAX,
};

struct LogInfo {
  std::string level_;
  std::string log_;
  LogicLogType type_;
};

class LogicLog : public Noncopyable {
  typedef BoundlessEntityRingQueue<LogInfo> LogQueue;

 public:
  LogicLog();
  ~LogicLog();

  bool Initialize(const std::string &suffix);

  void SetFileName(LogicLogType type, const std::string &file);

  // For log thread.
  void Logger();
  // For logic thread.
  void Logger(const char *log_level, const char *contect, LogicLogType type = LOG_TYPE_COMMON);

  // Stop logger.
  inline void Stop() {this->queue_->ProduceCompletely(); }

 private:
  void Flush(LogicLogType type, const char *log_level, const char *contect);

  LogQueue *queue_;
  std::string file_;
  std::string file_time_;
  std::string file_suffix_;

  std::string temp_file_;

  // Logic detail log.
  std::string day_instance_battle_file_;
  std::string day_train_battle_file_;
  std::string battle_detail_file_;
  std::string goods_file_;
};

}  // namespace core

#endif  // __LOGIC__LOG__H

