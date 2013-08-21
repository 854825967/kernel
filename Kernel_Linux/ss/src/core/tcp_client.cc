//
// core - server core source code.
//
// $Rev: 9885 $
// $Author: $
// $Date: 2012-08-27 18:14:28 +0800 (周一, 2012-08-27) $
//
// Define class TCPClient.
//

#include "core/tcp_client.h"

#include <string>

#include "core/client_thread_pool.h"
#include "core/connector.h"
#include "core/core_config.h"
#include "core/event_loop.h"
#include "core/tcp_connection.h"
#include "core/base/logging.h"
#include "core/base/time_tick.h"

namespace core {

TCPClient::TCPClient(const InetAddress &server_address, const std::string &name)
       : connected_(false), name_(name),
         loop_(NULL), connector_(NULL),
         connection_(NULL), server_address_(server_address),
         pool_(NULL), logic_connection_queue_(NULL) {
#ifdef _CORE_DEBUG
  CoreLog(INFO, "TCPClient::TCPClient()");
#endif
}

TCPClient::~TCPClient() {
#ifdef _CORE_DEBUG
  CoreLog(INFO, "TCPClient::~TCPClient() this=[%p]", this);
#endif
  if(this->connection_) {
    delete this->connection_;
    this->connection_ = NULL;
  }
  if(this->connector_) {
    delete this->connector_;
    this->connector_ = NULL;
  }
}

bool TCPClient::Initialize(EventLoop *loop, ClientThreadPool *pool, RingQueueLogicTCPConnection *queue) {
  this->loop_ = loop;
  this->pool_ = pool;
  this->logic_connection_queue_ = queue;

  this->connector_ = new Connector(this->loop_,
         this->server_address_, CoreConfig::GetConnector()->retry_msec_);
  if(this->connector_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate connector.", __FILE__, __LINE__, __FUNCTION__);
    return false;
  } else {
    this->connector_->SetNewConnectionCallback(function::Bind(&TCPClient::NewTCPConnection, this));
    return true;
  }
}

void TCPClient::Start() {
  if(this->connected_ == false) {
    this->connector_->Start();
  }
}

void TCPClient::Stop() {
#ifdef _CORE_DEBUG
  CoreLog(INFO, "TCPClient::Stop()");
#endif
  if(this->connected_ == false) {
    this->connector_->Stop();
  } else {
    this->connector_->Stop();
    // Set logic recycled, and Require network shutdown.
    this->connection_->SetLogicRecycled();
    this->connection_->RequireShutdown();
    // Block to network shoutdown finished.
    while(this->connection_->CheckCanRecycle() == false) {
      sleep(1);
    }
    // close socket and release memory.
    this->connection_->Shutdown();
    delete this->connection_;
    this->connection_ = NULL;
  }
  this->connected_ = false;
}

void TCPClient::NewTCPConnection(int sockfd, const InetAddress &local) {
  char buffer[16];
  snprintf(buffer, sizeof(buffer), ":%d", sockfd);
  std::string connection_name = this->name_ + buffer;
  this->connection_ = new TCPConnection(sockfd, this->pool_->GetNextClientLoop(),
        connection_name, local, this->server_address_);
  if(this->connection_ == NULL) {
    CoreLog(ERROR, "%s:%d (%s) Failed in allocate connection.", __FILE__, __LINE__, __FUNCTION__);
  } else if(this->connection_->Initialize(false, CoreConfig::GetTcpConnection()->open_tgw_) == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in Initialize connection.", __FILE__, __LINE__, __FUNCTION__);
    delete connection_;
    this->connection_ = NULL;
  } else {
    this->connection_->SetConnectionEstablishedCallback(
           function::Bind(&TCPClient::OnConnectionEstablished, this));
    TimeTick now;
    now.Update();
    // Start conection, this will callback OnConnectionEstablished.
    this->connection_->OnConnectionStart(now);
    this->GetLogicConnectionQueue()->Add(this->connection_);
    this->connected_ = true;
  }
}

}  // namespace core

