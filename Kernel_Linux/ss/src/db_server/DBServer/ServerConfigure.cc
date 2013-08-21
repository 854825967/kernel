//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 4012 $
// $Author: than $
// $Date: 2012-01-15 14:50:23 +0800 (周日, 2012-01-15) $
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

  // db server node.
  TiXmlElement *db_server_node = config_node->FirstChildElement("db_server");
  if(db_server_node == NULL) {
    printf("%s:%d (%s) [ERROR] Can't get node [db_server], file(%s).",
           __FILE__, __LINE__, __FUNCTION__, file);
    return false;
  } else {
    str = db_server_node->Attribute("core");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-core], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->core_dir_ = str;

    str = db_server_node->Attribute("core_log");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-core_log], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->core_log_ = str;

    str = db_server_node->Attribute("logic_log");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-logic_log], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->logic_log_ = str;

    str = db_server_node->Attribute("dbengine_log");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-dbengine_log], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->db_engine_log_ = str;
/*
    str = db_server_node->Attribute("db_engine");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-db_engine], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->db_engine_ = str;
*/
    str = db_server_node->Attribute("db_request");
    if(str == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-db_request], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    }
    this->db_request_ = str;

    // serverlist node.
    TiXmlElement *serverlist_node = db_server_node->FirstChildElement("serverlist");
    if(serverlist_node == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get node [db_server-serverlist], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    } else {
      // node node.
      TiXmlElement *node_node = serverlist_node->FirstChildElement("node");
      while(node_node) {
        u32 id = 0;
        SingleServerInfo info;
        if(node_node->Attribute("id", (int *)(&id)) == NULL) {
          printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-serverlist-id], file(%s).",
                 __FILE__, __LINE__, __FUNCTION__, file);
          return false;
        }

        str = node_node->Attribute("ip");
        if(str == NULL) {
          printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-serverlist-ip], file(%s).",
                 __FILE__, __LINE__, __FUNCTION__, file);
          return false;
        }
        info.ip_ = str;

        if(node_node->Attribute("port", (int *)(&info.port_)) == NULL) {
          printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-serverlist-port], file(%s).",
                 __FILE__, __LINE__, __FUNCTION__, file);
          return false;
        }

        if(node_node->Attribute("save_time", (int *)(&info.time_to_save_)) == NULL) {
          printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-serverlist-save_time], file(%s).",
                 __FILE__, __LINE__, __FUNCTION__, file);
          return false;
        }

        str = node_node->Attribute("db_engine");
        if(str == NULL) {
          printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-serverlist-db_engine], file(%s).",
              __FILE__, __LINE__, __FUNCTION__, file);
          return false;
        }
        info.db_engine_ = str;

        this->servers_.insert(std::make_pair(id, info));
        node_node = node_node->NextSiblingElement("node");
      }
    }

    // library node.
    TiXmlElement *library_node = db_server_node->FirstChildElement("librarys");
    if(library_node == NULL) {
      printf("%s:%d (%s) [ERROR] Can't get node [db_server-librarys], file(%s).",
             __FILE__, __LINE__, __FUNCTION__, file);
      return false;
    } else {
      // item node.
      TiXmlElement *item_node = library_node->FirstChildElement("item");
      while(item_node) {
        u32 id = 0;
        if(item_node->Attribute("id", (int *)(&id)) == NULL) {
          printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-librarys-id], file(%s).",
                 __FILE__, __LINE__, __FUNCTION__, file);
          return false;
        }
        str = item_node->Attribute("name");
        if(str == NULL) {
          printf("%s:%d (%s) [ERROR] Can't get attribute [db_server-librarys-name], file(%s).",
                 __FILE__, __LINE__, __FUNCTION__, file);
          return false;
        }

        this->librarys_.insert(std::make_pair(id, str));
        item_node = item_node->NextSiblingElement("item");
      }
    }
  }

  // deamon node.
  TiXmlElement *deamon_node = db_server_node->FirstChildElement("deamon");
  if(deamon_node == NULL) {
    printf("%s:%d (%s) [ERROR] Can't get node [db_server-deamon], file(%s).",
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

  return true;
}

bool ServerConfigure::GetLocalServerInfo(u32 key, std::string &ip, u16 &port, u32 &save_time, std::string &db_engine) {
  LocalServerConfigure::iterator iterator = this->servers_.find(key);
  if(iterator != this->servers_.end()) {
    ip = iterator->second.ip_;
    port = iterator->second.port_;
    save_time = iterator->second.time_to_save_;
    db_engine = iterator->second.db_engine_;
    return true;
  }

  return false;
}

const char *ServerConfigure::GetLibrary(u32 key) const {
  LibraryList::const_iterator iterator = this->librarys_.find(key);
  if(iterator != this->librarys_.end()) {
    return iterator->second.c_str();
  }

  return NULL;
}

