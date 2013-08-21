/*******************************************************************
** 文件名:	SingletonFactory.cpp
** 版  权:	
** 创建人:	
** 日  期:	2011/09/27
** 版  本:	1.0
** 描  述:	单件工厂模板
** 应  用:  	
	
**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef _SINGLETONFACTORY_H__
#define _SINGLETONFACTORY_H__

#include <stddef.h>

/// 单件工厂模板类（new出对象版本），继承使用
template <typename _T>
class SingletonFactory
{
public:
	SingletonFactory() {};
	~SingletonFactory() {};

public:
	/// 得到唯一实例
	static _T* GetInstance()
	{
		if(!g_Instance)
		{
			g_Instance = new _T;
		}
		return g_Instance;
	}

	/// 释放
	static void ReleaseInstance()
	{
		if(g_Instance)
		{
			delete g_Instance;
			g_Instance = NULL;
		}
	}

private:
	static _T* g_Instance;		/// 唯一实例
};

template <typename _T>
_T* SingletonFactory<_T>::g_Instance;

#endif	// _SINGLETONFACTORY_H__
