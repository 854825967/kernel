//
// core - server core source code.
//
// $Rev: 9885 $
// $Author: $
// $Date: 2012-08-27 18:14:28 +0800 (鍛ㄤ竴, 2012-08-27) $
//
// Define class CoreConfig.
//

#ifndef __CORE__CONFIG__H
#define __CORE__CONFIG__H

#include <pthread.h>

#include <string>

#include "core/base/mutex.h"
#include "core/base/noncopyable.h"
#include "core/tinyxml/tinyxml.h"

namespace core {

struct ThreadConfig {
  int verify_number_;
  int message_number_;
  int client_number_;
};

struct TCPConnectionConfig {
  int buffer_unit_size_;
  int buffer_init_size_;
  int ring_queue_size_;
  int ring_queue_unit_size_;
  int kick_timeout_;
  bool open_tgw_;
};

struct ConnectorConfig {
  int retry_msec_;
};

struct AcceptorConfig {
  int ring_size_;
};

struct TimerConfig {
  int unit_interval_msec_;
};

struct LogConfig {
  int log_ring_size_;
};

class CoreConfig : public Noncopyable {
 public:
  CoreConfig() {}
  ~CoreConfig() {}

  static inline bool CheckFinishLoad() { return CoreConfig::loaded_; }

  static void Init(const std::string &file) {
    CoreConfig::mutex_.Lock();
    CoreConfig::file_ = file;
    CoreConfig::mutex_.Unlock();

    ::pthread_once(&CoreConfig::once_, &CoreConfig::LoadConfig);
  }

  static inline const ThreadConfig *GetThread() {
    return &CoreConfig::thread_;
  }
  static inline const TCPConnectionConfig *GetTcpConnection() {
    return &CoreConfig::tcp_connection_;
  }
  static inline const ConnectorConfig *GetConnector() {
    return &CoreConfig::connector_;
  }
  static inline const AcceptorConfig *GetAcceptor() {
    return &CoreConfig::acceptor_;
  }
  static inline const TimerConfig *GetTimer() {
    return &CoreConfig::timer_;
  }
  static inline const  LogConfig *GetLog() {
    return &CoreConfig::log_;
  }

 private:
  static void LoadConfig();

  static std::string file_;
  static ThreadConfig thread_;
  static TCPConnectionConfig tcp_connection_;
  static ConnectorConfig connector_;
  static AcceptorConfig acceptor_;
  static TimerConfig timer_;
  static LogConfig log_;

  static Mutex mutex_;

  static pthread_once_t once_;

  static bool loaded_;
};

}  // namespace core

#endif  // __CORE__CONFIG__H

