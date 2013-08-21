//
// core - server core source code.
//
// $Rev: 5305 $
// $Author: $
// $Date: 2012-03-05 17:00:56 +0800 (周一, 2012-03-05) $
//
// Define class InetAddress.
// Simple wrapper of ipv4.
//

#include "core/inet_address.h"

#include <arpa/inet.h>

#include <sstream>

#include "core/base/logging.h"

namespace core {

InetAddress::InetAddress() {
  memset(&this->address_, 0, sizeof(this->address_));
}

InetAddress::InetAddress(uint16 port) {
  memset(&this->address_, 0, sizeof(this->address_));
  this->address_.sin_family = AF_INET;
  this->address_.sin_addr.s_addr = htonl(INADDR_ANY);
  this->address_.sin_port = htons(port); 
}

InetAddress::InetAddress(const std::string &ip, uint16 port) {
  memset(&this->address_, 0, sizeof(this->address_));
  this->address_.sin_family = AF_INET;
  // this->address_.sin_addr.s_addr = ::htonl(INADDR_ANY);
  if(::inet_pton(AF_INET, ip.c_str(), &(address_.sin_addr)) <= 0) {
    CoreLog(ERROR, "%s:%d (%s) Failed in inet_pton.", __FILE__, __LINE__, __FUNCTION__);
  }
  address_.sin_port = htons(port);
}

InetAddress::InetAddress(const struct sockaddr_in &address)
       : address_(address_) {}

const InetAddress &InetAddress::operator = (const InetAddress &address) {
  this->SetPrototype(address.GetPrototype());
  return *this;
}

std::string InetAddress::GetString() const {
  std::ostringstream oss;
  oss << inet_ntoa(this->address_.sin_addr) << ":" << ntohs(this->address_.sin_port);
  return oss.str();
}

void InetAddress::GetAddressInfo(std::string &ip, uint16 &port) const {
  ip = inet_ntoa(this->address_.sin_addr);
  port = ntohs(this->address_.sin_port);
}

void InetAddress::GetAddressInfo(char *ip, size_t size, uint16 &port) const {
  strncpy(ip, inet_ntoa(this->address_.sin_addr), size);
  port = ntohs(this->address_.sin_port);
}

}  // namespace core

