//
// core - server core source code.
//
// $Rev: 6775 $
// $Author: $
// $Date: 2012-04-13 17:11:45 +0800 (鍛ㄤ簲, 2012-04-13) $
//
// Wapper of server core.
//

#ifndef __SERVER__CORE__H
#define __SERVER__CORE__H

#include <string>

#include "core/base/boundless_entity_ring_queue.h"
#include "core/base/types.h"
#include "include/IServerKernel.h"

class ITimerAxis;
class IEventEngine;
class IScriptLoader;

namespace core {

class ClientThreadPool;
class ConnectionTask;
class EventLoop;
class LogicLoop;
class NetworkThreadPool;
class TCPServer;
class TCPClient;
class TCPConnection;
class LoopThread;
class LogicLog;
class LogLoop;

class ServerCore : public IServerKernel {
  typedef BoundlessEntityRingQueue<TCPConnection> RingQueueLogic;
 public:
  ServerCore();
  virtual ~ServerCore();

  virtual void Release() { delete this; }

  // Initialize the server core.
  virtual bool Initialize(const std::string &core_config_file, const std::string &core_log_file, bool daemon_flag);

  // Start a server/client.
  virtual bool StartServer(TCPServer *server, bool daemon_flag);
  virtual bool StartClient(TCPClient *client);

  // Start server core.
  virtual void StartLoop();

  // Main thread pool.
  virtual EventLoop *GetServerEventLoop();

  // Some tools interface.
  virtual bool CreateTimerAxis(ITimerAxis **ppTimerAxis);
  virtual bool CreateEventEngine(IEventEngine **ppEventEngine);
  virtual bool CreateScriptLoader(IScriptLoader** ppScriptLoader);
  virtual bool CreateLog(ILog** ppLog, const std::string &log_file);
  virtual bool CreateDetailLog(const std::string &instance, const std::string &train,
      const std::string &battle, const std::string &item);

  // Stop core.
  virtual void StopCore();

  // Close log thread.
  virtual void StopLogLoop();

  // Stop client.
  virtual void StopClient(core::TCPClient *client);

  // GetTickCount.
  // Just like in win32, but it's not very exact, every thread circle will update once.
  virtual uint32 GetTickCount() const;

 private:
  // This stopping will set to stopping state.
  void Stopping();

  // Main thread.
  EventLoop *main_loop_;

  // Logic thread.
  LogicLoop *logic_loop_;
  LoopThread *logic_thread_;

  // LogicLog
  LogicLog *log_instance_;

  // Log thread.
  LogLoop *log_loop_;
  LoopThread *log_thread_;

  // Client thread pool and server network thread pool.
  ClientThreadPool *client_thread_pool_;
  NetworkThreadPool *network_thread_pool_;

  // Rings use for commnicating between logic and network.
  RingQueueLogic *server_ring_;
  RingQueueLogic *client_ring_;

  // Server instance.
  TCPServer *server_;
};

}  // namespace core

#endif  // __SERVER__CORE__H

