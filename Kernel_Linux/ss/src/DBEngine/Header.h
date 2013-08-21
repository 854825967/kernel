#ifndef	__HEADER_H__
#define	__HEADER_H__

// 安全释放宏
#ifndef SAFE_RELEASE
#define	SAFE_RELEASE(p)	{ if ((p) != NULL) { (p)->Release(); (p) = NULL; } }
#endif

// 性能评测开关
// #define PERFORMANCE_TEST

// 抛包日志文件
#define REDUCE_LOG_FILE		"./log/抛包日志%d.txt"
// 缓存文件
#define CACHE_FILE		"./log/本地缓存%d.txt"

// 最大数据库连接字符串长度
#define MAX_CONNECTSTRING_LEN		256
// 脚本文件最大一行字符个数
#define MAX_LINE_NUMBER			1024
// 最大请求ID
#define MAX_REQUESTID			1024

#ifdef _MSC_VER

#else 
	enum ParameterDirectionEnum
	{
		adParamUnknown = 0,
		adParamInput = 1,
		adParamOutput = 2,
		adParamInputOutput = 3,
		adParamReturnValue = 4
	};

	enum DataTypeEnum
	{
		adEmpty = 0,
			adTinyInt = 16,
			adSmallInt = 2,
			adInteger = 3,
			adBigInt = 20,
			adUnsignedTinyInt = 17,
			adUnsignedSmallInt = 18,
			adUnsignedInt = 19,
			adUnsignedBigInt = 21,
			adSingle = 4,
			adDouble = 5,
			adCurrency = 6,
			adDecimal = 14,
			adNumeric = 131,
			adBoolean = 11,
			adError = 10,
			adUserDefined = 132,
			adVariant = 12,
			adIDispatch = 9,
			adIUnknown = 13,
			adGUID = 72,
			adDate = 7,
			adDBDate = 133,
			adDBTime = 134,
			adDBTimeStamp = 135,
			adBSTR = 8,
			adChar = 129,
			adVarChar = 200,
			adLongVarChar = 201,
			adWChar = 130,
			adVarWChar = 202,
			adLongVarWChar = 203,
			adBinary = 128,
			adVarBinary = 204,
			adLongVarBinary = 205,
			adChapter = 136,
			adFileTime = 64,
			adPropVariant = 138,
			adVarNumeric = 139,
			adArray = 8192
	};
#endif

#include "GameSys.h"
#include "IDBEngine.h"
#include "DBMemTextFile.h"
#include "DBADO.h"
#include "RequestConfig.h"
#include "AsynObject.h"
#include "AsynObjectList.h"
#include "DBEngine.h"

// 信息日志文件
#define INFO_FILE	"./log/DBEngine.txt"

// 输出信息日志
extern "C" void GPrintInfoLog(LPCSTR lpszFormat, ...);

// 获取TickCount
extern "C" u32 GetTickCount();

// 全局通用数据库引擎对象指针
extern CDBEngine		*g_pDBEngine;

// 全局数据库请求配置对象
extern CRequestConfig	g_RequestConfig;

#endif // __HEADER_H__
