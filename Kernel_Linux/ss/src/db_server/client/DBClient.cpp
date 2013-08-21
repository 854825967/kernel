//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 7083 $
// $Author: than $
// $Date: 2012-04-28 21:53:55 +0800 (鍛ㄥ叚, 2012-04-28) $
//
// Define class DBClient - CVestibule.
//

#include "DBClient.h"

#include "DBClientTempSink.h"
#include "ILog.h"
#include "ITimeAxis.h"
#include "IServerKernel.h"
#include "Header.h"

// 心跳包的时间间隔，单位：毫秒
#define TIME_KEEPALIVE 30000

#ifdef _CORE_DEBUG
static u64 kStatisticsSendBytes = 0;
#endif

// 构造函数
CVestibule::CVestibule(const InetAddress &server_address, const std::string &name)
       : TCPClient(server_address, name) {
  m_pVestibuleWarningSink = NULL;
  m_bRunning = FALSE;
  m_lState = STATE_NULL;
  m_dwAppID = -1;
  m_nReqID = 0;

  memset(m_pReqBuffer, 0, sizeof(m_pReqBuffer));

  m_vOutBuffer.resize(4096);
  m_lOutLen = 0;

  m_bReConnect = FALSE;
}

// 析构函数
CVestibule::~CVestibule() {
  Stop();

  std::map<s32, SReqInfo*>::iterator it = m_mapWaitingRetList.begin();
  for (; it != m_mapWaitingRetList.end(); ++it) {
    SReqInfo *pSReqInfo = (*it).second;

    if (g_pTrace != NULL && 0 != pSReqInfo->nRequestID) {
      g_pTrace->Logger(Error, "%s:%d (%s) 有请求未处理完, RequestID=%d, UserID=%ld!",
             __FILE__, __LINE__, __FUNCTION__, pSReqInfo->nRequestID, pSReqInfo->qwUserID);
    }

    delete pSReqInfo;
  }

  if (g_pTrace != NULL) {
    g_pTrace->Logger(Info, "前置机最大Vector大小为%d!", m_vOutBuffer.capacity());
  }

  m_mapWaitingRetList.clear();
}

// 创建服务
BOOL CVestibule::Create(IDBClientWarningSink *pWarningSink, u8 lType,
       u32 dwAppID, BOOL bReConnect) {
  if(m_bRunning == TRUE) {
    g_pTrace->Logger(Error, "%s:%d (%s) 操作失败，无法创建 CVestibule!",
           __FILE__, __LINE__, __FUNCTION__);
    return FALSE;
  }

  m_pVestibuleWarningSink = pWarningSink;
  m_dwAppID = dwAppID;

  m_lType = lType;

  if(g_pServerKernel->StartClient(this) == false) {
    return FALSE;
  }

  m_bReConnect = bReConnect;
  m_bRunning = TRUE;

  return TRUE;
}

// 停止服务
void CVestibule::Stop(void) {
  if(NULL != g_pTimerAxis) {
    g_pTimerAxis->KillTimer(enTimer_ID_KeepAlive, this);
  }

  this->CloseConnection();
  m_bRunning = FALSE;
}

// 释放前置机
void CVestibule::Release(void) {
  this->Stop();
  g_pServerKernel->StopClient(this);

  delete this;
}

// 发送DB请求包
BOOL CVestibule::Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
       LPSTR pData, s32 nDataLen, IDBClientSink *pVestibuleSink) {
  if (FALSE == IsConnected()) {
    g_pTrace->Logger(Error, "%s:%d (%s) 操作失败, 不处于连接状态%d!",
           __FILE__, __LINE__, __FUNCTION__, m_lState);
    return FALSE;
  }

  if (NULL == pData || nDataLen <= 0 || NULL == pVestibuleSink) {
    g_pTrace->Logger(Error, "%s:%d (%s) 操作失败, 参数非法!",
           __FILE__, __LINE__, __FUNCTION__);
    return FALSE;
  }

  if (nDataLen >= MAX_BUFFER_SIZE - 20) {
    g_pTrace->Logger(Error, "%s:%d (%s) 操作失败, 数据超长, RequestID=%d, DataLen=%d!",
           __FILE__, __LINE__, __FUNCTION__, nRequestID, nDataLen);
    return FALSE;
  }

  SReqInfo *pstReqInfo = new SReqInfo;
  if (NULL == pstReqInfo) {
    g_pTrace->Logger(Error, "%s:%d (%s) 操作失败, New失败!",
           __FILE__, __LINE__, __FUNCTION__);
    return FALSE;
  }

  pstReqInfo->lSrcIndex = nIndex;
  pstReqInfo->pSrcVestibuleSink = pVestibuleSink;
  pstReqInfo->nRequestID = nRequestID;
  pstReqInfo->qwUserID = qwUserID;

  int iReqIndex = m_nReqID++;
  m_mapWaitingRetList[iReqIndex] = pstReqInfo;

  // 按格式封包
  // 格式: VESTIB_COMMAND_REQUEST + iReqIndex + nRequestID + qwUserID + nDataLen + pData
  char *buf_ptr = m_pReqBuffer;
  int buf_size = 0;

  // 命令
  DWORD dwCmd = VESTIB_COMMAND_REQUEST;
  memcpy(buf_ptr, &dwCmd, sizeof(DWORD));
  buf_ptr  += sizeof(DWORD);
  buf_size += sizeof(DWORD);

  // iReqIndex
  memcpy(buf_ptr, &iReqIndex, sizeof(int));
  buf_ptr  += sizeof(int);
  buf_size += sizeof(int);

  // nRequestID
  memcpy(buf_ptr, &nRequestID, sizeof(int));
  buf_ptr  += sizeof(int);
  buf_size += sizeof(int);

  // qwUserID
  memcpy(buf_ptr, &qwUserID, sizeof(s64));
  buf_ptr  += sizeof(s64);
  buf_size += sizeof(s64);

  // nDataLen
  memcpy(buf_ptr, &nDataLen, sizeof(int));
  buf_ptr  += sizeof(int);
  buf_size += sizeof(int);

  // pData
  memcpy(buf_ptr, pData, nDataLen);
  buf_ptr  += nDataLen;
  buf_size += nDataLen;

  this->Send(m_pReqBuffer, buf_size);
#ifdef _CORE_DEBUG
  kStatisticsSendBytes += buf_size;
  // g_pTrace->Logger(Info, "kStatisticsSendBytes = [%lu]", kStatisticsSendBytes);
#endif

  return TRUE;
}

// 是否正常连接服务器
BOOL CVestibule::IsConnected(void) {
  return (STATE_CONNECTOK == m_lState);
}

void CVestibule::OnRecieve(const char *Buf, int nLen) {
  if (NULL == Buf || nLen < 0 || (size_t)nLen < sizeof(DWORD)) {
    g_pTrace->Logger(Error, "%s:%d (%s) 操作失败, 数据非法!",
           __FILE__, __LINE__, __FUNCTION__);
    m_lState = STATE_CONNECTERR;
    return;
  }

  DWORD dwCmd = *((DWORD*)Buf);

  // 连接数据前置机成功
  if (dwCmd == VESTIBULE_WARN_CONNECTED) {
    if (NULL != g_pTimerAxis) {
      // 开启心跳控制
      g_pTimerAxis->SetTimer(enTimer_ID_KeepAlive, TIME_KEEPALIVE, this,
             INFINITY_CALL,  "CVestibule::OnRecv");
    }

    m_lState = STATE_CONNECTOK;
    m_pVestibuleWarningSink->OnVestibuleWarning(VESTIBULE_WARN_CONNECTED, "已连接上了数据前置机");
  }
  else {
    LPCSTR pResultBuf = Buf + sizeof(DWORD);
    int nResultLen = nLen - sizeof(DWORD);
    RecvResult(pResultBuf, nResultLen);
  }
}

ConnectionTask *CVestibule::OnConnectionEstablished() {
  return this;
}

void CVestibule::OnConnectionOK() {
  m_lState = STATE_CONNECTOK;
  g_pTrace->TraceLn("连接数据前置机 IP[%s] 成功!", this->GetPeerString().c_str());
}

void CVestibule::OnCloseConnection(bool force) {
  g_pTrace->TraceErrorLn("%s:%d (%s) 数据前置机关闭了连接!",
         __FILE__, __LINE__, __FUNCTION__);
  m_lState = STATE_DISCONNECT;

  if(NULL != m_pVestibuleWarningSink) {
    m_pVestibuleWarningSink->OnVestibuleWarning(VESTIBULE_WARN_DISCONNECTED,
           "数据前置机关闭了连接!");
  }

  this->Stop();
  TCPClient::Stop();
  TCPClient::Start();
}

void CVestibule::OnTimer(DWORD dwEventID) {
  if(enTimer_ID_KeepAlive == dwEventID) {
    if(FALSE == IsConnected()) {
      return ;
    }

    char Buff[32] = {0};
    RequestEx(VESTIB_COMMAND_KeepAlive, 0, 0, 0, Buff, sizeof(Buff), &g_DBClientTempSink);
  }
}

// 返回处理
void CVestibule::RecvResult(LPCSTR pResultBuf, int nResultLen) {
  if(NULL == pResultBuf || nResultLen <= 0) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, 数据非法!",
           __FILE__, __LINE__, __FUNCTION__);
    return;
  }

  // 按格式解包
  // 格式: bEnd + iReqIndex + qwUserID + nRequestID + nReturn
  //			+ nInLen + pInData + nOutLen + pOutData
  BOOL bEnd = FALSE;
  s32 iReqIndex = 0;
  s64 qwUserID = 0;
  s32 nRequestID = 0;
  s32 nReturn = 0;
  s32 nInLen = 0;
  char pInData[MAX_BUFFER_SIZE] = {0};
  s32 nOutLen = 0;

  memcpy(&bEnd, pResultBuf, sizeof(BOOL));
  pResultBuf += sizeof(BOOL);
  nResultLen -= sizeof(BOOL);

  int nLen = m_lOutLen + nResultLen;
  if(nLen > (s32)m_vOutBuffer.capacity()) {
    std::vector<s8> tempVector;
    tempVector.resize(m_lOutLen);
    memcpy(&tempVector[0], &m_vOutBuffer[0], m_lOutLen);
    m_vOutBuffer.resize(nLen);
    memcpy(&m_vOutBuffer[0], &tempVector[0], m_lOutLen);
  }

  memcpy(&m_vOutBuffer[0] + m_lOutLen, pResultBuf, nResultLen);
  m_lOutLen += nResultLen;

  // 如果不是结束包标志, 则不处理
  if (FALSE == bEnd) {
    return;
  }

  pResultBuf = (char *)&m_vOutBuffer[0];
  nResultLen = m_lOutLen;
  m_lOutLen = 0;

  memcpy(&iReqIndex, pResultBuf, sizeof(s32));
  pResultBuf += sizeof(s32);
  nResultLen -= sizeof(s32);

  s32 nIndex = 0;
  IDBClientSink *pVestibuleSink = GetSinkByReqIndex(iReqIndex, nIndex);
  if(NULL == pVestibuleSink) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, 获取回调指针为NULL!",
           __FILE__, __LINE__, __FUNCTION__);
    return;
  }

  memcpy(&qwUserID, pResultBuf, sizeof(s64));
  pResultBuf += sizeof(s64);
  nResultLen -= sizeof(s64);

  memcpy(&nRequestID, pResultBuf, sizeof(s32));
  pResultBuf += sizeof(s32);
  nResultLen -= sizeof(s32);

  memcpy(&nReturn, pResultBuf, sizeof(s32));
  pResultBuf += sizeof(s32);
  nResultLen -= sizeof(s32);

  memcpy(&nInLen, pResultBuf, sizeof(s32));
  pResultBuf += sizeof(s32);
  nResultLen -= sizeof(s32);

  memcpy(pInData, pResultBuf, nInLen);
  pResultBuf += nInLen;
  nResultLen -= nInLen;

  memcpy(&nOutLen, pResultBuf, sizeof(s32));
  pResultBuf += sizeof(s32);
  nResultLen -= sizeof(s32);

  nResultLen -= nOutLen;

  if (nResultLen != 0) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, ResultLen=%d!",
           __FILE__, __LINE__, __FUNCTION__, nResultLen);
    return;
  }

  pVestibuleSink->OnRet(nIndex, nReturn, qwUserID, nRequestID, (char *)pResultBuf,
         nOutLen, pInData, nInLen);
}

// 获取请求回调指针
IDBClientSink* CVestibule::GetSinkByReqIndex(s32 iReqIndex, s32 &nIndex) {
  std::map<s32, SReqInfo*>::iterator it = m_mapWaitingRetList.find(iReqIndex);
  if (it == m_mapWaitingRetList.end()) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, 找不到请求信息!",
           __FILE__, __LINE__, __FUNCTION__);
    return NULL;
  }

  IDBClientSink *pVestibuleSink = NULL;
  SReqInfo *pSReqInfo = (*it).second;
  pVestibuleSink = pSReqInfo->pSrcVestibuleSink;
  nIndex = pSReqInfo->lSrcIndex;
  delete pSReqInfo;
  m_mapWaitingRetList.erase(it);

  return pVestibuleSink;
}

// 发送DB请求包
BOOL CVestibule::RequestEx(u32 dwCmdTemp, s32 nIndex, s32 nRequestID, s64 qwUserID,
       LPSTR pData, s32 nDataLen, IDBClientSink *pVestibuleSink) {
  if(FALSE == IsConnected()) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, 不处于连接状态%d!",
           __FILE__, __LINE__, __FUNCTION__, m_lState);
    return FALSE;
  }

  if(NULL == pData || nDataLen <= 0 || NULL == pVestibuleSink) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, 参数非法!",
           __FILE__, __LINE__, __FUNCTION__);
    return FALSE;
  }

  if(nDataLen >= MAX_BUFFER_SIZE - 20) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, 数据超长, RequestID=%d, DataLen=%d!",
           __FILE__, __LINE__, __FUNCTION__, nRequestID, nDataLen);
    return FALSE;
  }

  SReqInfo *pstReqInfo = new SReqInfo;
  if(NULL == pstReqInfo) {
    g_pTrace->TraceErrorLn("%s:%d (%s) 操作失败, new失败!",
           __FILE__, __LINE__, __FUNCTION__);
    return FALSE;
  }

  pstReqInfo->lSrcIndex = nIndex;
  pstReqInfo->pSrcVestibuleSink = pVestibuleSink;
  pstReqInfo->nRequestID = nRequestID;
  pstReqInfo->qwUserID = qwUserID;

  s32 iReqIndex = m_nReqID++;
  m_mapWaitingRetList[iReqIndex] = pstReqInfo;

  // 按格式封包
  // 格式: VESTIB_COMMAND_REQUEST + iReqIndex + nRequestID + qwUserID + nDataLen + pData
  char *buf_ptr = m_pReqBuffer;
  int buf_size = 0;

  // 命令
  DWORD dwCmd = dwCmdTemp;
  memcpy(buf_ptr, &dwCmd, sizeof(DWORD));
  buf_ptr  += sizeof(DWORD);
  buf_size += sizeof(DWORD);

  // iReqIndex
  memcpy(buf_ptr, &iReqIndex, sizeof(int));
  buf_ptr  += sizeof(int);
  buf_size += sizeof(int);

  // nRequestID
  memcpy(buf_ptr, &nRequestID, sizeof(int));
  buf_ptr  += sizeof(int);
  buf_size += sizeof(int);

  // qwUserID
  memcpy(buf_ptr, &qwUserID, sizeof(s64));
  buf_ptr  += sizeof(s64);
  buf_size += sizeof(s64);

  // nDataLen
  memcpy(buf_ptr, &nDataLen, sizeof(int));
  buf_ptr  += sizeof(int);
  buf_size += sizeof(int);

  // pData
  memcpy(buf_ptr, pData, nDataLen);
  buf_ptr  += nDataLen;
  buf_size += nDataLen;

  this->Send(m_pReqBuffer, buf_size);
#ifdef _CORE_DEBUG
  kStatisticsSendBytes += buf_size;
  // g_pTrace->Logger(Info, "kStatisticsSendBytes = [%lu]", kStatisticsSendBytes);
#endif

  return TRUE;
}


