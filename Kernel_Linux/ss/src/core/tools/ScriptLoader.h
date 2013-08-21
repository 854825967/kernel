/*****************************************************************************
模块名      : xml、CSV文件加载器
文件名      : ScriptLoader.h
相关文件    : 
文件实现功能: 封装xml、CSV加载的功能
作者        : 庄雪锋
版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/29  0.1         庄雪锋      创建
******************************************************************************/

#ifndef __ISCRIPTLOADER_H__
#define __ISCRIPTLOADER_H__

#include <map>
#include <list>
#include <string>

#include "include/IScriptLoader.h"
#include "include/GameType.h"
#include "include/GameSys.h"
#include "core/tinyxml/tinyxml.h"


class CScriptLoader : public IScriptLoader
{
	struct stFileSkin			// 文件回调
	{
		char			strFileName[MAX_PATH];		// 文件名字
		std::list<IScriptLoadSink *> sinkList;				// 回调处理列表

		stFileSkin()
		{
			memset(strFileName,0,sizeof(strFileName));			
			sinkList.clear();
		}
	};
	
	//typedef map<char *, stFileSkin>				FILESKINLIST;
	typedef std::map<std::string, stFileSkin>				FILESKINLIST;
	static CScriptLoader* _instance;		// 

public:
	CScriptLoader();
	virtual ~CScriptLoader();

	static CScriptLoader*	GetInstance();

	virtual  void Release();

	// 加载一个XML CSV获取其他的格式文件 通过回调获取文件数据指针
	// 当需要刷脚本功能的时候 使用这个函数 
	// （*） 回调时获取的文件数据指针 不需要释放 ，这个函数内部处理了
	virtual BOOL LoadFile(LPCSTR szFileName, IScriptLoadSink *pSikn);

	// 当需要刷脚本功能的时候 使用这个函数 
	// （*） 回调时获取的文件数据指针 不需要释放 ，这个函数内部处理了
	virtual BOOL UpdateFile(LPCSTR szFileName);

	// 获取CSV脚本文件的迭代器
	virtual ICSVIterator* LoadCSVFile(LPCSTR szFileName,BOOL bEncrypt = FALSE);
	virtual ICSVIterator* LoadCSVFile(LPCSTR szFileName,LPCSTR lpBuffData,int nLen);

 	// 加载INI 文件 获取INI对象 
	//virtual ISIni *LoadIniFile(LPCSTR szFileName);

	// 加载XML 文件自己释放啊
	virtual TiXmlDocument *LoadXmlFile(LPCSTR szFileName,BOOL bEncrypt = FALSE);

	virtual TiXmlDocument *LoadXmlFile(LPCSTR szFileName,LPCSTR lpBuffData,int nLen);

private:

	// 描  述：注册脚本回调接口
	// 参  数：[输入] LPCSTR szFile - 更新脚本文件名
	// 参  数：[输入] IScriptUpdateSink * pSink - 脚本更新回调接口
	void RegisterSink(LPCSTR szFile, IScriptLoadSink *pSink);

	// 描  述：取消注册脚本回调接口
	// 参  数：[输入] LPCSTR szFile - 更新脚本文件名
	// 参  数：[输入] IScriptUpdateSink * pSink - 脚本更新回调接口
	void UnRegisterSink(LPCSTR szFile, IScriptLoadSink *pSink);

	// 描  述：获得绝对路径
	// 参  数：[输入] LPCSTR szFile - 更新脚本文件名
	// 参  数：[输入] char *szPath  - Buf
	// 参  数：[输入] int nSize		- Buf大小
	// 返回值：Buf
	char* GetAbsolutePath(LPCSTR szFile, char *szPath, int nSize);

private:
	FILESKINLIST		m_vFileList;	//  文件回调

};
#endif// __ISCRIPTLOADER_H__
