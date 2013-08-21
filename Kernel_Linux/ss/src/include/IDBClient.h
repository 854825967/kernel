//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 9911 $
// $Author: xfzhuang $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Define interface IDBClient.
//

#ifndef __IDB__CLIENT__H
#define __IDB__CLIENT__H

#include <string.h>
#include <map>

#include "include/IDatabaseSorter.h"
#include "include/GameSys.h"
#include "IOsApi.h"

struct ILog;
struct IServerKernel;
struct ITimerAxis;

enum EN_VESTIBULE_RET {
  // DB引擎处理返回值直接发给应用服
  VESTIBULE_RET_RECV_RESULT = 1,      // 返回正常处理结果 同 DBRET_OK = 1
  VESTIBULE_RET_REQ_FAILED = 200,     // 前置机处理请求时操作失败
  VESTIBULE_RET_REQ_REPEATLY_LOGIN,   // 重复登录角色

  // 前置机报警定义
  VESTIBULE_WARN_CONNECTED = 300,     // 连接上了数据前置机
  VESTIBULE_WARN_DISCONNECTED,        // 数据前置机连接断开
  VESTIBULE_WARN_SVR_BUSY,            // 数据前置机已达到最大连接数
};

// 服务器跳转类型
enum EN_LOGIN_USER_JUMP_TYPE {
  LOGIN_USER_JUMP_TYPE_NULL = 0,      // 空状态, 不允许跳转
  LOGIN_USER_JUMP_TYPE_FIRST_LOGIN,   // 登录后即将进入场景服时(登录服发出)
  LOGIN_USER_JUMP_TYPE_CHANGE_SCENE,  // 游戏中即将切换场景服时(场景服发出)
  LOGIN_USER_JUMP_TYPE_CHANGE_ACTOR,  // 游戏中小退到选择人物时(场景服发出)
};

// 前置机客户端到前置机服务器的命令定义
enum {
  VESTIB_COMMAND_NULL = 0,
  VESTIB_COMMAND_REQUEST,             // 发起数据库请求
  VESTIB_COMMAND_CLOSE,	              // 客户端正常关闭
  VESTIB_COMMAND_KeepAlive,           // 客户端发送的心跳包
  VESTIB_COMMAND_MAX                  // 命令个数
};

// 前置机提供的请求
#define REQ_VESTIB_LOGIN_USER_JUMP_START (REQUESTID_MAX + 1)    // 已登录玩家服务器跳转开始(获取验证码)
#define REQ_VESTIB_LOGIN_USER_JUMP_FINISH (REQUESTID_MAX + 2)   // 已登录玩家服务器跳转完成(上发验证码)
#define REQ_VESTIB_USERDEFINED_LOAD (REQUESTID_MAX + 3)         // 读取自定义玩家数据
#define REQ_VESTIB_USERDEFINED_SAVE (REQUESTID_MAX + 4)         // 保存自定义玩家数据
#define REQ_VESTIB_USER_SAVE_OK (REQUESTID_MAX + 11)            // 切换场景服时，玩家数据已保存OK
#define REQ_VESTIB_KICK_USER (REQUESTID_MAX + 12)               // 踢玩家
#define MAX_USERDEFINED_LENGTH 3600                             // 自定义玩家数据长度

#pragma pack(push, 1)

//////////////////////////////////////////////////////////////////////////
// REQ_VESTIB_LOGIN_USER_JUMP_START
// 已登录玩家服务器跳转开始(获取验证码) - 输入结构体
struct SLoginUserJumpStart_Set
{
  s64 qwUserID;      // 用户ID
  s32 lJumpType;    // 跳转类型, 取值 EN_LOGIN_USER_JUMP_TYPE, 需置为对应类型
  char szRand[16];    // 客户端标示串

  SLoginUserJumpStart_Set() {
    memset(this, 0, sizeof(*this));
  }
};

// 已登录玩家服务器跳转开始(获取验证码) - 输出结构体
struct SLoginUserJumpStart_Get {
  s32 lReturn;               // 返回值
  u32 ValidationCode[4];     // 验证码

  SLoginUserJumpStart_Get() {
    memset(this, 0, sizeof(*this));
  }
};
// REQ_VESTIB_LOGIN_USER_JUMP_START
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQ_VESTIB_LOGIN_USER_JUMP_FINISH
// 已登录玩家服务器跳转完成(上发验证码) - 输入结构体
struct SLoginUserJumpFinish_Set {
  s64 qwUserID;               // 用户ID
  u32 ValidationCode[4];     // 验证码
  char szRand[16];             // 客户端标示串

  SLoginUserJumpFinish_Set() {
    memset(this, 0, sizeof(*this));
  }
};

// 已登录玩家服务器跳转完成(上发验证码) - 输出结构体
struct SLoginUserJumpFinish_Get {
  s32 lReturn;       // 返回值
  s32 lJumpType;     // 跳转类型, 取值 EN_LOGIN_USER_JUMP_TYPE, 需置为对应类型

  SLoginUserJumpFinish_Get() {
    memset(this, 0, sizeof(*this));
  }
};
// REQ_VESTIB_LOGIN_USER_JUMP_FINISH
//////////////////////////////////////////////////////////////////////////

#pragma pack(pop)

// 前置机回调接口
// 注意：继承这个接口的对象最好是全局的，因为这个是异步过程，可能返回周期会比较长
// 一定要保证返回时可以回调到正确的指针
struct IDBClientSink {
  virtual ~IDBClientSink() {}

  // 前置机回调
  // nIndex: 请求流水号
  // nRetCode: 取值于 EN_VESTIBULE_RET
  virtual void OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID,
         LPSTR pOutData, s32 nOutDataLen, LPSTR pInData = NULL, s32 nInDataLen = 0) = 0;
};

// 前置机报警回调接口
struct IDBClientWarningSink {
  virtual ~IDBClientWarningSink() {}

  // 前置机报警回调函数
  // nErrorCode: 取值于上面报警定义
  // szDesc: 报警信息描述
  virtual void OnVestibuleWarning(s32 nErrorCode, LPCSTR szDesc) = 0;
};

// 前置机接口
struct IVestibule {
  virtual ~IVestibule() {};

  // 释放前置机
  virtual void Release(void) = 0;

  // 发送DB请求包
  // nIndex: 请求流水号, 唯一对应每个请求
  // nRequestID: 请求ID
  // qwUserID: 发出本请求的用户ID, 用于取模进行负载均衡
  // pData: 输入数据缓冲区
  // nDataLen: 输入数据缓冲区长度
  // pVestibuleSink: 请求返回回调接口
  virtual BOOL Request(s32 nIndex, s32 nRequestID, s64 qwUserID,
         LPSTR pData, s32 nDataLen, IDBClientSink *pVestibuleSink) = 0;

  // 得到排序接口
	virtual IDatabaseSorter *GetSorter() = 0;
};

struct IVestibuleMgr {
  virtual ~IVestibuleMgr() {}

  // 释放
  virtual void Release() = 0;

  // 启动前置机
  virtual IVestibule* Start(u32 dwDBServerID, LPCSTR lpszServerIP, u16 wServerPort,
         IDBClientWarningSink *pVestibuleWarningSink, LPCSTR lpszAppName, u8 lType,
         u32 dwAppID, BOOL bReConnect) = 0;

  // 停止前置机
  virtual void Stop(u32 dwDBServerID) = 0;

  // 获取所有前置机
  virtual std::map<u32, IVestibule*> &GetAllVestibule() = 0;
};

// 创建输入参数结构体
struct SVestibCreateParam {
  ILog* pTrace;                      // Trace指针
  IServerKernel* pServerKernel;      // 内核系统指针
  ITimerAxis* pTimeAxis;             // 时间轴指针
  char lpszAppName[32];                // 应用服名称
  u8 lType;                          // 服务器类型 
  u32 dwAppID;                       // 应用服ID

  SVestibCreateParam() {
    memset(this, 0, sizeof(*this));
  }
};

// 创建前置机(输出函数)
extern "C" BOOL CreateVestibuleMgr(ILog *pTrace, IServerKernel *pServerKernel,
       ITimerAxis *pTimeAxis, IVestibuleMgr **ppVestibuleMgr);
typedef BOOL (*ProcCreateVestibuleMgr)(ILog *pTrace, IServerKernel *pServerKernel,
       ITimerAxis *pTimeAxis, IVestibuleMgr **ppVestibuleMgr);

// 前置机管理器创建辅助类
class CVestibuleMgrHelper {
 public:
  // 构造函数
  CVestibuleMgrHelper() {
    m_pVestibuleMgr = NULL;
  }

  // 析构函数
  virtual ~CVestibuleMgrHelper() {
    Close();
  }

  // 创建前置机
  BOOL Create(IDBClientWarningSink *pVestibuleWarningSink, SVestibCreateParam &stCreateParam,
         const char *db_client_so) {
    if(!m_DynamicLoader.LoadLibrary(db_client_so)) {
      return FALSE;
    }

    ProcCreateVestibuleMgr proc = NULL;
    proc = (ProcCreateVestibuleMgr)(m_DynamicLoader.GetProcAddress("CreateVestibuleMgr"));
    if (NULL == proc) {
      return FALSE;
    }

    if(FALSE == proc(stCreateParam.pTrace, stCreateParam.pServerKernel,
           stCreateParam.pTimeAxis, &m_pVestibuleMgr)) {
      return FALSE;
    }

    return TRUE;
  }

  IVestibuleMgr* operator->() {
    return m_pVestibuleMgr;
  }

  // 关闭前置机
  void Close() {
    if(m_pVestibuleMgr != NULL) {
      m_pVestibuleMgr->Release();
      m_pVestibuleMgr = NULL;
    }

    m_DynamicLoader.FreeLibrary();
  }

  // 前置机管理器指针
  IVestibuleMgr *m_pVestibuleMgr;

 private:
  // 动态库加载器
  CDynamicLoader m_DynamicLoader;
};

#endif  // __IDB__CLIENT__H

