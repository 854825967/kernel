#ifndef __SAVE_DB_DATA_H__
#define __SAVE_DB_DATA_H__
#include "IDBEngine.h"
#include "ITimeAxis.h"

class CDataProcSaveDB;

class CSaveDBData : public IDBRetSink, public ITimerHandler
{
public:
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////// IDBRetSink ////////////////////////////
	// 数据库请求返回回调函数
	// nReturn: 参考上面数据库请求返回值定义
	// pOutData: 输出数据缓冲区指针
	// nOutLen: 输出数据缓冲区长度
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen);

	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////// ITimerSink ////////////////////////////
	// 定时器回调
	virtual void OnTimer(u32 dwTimerID);

	//////////////////////////////////////////////////////////////////////////
	///////////////////////////////// CSaveDBData ////////////////////////////
	CSaveDBData(s32 nDataType, s64 nDataKey, LPVOID dwServerID, CDataProcSaveDB *pDataProcUser);

	~CSaveDBData();

	//是否正在存盘
	BOOL IsSaving(void);

	//获取服务器ID
	LPVOID GetServerID(void);

	//设置服务器ID
	void SetServerID(LPVOID dwServerID);

	//保存数据
	BOOL Save(s32 nRequestID, LPSTR pInData, s32 nInDataLen, LPSTR pOutData, s32 &nOutDataLen);

	//装载数据
	BOOL Load(s32 nRequestID, LPSTR pInData, s32 nInDataLen, LPSTR pOutData, s32 &nOutDataLen);

	//关闭服务器，用于处理缓存数据的保存
	void CloseServer(void);

private:
	s32 m_nDataType;		//数据类型
	s64 m_qwDataKey;			//数据子类
	LPVOID m_dwServerID;	//服务器ID
	BOOL m_bSaving;			//正在存盘标志
	s32 m_dwLastSave;		//最后存盘时间
	s32 m_nSaveRID;			//存盘请求的ID
	vector<char> m_VecData;	//数据
	CDataProcSaveDB *m_pProcSaveDB;		//数据处理指针
};

#endif //__SAVE_DB_DATA_H__

