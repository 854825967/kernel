//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7062 $
// $Author: than $
// $Date: 2012-04-28 11:08:42 +0800 (鍛ㄥ叚, 2012-04-28) $
//
// Define class CRunStateSink.
//

#ifndef __RUN__STATE__SINK__H
#define __RUN__STATE__SINK__H

#include "DServerDef.h"
#include "UserClientSinkBase.h"

class CGameClientConn;

class CRunStateSink : public CUserClientSinkBase {
 public:
  CRunStateSink();
  virtual ~CRunStateSink();

  // Invoke by LogicLoop.
  // OnRecieve is a interface, implement by inheritance class.
  virtual void OnRecieve(const char *message, int size);

  // Invoke by logic loop when closing connection.
  virtual void OnCloseConnection(bool force);

  virtual void OnConnectionOK();

  //给玩家客户端发送数据
  virtual void SendData(LPCSTR pData, s32 nDataLen);

  // 取得当前的连接状态
  virtual u8 GetConnectSinkState(void);
  // 取得此客户端连接对应的游戏服ID
  virtual u32 GetGameID(void);

  // 启用本对象实例
  //         dwConnectIndex为连接序号（由CConnectSinkManager分配）
  // 返回值：成功返回TRUE
  virtual BOOL StartConnectSink(u32 dwConnectIndex);

  //对象实例回收时，清除现有的数据，bSink为TRUE表示要清除本连接在登陆信号槽管理器中的记录
  virtual BOOL Clean(BOOL bSink = TRUE);

  virtual void OnMessage(u32 dwMessage, LPCSTR pData, s32 nDataLen);

  // 关闭与玩家客户端的连接
  virtual BOOL CloseConnects(CLOSE_CONN enReason);

  // nIndex: 请求流水号
  // nRetCode 取值于 EN_VESTIBULE_RET
  virtual void OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID,
         LPSTR pOutData, s32 nOutDataLen, LPSTR pInData = NULL, s32 nInDataLen = 0);

  // 定时器回调
  virtual void OnTimer(u32 dwTimerID);

 private:
  // ------------------------------------
  // CLoginStateSink
  //
  // 解释MAC
  void InterpretMac(LPCSTR pBuf, s32 nLen);

  // nTurnSType为跳转类型，取值见IVestibule.h的 EN_LOGIN_USER_JUMP_TYPE
  void TurnToRunState(s32 nTurnSType);
  // ------------------------------------
  
  u32 m_dwEnterCode;                      // 随机进入码，用于加密MAC

  u32 m_dwConnectIndex;                   // 连接序号（由CConnectSinkManager分配）
  ClientID m_ClientID;
  s64 m_qwUserDBID;                        // 帐号DB ID
  s32 m_nActorDBID;                       // 角色DB ID
  s32 m_nTurnSType;                       // 跳转类型，取值见IVestibule.h的 EN_LOGIN_USER_JUMP_TYPE
  s32 m_nLogoutType;                      // 跳转类型，取值见IVestibule.h的 EN_LOGIN_USER_JUMP_TYPE
  s32 m_nState;                           // 1：请求登陆OK，2：获得角色基本数据OK，3：收到物品数据OK
  BOOL m_bIsNextMap;                      // 为TRUE表示玩家正在切换地图
  char m_bRandC16[16];                    // 客户端发送上来的随机串
  char m_szIP[16];                        // 服务器IP
  u16 m_wPort;                            // 服务器开放的端口
  u32 m_ValidationCode[4];                // 验证码
  s8 m_bJumpFlag;                         // 1：切换场景服，2：小退
  CGameClientConn *m_pSceneClientConn;
  char m_BuffData[4096];
  char m_szUserIpAddress[16];               // 登录Ip地址
  char m_szUserSerialNO[20];                // 网卡MAC

  u8 m_byConnectState;                    // 连接状态(CONN_STATE)
};

#endif  // __RUN__STATE__SINK__H

