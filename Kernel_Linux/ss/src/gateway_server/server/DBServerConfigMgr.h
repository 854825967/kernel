#ifndef _DBSERVERCONFIGMGR_H__
#define _DBSERVERCONFIGMGR_H__

#include <string.h>

#include <list>

#include "MemTextFile.h"

struct SDBServerConfig
{
	u32		dwDBServerID;
	char		szDBServerIP[14];
	u32		dwDBServerPort;
	
	SDBServerConfig()
	{
		memset(this, 0, sizeof(*this));
	}
};

class DBServerConfigMgr
{
public:
	// 构造函数
	DBServerConfigMgr();

	// 析构函数
	~DBServerConfigMgr();

	// 加载配置
	BOOL	Load(LPCSTR szConfig, s32& nErrLine);

	// 获取所有DB前端配置
	std::list<SDBServerConfig>& GetAllDBConfig()
	{
		return m_listDBServerConfig;
	}

private:
	// 过滤字符串左面的空格和tab键
	LPSTR TrimL(LPSTR szStr);

	// 查找文件中以某个字符串开始的行
	BOOL FindStrInFile(CMemTextFile *pFileObj, LPCSTR szStr, s32 &nCurLine, LPSTR szBuf);

private:
	std::list<SDBServerConfig>		m_listDBServerConfig;
};

#endif //_DBSERVERCONFIGMGR_H__
