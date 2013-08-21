//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 10403 $
// $Author: xfzhuang $
// $Date: 2012-09-24 15:01:12 +0800 (鍛ㄤ竴, 2012-09-24) $
//
// library define.
//

#ifndef __LIBRARY__DEFINE__H
#define __LIBRARY__DEFINE__H

enum DBLibraryType {
  DB_LIBRARY_PROXY = 1,
  DB_LIBRARY_ENGINE,

  DB_LIBRARY_MAX,
};

enum LobbyLibraryType {
  LOBBY_LIBRARY_AI = 1,                         // AI.
  LOBBY_LIBRARY_ATTACK,                         // attack.
  LOBBY_LIBRARY_BUFF,                           // buff.
  LOBBY_LIBRARY_COLD,                           // cold.
  LOBBY_LIBRARY_CONTAINER_MGR,                  // container.
  LOBBY_LIBRARY_DROP,                           // drop.
  LOBBY_LIBRARY_DRUGGIST,                       // druggist.
  LOBBY_LIBRARY_EFFECT,                         // effect.
  LOBBY_LIBRARY_ENTITY,                         // entity.
  LOBBY_LIBRARY_GAME_DATA_CENTER,               // game data center.
  LOBBY_LIBRARY_GAME_RES_BUILDER,               // game resource builder.
  LOBBY_LIBRARY_LUA_ENGINE,                     // lua engine.
  LOBBY_LIBRARY_MATCH_SERVER,                   // match.
  LOBBY_LIBRARY_OSS,                            // oss.
  LOBBY_LIBRARY_ROOM_MANAGE,                    // room manage.
  LOBBY_LIBRARY_SKILL,                          // skill.
  LOBBY_LIBRARY_TASK,                           // task.
  LOBBY_LIBRARY_RANK_MANAGE,                    // rank manage.

  LOBBY_LIBRARY_MAX,
};

#endif // __LIBRARY__DEFINE__H

