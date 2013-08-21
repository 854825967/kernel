#ifndef	__DBADO_H__
#define	__DBADO_H__
#include "mysql++.h"
using namespace mysqlpp;

class CAsynObjectList;

class CDBADO
{
public:
	// 构造函数
	CDBADO();
	// 析构函数
	~CDBADO();

	// 创建数据库访问
	BOOL Create(void);

	// 关闭数据库访问
	void Close(void);

	// 连接数据库
	BOOL Connect(LPSTR szDataSource, s32 nServerPort, LPSTR szDBName, LPSTR szUser, LPSTR szPwd);

	// 断开数据库连接
	BOOL Disconnect(void);

	// 数据库是否已经连接
	BOOL IsConnected(void);

	// 设置当前存储过程名
	BOOL SetSPName(LPCSTR szSPName);

	// 清除当前命令的所有参数 
	BOOL ClearParam(void);

	// 添加一个参数到当前命令中
	BOOL AddParam(SQLTypeAdapter& staParam, DataTypeEnum type, u32 dwParamIndex, u32 dwTotalParam);

	// 执行命令并返回记录集
  // >0:成功
  // =0:连接断开，需要重新执行
  // <0:错误
	int OpenRecordset(void);

	// 关闭结果集
	BOOL CloseRecordset(void);

	// 结果集是否已打开
	BOOL IsRecordsetOpened(void);

	// 获取结果集中结果的个数
	int GetRecordCount(void);
	// 下一条结果
	BOOL RecordsetNext(void);

	// 获取结果集结束标志
	BOOL IsRecordsetEOF(void);

	// 执行命令不返回记录集
	int OpenNoRecordset(void);

	// 获取命令执行后参数的值
	BOOL GetParamValue(char *szName, String &vtValue);

	// 获取命令执行后域的值
	BOOL GetFieldValue(char *szName, String &vtValue);

	// 设置所属异步队列指针
	void SetAsynObjectList(CAsynObjectList *pAsynObjectList);

	// 转义字符串
	u32	EscapeString(char* szEscaped, const char* szOriginal, u32 dwLen);

private:
	Connection*			m_pConnection;		// 连接对象
	Query				m_Query;			// 命令对象
	StoreQueryResult	m_StoreQueryResult;	// 记录集对象
	u32					m_dwCurResultIndex;	// 当前Row下标
	CAsynObjectList	*	m_pAsynObjectList;	// 所属异步队列指针
	string				m_strDataSource;	// 数据源
	s32				m_nPort;
	string				m_strDBName;		// 数据库名
	string				m_strUserName;		// 用户名
	string				m_strPwd;			// 密码
};

#endif // __DBADO_H__
