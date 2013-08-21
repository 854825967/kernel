#ifndef	__ASYNOBJECT_H__
#define	__ASYNOBJECT_H__
#include "GameSys.h"

class CDBADO;
struct IDBRetSink;
struct REQUESTCONFIG;

// 异步对象类
class CAsynObject
{
public:
	// 构造函数
	CAsynObject();
	// 析构函数
	virtual ~CAsynObject();

	// 创建异步对象环境
	BOOL Create(s32 nIndex, s32 nRequestID, s64 qwUserID, LPSTR pInData, s32 nInDataLen,
		CDBADO *pDBADO, IDBRetSink *pRet);

	// 释放异步对象
	void Close(void);

	// 处理异步对象的数据库请求
	virtual s32 OnRequest(void);

	// 处理异步对象的数据库返回
	void OnRet(void);

	// 获取发出用户ID
	s64 GetUserID(void);

	// 获取重要度
	s32 GetWeightness(void);

	// 获取请求ID
	s32 GetRequestID(void);

	// 保存内容到文件
	void DumpToFile(FILE *fp);

private:
	// 获取输入数据长度
	s32 GetInDataLen(void);
	// 获取输入数据的成员信息, 注意存在字节对齐问题
	BOOL GetInDataMem(LPSTR szMemName, s32 nType, SQLTypeAdapter &vtMem);
	// 获取输出数据长度
	s32 GetOutDataLen(void);
	// 填写直通数据到输出数据中, 注意存在字节对齐问题
	LPSTR PutOutDataMemForStruct(LPSTR pOutData, LPSTR szMemName, s32 nMemLen);
	// 填写VT数据到输出数据中, 注意存在字节对齐问题
	LPSTR PutOutDataMemForVT(LPSTR pOutData, String &vtMem, s32 nLen);

private:
	s32		m_nIndex;		// 流水号
	s64		m_qwUserID;		// 发出用户ID
	char	*m_pInData;		// 输入数据缓冲区
	s32		m_nInDataLen;	// 输入数据缓冲区长度
	char	*m_pOutData;	// 输出数据缓冲区
	s32		m_nOutDataLen;	// 输出数据缓冲区长度
	s32		m_nReturn;		// 数据库返回值

	REQUESTCONFIG	*m_pRequestConfig;	// 数据库请求配置信息
	CDBADO			*m_pDBADO;	// CDBADO对象指针
	IDBRetSink		*m_pRet;	// 数据库请求返回回调接口指针
	char	m_EscapeStringBuffer[8193];
};

#endif // __ASYNOBJECT_H__

