//
// core - server core source code.
//
// $Rev: 6067 $
// $Author: $
// $Date: 2012-03-19 14:30:39 +0800 (周一, 2012-03-19) $
//
// Define class TCPSocket.
//
// TCPSocket is a wrapper of socket and it only supports TCP connection.
//

#include "core/tcp_socket.h"

#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>

#include "core/base/logging.h"

namespace core {

TCPSocket::TCPSocket(int socket)
       : socket_(socket),
         link_available_(false), 
         nonblocking_(false) {
}

TCPSocket::~TCPSocket() {
  this->Close();
}

bool TCPSocket::CreateSocket(bool reuse) {
  this->socket_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(this->socket_ == -1) {
    CoreLog(ERROR, "%s:%d (%s) Failed to create a socket.", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  int opt = reuse ? 1 : 0;
  if(::setsockopt(this->socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) != 0) {
    CoreLog(ERROR, "%s:%d (%s) Failed to setsockopt.", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  return true;
}

bool TCPSocket::Connect(const InetAddress &address) {

  int retcode = ::connect(this->socket_,
         (const struct sockaddr *)(&address.GetPrototype()), address.GetSize());
  int error_id = (retcode == 0) ? 0 : errno;
  switch(error_id) {
    case 0:
    case EINPROGRESS:
    case EISCONN:
      this->SetAvailable();
      return true;
    default:
      this->Close();
      CoreLog(ERROR, "%s:%d (%s) Failed to connect.", __FILE__, __LINE__, __FUNCTION__);
      return false;
  }
}

bool TCPSocket::Bind(const InetAddress &address) {
  if(::bind(this->socket_, (const struct sockaddr *)(&address.GetPrototype()),
         address.GetSize()) >= 0) {
    this->SetAvailable();
    return true;
  }

  // Failed, close the socket
  this->Close();
  CoreLog(ERROR, "%s:%d (%s) Failed to Bind.", __FILE__, __LINE__, __FUNCTION__);

  return false;
}

bool TCPSocket::Listen(int max_connection) {
  if(::listen(this->socket_, max_connection) >= 0) {
    return true;
  }

  // Failed, close socket
  this->Close();
  CoreLog(ERROR, "%s:%d (%s) Failted to Listen.", __FILE__, __LINE__, __FUNCTION__);

  return false;
}

int TCPSocket::Accept(InetAddress &address) {
  socklen_t len = address.GetSize();

  int sock_client = ::accept(this->socket_,
         (struct sockaddr *)(&address.GetPrototype()), &len);
  if(sock_client < 0) {
    CoreLog(ERROR, "%s:%d (%s) Failed to accept, errno(%d)", __FILE__, __LINE__, __FUNCTION__, errno);
  } else {
    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));
    socklen_t addrlen = sizeof(peeraddr);
    if(::getpeername(sock_client, (struct sockaddr *)(&peeraddr), &addrlen) < 0) {
      CoreLog(ERROR, "%s:%d (%s) Failed to getpeername, errno(%d)", __FILE__, __LINE__, __FUNCTION__, errno);
    } else {
      address.SetPrototype(peeraddr);
    }
  }

  return sock_client;
}

bool TCPSocket::Shutdown(int shut_flag) {
  return ::shutdown(this->socket_, shut_flag) == 0;
}

bool TCPSocket::Close() {
  if(this->socket_ >= 0) {
    if(::close(this->socket_) != 0) {
      CoreLog(ERROR, "%s:%d (%s) Close error.", __FILE__, __LINE__, __FUNCTION__);
      return false;
    }
  }
  this->SetUnavailable();
  this->socket_ = -1;
  return true;
}

bool TCPSocket::SetNonblock() {
  int flags = 0;
  flags = fcntl(this->socket_, F_GETFL, 0);
  if(::fcntl(this->socket_, F_SETFL, flags | O_NONBLOCK) < 0) {
    CoreLog(ERROR, "%s:%d (%s) SetNonblock error on fcntl.", __FILE__, __LINE__, __FUNCTION__);
    return false;
  }

  this->nonblocking_ = true;

  return true;
}

}  // namespace core

