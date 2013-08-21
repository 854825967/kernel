#ifndef __DATA_PROC_SAVE_DB_H__
#define __DATA_PROC_SAVE_DB_H__
#include "DataProc.h"
#include "IDBEngine.h"

#define MAKE_SDB_DATATYPE(nRequestID, nMainType, nSubType)		(((nRequestID) << 20) | ((nMainType) & 0xFFC00) | (nSubType))
#define GET_SDB_REQUESTID(nDataType)							((nDataType) >> 20)
#define GET_SDB_MAINTYPE(nDataType)								((nDataType) & 0xFFC00)
#define GET_SDB_SUBTYPE(nDataType)								((nDataType) & 0x3FF)

class CSaveDBData;

class CDataProcSaveDB : public CDataProc, public IDBRetSink
{
public:
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////// CDataProc /////////////////////////////
	// 请求处理
	virtual BOOL Request( s32 nIndex, s32 nRequestID, s64 qwUserID,
		LPSTR pInData, s32 nInDataLen, IDBProxyRetSink *pRet, LPVOID dwServerID);

	//////////////////////////////////////////////////////////////////////////
	///////////////////////////////// IDBRetSink /////////////////////////////
	// 数据库请求返回回调函数
	// nReturn: 参考上面数据库请求返回值定义
	// pOutData: 输出数据缓冲区指针
	// nOutLen: 输出数据缓冲区长度
	virtual void OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
		s32 nReturn, LPSTR pOutData, s32 nOutLen);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////// CDataProcSaveDB /////////////////////////////
	CDataProcSaveDB();

	~CDataProcSaveDB();

	// 查找数据，nDataType见 MAKE_SDB_DATATYPE 的定义
	CSaveDBData* FindDBData(s32 nDataType, s32 nDataKey);

	// 删除数据，nDataType见 MAKE_SDB_DATATYPE 的定义
	void DelDBData(s32 nDataType, s32 nDataKey, CSaveDBData *pDBData);

	//关闭服务器，用于处理缓存数据的保存
	void CloseServer(LPVOID dwServerID);

private:
	//返回数据类型
	s32 GetDataType(s32 nRequestID, LPSTR pInData, s32 nInDataLen);

	//获取数据
	CSaveDBData* GetSaveDBData(s32 nRequestID, s64 qwUserID, LPSTR pInData, s32 nInDataLen, LPVOID dwServerID);

private:
	typedef map<s64, CSaveDBData *> MAP_SDB_DATA;		//某种类型的数据的集合
	typedef map<s32, MAP_SDB_DATA> MAP_ALL_DATA;		//所有数据的集合

	map<s32, IDBProxyRetSink*> m_RequestMap;			//请求映射表
	MAP_ALL_DATA m_MapAllData;							//用户映射表
};

#endif //__DATA_PROC_SAVE_DB_H__

