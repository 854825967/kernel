//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 9911 $
// $Author: xfzhuang $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Define class DBClient - CVestibule.
//

#ifndef __DB__CLIENT__H
#define __DB__CLIENT__H

#include <map>
#include <vector>

#include "IDBClient.h"
#include "IServerKernel.h"
#include "ITimeAxis.h"
#include "core/connection_task.h"
#include "core/tcp_client.h"
#include "db_server/client/Sorter.h"

// 请求的归属信息
struct SReqInfo {
  s32 lSrcIndex;                        // 请求流水号
  IDBClientSink* pSrcVestibuleSink;     // 对应返回
  s32 nRequestID;                       // 请求ID
  s64 qwUserID;                          // 用户ID

  SReqInfo() {
    memset(this, 0, sizeof(*this));
  }
};

using namespace core;

class CVestibule : public IVestibule,
       public core::TCPClient,
       public core::ConnectionTask,
       public ITimerHandler {
 public:
  CVestibule(const InetAddress &server_address, const std::string &name);
  virtual ~CVestibule();

  // 创建服务
  BOOL Create(IDBClientWarningSink *pWarningSink, u8 lType, u32 dwAppID, BOOL bReConnect);

  // 停止服务
  void Stop();

  // 释放前置机
  virtual void Release();

  // 发送DB请求包
  virtual BOOL Request(s32 nIndex, s32 nRequestID, s64 qwUserID, LPSTR pData,
         s32 nDataLen, IDBClientSink *pVestibuleSink);

  // 是否出于连接状态
  BOOL IsConnected();

  // 消息回调
  virtual void OnRecieve(const char *Buf, int nLen);

  // 连接建立完成时
  virtual ConnectionTask *OnConnectionEstablished();

  // 连接成功时
  virtual void OnConnectionOK();

  // 连接关闭时
  virtual void OnCloseConnection(bool force);

  // Timer
  virtual void OnTimer(DWORD dwEventID);

  // 得到排序接口
	virtual IDatabaseSorter *GetSorter() { return &this->m_sorter; }

 private:
  enum {
    STATE_NULL = 0,     // 初始状态
    STATE_CONNECTOK,    // 连接OK
    STATE_CONNECTERR,   // 连接错误
    STATE_DISCONNECT,   // 连接断开
  };

  // 返回处理
  void RecvResult(LPCSTR pResultBuf, s32 nResultLen);

  // 获取请求回调指针
  IDBClientSink* GetSinkByReqIndex(s32 iReqIndex, s32 &nIndex);

  // 发送DB请求包
  BOOL RequestEx(u32 dwCmdTemp, s32 nIndex, s32 nRequestID, s64 qwUserID,
         LPSTR pData, s32 nDataLen, IDBClientSink *pVestibuleSink);

  // 报警回调指针
  IDBClientWarningSink* m_pVestibuleWarningSink;
  // 是否运行中
  BOOL m_bRunning;
  // 连接状态
  s32 m_lState;
  // 应用服类型
  u8 m_lType;
  // 应用服ID(房间服ID需大于0, 登录服为0)
  u32 m_dwAppID;
  // 请求流水号
  s32 m_nReqID;
  // 等待返回的请求(请求流水号, 对应会话对象)
  std::map<s32, SReqInfo*> m_mapWaitingRetList;
  // 请求时数据缓存
  char m_pReqBuffer[MAX_BUFFER_SIZE];
  // 输出数据
  std::vector<s8> m_vOutBuffer;
  // 输出数据长度
  s32 m_lOutLen;
  // 为TRUE表示需要自动重连
  BOOL m_bReConnect;

  // 排序器
  Sorter m_sorter;
};

#endif  // __DB__CLIENT__H

