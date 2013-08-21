//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Define network message of cache.
//

#ifndef __CACHE__MESSAGE__H
#define __CACHE__MESSAGE__H

#include "include/GameType.h"

namespace cache {

enum CacheMessage {
  CACHE_CSMSG_SERVER_LOGIN_CMD = 0,
  CACHE_CSMSG_REQUEST_CMD = 1,
  CACHE_SCMSG_RESPONSE_CMD = 2,
  CACHE_CSMSG_MAX,
};

#pragma pack(push, 1)

struct CacheMsgHead {
  CacheMsgHead() { key_ = 0; }
  u8 key_;
};

// CACHE_CSMSG_SERVER_LOGIN_CMD
struct CacheMsgServerLoginCmd : public CacheMsgHead {
  CacheMsgServerLoginCmd() {
    key_ = CACHE_CSMSG_SERVER_LOGIN_CMD;
  }
};

// CACHE_CSMSG_REQUEST_CMD
struct CacheMsgRequestCmd : public CacheMsgHead {
  CacheMsgRequestCmd() {
    key_ = CACHE_CSMSG_REQUEST_CMD;
    sequence_ = 0;
    request_ = 0;
    user_id_ = 0;
    size_ = 0;
  }

  u64 sequence_;
  s32 request_;
  s64 user_id_;
  s32 size_;
  char data_[0];
};


// Requet data and response data.
struct RequestData {
  s32 size_;
  char data_[0];
};
struct ResponseData {
  s32 size_;
  char data_[0];
};

// CACHE_SCMSG_RESPONSE_CMD
struct CacheMsgResponseCmd : public CacheMsgHead {
  CacheMsgResponseCmd() {
    key_ = CACHE_SCMSG_RESPONSE_CMD;
    sequence_ = 0;
    request_ = 0;
    user_id_ = 0;
    result_ = 0;
    size_ = 0;
  }

  u64 sequence_;
  s32 request_;
  s64 user_id_;
  s16 result_;
  s32 size_;
  char data_[0];     // RequestData + ResponseData
};

#pragma pack(pop)

}  // namespace cache

#endif  // __CACHE__MESSAGE__H

