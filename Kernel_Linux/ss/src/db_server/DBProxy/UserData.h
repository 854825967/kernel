#ifndef __USERDATA_H__
#define __USERDATA_H__
#include "IDBEngine.h"
#include "ITimeAxis.h"
#include "IDBStruct.h"

class CDataProcUser;

// 用户数据
class CUserData : public IDBRetSink, public ITimerHandler
{
public:
	// 构造函数
	CUserData(s64 qwUserID, s32 lActorID, LPVOID dwServerID, CDataProcUser *pDataProcUser);
	// 析构函数
	~CUserData();

	// 数据库请求返回回调函数
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen);

	// 定时器回调
	virtual void OnTimer(u32 dwTimerID);

	// 是否正在存盘
	BOOL IsSaving(void);

	// 获取服务器ID
	LPVOID GetServerID(void);

	// 设置服务器ID
	void SetServerID(LPVOID dwServerID);

	// 保存数据
	BOOL Save(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
		LPSTR pOutData, s32 &nOutDataLen);

	// 装载数据
	BOOL Load(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
		LPSTR pOutData, s32 &nOutDataLen);

	//返回TRUE表示切换场景数据保存OK，用于踢人
	BOOL IsDataSaveOK(void);

	//踢玩家
	void KickUser(void);

private:
	// 定时存盘处理  增加参数 本次存盘是否升级 修改
	void TimeSave(BOOL bUpdateLevel = FALSE);

private:
	s64						m_qwUserID;		// 用户ID
	s32						m_lActorID;		// 角色ID
	LPVOID					m_dwServerID;	// 服务器ID
	BOOL					m_bSaving;		// 正在存盘标志
	s32						m_dwLastSave;	// 最后存盘时间
	BOOL					m_bDataSaveOK;	// 玩家切换场景数据保存OK，用于踢人
	CDataProcUser	*		m_pDataProcUser;// 数据处理指针
	SActorUpdate_Set		m_UpdateSet;	// 角色更新数据
	list<SGoodsUpdate_Set>	m_GoodsSet;		// 角色物品更新
	SInteractSave_Set		m_InteractSet;	// 交互数据更新
};

#endif // __USERDATA_H__

