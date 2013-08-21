//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Define interface of cache.
//

#ifndef __CACHE__INTERFACE__H
#define __CACHE__INTERFACE__H

#include <vector>

#include "include/GameSys.h"
#include "include/IOsApi.h"

class ILog;
class IServerKernel;
class ITimerAxis;

namespace cache {

enum CacheResponseDefine {
  CACHE_RESPONSE_SUCCESS = 0,
  CACHE_RESPONSE_ERROR_UNKNOWN = 128,
  CACHE_RESPONSE_ERROR_CACHE_HANDLE,
  CACHE_RESPONSE_ERROR_KEY_SIZE,
  CACHE_RESPONSE_ERROR_VALUE_SIZE,
  CACHE_RESPONSE_ERROR_VALUE_NUMBER,
  CACHE_RESPONSE_ERROR_FINISH_FETCH_VALUE,
  CACHE_RESPONSE_ERROR_PARAMETER,
  CACHE_RESPONSE_ERROR_KEY,
};

class CacheInterface {
 public:
  virtual ~CacheInterface() {}

  // Initialize, configure is the absolute directory of configure file.
  virtual bool Initialize(const char *configure) = 0;

  // Get and set.
  virtual u16 Set(const char *key,
      size_t key_size, const char *value, size_t value_size) = 0;
  virtual u16 Get(const char *key,
      size_t key_size, char *value, size_t &value_size) = 0;

  // Batch get.
  virtual u16 BatchGet(const char *const *keys,
      const size_t *key_length, const size_t number_of_keys) = 0;
  // Fetch result value.
  virtual u16 FetchValue(char *key,
      size_t &key_size, char *value, size_t &value_size) = 0;
  // Quit fetch, after fetch you should invoke this function.
  virtual void QuitFetchValue() = 0;

  // Increase and decrease offset. 
  virtual u16 Increase(const char *key, size_t key_size, 
      u32 offset, u64 &value) = 0;
  virtual u16 Decrease(const char *key, size_t key_size, 
      u32 offset, u64 &value) = 0;

  // Check error type:
  //
  // Not found key.
  virtual bool CheckErrorKeyNotFound(u16 error_code) = 0;
};

class CacheResponse {
 public:
  virtual ~CacheResponse() {}

  virtual void OnResponse(s32 request, s64 user_id, u16 result,
      const char *request_data, size_t request_size,
      const char *response_data, size_t response_size, u64 sequence) = 0;
};

class CacheRequest {
 public:
  virtual ~CacheRequest() {}

  virtual void Request(s32 request, s64 user_id, const char *data,
      size_t size, CacheResponse *response) = 0;
};

namespace cache_proxy {

class CacheClientInterface {
 public:
  virtual ~CacheClientInterface() {}

  virtual bool Request(s32 request, s64 user_id, const char *data,
      size_t size, CacheResponse *response, u64 &sequence) = 0;
  virtual bool CancelRequest(u64 sequence) = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual void Disconnect() = 0;
};

class CacheClientSetInterface {
 public:
  virtual ~CacheClientSetInterface() {}

  virtual CacheClientInterface *Connect(u32 server_id,
      const char *host, u16 port, const string &name) = 0;
  virtual void Disconnect(u32 server_id) = 0;
  virtual const std::vector<CacheClientInterface *> &GetAllClient() const = 0;
};

extern "C" bool CreateCacheClientSet(ILog *log, IServerKernel *server_kernel,
ITimerAxis *timer_axis, CacheClientSetInterface **client_set);

typedef bool (*ProcCreateCacheClientSet)(ILog *log, IServerKernel *server_kernel,
ITimerAxis *timer_axis, CacheClientSetInterface **client_set);

class CacheClientSetHelper {
 public:
  CacheClientSetHelper() : client_set_(NULL) {}
  virtual ~CacheClientSetHelper() {}

  bool Create(ILog *log, IServerKernel *server_kernel, ITimerAxis *timer_axis,
      const char *so) {
    if(this->loader_.LoadLibrary(so) == FALSE) {
      printf("CacheClientSetHelper LoadLibrary error\n");
      return false;
    }

    ProcCreateCacheClientSet proc = NULL;
    proc = (ProcCreateCacheClientSet)this->loader_.GetProcAddress("CreateCacheClientSet");

    if(proc == NULL) {
      printf("CacheClientSetHelper CreateCacheClientSet error\n");
      return false;
    }

    return proc(log, server_kernel, timer_axis, &this->client_set_);
  }

  void Close() {
    if(this->client_set_) {
      delete this->client_set_;
      this->client_set_ = NULL;
    }
    this->loader_.FreeLibrary();
  }

  CacheClientSetInterface *client_set_;

 private:
  CDynamicLoader loader_;
};

}  // namespace cache_proxy

}  // namespace cache

#endif  // __CACHE__INTERFACE__H

