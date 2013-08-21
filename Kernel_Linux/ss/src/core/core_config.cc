//
// core - server core source code.
//
// $Rev: 9885 $
// $Author: $
// $Date: 2012-08-27 18:14:28 +0800 (周一, 2012-08-27) $
//
// Define class CoreConfig.
//

#include "core/core_config.h"

#include "core/base/logging.h"

namespace core {

pthread_once_t CoreConfig::once_ = PTHREAD_ONCE_INIT;
std::string CoreConfig::file_;
ThreadConfig CoreConfig::thread_;
TCPConnectionConfig CoreConfig::tcp_connection_;
ConnectorConfig CoreConfig::connector_;
AcceptorConfig CoreConfig::acceptor_;
TimerConfig CoreConfig::timer_;
LogConfig CoreConfig::log_;
Mutex CoreConfig::mutex_;
bool CoreConfig::loaded_ = false;


void CoreConfig::LoadConfig() {
  if(CoreConfig::file_.empty() == true) {
    CoreLog(ERROR, "%s:%d (%s) File name empty.",
           __FILE__, __LINE__, __FUNCTION__);
    return ;
  }

  // Load CoreConfig::file_.
  TiXmlDocument doc;
  if(doc.LoadFile(file_.c_str()) == false) {
    CoreLog(ERROR, "%s:%d (%s) Load CoreConfig::file_(%s) error.",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return ;
  }

  // config node.
  TiXmlElement *config_node = doc.FirstChildElement("config");
  if(config_node == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Can't get node [config], CoreConfig::file_(%s).",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return ;
  }

  // thread node.
  TiXmlElement *thread_node = config_node->FirstChildElement("thread");
  if(thread_node == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Can't get node [thread], CoreConfig::file_(%s).",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return;
  } else {
    // message_thread_node.
    TiXmlElement *message_thread_node = thread_node->FirstChildElement("message_thread");
    if(message_thread_node == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get node [thread-message_thread], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
    if(message_thread_node->Attribute("number", &CoreConfig::thread_.message_number_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [thread-message_thread-number], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
    // client_thread_node.
    TiXmlElement *client_thread_node = thread_node->FirstChildElement("client_thread");
    if(client_thread_node == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get node [thread-client_thread], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
    if(client_thread_node->Attribute("number", &CoreConfig::thread_.client_number_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [thread-client_thread-number], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
#ifdef _CORE_DEBUG
    CoreLog(INFO, "<verify_thread number=\"%d\"/>", CoreConfig::thread_.verify_number_);
    CoreLog(INFO, "<message_thread number=\"%d\"/>", CoreConfig::thread_.message_number_);
    CoreLog(INFO, "<client_thread number=\"%d\"/>", CoreConfig::thread_.client_number_);
#endif
  }

  // tcp_connection node.
  TiXmlElement *tcp_connection_node = config_node->FirstChildElement("tcp_connection");
  if(tcp_connection_node == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Can't get node [tcp_connection], CoreConfig::file_(%s).",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return ;

  } else {
    if(tcp_connection_node->Attribute("kick_timeout", &CoreConfig::tcp_connection_.kick_timeout_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [tcp_connection-kick_timeout], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }

    const char *str = tcp_connection_node->Attribute("tgw");
    if(str && strncmp(str, "true", sizeof(str)) == 0) {
      CoreConfig::tcp_connection_.open_tgw_ = true;
      CoreLog(INFO, "tgw=true\n");
    } else {
      CoreConfig::tcp_connection_.open_tgw_ = false;
      CoreLog(INFO, "tgw=false\n");
    }

    // buffer node.
    TiXmlElement *buffer_node = tcp_connection_node->FirstChildElement("buffer");
    if(buffer_node == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get node [tcp_connection-buffer], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
    if(buffer_node->Attribute("unit_size", &CoreConfig::tcp_connection_.buffer_unit_size_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [tcp_connection-buffer-unit_size], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
    if(buffer_node->Attribute("init_size", &CoreConfig::tcp_connection_.buffer_init_size_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [tcp_connection-buffer-buffer_init_size], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }

#ifdef _CORE_DEBUG
      CoreLog(INFO, "<buffer unit_size=\"%d\", init_size\"%d\"/>",
             CoreConfig::tcp_connection_.buffer_unit_size_, CoreConfig::tcp_connection_.buffer_init_size_);
#endif

    // ring_queue node.
    TiXmlElement *ring_queue_node = tcp_connection_node->FirstChildElement("ring_queue");
    if(ring_queue_node == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get node [tcp_connection-ring_queue], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
    if(ring_queue_node->Attribute("size", &CoreConfig::tcp_connection_.ring_queue_size_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [tcp_connection-ring_queue_size], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
    if(ring_queue_node->Attribute("unit_size", &CoreConfig::tcp_connection_.ring_queue_unit_size_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [tcp_connection-ring_queue_unit_size], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }

#ifdef _CORE_DEBUG
      CoreLog(INFO, "<ring_queue size=\"%d\" unit_size=\"%d\"/>",
             CoreConfig::tcp_connection_.ring_queue_size_, CoreConfig::tcp_connection_.ring_queue_unit_size_);
#endif

  }

  // connector node.
  TiXmlElement *connector_node = config_node->FirstChildElement("connector");
  if(connector_node == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Can't get node [connector], CoreConfig::file_(%s).",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return;
  } else {
    if(connector_node->Attribute("retry_msec", &CoreConfig::connector_.retry_msec_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [connector_-retry_msec], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
#ifdef _CORE_DEBUG
    CoreLog(INFO, "<connector retry_msec=\"%d\"/>", CoreConfig::connector_.retry_msec_);
#endif
  }

  // acceptor node.
  TiXmlElement *acceptor_node = config_node->FirstChildElement("acceptor");
  if(acceptor_node == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Can't get node [acceptor], CoreConfig::file_(%s).",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return;
  } else {
    if(acceptor_node->Attribute("ring_size", &CoreConfig::acceptor_.ring_size_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [acceptor-ring_size], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
#ifdef _CORE_DEBUG
    CoreLog(INFO, "<acceptor ring_size=\"%d\"/>", CoreConfig::acceptor_.ring_size_);
#endif
  }

  // timing_wheel node.
  TiXmlElement *timing_wheel_node = config_node->FirstChildElement("timing_wheel");
  if(timing_wheel_node == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Can't get node [timing_wheel], CoreConfig::file_(%s).",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return ;
  } else {
    if(timing_wheel_node->Attribute("tick_msec", &CoreConfig::timer_.unit_interval_msec_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [timing_wheel-tick_msec], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
#ifdef _CORE_DEBUG
    CoreLog(INFO, "<timing_wheel tick_msec=\"%d\"/>", CoreConfig::timer_.unit_interval_msec_);
#endif

  }

  // log node.
  TiXmlElement *log_node = config_node->FirstChildElement("logging");
  if(log_node == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Can't get node [log], CoreConfig::file_(%s).",
           __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
    return ;
  } else {
    if(log_node->Attribute("log_ring_size", &CoreConfig::log_.log_ring_size_) == NULL) {
      CoreLog(ERROR, "%s:%d (%s) Can't get attribute [logging-log_ring_size], CoreConfig::file_(%s).",
             __FILE__, __LINE__, __FUNCTION__, CoreConfig::file_.c_str());
      return ;
    }
#ifdef _CORE_DEBUG
    CoreLog(INFO, "<log log_ring_size=\"%d\"/>", CoreConfig::log_.log_ring_size_);
#endif

  }

  CoreConfig::loaded_ = true;
}

}  // namespace core
