#include "GameSys.h"
#include "DBServerConfigMgr.h"

// DB前端配置总数量标志
#define DBSERVER_CONFIG_NUM_FLAG		"totalnum ="

// DB前端配置标志
#define DBSERVER_CONFIG_FLAG			"dbserver config"

// DB前端ID标志
#define DBSERVER_ID_CONFIG_FLAG			"DBServerID ="

// DB前端IP地址标志
#define DBSERVER_IP_CONFIG_FLAG			"DBServerIP ="

// DB前端端口标志
#define DBSERVER_PORT_CONFIG_FLAG		"DBServerPort ="

// 构造函数
DBServerConfigMgr::DBServerConfigMgr()
{
	m_listDBServerConfig.clear();
}

// 析构函数
DBServerConfigMgr::~DBServerConfigMgr()
{

}

// 创建异步队列处理验证宏
#define ASSERT_ALCREATE(r)	{ if (!(r)) { return FALSE; } }

// 加载配置
BOOL DBServerConfigMgr::Load(LPCSTR szConfig, s32& nErrLine)
{
	CMemTextFile	FileObj;

	if (FALSE == FileObj.Open(szConfig))
	{
		return FALSE;
	}

	char		szBuf[1024] = {0};
	s32		nCurNum = 0;
	s32		nTotalNum = 0;

	SDBServerConfig	dbServerConfig;
	s32				nID = 0;
	s32				nNum = 0;

	// "totalnum ="
	ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DBSERVER_CONFIG_NUM_FLAG, nErrLine, szBuf));

	// 获取异步队列配置的总数量
	s32	nInputNum = sscanf(szBuf + strlen(DBSERVER_CONFIG_NUM_FLAG), "%d", &nTotalNum);
	ASSERT_ALCREATE(1 == nInputNum && nTotalNum > 0);

	// 获取异步队列配置信息
	while (FALSE == FileObj.IsEnd())
	{
		// "dbserver config"
		if (FALSE == FindStrInFile(&FileObj, DBSERVER_CONFIG_FLAG, nErrLine, szBuf))
		{
			break;
		}

		// "{"
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));

		// 获取DB前端ID
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DBSERVER_ID_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DBSERVER_ID_CONFIG_FLAG), "%d", &dbServerConfig.dwDBServerID);
		ASSERT_ALCREATE(1 == nInputNum && dbServerConfig.dwDBServerID > 0);

		// 获取DB前端IP地址
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DBSERVER_IP_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DBSERVER_IP_CONFIG_FLAG), "%s", dbServerConfig.szDBServerIP);
		ASSERT_ALCREATE(1 == nInputNum && strlen(dbServerConfig.szDBServerIP) > 0);

		// 获取DB前端端口
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, DBSERVER_PORT_CONFIG_FLAG, nErrLine, szBuf));
		nInputNum = sscanf(szBuf + strlen(DBSERVER_PORT_CONFIG_FLAG), "%d", &dbServerConfig.dwDBServerPort);
		ASSERT_ALCREATE(1 == nInputNum && dbServerConfig.dwDBServerPort > 0);

		// "}"
		ASSERT_ALCREATE(TRUE == FindStrInFile(&FileObj, "}", nErrLine, szBuf));

		m_listDBServerConfig.push_back(dbServerConfig);

		nCurNum ++;
	}

	ASSERT_ALCREATE(nCurNum == nTotalNum);

	return TRUE;
}

// 过滤字符串左面的空格和tab键
LPSTR DBServerConfigMgr::TrimL(LPSTR szStr)
{
	char	*szTemp = szStr;
	while (*szTemp == ' ' || *szTemp == 9)
	{
		++szTemp;
	}

	memmove(szStr, szTemp, strlen(szTemp) + 1);
	return szStr;
}

// 查找文件中以某个字符串开始的行
BOOL DBServerConfigMgr::FindStrInFile(CMemTextFile *pFileObj, LPCSTR szStr, s32 &nCurLine, LPSTR szBuf)
{
	if (NULL == pFileObj || NULL == szStr || NULL == szBuf)
	{
		return FALSE;
	}

	while (FALSE == pFileObj->IsEnd())
	{
		memset(szBuf, 0, sizeof(szBuf));
		pFileObj->GetLine(szBuf, 1024);
		TrimL(szBuf);
		nCurLine ++;
		if (0 == memcmp(szBuf, szStr, strlen(szStr)))
		{
			return TRUE;
		}
	}

	return FALSE;
}

