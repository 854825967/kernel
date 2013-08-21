/*****************************************************************************
模块名      : 系统接口
文件名      : IOsApi.h
相关文件    : 
文件实现功能: 跨平台系统函数封装
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/
#ifndef __IOSAPI_H__
#define __IOSAPI_H__

#include <dlfcn.h>

#include <iostream>

#include "GameSys.h"

class CDynamicLoader
{
public:
	// 构造函数
	CDynamicLoader()
	{
		m_hDll = NULL;
	}

	// 析构函数
	~CDynamicLoader()
	{
		if( NULL != m_hDll )
		{
			FreeLibrary();
		}
	}

	// 加载动态库
	BOOL LoadLibrary(LPCSTR lpszDllName)
	{
#ifdef WIN32
		m_hDll = ::LoadLibrary(lpszDllName);
#else
		m_hDll = ::dlopen(lpszDllName,RTLD_LAZY);
#endif
		if (NULL == m_hDll)
		{
#ifndef WIN32
			std::cout << dlerror() << std::endl;
#endif
			return FALSE;
		}
		return TRUE;
	}

	// 获取导出函数地址
	void* GetProcAddress(LPCSTR lpszFuncName)
	{
		if( NULL == m_hDll)
		{
			return NULL;
		}
		void* pFun = NULL;
#ifdef WIN32
		pFun = ::GetProcAddress(m_hDll, lpszFuncName);
#else
		pFun = ::dlsym(m_hDll,lpszFuncName);
#endif
		return pFun;
	}

	// 释放动态库
	void FreeLibrary()
	{
		if (m_hDll != NULL)
		{
#ifdef WIN32
			::FreeLibrary(m_hDll);
#else
			::dlclose(m_hDll);
#endif
			m_hDll = NULL;
		}
	}

private:
#ifdef WIN32
	HINSTANCE	m_hDll;		// 动态库句柄
#else
	void*		m_hDll;		// 动态库句柄
#endif
};


#endif// __IOSAPI_H__
