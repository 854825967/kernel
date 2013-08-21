#ifndef	__REQUESTCONFIG_H__
#define	__REQUESTCONFIG_H__
#include "../include/GameSys.h"

// 最大参数名称长度
#define MAX_PARAM_NAME_LEN	32
// 最大存储过程名称长度
#define MAX_SPNAME_LEN		32

class CDBMemTextFile;

// 数据库请求重要度级别定义
enum
{
	REQUEST_WEIGHTNESS_1 = 0,	// 最低重要度
	REQUEST_WEIGHTNESS_2,
	REQUEST_WEIGHTNESS_3,
	REQUEST_WEIGHTNESS_4,
	REQUEST_WEIGHTNESS_5,		
	REQUEST_WEIGHTNESS_MAX		// 最高重要度
};

// 数据来源定义
enum
{
	DS_INPUTSTRUCT = 0,		// 来自于输入数据结构
	DS_STOREPROCEDURE,		// 来自于存储过程
	DS_RECORDSET			// 来自于结果集
};

// 输入数据结构成员
struct INPUTSTRUCTMEM
{
	char	szName[MAX_PARAM_NAME_LEN];	// 成员名称
	s32		nLen;						// 成员字节长度

	INPUTSTRUCTMEM()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 存储过程参数
struct SPPARAM
{
	char	szName[MAX_PARAM_NAME_LEN];	// 参数名称
	s32		nDirection;					// 参数方向
	s32		nType;						// 参数类型
	s32		nLen;						// 参数字节长度
	char	szInputStructMemName[MAX_PARAM_NAME_LEN];	// 对应输入数据结构成员名称

	SPPARAM()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 输出数据结构成员
struct OUTPUTSTRUCTMEM
{
	s32		nLen;								// 成员字节长度
	s32		nSource;							// 数据来源
	char	szParamName[MAX_PARAM_NAME_LEN];	// 数据来源的参数名称

	OUTPUTSTRUCTMEM()
	{
		memset(this, 0, sizeof(*this));
	}
};

// 数据库请求配置结构
struct REQUESTCONFIG
{
	s32		nID;						// 序号
	char	szSPName[MAX_SPNAME_LEN];	// 存储过程名
	s32		nDBType;					// 数据库类型
	BOOL	bRecordset;					// 是否有结果集
	s32		nWeightNess;				// 重要度
	list<INPUTSTRUCTMEM>	InputStructMemList;			// 输入数据结构成员列表
	list<SPPARAM>			SPParamList;				// 存储过程参数列表
	list<OUTPUTSTRUCTMEM>	OutputStructMemList;		// 输出数据结构成员列表
	list<OUTPUTSTRUCTMEM>	OutputStructMemForRstList;	// 用于输出结果集的数据结构成员列表

	REQUESTCONFIG()
	{
		nID = -1;
		memset(szSPName, 0, sizeof(szSPName));
		nDBType = 0;
		bRecordset = FALSE;
		nWeightNess = 0;
		InputStructMemList.clear();
		SPParamList.clear();
		OutputStructMemList.clear();
		OutputStructMemForRstList.clear();
	}
};

// 数据库请求配置类
class CRequestConfig
{
public:
	// 构造函数
	CRequestConfig();

	// 析构函数
	~CRequestConfig();

	// 创建数据库请求配置
	BOOL Create(LPCSTR szFileName, s32 &nErrLine, LPSTR szKey);

	// 关闭数据库请求配置
	void Close(void);

	// 查找数据库请求配置信息
	REQUESTCONFIG* FindRequestConfig(s32 iID);

private:
	// 过滤字符串左面的空格和tab键
	LPSTR TrimL(LPSTR szStr);
	// 查找文件中以某个字符串开始的行
	BOOL FindStrInFile(CDBMemTextFile *pFileObj, LPCSTR szStr, s32 &nCurLine, LPSTR szBuf);
	// 查找输入数据结构成员是否存在
	BOOL FindInputStructMem(REQUESTCONFIG *pRequestConfig, LPSTR szMemName);
	// 查找存储过程参数是否存在
	BOOL FindSPParam(REQUESTCONFIG *pRequestConfig, LPSTR szParamName);
	// 查找存储过程参数中是否存在返回值
	BOOL FindSPReturn(REQUESTCONFIG *pRequestConfig);

	// 通过类型名获取DB参数类型值
	s32 GetDBType(LPSTR szType);
	// 通过方向名获取DB参数方向值
	s32 GetDBDirection(LPSTR szDirection);
	// 通过来源名获取数据来源值
	s32 GetDataSource(LPSTR szSource);

private:
	vector<REQUESTCONFIG>	m_vecRequestConfig;	// 数据库请求配置表
};

#endif // __REQUESTCONFIG_H__
