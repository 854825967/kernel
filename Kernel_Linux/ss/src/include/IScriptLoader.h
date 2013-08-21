/*******************************************************************
** 文件名:	ScriptLoader.h
** 版  权:	(C) 
** 创建人:	
** 日  期:	
** 版  本:	1.0
** 描  述:	CSV脚本 文件加载器
** 应  用:  支持在线刷新脚本

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef _ISCRIPTLOADER_H_
#define _ISCRIPTLOADER_H_

#include <stdlib.h>

#include "GameSys.h"

// #pragma warning(disable : 4355) 

#ifndef ASSERT
#	ifdef _DEBUG
#		define ASSERT(expr)	{if (!(expr))__asm int 3}
#	else
#		define ASSERT(expr)	 ((void*)0)
#	endif
#endif

#ifndef TIXML_USE_STL
	#define TIXML_USE_STL
#endif //TIXML_USE_STL
/*
#ifdef _DEBUG
#pragma comment (lib,"tinyxmld_STL.lib")
#else
#pragma comment (lib,"tinyxml_STL.lib")
#endif
*/

/*******************************************************************
使用方法

具体指针自己获取
ICSVIterator* pit = //CScriptAdapterCSV::GetScriptIterator(void);

CVariant table(pit);
int n = table.Bound();
for(int i = 2; i < table.Bound(); i++)
{
	LPCSTR s= table[i]["ddd"];
}
********************************************************************/

struct ICSVIterator; 


// 复合变量类型
struct _VARIANT
{
	enum _TYPE_
	{
		enType_EMPTY = 0,
		enType_LONG,		// 支持整型数据
		enType_FLOAT,		// 支持浮点数据
		enType_STRING,		// 支持字符数据
		enType_ITERATOR,	// 支持多维脚本
		enType_MAX,

	} m_Type; // 数据类型

	union _VALUE_
	{
		int	lValue;			// 可能是整型类型
		double	dValue;			// 可能是浮点类型
		LPCSTR	str;			// 可能是字符串类型
		ICSVIterator	*it;	// 可能是子脚本, 用来实现任意多维的脚本

	} m_Data;
};


// CSV脚本迭代器用来实现脚本类型无关性
struct ICSVIterator
{
  virtual ~ICSVIterator() {}
	//  释放资源
	virtual void Release(void) = 0;

	// 获取数据的个数
	virtual int Size(void) const = 0;

	// 获取数据
	virtual _VARIANT& GetData(int nIndex) = 0;
	virtual _VARIANT& operator [](int nIndex) = 0;
	virtual _VARIANT& GetData(LPCSTR szName) = 0;
	virtual _VARIANT& operator [](LPCSTR szName) = 0;
};



// 使复合类型支持更多操作符，方便使用
class CVariant : protected _VARIANT
{
public:
	CVariant() : m_variant(*((_VARIANT *)this))
	{
		m_variant.m_Type = enType_EMPTY;
		m_variant.m_Data.dValue = 0;
	}

	CVariant(char *str) : m_variant(*((_VARIANT *)this))
	{
		m_variant.m_Type = enType_STRING;
		m_variant.m_Data.str = str;
	}

	CVariant(int lValue) : m_variant(*((_VARIANT *)this))
	{
		m_variant.m_Type = enType_LONG;
		m_variant.m_Data.lValue = lValue;
	}

	CVariant(double dValue) : m_variant(*((_VARIANT *)this))
	{
		m_variant.m_Type = enType_FLOAT;
		m_variant.m_Data.dValue = dValue;
	}

	CVariant(ICSVIterator *it) : m_variant(*((_VARIANT *)this))
	{
		m_variant.m_Type = enType_ITERATOR;
		m_variant.m_Data.it = it;
	}

	CVariant(_VARIANT &value) : m_variant(value)
	{
	}

	CVariant operator[](int nIndex)
	{
		ASSERT(m_variant.m_Type == enType_ITERATOR);
		return (*m_variant.m_Data.it)[nIndex];
	}

	CVariant operator[](LPCSTR szName)
	{
		ASSERT(m_variant.m_Type == enType_ITERATOR);
		return (*m_variant.m_Data.it)[szName];
	}

	int Bound()
	{
		ASSERT(m_variant.m_Type == enType_ITERATOR);
		return m_variant.m_Data.it->Size();
	}

	operator LPCSTR()
	{
		if (m_variant.m_Type != enType_STRING)
		{
			ChangeType(enType_STRING);
		}

		return m_variant.m_Data.str;
	}

	operator int()
	{
		if (m_variant.m_Type != enType_LONG)
		{
			ChangeType(enType_LONG);
		}

		return m_variant.m_Data.lValue;
	}

	operator double()
	{
		if (m_variant.m_Type != enType_FLOAT)
		{
			ChangeType(enType_FLOAT);
		}

		return m_variant.m_Data.dValue;
	}

	typedef void (CVariant::*CHANGETYPEPOC)();

	// 转换类型
	void ChangeType(_TYPE_ type)
	{
		static CHANGETYPEPOC s_change_poc[enType_MAX][enType_MAX] =
		{
			{NULL, NULL, NULL, NULL, NULL},
			{NULL, NULL, &CVariant::ChangeType_long2float, NULL, NULL},
			{NULL, &CVariant::ChangeType_float2long, NULL, NULL, NULL},
			{NULL, &CVariant::ChangeType_str2long, &CVariant::ChangeType_str2float, NULL, NULL},
			{NULL, NULL, NULL, NULL, NULL}
		};

		if (s_change_poc[m_variant.m_Type][type] != NULL)
		{
			(this->*s_change_poc[m_variant.m_Type][type])();
		}
	}

	// int -> float
	void ChangeType_long2float()
	{
		m_variant.m_Data.dValue = m_variant.m_Data.lValue;
		m_variant.m_Type = enType_FLOAT;
	}

	// float -> int
	void ChangeType_float2long()
	{
		m_variant.m_Data.lValue = (int)m_variant.m_Data.dValue;
		m_variant.m_Type = enType_LONG;
	}

	// str -> int
	void ChangeType_str2long()
	{
		int lTemp = 0;
		lTemp = atoi(m_variant.m_Data.str);
		m_variant.m_Data.lValue = lTemp;
		m_variant.m_Type = enType_LONG;
	}

	// str -> float
	void ChangeType_str2float()
	{
		float dTemp = 0.0;
		dTemp =(float) atof(m_variant.m_Data.str);
		m_variant.m_Data.dValue = dTemp;
		m_variant.m_Type = enType_FLOAT;
	}
	_TYPE_ GetDataType()
	{
		return m_variant.m_Type;
	}

public:
	_VARIANT	&m_variant;	// 变量

};


class TiXmlDocument;
 // 文件加载回调
struct IScriptLoadSink
{
  virtual ~IScriptLoadSink() {}
	// 文件加载 
	// 参数： FilePointer 文件数据指针
	virtual BOOL OnFileLoad(LPCSTR szFile, ICSVIterator *pFilePointer, TiXmlDocument *pTiXmlDocument) = 0;

	// 文件更新
	// 参数： FilePointer 文件数据指针  
	virtual BOOL OnFileUpdate(LPCSTR szFile, ICSVIterator *pFilePointer, TiXmlDocument *pTiXmlDocument) = 0;

};

struct IScriptLoader  
{
  virtual ~IScriptLoader() {}
	//////////////////////////////////////////////////////////////////////////
	// 功能： 释放资源
	virtual void Release() = 0;

	//////////////////////////////////////////////////////////////////////////
	// 功能: 加载一个文件(具有回调功能)
	// (*注意) 只有当你需要 您的程序具有 《脚本刷新》 功能的时候 才使用该函数 
	// 加载一个XML CSV获取其他的格式文件 通过回调获取文件数据指针
	// 回调时获取的文件数据指针 不需要释放 ，这个函数内部处理了
	// 参数 : LPCSTR szFileName			-----文件名
	//		  IFileLoadSink *pSikn		-----文件加载后的回调指针，你的必须要实现该方法
	virtual BOOL LoadFile(LPCSTR szFileName, IScriptLoadSink *pSikn) = FALSE;

	// 当需要刷脚本功能的时候 使用这个函数 
	// （*） 回调时获取的文件数据指针 不需要释放 ，这个函数内部处理了
	virtual BOOL UpdateFile(LPCSTR szFileName) = FALSE;


	// 获取CSV脚本文件的迭代器
	virtual ICSVIterator* LoadCSVFile(LPCSTR szFileName,BOOL bEncrypt = FALSE) = 0;
	virtual ICSVIterator* LoadCSVFile(LPCSTR szFileName,LPCSTR lpBuffData,int nLen) = 0;


	// 加载XML 文件自己释放啊
	virtual TiXmlDocument *LoadXmlFile(LPCSTR szFileName,BOOL bEncrypt = FALSE) = 0;
	virtual TiXmlDocument *LoadXmlFile(LPCSTR szFileName,LPCSTR lpBuffData,int nLen) = 0;
 

};


#endif //_ISCRIPTLOADER_H_
