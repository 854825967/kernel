//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 4012 $
// $Author: than $
// $Date: 2012-01-15 14:50:23 +0800 (鍛ㄦ棩, 2012-01-15) $
//
// Define class ServerConfigure.
//

#ifndef __SERVER__CONFIGURE__H
#define __SERVER__CONFIGURE__H

#include <string>

#include "core/tinyxml/tinyxml.h"

struct SingleServerInfo {
  std::string ip_;
  u16 port_;
  u32 time_to_save_;
  std::string db_engine_;
};

class ServerConfigure {
  typedef std::map<u32, SingleServerInfo> LocalServerConfigure;
  typedef std::map<u32, std::string> LibraryList;

 public:
  ServerConfigure();
  ~ServerConfigure();

  bool Load(const char *file);

  inline const std::string &GetCoreDir() const { return this->core_dir_; }
  inline const std::string &GetCoreLog() const { return this->core_log_; }
  inline const std::string &GetLogicLog() const { return this->logic_log_; }
  inline const std::string &GetDBEngineLog() const { return this->db_engine_log_; }
  // inline const std::string &GetDBEngine() const { return this->db_engine_; }
  inline const std::string &GetDBRequest() const { return this->db_request_; }

  bool GetLocalServerInfo(u32 key, std::string &ip, u16 &port, u32 &save_time, std::string &db_engine);

  const char *GetLibrary(u32 key) const;

  inline bool CheckDeamon() const { return this->deamon_; }

 private:
  std::string core_dir_;
  std::string core_log_;
  std::string logic_log_;
  std::string db_engine_log_;
  // std::string db_engine_;
  std::string db_request_;

  LocalServerConfigure servers_;
  LibraryList librarys_;

  bool deamon_;
};

#endif  // __SERVER__CONFIGURE__H

