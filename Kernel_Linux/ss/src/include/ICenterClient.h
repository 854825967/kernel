//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7062 $
// $Author: than $
// $Date: 2012-04-28 11:08:42 +0800 (鍛ㄥ叚, 2012-04-28) $
//
// Define interface ICenterClient.
//

#ifndef __ICENTER__CLIENT__H
#define __ICENTER__CLIENT__H

#include "include/GameSys.h"
#include "include/IOsApi.h"
#include "common/DServerDef.h"

struct ITimerAxis;
struct SServerKey;
struct SCenterActorLoginContext;
struct ILog;
struct IServerKernel;

// 应用服务器接口（需要每台非中心服的服务器继承这些接口）
// 主要用于：中心服客户端在其他服务器使用中可能需要用到服务器的一些接口
//           因为这里抽象了所有其他服务器使用的中心服客户端，所以接口被
//           揉到了一起...
//           这些接口基本上是各服务器的中心服客户端接到中心服的一些消息
//           后，进行的一些回调，因为不同的服务器有不同的响应，或不同的
//           服务器只需要使用其中一部分接口，所以这些接口都是非主动调用
//           的。
struct IAppServer {
  virtual ~IAppServer() {}

  // 获取应用服务器信息
  // len为name的大小
  // type 值参考 DCenterServerMsg.h 的定义
  virtual BOOL GetInfo(LPSTR name, s32 len, u32 &id, u8 &type, u16 &port) = 0;

  // 应用服务器登录后回调
  // result：TRUE表示登录成功，FALSE表示登录失败
  virtual void OnServerLogin(BOOL result, LPCSTR desc) = 0;

  // 应用服务器退出时回调
  virtual void OnServerLogout() = 0;

  // 发给某个角色数据的回调
  virtual void OnSendDataToActor(s32 actor_id, LPSTR buff, s32 len) = 0;

  // 发给某个房间数据的回调
  virtual void OnSendDataToRoom(s32 map_id, LPSTR buff, s32 len) = 0;

  // 全服务器广播数据的回调
  virtual void OnBroadcastData(LPSTR buff, s32 len) = 0;

  // 服务器登录和登出时回调
  virtual void OnAppInfo(LPSTR buff, s32 len) = 0;
};

// 社会服务器接口
struct ISocietyAppServer : public IAppServer {
  virtual ~ISocietyAppServer() {}

  // 社会服务器接收消息回调接口
  virtual void OnSendDataToSociety(LPSTR buff, s32 len) = 0;
};

// 登录服务器接口
struct ILoginServer : public IAppServer {
  virtual ~ILoginServer() {}

  // 在线人数更新通知
  virtual void OnUpdateOnlineNum(LPSTR buff, s32 len) = 0;

  // 角色登录登出后回调
  virtual void OnActorLoginLogout(LPSTR buff, s32 len) = 0;
};

// 大厅服务器接口
struct ILobbyServer : public IAppServer {
  virtual ~ILobbyServer() {}

  // 创建新房间后回调
  virtual void OnNewRoom(LPSTR buff, s32 len) = 0;

  // 房间登录后回调
  virtual void OnRoomLogin(u32 room_id, u32 map_id) = 0;
};

struct IRoomServer : public IAppServer {};

// 中心服务器客户端接口
struct ICenterClient {
  virtual ~ICenterClient() {}

  // 销毁中心服客户端
  virtual void Release() = 0;

  // 得到游戏世界名字
  virtual LPCSTR GetGameName() = 0;

  // 房间更新列表，应用服务器登录成功后，需要调用此方法进行更新
  // first 用于分批次更新时，表明是否是第一批更新
  virtual BOOL RoomUpdateList(s32 room_num, ServerRoomInfo *room_ids, BOOL first) = 0;

  // 房间创建
  virtual BOOL RoomLogin(u32 room_id, u32 map_id) = 0;

  // 房间销毁
  virtual BOOL RoomLogout(u32 room_id) = 0;

  // 角色更新列表，应用服务器登录成功后，需要调用此方法进行更新
  // first 用于分批次更新时，表明是否是第一批更新
  virtual BOOL ActorUpdateList(s32 actor_num, SCenterActorLoginContext *actor_list, BOOL first) = 0;

  // 角色登录 op_type = 0: 上线登录，op_type = 1: 跨场景服登录
  virtual BOOL ActorLogin(s64 user_id, s32 actor_id, LPCSTR actor_name, u8 op_type, s32 reserve) = 0;

  // 角色退出 op_type = 0: 下线登出，op_type = 1: 跨场景服登出
  virtual BOOL ActorLogout(s64 user_id, s32 actor_id, u8 op_type, s32 reserve) = 0;

  // 发送数据给某个角色
  virtual BOOL SendDataToActor(s32 actor_id, LPSTR buff, s32 len) = 0;

  // 发送数据给某个房间
  virtual BOOL SendDataToRoom(s32 room_id, char *buff, s32 len) = 0;

  // 向全世界广播消息
  virtual BOOL BroadcastData(LPSTR buff, s32 len) = 0;

  // 向插件模块发送消息
  virtual BOOL SendToPlugin(u16 event_id, u8 src_type_id, LPSTR buff, s32 len) = 0;

  // 发送数据到社会服务器
  virtual BOOL SendDataToSciety(LPSTR buff, s32 len) = 0;

  // 查找一个网关服务器，获取的是在线人数最低的 找到返回TRUE
  // user_id：玩家ID 用于负载均衡
  virtual BOOL FindGateWay(SServerKey &ServerKey, s64 user_id) = 0;

  // 获取所有服务器总在线人数
  virtual s32 GetTotalOnlineNum() = 0;

  // 获取服务器在线人数
  virtual s32 GetServerOnlineNum(SServerKey &key) = 0;

  // 直接发送数据中心服
  virtual BOOL SendToCenterSvr(LPSTR buff, s32 len) = 0;

  // 检查某个服务器是否存在
  virtual BOOL ExistServer(SServerKey key) = 0;

  // 根据地图ID查询服务器信息
  virtual BOOL FindServer(s32 room_id, SServerKey &key) = 0;

  // 查找最闲的房间
  virtual BOOL FindFreeRoomServer(SServerKey &key) = 0;

  // 查找大厅服务器
  virtual BOOL FindLobbyServer(s32 server_id, SServerKey &key) = 0;
};

extern "C" BOOL CreateCenterClient(ICenterClient **center_client, IAppServer *app_server, ITimerAxis *time_axis,
       ILog *log, IServerKernel *server_kernel, LPCSTR center_server_ip, u16 center_server_port);

typedef BOOL (*ProcCreateCenterClient)(ICenterClient **center_client, IAppServer *app_server, ITimerAxis *time_axis,
       ILog *log, IServerKernel *server_kernel, LPCSTR center_server_ip, u16 center_server_port);

// 中心服客户端创建辅助类
class CCenterClientHelper {
 public:
  CCenterClientHelper() : center_client_(NULL) {}
  ~CCenterClientHelper() { this->Close(); }

  BOOL Create(IAppServer *app_server, ITimerAxis *time_axis, ILog *log, IServerKernel *server_kernel,
         LPCSTR center_server_ip, u16 center_server_port, const char *center_client_so) {
    if(this->dynamic_loader_.LoadLibrary(center_client_so) == FALSE) {
      return FALSE;
    }

    ProcCreateCenterClient proc = NULL;
    proc = (ProcCreateCenterClient)(this->dynamic_loader_.GetProcAddress("CreateCenterClient"));

    if(proc == NULL)
      return FALSE;

    return proc(&(this->center_client_), app_server, time_axis, log, server_kernel,
           center_server_ip, center_server_port);
  }

  void Close() {
    if(this->center_client_) {
      this->center_client_->Release();
      this->center_client_ = NULL;
    }
    this->dynamic_loader_.FreeLibrary();
  }

  ICenterClient *center_client_;

 private:
  CDynamicLoader dynamic_loader_;
};

#endif  // __ICENTER__CLIENT__H

