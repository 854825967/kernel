/*****************************************************************************
模块名      : 文本方式读取文件类
文件名      : DBMemTextFile.h
相关文件    : 
文件实现功能: 封装文本文件读取文件等功能
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/
#ifndef _DBMemTextFile_H__
#define _DBMemTextFile_H__

#include "include/GameSys.h"

class CDBMemTextFile
{
public:
	CDBMemTextFile() : m_pBuffer(NULL), m_nBufSize(0), m_nFileSize(0), m_pPos(NULL) {}
	~CDBMemTextFile();

	BOOL IsEnd()							{return m_pPos - m_pBuffer >= m_nFileSize;}
	BOOL Open(LPCSTR szFileName);
	BOOL Open(LPCSTR lpBuff,int nLen);

	BOOL Save(LPCSTR szFileName);
	char* GetLine(char* pString, int nSize);
	
	//protected:
	BOOL MakeSimpleMap(BYTE* buf, int nLen);
	void MakeSimpleMap2(BYTE* buf, const char *szKey);

protected:
	char*	m_pBuffer;		// 内存文件缓存，保存了解密后的文本文件内容
	int		m_nBufSize;		// 缓存尺寸
	int		m_nFileSize;	// 文件尺寸
	char*	m_pPos;			// 文件指针位置，用于GetLine的操作

};

#endif // _DBMemTextFile_H__
