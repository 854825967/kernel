//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: xfzhuang $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Abstract interface for ServerKernel.
//

#ifndef __ISERVER__KERNEL__H
#define __ISERVER__KERNEL__H

#include <string>

#include "include/IOsApi.h"

namespace core {

class EventLoop;
class TCPServer;
class TCPClient;

}  // namespace core

class ITimerAxis;
class IEventEngine;
class IScriptLoader;
class ILog;

struct IServerKernel
{
  virtual ~IServerKernel() {}

  virtual void Release() = 0;

  // Only use main thread.
  // Initialize server kernel, will establish main loop.
  virtual bool Initialize(const std::string &core_config_file, const std::string &core_log_file, bool daemon_flag = true) = 0;
  // Start a server.
  virtual bool StartServer(core::TCPServer *server, bool daemon = false) = 0;
  // Start a client.
  virtual bool StartClient(core::TCPClient *client) = 0;
  // Start main loop.
  virtual void StartLoop() = 0;
  // Get main loop.
  virtual core::EventLoop *GetServerEventLoop() = 0;
  // Stop core after stopping logic model.
  virtual void StopCore() = 0;
  // Close log thread.
  virtual void StopLogLoop() = 0;
  // Stop client
  virtual void StopClient(core::TCPClient *client) = 0;

  // Only use by logic.
  virtual bool CreateTimerAxis(ITimerAxis **ppTimerAxis) = 0;
  virtual bool CreateEventEngine(IEventEngine **ppEventEngine) = 0;
  virtual bool CreateScriptLoader(IScriptLoader** ppScriptLoader) = 0;
  virtual bool CreateLog(ILog** ppLog, const std::string &log_file) = 0;
  virtual bool CreateDetailLog(const std::string &instance, const std::string &train,
      const std::string &battle, const std::string &item) = 0;

  // Transplant from win32, but it's not very exact, every thread circle will update once.
  virtual u32 GetTickCount() const = 0;
};

extern "C" bool CreateServerKernel(IServerKernel **server_kernel);

class CServerKernelCreateHelper {
  typedef bool (*ProcCreateServerKernal)(IServerKernel **server_kernel);

 public:
  CServerKernelCreateHelper() : server_kernel_(NULL) {}
  ~CServerKernelCreateHelper() {}

  BOOL Create() {
    this->server_kernel_ = NULL;
    return CreateServerKernel(&this->server_kernel_);
  }

  void Close() {
    if(this->server_kernel_) {
      this->server_kernel_->Release();
      this->server_kernel_ = NULL;
    }
  }

  IServerKernel *server_kernel_;
};

#endif  // __ISERVER__KERNEL__H

