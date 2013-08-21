//
// core - server core source code.
//
// $Rev: 6033 $
// $Author: $
// $Date: 2012-03-16 14:43:23 +0800 (鍛ㄤ簲, 2012-03-16) $
//
// Test code of server.
//

#ifndef __TEST__SERVER__H
#define __TEST__SERVER__H

#include "core/connection_task.h"
#include "core/tcp_server.h"
#include "core/base/logging.h"
#include "include/ILog.h"

namespace core {

static ILog *logger = NULL;

class TestConnectionTask : public ConnectionTask {
 public:
  TestConnectionTask() {}
  virtual ~TestConnectionTask() {}

  virtual void OnRecieve(const char *message_, int size) {
    char message[10240];
    memset(message, 0, sizeof(sizeof(message)));
    memcpy(message, message_, size);
    message[size] = '\0';
    if(strncmp(message, "67891", sizeof("67891")) == 0) {
      //CoreLog(INFO, "[SERVER____ERROR] Logic recieve message [size=%d] [message=%s]", size, message);
      logger->Logger(INFO, "[SERVER____ERROR] Logic recieve message [size=%d] [message=%s]", size, message);
    } else {
      //CoreLog(INFO, "[SERVER] Logic recieve message [size=%d] [message=%s]", size, message);
      logger->Logger(INFO, "[SERVER] Logic recieve message [size=%d] [message=%s]", size, message);
    }
    this->Send(message, size);
    //CoreLog(INFO, "[SERVER] Logic send message [size=%d] [message=%s]", size, message);
    logger->Logger(INFO, "[SERVER] Logic send message [size=%d] [message=%s]", size, message);
  }
  virtual void OnConnectionOK() {
    CoreLog(INFO, "TestConnectionTask::OnConnectionOK new connection!!");
  }
  virtual void OnCloseConnection(bool force) {
    CoreLog(INFO, "TestConnectionTask::OnCloseConnection delete!!");
    delete this;
  }
};

class TestServer : public TCPServer {
 public:
  TestServer(const InetAddress &address, const std::string &name)
         : TCPServer(address, name) {}
  virtual ~TestServer() {}

  virtual ConnectionTask *OnConnectionEstablished() {
    CoreLog(INFO, "TestServer::OnConnectionEstablished");
    TestConnectionTask *task = new TestConnectionTask();
    if(task == NULL) {
      return NULL;
    }
    return task;
  }
};

}  // namespace core

#endif  // __TEST__SERVER__H

