//
// core - server core source code.
//
// $Rev: 6775 $
// $Author: $
// $Date: 2012-04-13 17:11:45 +0800 (周五, 2012-04-13) $
//
// Define class LogicLog.
//

#include "core/logic_log.h"

#include "core/core_config.h"
#include "core/base/logging.h"

namespace core {

LogicLog::LogicLog() : queue_(NULL) {}

LogicLog::~LogicLog() {
  if(this->queue_) {
    delete this->queue_;
    this->queue_ = NULL;
  }
}

bool LogicLog::Initialize(const std::string &suffix) {
  this->queue_ = new LogQueue(CoreConfig::GetLog()->log_ring_size_,
         ring_queue::BLOCKING_CONSUMER);
  if(this->queue_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed to allocate queue.",
           __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  this->file_suffix_ = suffix;

  return true;
}

void LogicLog::SetFileName(LogicLogType type, const std::string &file) {
  switch(type) {
    case LOG_TYPE_COMMON:
      this->file_ = file;
      break;
    case LOG_TYPE_INSTANCE:
      this->day_instance_battle_file_ = file;
      break;
    case LOG_TYPE_TRAIN:
      this->day_train_battle_file_ = file;
      break;
    case LOG_TYPE_BATTLE:
      this->battle_detail_file_ = file;
      break;
    case LOG_TYPE_GOODS:
      this->goods_file_ = file;
      break;
    default:
      break;
  }
}

// For logic thread.
void LogicLog::Logger(const char *log_level, const char *contect, LogicLogType type) {
  if(type >= LOG_TYPE_MAX) return ;

  LogInfo *log = new LogInfo;
  log->level_ = log_level;
  log->log_ = contect;
  log->type_ = type;

  this->queue_->Add(log);
}

// For log thread.
void LogicLog::Logger() {
  LogInfo *log = NULL;
  if(this->queue_->Remove(log) == ring_queue::kErrorCodeSuccess) {
    this->Flush(log->type_, log->level_.c_str(), log->log_.c_str());
    delete log;
    log = NULL;
  }
}

void LogicLog::Flush(LogicLogType type, const char *level, const char *content) {
  time_t now;
  now = time(NULL);

  tm *tm_now = localtime(&now);
  char current_time[32] = {0};
  strftime(current_time, sizeof(current_time), "%Y-%m-%d %H:%M:%S", tm_now);
  char file_time[32];
  strftime(file_time, sizeof(file_time), "-%Y-%m-%d", tm_now);

  switch(type) {
    case LOG_TYPE_COMMON:
      this->temp_file_ = this->file_;
      break;
    case LOG_TYPE_INSTANCE:
      this->temp_file_ = this->day_instance_battle_file_;
      break;
    case LOG_TYPE_TRAIN:
      this->temp_file_ = this->day_train_battle_file_;
      break;
    case LOG_TYPE_BATTLE:
      this->temp_file_ = this->battle_detail_file_;
      break;
    case LOG_TYPE_GOODS:
      this->temp_file_ = this->goods_file_;
      break;
    default:
      return ;
  }

  this->temp_file_ += file_time + this->file_suffix_;
  FILE *fp = fopen((this->temp_file_).c_str(), "a");
  if(fp != NULL) {
    fprintf(fp, "[%s][%s]:%s\n", current_time, level, content);
    fclose(fp);
  }
}

}  // namespace core

