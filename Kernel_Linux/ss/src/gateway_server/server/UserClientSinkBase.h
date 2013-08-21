//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7062 $
// $Author: than $
// $Date: 2012-04-28 11:08:42 +0800 (鍛ㄥ叚, 2012-04-28) $
//
// Define class CUserClientSinkBase.
//

#ifndef _USERCLIENTSINKBASE_H__
#define _USERCLIENTSINKBASE_H__

#include "DErrorCode.h"
#include "IConnectSink.h"
#include "core/connection_task.h"

using namespace core;

class CUserClientSinkBase
       : public IConnectSink,
         public ConnectionTask {

 public:
  CUserClientSinkBase();
  virtual ~CUserClientSinkBase();

  //取得当前的连接状态
  virtual u8 GetConnectSinkState(void) = 0;

  //取得此客户端连接对应的游戏服Id
  virtual u32 GetGameID(void) { return 0; }

  // 启用本对象实例
  virtual BOOL StartConnectSink(u32 dwConnectIndex) = 0;

  //对象实例回收时，清除现有的数据
  virtual BOOL Clean(BOOL bSink) = 0;

  //返回TRUE表示此对象实例已被使用
  virtual BOOL IsHaveUsed(void) { return this->m_bIsHaveUsed; }

  //通知玩家出错（ErrorMsg为错误消息），并断开与玩家的连接（dwSocketID为玩家连接的SocketID）
  virtual BOOL KickUser(SC_ERRORCODE_MSGFORMAT &ErrorMsg);

  //给玩家客户端发送数据
  virtual void SendData(LPCSTR pData, s32 nDataLen) = 0;

  //消息
  virtual void OnMessage(u32 dwMessage, LPCSTR pData, s32 nDataLen) = 0;	

  //关闭与玩家客户端的连接
  virtual BOOL CloseConnects(CLOSE_CONN enReason) = 0;

  //获取客户端的IP和端口信息
  virtual BOOL GetClientInfo(LPSTR szIP, u16 &wPort);

  //nIndex: 请求流水号
  //nRetCode 取值于 EN_VESTIBULE_RET
  virtual void OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID, LPSTR pOutData,
         s32 nOutDataLen, LPSTR pInData = NULL, s32 nInDataLen = 0) = 0;

  // 定时器
  virtual void OnTimer(u32 id) {}

  // 出错消息
  virtual void GetErrorDesc(SC_ERRORCODE_MSGFORMAT &ErrMsg, s32 nRetCode);

  // Invoke by LogicLoop.
  // OnRecieve is a interface, implement by inheritance class.
  virtual void OnRecieve(const char *message, int size) {}

  // On connection ok callback.
  virtual void OnConnectionOK() = 0;

  // Invoke by logic loop when closing connection.
  virtual void OnCloseConnection(bool force) = 0;

 protected:
  // 为TRUE表示此对象实例已被使用
  BOOL m_bIsHaveUsed;
  // 客户端的IP
  char m_szClientIP[32];
  // 客户端的端口号
  u16 m_wClientPort;
};

#endif //_USERCLIENTSINKBASE_H__

