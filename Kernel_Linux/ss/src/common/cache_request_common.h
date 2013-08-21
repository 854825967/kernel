//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Cache request common define.
//

#ifndef __CACHE__REQUEST__COMMON__H
#define __CACHE__REQUEST__COMMON__H

#include <include/GameSys.h>

namespace cache {

const size_t static kMaxCacheRequestSize = 4096;
const size_t static kMaxCacheResponseSize = 4096;

enum CacheRequestID {
  CACHE_REQUEST_MIN = 0,
  CACHE_REQUEST_SET_CREATE_ACTOR_TIME = 1,
  CACHE_REQUEST_GET_CREATE_ACTOR_TIME = 2,
  CACHE_REQUEST_SET_FRIEND_COLLECT_TIME = 3,
  CACHE_REQUEST_GET_FRIEND_COLLECT_TIME = 4,
  CACHE_REQUEST_GET_WHEELING_DRAW_RANK = 5,
  CACHE_REQUEST_GET_CARD_ROLL_LIST = 6,
  CACHE_REQUEST_SET_CARD_ROLL_LIST = 7,
 
  CACHE_REQUEST_MAX,
};

#pragma pack(push,1)

/////////////////////////////////////
// CACHE_REQUEST_SET_CREATE_ACTOR_TIME
//
// Request:
struct SetCreateActorTimeRequest {
  SetCreateActorTimeRequest()
    : actor_id(0), create_time(0) {}

  u32 actor_id;
  u64 create_time;
};

/////////////////////////////////////
// CACHE_REQUEST_GET_CREATE_ACTOR_TIME
//
// Request:
struct GetCreateActorTimeRequest {
  GetCreateActorTimeRequest()
    : actor_id(0) {}

  u32 actor_id;
};
//
// Response:
struct GetCreateActorTimeResponse {
  GetCreateActorTimeResponse()
    : create_time(0) {}

  u64 create_time;
};

/////////////////////////////////////
// CACHE_REQUEST_SET_FRIEND_COLLECT_TIME
//
// Request:
struct SetFriendCollectTimeRequest {
  SetFriendCollectTimeRequest() 
    : user_id(0), friend_user_id(0),
    last_collect_time(0) {}

  u64 user_id;
  u64 friend_user_id;
  s64 last_collect_time;
};

/////////////////////////////////////
// CACHE_REQUEST_GET_FRIEND_COLLECT_TIME
//
// Request:
struct GetFriendCollectTimeRequest {
  GetFriendCollectTimeRequest()
    : actor_id(0), user_id(0), size(0) {}

  u32 actor_id;
  u64 user_id;
  u16 size;
  u64 friend_user_ids[0];
};
//
// Data:
struct FriendLastCollectTime {
  u64 friend_user_id;
  s64 last_collect_time;
};
// Response:
struct GetFriendCollectTimeResponse {
  GetFriendCollectTimeResponse()
    : size(0) {}

  u64 user_id;
  u16 size;
  FriendLastCollectTime data[0];
};

/////////////////////////////////////
// CACHE_REQUEST_GET_WHEELING_DRAW_RANK
// Request:
struct GetWheelingDrawRankRequest {
  GetWheelingDrawRankRequest() : actor_id(0) {}

  u32 actor_id;
};
// 
// Response:
struct GetWheelingDrawRankResponse {
  GetWheelingDrawRankResponse() : rank(0) {}

  u64 rank;     // 名次
};

/////////////////////////////////////
// CACHE_REQUEST_GET_CARD_ROLL_LIST
//
// Request:
struct GetCardRollListRequest
{
	GetCardRollListRequest()
	{
	
	}
};
//
// Data:
struct CardRollResult
{
	u64 user_id;
	char szActorName[32];
	s32 goods_id;
};
// Response:
struct GetCardRollListResponse
{
	GetCardRollListResponse()
	  : size(0) {}
	u16 size;
	CardRollResult data[0];
};


/////////////////////////////////////
// CACHE_REQUEST_SET_CARD_ROLL_LIST
//
// Request:
struct SetCardRollListRequest {
	SetCardRollListRequest()
		: size(0) {}
	u16	size;
	CardRollResult data[0];
};

#pragma pack(pop)

}  // namespace cache

#endif  // __CACHE__REQUEST__COMMON__H

