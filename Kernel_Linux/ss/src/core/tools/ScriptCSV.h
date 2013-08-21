/*****************************************************************************
模块名      : CSV文件
文件名      : ScriptCSV.h
相关文件    : 
文件实现功能: 封装适配CSV格式的功能
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/
#ifndef __SCRIPTADAPTERCSV_H__
#define __SCRIPTADAPTERCSV_H__

#include <string>
#include <vector>

#include "include/GameType.h"
#include "include/IScriptLoader.h"
#include "core/tools/MemTextFile.h"

class CScriptAdapterCSV;

enum
{
	enMax_Line_Len = 1024 * 8,	// 一行最大字节数
	enMax_Segment_Count = 1024,	// 一行最大数据个数
};

// CSV行数据类
class CScriptAdapterCSVRow : public ICSVIterator
{
public:
	// 构造函数
	CScriptAdapterCSVRow();
	// 析构函数
	~CScriptAdapterCSVRow();

	// 初始化数据
	// cSeparator: 分隔符
	// bAllowSeries: 是否允许连续出现
	BOOL InitData(CScriptAdapterCSV *pScript,
		char *line, char cSeparator, BOOL bAllowSeries);

	// 释放迭代器
	virtual void Release(void);

	// 获取数据的个数
	virtual int Size() const;

	// 获取数据
	virtual _VARIANT& GetData(int nIndex);
	virtual _VARIANT& operator [](int nIndex);
	virtual _VARIANT& GetData(LPCSTR szName);
	virtual _VARIANT& operator [](LPCSTR szName);

private:
	_VARIANT			*m_pData;		// 数据列表指针
	int					m_nSize;		// 数据个数
	CScriptAdapterCSV	*m_pScript;		// CVS适配器指针
	char				*m_pLine;		// 数据内容指针

};


// CSV适配器
class CScriptAdapterCSV : public ICSVIterator
{
public:
	// 构造函数
	CScriptAdapterCSV();
	// 析构函数
	~CScriptAdapterCSV();

	// 装载脚本
	virtual BOOL LoadScript(LPCSTR szFile, BOOL bEncrypt);

	BOOL LoadBuffScript(LPCSTR lpBuffData,int nLen);
	// 获取脚本迭代器
	virtual ICSVIterator* GetScriptIterator(void);

	// 释放迭代器
	virtual void Release(void);
	
	// 获取数据的个数
	virtual int Size() const;
	
	// 获取数据
	virtual _VARIANT& GetData(int nIndex);
	virtual _VARIANT& operator [](int nIndex);
	virtual _VARIANT& GetData(LPCSTR szName);
	virtual _VARIANT& operator [](LPCSTR szName);

	// 根据参数名字查找参数在第几列
	int FindPropName(LPCSTR szName);

private:
	// 根据参数名字查找对象在第几行
	int FindObjectName(LPCSTR szName);

	// 加载CSV脚本
	BOOL LoadScriptCSV(LPCSTR szFile);
	// 加载CSE脚本
	BOOL LoadScriptCSE(LPCSTR szFile);

private:
	std::vector<_VARIANT>		m_RowTable;	// 行列表
	int						m_nSize;	// 行数
	std::vector<std::string>			m_ObjectNameTable;	// 行名，取第一列名字
	CScriptAdapterCSVRow	m_title;	// 标题

};
// 空变量
extern _VARIANT			empty_variant;
#endif //__SCRIPTADAPTERCSV_H__

