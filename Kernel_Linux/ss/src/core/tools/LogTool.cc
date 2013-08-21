//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7191 $
// $Author: $
// $Date: 2012-05-05 20:23:03 +0800 (周六, 2012-05-05) $
//
// Define class LogTool.
//

#include "core/tools/LogTool.h"

#include "core/logic_log.h"
#include "core/base/variable_parameter.h"

static const u32 kLogMaxLen = 4096;
static const std::string kLogLevelName[LogLevelMax] = {
  "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

LogTool::LogTool() : log_level_(Debug), log_(NULL) {}
LogTool::~LogTool() {}

bool LogTool::Initialize(LogicLog *log) {
  this->log_ = log;
  return true;
}

void LogTool::Release() {
  delete this;
}

void LogTool::Logger(u8 level, const char * format, ...) {
  if(level >= this->log_level_) {
    char buff[kLogMaxLen + 1] = {0};
    bzero(buff, sizeof(buff));
    GET_VARIABLE_PARAMETERS(buff, sizeof(buff), format);

    this->log_->Logger(kLogLevelName[level].c_str(), buff);
  }
}

void LogTool::TraceLn(LPCSTR lpszFormat, ...) {
  if(Info >= this->log_level_) {
    char buff[kLogMaxLen + 1] = {0};
    bzero(buff, sizeof(buff));
    GET_VARIABLE_PARAMETERS(buff, sizeof(buff), lpszFormat);

    this->log_->Logger(kLogLevelName[Info].c_str(), buff);
  }
}

void LogTool::TraceErrorLn(LPCSTR lpszFormat, ...) {
  if(Error >= this->log_level_) {
    char buff[kLogMaxLen + 1] = {0};
    bzero(buff, sizeof(buff));
    GET_VARIABLE_PARAMETERS(buff, sizeof(buff), lpszFormat);

    this->log_->Logger(kLogLevelName[Error].c_str(), buff);
  }
}

void LogTool::ItemLog(u8 level, const char *format, ...) {
  if(level >= this->log_level_) {
    char buff[kLogMaxLen + 1] = {0};
    bzero(buff, sizeof(buff));
    GET_VARIABLE_PARAMETERS(buff, sizeof(buff), format);

    this->log_->Logger(kLogLevelName[level].c_str(), buff, LOG_TYPE_GOODS);
  }
}

void LogTool::InstanceLog(u8 level, const char *format, ...) {
  if(level >= this->log_level_) {
    char buff[kLogMaxLen + 1] = {0};
    bzero(buff, sizeof(buff));
    GET_VARIABLE_PARAMETERS(buff, sizeof(buff), format);

    this->log_->Logger(kLogLevelName[level].c_str(), buff, LOG_TYPE_INSTANCE);
  }
}

void LogTool::TrainLog(u8 level, const char *format, ...) {
  if(level >= this->log_level_) {
    char buff[kLogMaxLen + 1] = {0};
    bzero(buff, sizeof(buff));
    GET_VARIABLE_PARAMETERS(buff, sizeof(buff), format);

    this->log_->Logger(kLogLevelName[level].c_str(), buff, LOG_TYPE_TRAIN);
  }
}

void LogTool::BattleLog(u8 level, const char *format, ...) {
  if(level >= this->log_level_) {
    char buff[kLogMaxLen + 1] = {0};
    bzero(buff, sizeof(buff));
    GET_VARIABLE_PARAMETERS(buff, sizeof(buff), format);

    this->log_->Logger(kLogLevelName[level].c_str(), buff, LOG_TYPE_BATTLE);
  }
}

