//
// core - server core source code.
//
// $Rev: 6033 $
// $Author: $
// $Date: 2012-03-16 14:43:23 +0800 (周五, 2012-03-16) $
//
// Define class ClientThreadPool.
//

#include "core/client_thread_pool.h"

#include "core/tcp_client.h"

namespace core {

ClientThreadPool::ClientThreadPool() {}

ClientThreadPool::~ClientThreadPool() {}

bool ClientThreadPool::Initialize() {
  // Client thread group.
  if(this->client_threads_.Initialize(CoreConfig::GetThread()->client_number_, "ClientThread") == false) {
    CoreLog(ERROR, "%s:%d (%s) Failed in initialize client_threads_", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  return true;
}

void ClientThreadPool::Start() {
  this->client_threads_.Start();
}

void ClientThreadPool::Stop() {
  this->client_threads_.Stop();
}

}  // namespace core

