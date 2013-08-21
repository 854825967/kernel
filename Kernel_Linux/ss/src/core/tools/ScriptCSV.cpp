
#include <string.h>

#include "ScriptCSV.h"

// 空变量
_VARIANT empty_variant = {_VARIANT::enType_EMPTY, {0}};

// 安全释放宏
#ifndef SAFE_RELEASE
#define	SAFE_RELEASE(p)	{ if ((p) != NULL) { (p)->Release(); (p) = NULL; } }
#endif

// 构造函数
CScriptAdapterCSVRow::CScriptAdapterCSVRow()
{
	m_pData = NULL;
	m_nSize = 0;
	m_pScript = NULL;
	m_pLine = NULL;
}

// 析构函数
CScriptAdapterCSVRow::~CScriptAdapterCSVRow()
{
	if (m_pData != NULL)
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	
	if (m_pLine != NULL)
	{
		delete [] m_pLine;
		m_pLine = NULL;
	}
	
	m_nSize = 0;
	m_pScript = NULL;
}

// 初始化数据
// cSeparator: 分隔符
// bAllowSeries: 是否允许连续出现
BOOL CScriptAdapterCSVRow::InitData(CScriptAdapterCSV *pScript,
			char *line, char cSeparator, BOOL bAllowSeries)
{
	if (line == NULL)
	{
		return FALSE;
	}

	int		nLineLen = 0;
	int		nPosTemp[enMax_Segment_Count] = {0};
	char	c = line[nLineLen++];
	BOOL	bRecord = TRUE;

	while (c != 0 && c != '\r' && c != '\n')
	{
		// 如果遇到分隔符
		if (c == cSeparator)
		{
			line[nLineLen - 1] = 0;
			
			if (bAllowSeries) // 允许连续出现，类似','分隔
			{
				if (bRecord)
				{
					nPosTemp[m_nSize++] = nLineLen - 1;
				}
				else
				{
					bRecord = TRUE;
				}
			}
			else // 不允许连续出现，类似' '分隔
			{
				bRecord = TRUE;
			}
		}
		// 如果不是分隔符
		else
		{
			// 开始记录一个数据
			if (TRUE == bRecord)
			{
				nPosTemp[m_nSize++] = nLineLen - 1;
				bRecord = FALSE;
			}
		}

		c = line[nLineLen++];
		if (m_nSize >= enMax_Segment_Count)
		{
			break;
		}
	}

	line[nLineLen - 1] = 0;

	m_pLine = new char[nLineLen];
	m_pData = new _VARIANT[m_nSize];
	if (NULL == m_pLine || NULL == m_pData)
	{
		return FALSE;
	}

	memcpy(m_pLine, line, nLineLen);
	for (int i = 0; i < m_nSize; i++)
	{
		m_pData[i].m_Type = _VARIANT::enType_STRING;
		m_pData[i].m_Data.str = &m_pLine[nPosTemp[i]];
	}
	
	m_pScript = pScript;

	return TRUE;
}

// 释放迭代器
void CScriptAdapterCSVRow::Release(void)
{
	delete this;
}

// 获取数据个数
int CScriptAdapterCSVRow::Size() const
{
	return m_nSize;
}

// 获取数据
_VARIANT& CScriptAdapterCSVRow::GetData(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		return empty_variant;
	}

	return m_pData[nIndex];
}

// 获取数据
_VARIANT& CScriptAdapterCSVRow::operator [](int nIndex)
{
	return GetData(nIndex);
}

// 获取数据
_VARIANT& CScriptAdapterCSVRow::GetData(LPCSTR szName)
{
	int nIndex = m_pScript->FindPropName(szName);
	return GetData(nIndex);
}

// 获取数据
_VARIANT& CScriptAdapterCSVRow::operator [](LPCSTR szName)
{
	return GetData(szName);
}


// 构造函数
CScriptAdapterCSV::CScriptAdapterCSV()
{
	m_nSize = 0;
}

// 析构函数
CScriptAdapterCSV::~CScriptAdapterCSV()
{
	for (int i = 0; i < m_nSize; i++)
	{
		if (m_RowTable[i].m_Type == _VARIANT::enType_ITERATOR)
		{
			if (m_RowTable[i].m_Data.it != NULL)
			{
				m_RowTable[i].m_Data.it->Release();
				m_RowTable[i].m_Data.it = NULL;
			}
		}
	}

	m_nSize = 0;
}

// 装载脚本
BOOL CScriptAdapterCSV::LoadScript(LPCSTR szFile, BOOL bEncrypt)
{
	if (TRUE == bEncrypt)
	{
		return LoadScriptCSE(szFile);
	}

	return LoadScriptCSV(szFile);
}

// 获取脚本迭代器
ICSVIterator* CScriptAdapterCSV::GetScriptIterator(void)
{
	return static_cast<ICSVIterator *>(this);
}

// 释放迭代器
void CScriptAdapterCSV::Release(void)
{
	delete this;
}

// 获取数据的个数
int CScriptAdapterCSV::Size() const
{
	return m_nSize;
}

// 获取数据
_VARIANT& CScriptAdapterCSV::GetData(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		return empty_variant;
	}

	return m_RowTable[nIndex];
}

// 获取数据
_VARIANT& CScriptAdapterCSV::operator [](int nIndex)
{
	return GetData(nIndex);
}

// 获取数据
_VARIANT& CScriptAdapterCSV::GetData(LPCSTR szName)
{
	int nIndex = FindObjectName(szName);
	return GetData(nIndex);
}

// 获取数据
_VARIANT& CScriptAdapterCSV::operator [](LPCSTR szName)
{
	return GetData(szName);
}

// 根据参数名字查找参数在第几列
int CScriptAdapterCSV::FindPropName(LPCSTR szName)
{
	for (int i = 0; i < m_title.Size(); i++)
	{
		//if (_stricmp(m_title[i].m_Data.str, szName) == 0)
		if(strcmp(m_title[i].m_Data.str, szName) == 0)
		{
			return i;
		}
	}

	return -1;
}

// 根据参数名字查找对象在第几行
int CScriptAdapterCSV::FindObjectName(LPCSTR szName)
{
	int nReturn = 0;
	std::vector<std::string>::iterator it = m_ObjectNameTable.begin();
	for (; it != m_ObjectNameTable.end(); ++it)
	{
		//if (_stricmp((*it).c_str(), szName) == 0)
		if (strcmp((*it).c_str(), szName) == 0)
		{
			return nReturn;
		}
		else 
		{
			nReturn ++;
		}
	}

	return -1;
}

// 加载CSV脚本
BOOL CScriptAdapterCSV::LoadScriptCSV(LPCSTR szFile)
{
	char line[enMax_Line_Len] = {0};

	FILE *stream = fopen(szFile, "r");
	if (NULL == stream)
	{
		return FALSE;
	}
	
	// 读取标题
	if (fgets(line, enMax_Line_Len, stream) == NULL)
	{
		fclose(stream);
		return FALSE;
	}
	
	// 确定是用什么符号分隔的
	char cSeparator = ' ';
	BOOL bAllowSeries = FALSE;
	for (int i = 0; line[i] != 0 && line[i] != '\r'; i++)
	{
		if (line[i] == ',')
		{
			cSeparator = ',';		// 逗号分隔符
			bAllowSeries = TRUE;	// 允许连续出现
			break;
		}
	}
	
	// 装载标题数据
	if (FALSE == m_title.InitData(this, line, cSeparator, bAllowSeries))
	{
		fclose(stream);
		return FALSE;
	}
	
	// 装载其他数据
	while (fgets(line, enMax_Line_Len, stream) != NULL)
	{
		CScriptAdapterCSVRow *pRow = new CScriptAdapterCSVRow;
		if (NULL == pRow
			|| FALSE == pRow->InitData(this, line, cSeparator, bAllowSeries))
		{
			SAFE_RELEASE(pRow);
			fclose(stream);
			return FALSE;
		}
		
		if (pRow->Size() <= 0)
		{
			SAFE_RELEASE(pRow);
			continue;
		}
		
		_VARIANT data;
		data.m_Type = _VARIANT::enType_ITERATOR;
		data.m_Data.it = pRow;
		m_RowTable.push_back(data);
		m_ObjectNameTable.push_back(pRow->GetData(0).m_Data.str);
	}
	
	m_nSize = m_RowTable.size();
	
	fclose(stream);
	
	return TRUE;
}
BOOL CScriptAdapterCSV::LoadBuffScript(LPCSTR lpBuffData,int nLen)
{
	CMemTextFile stream;
 	if (FALSE == stream.Open(lpBuffData,nLen))
 	{
 		return FALSE;
 	}
	char line[enMax_Line_Len] = {0};

	// 读取标题，注意这里对应的是列标题
	if (stream.GetLine(line, enMax_Line_Len) == NULL)
	{
		return FALSE;
	}

	// 确定是用什么符号分隔的
	char cSeparator = ' ';
	BOOL bAllowSeries = FALSE;
	for (int i = 0; line[i] != 0 && line[i] != '\r'; i++)
	{
		if (line[i] == ',')
		{
			cSeparator = ',';		// 逗号分隔符
			bAllowSeries = TRUE;	// 允许连续出现
			break;
		}
	}

	// 装载标题数据
	if (FALSE == m_title.InitData(this, line, cSeparator, bAllowSeries))
	{
		return FALSE;
	}

	// 读其他所有行
	while (FALSE == stream.IsEnd())
	{
		if (stream.GetLine(line, enMax_Line_Len) == NULL)
		{
			continue;
		}

		CScriptAdapterCSVRow *pRow = new CScriptAdapterCSVRow;
		if (pRow == NULL
			|| FALSE == pRow->InitData(this, line, cSeparator, bAllowSeries))
		{
			SAFE_RELEASE(pRow);
			return FALSE;
		}

		if (pRow->Size() <= 0)
		{
			SAFE_RELEASE(pRow);
			continue;
		}

		_VARIANT data;
		data.m_Type = _VARIANT::enType_ITERATOR;
		data.m_Data.it = pRow;
		m_RowTable.push_back(data);
		m_ObjectNameTable.push_back(pRow->GetData(0).m_Data.str);
	}

	m_nSize = m_RowTable.size();

	return TRUE; 
}

// 加载CSE脚本
BOOL CScriptAdapterCSV::LoadScriptCSE(LPCSTR szFile)
{
 	char line[enMax_Line_Len] = {0};
 
 	// 读文件
 	CMemTextFile stream;
 	if (FALSE == stream.Open(szFile))
 	{
 		return FALSE;
 	}
 
 	// 读取标题，注意这里对应的是列标题
 	if (stream.GetLine(line, enMax_Line_Len) == NULL)
 	{
 		return FALSE;
 	}
 
 	// 确定是用什么符号分隔的
 	char cSeparator = ' ';
 	BOOL bAllowSeries = FALSE;
 	for (int i = 0; line[i] != 0 && line[i] != '\r'; i++)
 	{
 		if (line[i] == ',')
 		{
 			cSeparator = ',';		// 逗号分隔符
 			bAllowSeries = TRUE;	// 允许连续出现
 			break;
 		}
 	}
 	
 	// 装载标题数据
 	if (FALSE == m_title.InitData(this, line, cSeparator, bAllowSeries))
 	{
 		return FALSE;
 	}
 
 	// 读其他所有行
 	while (FALSE == stream.IsEnd())
 	{
 		if (stream.GetLine(line, enMax_Line_Len) == NULL)
 		{
 			continue;
 		}
 
 		CScriptAdapterCSVRow *pRow = new CScriptAdapterCSVRow;
 		if (pRow == NULL
 			|| FALSE == pRow->InitData(this, line, cSeparator, bAllowSeries))
 		{
 			SAFE_RELEASE(pRow);
 			return FALSE;
 		}
 
 		if (pRow->Size() <= 0)
 		{
 			SAFE_RELEASE(pRow);
 			continue;
 		}
 
 		_VARIANT data;
 		data.m_Type = _VARIANT::enType_ITERATOR;
 		data.m_Data.it = pRow;
 		m_RowTable.push_back(data);
 		m_ObjectNameTable.push_back(pRow->GetData(0).m_Data.str);
 	}
 
 	m_nSize = m_RowTable.size();

	return TRUE;
}
