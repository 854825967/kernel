//
// core - server core source code.
//
// $Rev: 6033 $
// $Author: $
// $Date: 2012-03-16 14:43:23 +0800 (鍛ㄤ簲, 2012-03-16) $
//
// Test code of client.
//

#ifndef __TEST__CLIENT__H
#define __TEST__CLIENT__H

#include "core/connection_task.h"
#include "core/tcp_client.h"
#include "core/base/logging.h"

namespace core {

class TestConnectionTask : public ConnectionTask {
 public:
  TestConnectionTask(TCPClient *client) : client_(client) {}
  virtual ~TestConnectionTask() {}

  virtual void OnRecieve(const char *message_, int size) {
    char message[10240];
    memcpy(message, message_, size);
    message[size] = '\0';
    CoreLog(INFO, "[CLIENT] Logic recieve message [size=%d] [message=%s]", size, message);
    this->Send(message, size);
    CoreLog(INFO, "[CLIENT] Logic send message [size=%d] [message=%s]", size, message);
  }
  virtual void OnConnectionOK() {
    static std::string connection_ok_send = "12345";
    CoreLog(INFO, "TestConnectionTask::OnConnectionOK");
    this->Send(connection_ok_send.c_str(), connection_ok_send.size());
    CoreLog(INFO, "[CLIENT] send message [size=%d] [message=%s]", connection_ok_send.size(), connection_ok_send.c_str());
    connection_ok_send = "678910";
    this->Send(connection_ok_send.c_str(), connection_ok_send.size());
    CoreLog(INFO, "[CLIENT] send message [size=%d] [message=%s]", connection_ok_send.size(), connection_ok_send.c_str());
    connection_ok_send = "aaaaaaaaaa";
    this->Send(connection_ok_send.c_str(), connection_ok_send.size());
    CoreLog(INFO, "[CLIENT] send message [size=%d] [message=%s]", connection_ok_send.size(), connection_ok_send.c_str());
  }
  virtual void OnCloseConnection(bool force) {
    CoreLog(INFO, "TestConnectionTask::OnCloseConnection delete!!");
    this->client_->Stop();
    this->client_->Start();
    delete this;
  }

 private:
  TCPClient *client_;
};

class TestClient : public TCPClient {
 public:
  TestClient(const InetAddress &address, std::string name)
         : TCPClient(address, name) {}
  virtual ~TestClient() {}

  virtual ConnectionTask *OnConnectionEstablished() {
    CoreLog(INFO, "TestClient::OnConnectionEstablished");
    TestConnectionTask *task = new TestConnectionTask(this);
    if(task == NULL) {
      return NULL;
    }
    return task;
  }
};

}  // namespace core

#endif  // __TEST__CLIENT__H

