#include "Header.h"
#include "RequestConfig.h"

// 请求总数量标志
#define REQUEST_NUM_FLAG				"totalnum ="
// 请求配置标志
#define REQUEST_CONFIT_FLAG				"request ="
// 存储过程名配置标志
#define SPNAME_CONFIG_FLAG				"spname ="
// 所属数据库类型
#define DBTYPE_CONFIG_FLAG				"dbtype ="
// 是否有结果集配置标志
#define RECORDSET_CONFIG_FLAG			"recordset ="
// 重要度配置标志
#define WEIGHTNESS_CONFIG_FLAG			"weightness ="
// 输入数据结构配置标志
#define INPUTSTRUCT_CONFIG_FLAG			"input struct"
// 存储过程配置标志
#define SP_CONFIG_FLAG					"store procedure"
// 输出数据结构配置标志
#define OUTPUTSTRUCT_CONFIG_FLAG		"output struct"
// 用于输出结果集的数据结构配置标志
#define OUTPUTSTRUCTFORRST_CONFIG_FLAG	"output struct for recordset"

// 全局数据库请求配置对象
CRequestConfig	g_RequestConfig;

// 构造函数
CRequestConfig::CRequestConfig() : m_vecRequestConfig(MAX_REQUESTID)
{
}

// 析构函数
CRequestConfig::~CRequestConfig()
{
}

// 创建数据库请求配置处理验证宏
#define ASSERT_RSCREATE(r)	{ if (!(r)) { return FALSE; } }

// 创建数据库请求配置
BOOL CRequestConfig::Create(LPCSTR szFileName, s32 &nErrLine, LPSTR szKey)
{
	CDBMemTextFile	FileObj;

	if (FALSE == FileObj.Open(szFileName))
	{
		return FALSE;
	}
	char	szBuf[MAX_LINE_NUMBER] = {0};
	s32		nTotalNum = 0;
	s32		nCurNum = 0;

	nErrLine = 0;

	// "totalnum ="
	ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, REQUEST_NUM_FLAG, nErrLine, szBuf));

	// 获取数据库请求的总数量
	s32	nInputNum = sscanf(szBuf + strlen(REQUEST_NUM_FLAG), "%d", &nTotalNum);
	ASSERT_RSCREATE(1 == nInputNum && nTotalNum > 0);

	// 获取数据库请求的配置信息
	while (FALSE == FileObj.IsEnd())
	{
		REQUESTCONFIG	RequestConfig;

		// "request ="
		if (FALSE == FindStrInFile(&FileObj, REQUEST_CONFIT_FLAG, nErrLine, szBuf))
		{
			break;
		}

		// 获取数据库请求的ID
		nInputNum = sscanf(szBuf + strlen(REQUEST_CONFIT_FLAG), "%d", &RequestConfig.nID);
		ASSERT_RSCREATE(1 == nInputNum && RequestConfig.nID >= 0 && RequestConfig.nID < MAX_REQUESTID
			&& NULL == FindRequestConfig(RequestConfig.nID));

		// "{"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));
		// "spname ="
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, SPNAME_CONFIG_FLAG, nErrLine, szBuf));

		// 获取存储过程名
		nInputNum = sscanf(szBuf + strlen(SPNAME_CONFIG_FLAG), "%s", RequestConfig.szSPName);
		ASSERT_RSCREATE(1 == nInputNum && strlen(RequestConfig.szSPName) > 0);

		// "dbtype ="
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, DBTYPE_CONFIG_FLAG, nErrLine, szBuf));

		// 获取所属数据库类型
		nInputNum = sscanf(szBuf + strlen(DBTYPE_CONFIG_FLAG), "%d", &RequestConfig.nDBType);
		ASSERT_RSCREATE(1 == nInputNum && RequestConfig.nDBType > 0);

		// "recordset ="
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, RECORDSET_CONFIG_FLAG, nErrLine, szBuf));

		// 获取是否有结果集标志
		nInputNum = sscanf(szBuf + strlen(RECORDSET_CONFIG_FLAG), "%d", &RequestConfig.bRecordset);
		ASSERT_RSCREATE(1 == nInputNum && (TRUE == RequestConfig.bRecordset || FALSE == RequestConfig.bRecordset));

		// "weightness ="
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, WEIGHTNESS_CONFIG_FLAG, nErrLine, szBuf));

		// 获取数据库请求重要度
		nInputNum = sscanf(szBuf + strlen(WEIGHTNESS_CONFIG_FLAG), "%d", &RequestConfig.nWeightNess);
		ASSERT_RSCREATE(1 == nInputNum && RequestConfig.nWeightNess >= REQUEST_WEIGHTNESS_1
			&& RequestConfig.nWeightNess < REQUEST_WEIGHTNESS_MAX);

		// "input struct"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, INPUTSTRUCT_CONFIG_FLAG, nErrLine, szBuf));
		// "{"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));

		// 获取输入数据结构成员信息
		while (FALSE == FileObj.IsEnd())
		{
			memset(szBuf, 0, sizeof(szBuf));
			FileObj.GetLine(szBuf, MAX_LINE_NUMBER);
			TrimL(szBuf);
			nErrLine ++;
			if (0 == memcmp(szBuf, "}", 1))
			{
				break;
			}

			if (strlen(szBuf) > 0)
			{
				INPUTSTRUCTMEM	InputStructMem;
				nInputNum = sscanf(szBuf, "%s%d", InputStructMem.szName, &InputStructMem.nLen);
				ASSERT_RSCREATE(2 == nInputNum && strlen(InputStructMem.szName) > 0 && InputStructMem.nLen > 0);
				// 确保成员名字没有重复的
				ASSERT_RSCREATE(FALSE == FindInputStructMem(&RequestConfig, InputStructMem.szName));

				RequestConfig.InputStructMemList.push_back(InputStructMem);
			}
		}

		// 输入数据结构成员数不能为0
		ASSERT_RSCREATE(RequestConfig.InputStructMemList.size() > 0);

		// "store procedure"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, SP_CONFIG_FLAG, nErrLine, szBuf));
		// "{"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));

		// 获取存储过程参数信息
		while (FALSE == FileObj.IsEnd())
		{
			memset(szBuf, 0, sizeof(szBuf));
			FileObj.GetLine(szBuf, MAX_LINE_NUMBER);
			TrimL(szBuf);
			nErrLine ++;
			if (0 == memcmp(szBuf, "}", 1))
			{
				break;
			}

			if (strlen(szBuf) > 0)
			{
				char	szType[MAX_LINE_NUMBER] = {0};
				char	szDirection[MAX_LINE_NUMBER] = {0};
				SPPARAM		SPParam;
				nInputNum = sscanf(szBuf, "%s%s%s%d%s", SPParam.szName, szDirection, szType, &SPParam.nLen, SPParam.szInputStructMemName);
				SPParam.nType = GetDBType(szType);
				SPParam.nDirection = GetDBDirection(szDirection);
				ASSERT_RSCREATE(5 == nInputNum && SPParam.nType != -1
					&& SPParam.nDirection != -1 && SPParam.nLen > 0);
				// 确保对应输入数据结构成员名称存在
				if (adParamInput == SPParam.nDirection || adParamInputOutput == SPParam.nDirection)
				{
					ASSERT_RSCREATE(TRUE == FindInputStructMem(&RequestConfig, SPParam.szInputStructMemName));
				}

				RequestConfig.SPParamList.push_back(SPParam);
			}
		}

		// 输入存储过程参数数不能为0
		ASSERT_RSCREATE(RequestConfig.SPParamList.size() > 0);
		// sqlserver存储过程参数中必须有返回值
#ifdef DEFINE_DRIVERTYPE_MSSQL
		ASSERT_RSCREATE(TRUE == FindSPReturn(&RequestConfig));
#endif

		// "output struct"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, OUTPUTSTRUCT_CONFIG_FLAG, nErrLine, szBuf));
		// "{"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));

		// 获取输出数据结构成员信息
		while (FALSE == FileObj.IsEnd())
		{
			memset(szBuf, 0, sizeof(szBuf));
			FileObj.GetLine(szBuf, MAX_LINE_NUMBER);
			TrimL(szBuf);
			nErrLine ++;
			if (0 == memcmp(szBuf, "}", 1))
			{
				break;
			}

			if (strlen(szBuf) > 0)
			{
				char	szSource[MAX_LINE_NUMBER] = {0};
				OUTPUTSTRUCTMEM	OutputStructMem;
				nInputNum = sscanf(szBuf, "%d%s%s", &OutputStructMem.nLen, szSource, OutputStructMem.szParamName);
				OutputStructMem.nSource = GetDataSource(szSource);
				ASSERT_RSCREATE(3 == nInputNum && OutputStructMem.nLen > 0);
				ASSERT_RSCREATE(DS_INPUTSTRUCT == OutputStructMem.nSource
					|| DS_STOREPROCEDURE == OutputStructMem.nSource);
				// 确保数据来源的参数名称存在
				if (DS_INPUTSTRUCT == OutputStructMem.nSource)
				{
					ASSERT_RSCREATE(TRUE == FindInputStructMem(&RequestConfig, OutputStructMem.szParamName));
				}
				else if (DS_STOREPROCEDURE == OutputStructMem.nSource)
				{
					ASSERT_RSCREATE(TRUE == FindSPParam(&RequestConfig, OutputStructMem.szParamName));
				}

				RequestConfig.OutputStructMemList.push_back(OutputStructMem);
			}
		}

		// mssql的输出数据结构成员数不能为0
#ifdef DEFINE_DRIVERTYPE_MSSQL
		ASSERT_RSCREATE(RequestConfig.OutputStructMemList.size() > 0);
#endif

		// "output struct for recordset"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, OUTPUTSTRUCTFORRST_CONFIG_FLAG, nErrLine, szBuf));
		// "{"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, "{", nErrLine, szBuf));

		// 获取用于输出结果集的数据结构成员信息
		while (FALSE == FileObj.IsEnd())
		{
			memset(szBuf, 0, sizeof(szBuf));
			FileObj.GetLine(szBuf, MAX_LINE_NUMBER);
			TrimL(szBuf);
			nErrLine ++;
			if (0 == memcmp(szBuf, "}", 1))
			{
				break;
			}

			if (strlen(szBuf) > 0)
			{
				char	szSource[MAX_LINE_NUMBER] = {0};
				OUTPUTSTRUCTMEM	OutputStructMemForRst;
				nInputNum = sscanf(szBuf, "%d%s%s", &OutputStructMemForRst.nLen, szSource, OutputStructMemForRst.szParamName);
				OutputStructMemForRst.nSource = GetDataSource(szSource);
				ASSERT_RSCREATE(3 == nInputNum && OutputStructMemForRst.nSource != -1
					&& OutputStructMemForRst.nLen > 0);
				// 确保数据来源的参数名称存在
				if (DS_INPUTSTRUCT == OutputStructMemForRst.nSource)
				{
					ASSERT_RSCREATE(TRUE == FindInputStructMem(&RequestConfig, OutputStructMemForRst.szParamName));
				}
				else if (DS_STOREPROCEDURE == OutputStructMemForRst.nSource)
				{
					ASSERT_RSCREATE(TRUE == FindSPParam(&RequestConfig, OutputStructMemForRst.szParamName));
				}

				RequestConfig.OutputStructMemForRstList.push_back(OutputStructMemForRst);
			}
		}

		if (TRUE == RequestConfig.bRecordset)
		{
			// 输出用于输出结果集的数据结构成员数不能为0
			ASSERT_RSCREATE(RequestConfig.OutputStructMemForRstList.size() > 0);
		}

		// "}"
		ASSERT_RSCREATE(TRUE == FindStrInFile(&FileObj, "}", nErrLine, szBuf));

		m_vecRequestConfig[RequestConfig.nID] = RequestConfig;
		nCurNum ++;
	}

	ASSERT_RSCREATE(nCurNum == nTotalNum);

	return TRUE;
}

// 关闭数据库请求配置
void CRequestConfig::Close(void)
{
}

// 获取数据库请求配置信息
REQUESTCONFIG* CRequestConfig::FindRequestConfig(s32 iID)
{
	if (iID < 0 || iID >= MAX_REQUESTID)
	{
		return NULL;
	}

	REQUESTCONFIG &requestConfig = m_vecRequestConfig[iID];
	if (requestConfig.nID != -1)
	{
		return &requestConfig;
	}

	return NULL;
}

// 过滤字符串前面的空格和tab键
LPSTR CRequestConfig::TrimL(LPSTR szStr)
{
	char	*szTemp = szStr;
	while (*szTemp == ' ' || *szTemp == 9)
	{
		szTemp ++;
	}

	memmove(szStr, szTemp, strlen(szTemp)+1);
	return szStr;
}

// 查找文件中以某个字符串开始的行
BOOL CRequestConfig::FindStrInFile(CDBMemTextFile *pFileObj, LPCSTR szStr, s32 &nCurLine, LPSTR szBuf)
{
	if (NULL == pFileObj || NULL == szStr || NULL == szBuf)
	{
		return FALSE;
	}

	while (FALSE == pFileObj->IsEnd())
	{
		memset(szBuf, 0, sizeof(szBuf));
		pFileObj->GetLine(szBuf, MAX_LINE_NUMBER);
		TrimL(szBuf);
		nCurLine ++;
		if (0 == memcmp(szBuf, szStr, strlen(szStr)))
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 查找输入数据结构成员是否存在
BOOL CRequestConfig::FindInputStructMem(REQUESTCONFIG *pRequestConfig, LPSTR szMemName)
{
	if (NULL == pRequestConfig || NULL == szMemName)
	{
		return FALSE;
	}

	list<INPUTSTRUCTMEM>::iterator	it = pRequestConfig->InputStructMemList.begin();
	for (; it != pRequestConfig->InputStructMemList.end(); ++ it)
	{
		INPUTSTRUCTMEM	*pInputStructMem = &(*it);
		if (0 == strcmp(szMemName, pInputStructMem->szName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 查找存储过程参数是否存在
BOOL CRequestConfig::FindSPParam(REQUESTCONFIG *pRequestConfig, LPSTR szParamName)
{
	if (NULL == pRequestConfig || NULL == szParamName)
	{
		return FALSE;
	}

	list<SPPARAM>::iterator	it = pRequestConfig->SPParamList.begin();
	for (; it != pRequestConfig->SPParamList.end(); ++ it)
	{
		SPPARAM	*pSPParam = &(*it);
		if (0 == strcmp(szParamName, pSPParam->szName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 查找存储过程参数中是否存在返回值
BOOL CRequestConfig::FindSPReturn(REQUESTCONFIG *pRequestConfig)
{
	if (NULL == pRequestConfig)
	{
		return FALSE;
	}

	list<SPPARAM>::iterator	it = pRequestConfig->SPParamList.begin();
	for (; it != pRequestConfig->SPParamList.end(); ++ it)
	{
		SPPARAM	*pSPParam = &(*it);
		if (adParamReturnValue == pSPParam->nDirection)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 通过类型名获取DB参数类型值
s32 CRequestConfig::GetDBType(LPSTR szType)
{
	if (NULL == szType)
	{
		return -1;
	}

	if (0 == strcmp(szType, "tinyint"))
	{
		return adTinyInt;
	}
	else if (0 == strcmp(szType, "smallint"))
	{
		return adSmallInt;
	}
	else if(0 == strcmp(szType, "int"))
	{
		return adInteger;
	}
	else if (0 == strcmp(szType, "bigint"))
	{
		return adBigInt;
	}
	else if(0 == strcmp(szType, "float"))
	{
		return adDouble;
	}
	else if (0 == strcmp(szType, "char"))
	{
		return adChar;
	}
	else if (0 == strcmp(szType, "varchar"))
	{
		return adVarChar;
	}
	else if (0 == strcmp(szType, "binary"))
	{
		return adBinary;
	}
	else if (0 == strcmp(szType, "varbinary"))
	{
		return adVarBinary;
	}
	else if (0 == strcmp(szType, "blob"))
	{
		return adVarBinary;
	}

	return -1;
}

// 通过方向名获取DB参数方向值
s32 CRequestConfig::GetDBDirection(LPSTR szDirection)
{
	if (NULL == szDirection)
	{
		return -1;
	}

	if (0 == strcmp(szDirection, "input"))
	{
		return adParamInput;
	}
	else if (0 == strcmp(szDirection, "output"))
	{
		return adParamOutput;
	}
	else if (0 == strcmp(szDirection, "inputoutput"))
	{
		return adParamInputOutput;
	}
	else if (0 == strcmp(szDirection, "return"))
	{
		return adParamReturnValue;
	}

	return -1;
}

// 通过来源名获取数据来源值
s32 CRequestConfig::GetDataSource(LPSTR szSource)
{
	if (NULL == szSource)
	{
		return -1;
	}

	if (0 == strcmp(szSource, "struct"))
	{
		return DS_INPUTSTRUCT;
	}
	else if (0 == strcmp(szSource, "sp"))
	{
		return DS_STOREPROCEDURE;
	}
	else if (0 == strcmp(szSource, "rdset"))
	{
		return DS_RECORDSET;
	}

	return -1;
}

