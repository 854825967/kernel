//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 6799 $
// $Author: than $
// $Date: 2012-04-14 18:02:32 +0800 (鍛ㄥ叚, 2012-04-14) $
//
// Define class ServerConfigure.
//

#include "Header.h"
#include "ServerConfigure.h"
#include "core/base/logging.h"

ServerConfigure::ServerConfigure() {}
ServerConfigure::~ServerConfigure() {}

bool ServerConfigure::Load(const char *file) {
  TiXmlDocument doc;
  if(doc.LoadFile(file) == false) {
    printf("%s:%d (%s) [ERROR] Load file(%s) error.",
           __FILE__, __LINE__, __FUNCTION__, file);
    return false;
  }

  const char *str = NULL;

  // config node.
  TiXmlElement *config_node = doc.FirstChildElement("config");
  if(config_node == NULL) {
    printf("%s:%d (%s) [ERROR] Can't get node [config], file(%s).",
           __FILE__, __LINE__, __FUNCTION__, file);
    return false;
  }

  // gateway server node.
  TiXmlElement *gateway_server_node = config_node->FirstChildElement("gateway_server");
  if(gateway_server_node == NULL) {
    printf("%s:%d (%s) [ERROR] Can't get node [gateway_server], file(%s).",
           __FILE__, __LINE__, __FUNCTION__, file);
    return false;
  } else {
    str = gateway_server_node->Attribute("core");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-core], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->core_dir_ = str;

    str = gateway_server_node->Attribute("core_log");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-core_log], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->core_log_ = str;

    str = gateway_server_node->Attribute("logic_log");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-logic_log], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->logic_log_ = str;

    str = gateway_server_node->Attribute("db_config");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-db_config], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->db_server_ini_ = str;

    // node node.
    TiXmlElement *node_node = gateway_server_node->FirstChildElement("node");
    while(node_node) {
      u32 id = 0;
      SingleServerInfo info;
      if(node_node->Attribute("id", (int *)(&id)) == NULL) {
        printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-node-id], file(%s).",
               __FILE__, __LINE__, __FUNCTION__, file);
        return false;
      }

      str = node_node->Attribute("ip");
      if(str == NULL) {
        printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-node-ip], file(%s).",
               __FILE__, __LINE__, __FUNCTION__, file);
        return false;
      }
      info.ip_ = str;

      if(node_node->Attribute("port", (int *)(&info.port_)) == NULL) {
        printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-node-port], file(%s).",
               __FILE__, __LINE__, __FUNCTION__, file);
        return false;
      }

      if(node_node->Attribute("user_max_number", (int *)(&info.user_max_number_)) == NULL) {
        printf("%s:%d (%s) [ERROR] Can't get attribute [gateway_server-node-user_max_number], file(%s).",
               __FILE__, __LINE__, __FUNCTION__, file);
        return false;
      }

      this->servers_.insert(std::make_pair(id, info));
      node_node = node_node->NextSiblingElement("node");
    }

    // deamon node.
    TiXmlElement *deamon_node = gateway_server_node->FirstChildElement("deamon");
    if(deamon_node == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get node [gateway_server-deamon], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    } else { 
      str = deamon_node->Attribute("value");
      if(str == NULL || strncmp(str, "true", 5) == 0) {
        this->deamon_ = true;
      } else {
        this->deamon_ = false;
      }
    }
  }

  // center server node.
  TiXmlElement *center_server_node = config_node->FirstChildElement("center_server");
  if(center_server_node == NULL) {
    printf("%s:%d (%s) [ERROR] Can't get node [center_server], file(%s).",
           __FILE__, __LINE__, __FUNCTION__, file);
    return false;
  } else {
    str = center_server_node->Attribute("client");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [center_server-client], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->center_client_so_ = str;

    // server node.
    TiXmlElement *server_node = center_server_node->FirstChildElement("server");
    if(server_node == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get node [center_server-server], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    str = server_node->Attribute("ip");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [center_server-server-ip], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->center_server_ip_ = str;

    if(server_node->Attribute("port", (int *)(&this->center_server_port_)) == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [center_server-server-port], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
  }

  // db server node.
  TiXmlElement *db_server_node = config_node->FirstChildElement("db_server");
  if(db_server_node == NULL) {
    printf("%s:%d (%s) [ERROR] Can't get node [db_server], file(%s).",
           __FILE__, __LINE__, __FUNCTION__, file);
    return false;
  } else {
    str = db_server_node->Attribute("client");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-client], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->db_client_so_ = str;
  }
  return true;
}

bool ServerConfigure::GetLocalServerInfo(u32 key, std::string &ip,
       u16 &port, u32 &user_max_number) {
  LocalServerConfigure::iterator iterator = this->servers_.find(key);
  if(iterator != this->servers_.end()) {
    ip = iterator->second.ip_;
    port = iterator->second.port_;
    user_max_number = iterator->second.user_max_number_;
    return true;
  }

  return false;
}
