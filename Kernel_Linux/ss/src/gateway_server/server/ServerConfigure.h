//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 5865 $
// $Author: than $
// $Date: 2012-03-12 18:31:55 +0800 (鍛ㄤ竴, 2012-03-12) $
//
// Define class ServerConfigure.
//

#ifndef __SERVER__CONFIGURE__H
#define __SERVER__CONFIGURE__H

#include <map>
#include <string>

#include "core/tinyxml/tinyxml.h"

struct SingleServerInfo {
  std::string ip_;
  u16 port_;
  u32 user_max_number_;
};

class ServerConfigure {
  typedef std::map<u32, SingleServerInfo> LocalServerConfigure;

 public:
  ServerConfigure();
  ~ServerConfigure();

  bool Load(const char *file);

  inline const std::string &GetCoreDir() const { return this->core_dir_; }
  inline const std::string &GetCoreLog() const { return this->core_log_; }
  inline const std::string &GetLogicLog() const { return this->logic_log_; }
  inline const std::string &GetDBServerIni() const { return this->db_server_ini_; }

  bool GetLocalServerInfo(u32 key, std::string &ip, u16 &port, u32 &user_max_number);

  inline const char *GetCenterServerIP() const { return this->center_server_ip_.c_str(); }
  inline u16 GetCenterServerPort() const { return this->center_server_port_; }

  inline const std::string &GetDBClientSo() const { return this->db_client_so_; }
  inline const std::string &GetCenterClientSo() const { return this->center_client_so_; }

  inline bool CheckDeamon() const { return this->deamon_; }

 private:
  LocalServerConfigure servers_;
  std::string core_dir_;
  std::string core_log_;
  std::string logic_log_;
  std::string db_server_ini_;
  std::string db_client_so_;
  std::string center_server_ip_;
  u16 center_server_port_;
  std::string center_client_so_;
  bool deamon_;
};

#endif  // __SERVER__CONFIGURE__H

