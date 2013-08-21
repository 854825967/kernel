#include "core/tools/ScriptLoader.h"

#include <string.h>

#include "core/base/common.h"
#include "core/tools/ScriptCSV.h" 


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CScriptLoader* CScriptLoader::_instance = NULL;

CScriptLoader::CScriptLoader()
{
	CScriptLoader::_instance = this;
}

CScriptLoader::~CScriptLoader()
{
	m_vFileList.clear();
}

// 加载一个XML CSV获取其他的格式文件
BOOL CScriptLoader::LoadFile(LPCSTR szFileName, IScriptLoadSink *pSikn = NULL)
{
	char filename[1024];
	memset(filename,0,sizeof(filename));
	strncpy(filename,szFileName,sizeof(filename));

/*
	char *tmp = (char *)filename;
	while(*tmp)
	{
		if(*tmp == '/')
		{
			*tmp= '\\';
		}
		tmp++;
	}
*/
	int nLen = strlen(filename);
	if (nLen < 3)
	{
		return FALSE;
	}
	

	RegisterSink(filename,pSikn);
/*
	char szPath[MAX_PATH] = {0};
	if (NULL == GetAbsolutePath(filename, szPath, MAX_PATH))
	{
		return FALSE;
	}

	FILESKINLIST::iterator it = m_vFileList.find(szPath);
*/
	FILESKINLIST::iterator it = m_vFileList.find(filename);
	if (it == m_vFileList.end())
	{
		return FALSE;
	}

	// 取出扩展名
	LPCSTR pExternName = filename + nLen - 3;
	BOOL Flg = FALSE;
 	ICSVIterator *pCsvit= NULL;
	TiXmlDocument tixmldocument;
	int nFileType = 0;

	if (strcmp(pExternName, "csv") == 0)
	{
		pCsvit= LoadCSVFile(filename,FALSE);
		if (pCsvit == NULL)
		{
			UnRegisterSink(filename,pSikn);
			return FALSE;
		}
		nFileType = 1;
 		Flg = TRUE;	
	}
	else if (strcmp(pExternName, "wcv") == 0)
	{
		pCsvit= LoadCSVFile(filename,TRUE);
		if (pCsvit == NULL)
		{
			UnRegisterSink(filename,pSikn);
			return FALSE;
		}
		nFileType = 1;
		Flg = TRUE;	
	}
	else if (strcmp(pExternName, "xml") == 0)
	{
		if(!tixmldocument.LoadFile(filename))
		{
			UnRegisterSink(filename,pSikn);
			return FALSE;
		}

		if (tixmldocument.ErrorId() > 0)
		{
			UnRegisterSink(filename,pSikn);
			return FALSE;
		}
		nFileType = 2;
		Flg = TRUE;	
	}

	if (!Flg)
	{
		UnRegisterSink(filename,pSikn);
		return FALSE;
	}
 
	stFileSkin &info = (*it).second;

	BOOL bSucceed = TRUE;
	std::list<IScriptLoadSink*>::iterator itList = info.sinkList.begin();
	for (; itList != info.sinkList.end(); ++itList)
	{
		IScriptLoadSink *pSink = *itList;
		if (pSink != NULL)
		{
			try
			{
				if (nFileType == 1)
				{
					if (FALSE == pSink->OnFileLoad(szFileName,pCsvit,NULL))
					{
						bSucceed = FALSE;
						break;
					}
				}
				else
				{
					if (FALSE == pSink->OnFileLoad(szFileName,NULL,&tixmldocument))
					{
						bSucceed = FALSE;
						break;
					}

				}
				
			}
			catch (...)
			{
				bSucceed = FALSE;
			}
		}
	}
	
	if (pCsvit != NULL)
	{
		pCsvit->Release();
		pCsvit = NULL;
	} 
	return bSucceed;
}

BOOL CScriptLoader::UpdateFile(LPCSTR szFileName)
{
	char filename[1024];
	memset(filename,0,sizeof(filename));
	strncpy(filename,szFileName,sizeof(filename));

	char *tmp = (char *)filename;
	while(*tmp)
	{
		if(*tmp == '/')
		{
			*tmp= '\\';
		}
		tmp++;
	}

	int nLen = strlen(filename);
	if (nLen < 3)
	{
		return FALSE;
	}
/*
	char szPath[MAX_PATH] = {0};
	if (NULL == GetAbsolutePath(filename, szPath, MAX_PATH))
	{
		return FALSE;
	}

	FILESKINLIST::iterator it = m_vFileList.find(szPath);
*/
	FILESKINLIST::iterator it = m_vFileList.find(filename);
	if (it == m_vFileList.end())
	{
		return FALSE;
	}

	// 取出扩展名
	LPCSTR pExternName = filename + nLen - 3;
	BOOL Flg = FALSE;
 	ICSVIterator *pCsvit= NULL;
	int nFileType = 0;
	TiXmlDocument tixmldocument;

	if (strcmp(pExternName, "csv") == 0)
	{
		pCsvit= LoadCSVFile(filename);
		if (pCsvit == NULL)
		{
			return FALSE;
		}
		nFileType = 1;
 		Flg = TRUE;	
	}	
	else if (strcmp(pExternName, "xml") == 0)
	{
		tixmldocument.LoadFile(filename);
		nFileType = 2;
		Flg = TRUE;	
	}


	if (!Flg)
	{
		return FALSE;
	}
 
	stFileSkin &info = (*it).second;

	BOOL bSucceed = TRUE;
	std::list<IScriptLoadSink*>::iterator itList = info.sinkList.begin();
	for (; itList != info.sinkList.end(); ++itList)
	{
		IScriptLoadSink *pSink = *itList;
		if (pSink != NULL)
		{
			try
			{				
				if (nFileType == 1)
				{
					if (FALSE == pSink->OnFileUpdate(szFileName,pCsvit,NULL))
					{
						bSucceed = FALSE;
						break;
					}

				}
				else
				{
					if (FALSE == pSink->OnFileUpdate(szFileName,NULL,&tixmldocument))
					{
						bSucceed = FALSE;
						break;
					}
				}

			}
			catch (...)
			{
				bSucceed = FALSE;
			}
		}
	}
	
	if (pCsvit != NULL)
	{
		pCsvit->Release();
		pCsvit = NULL;
	} 

	return bSucceed;
}

ICSVIterator* CScriptLoader::LoadCSVFile(LPCSTR szFileName,BOOL bEncrypt)
{	
	CScriptAdapterCSV *pScriptAdapter = new CScriptAdapterCSV();
	if (FALSE == pScriptAdapter->LoadScript(szFileName, bEncrypt))
	{
		delete pScriptAdapter;
		return NULL;
	}

	return pScriptAdapter->GetScriptIterator();
}

ICSVIterator* CScriptLoader::LoadCSVFile(LPCSTR szFileName,LPCSTR lpBuffData,int nLen)
{	
	CScriptAdapterCSV *pScriptAdapter = new CScriptAdapterCSV();
	if (FALSE == pScriptAdapter->LoadBuffScript(lpBuffData,nLen))
	{
		delete pScriptAdapter;
		return NULL;
	}

	return pScriptAdapter->GetScriptIterator();
}

// 描  述：注册脚本回调接口
// 参  数：[输入] LPCSTR szFile - 更新脚本文件名
// 参  数：[输入] IScriptUpdateSink * pSink - 脚本更新回调接口
void CScriptLoader::RegisterSink(LPCSTR szFile, IScriptLoadSink *pSink)
{
/*
	// 获取绝对路径
	char szPath[MAX_PATH] = {0};
	if (NULL == GetAbsolutePath(szFile, szPath, MAX_PATH))
	{
		return;
	}
*/

	const char *szPath = szFile;	

	FILESKINLIST::iterator it = m_vFileList.find(szPath);
	if (it != m_vFileList.end())
	{
		// 已经存在该文件, 直接添加新的回调
		stFileSkin &info = (*it).second;
		info.sinkList.push_back(pSink);
	}
	else
	{
		// 不存在该文件, 则添加新的节点
		stFileSkin info;
		strncpy(info.strFileName, szPath, MAX_PATH);
		info.sinkList.push_back(pSink);
		m_vFileList[szPath] = info;
	}
}

// 描  述：取消注册脚本回调接口
// 参  数：[输入] LPCSTR szFile - 更新脚本文件名
// 参  数：[输入] IScriptUpdateSink * pSink - 脚本更新回调接口
void CScriptLoader::UnRegisterSink(LPCSTR szFile, IScriptLoadSink *pSink)
{
/*
	// 获取绝对路径
	char szPath[MAX_PATH] = {0};
	if (NULL == GetAbsolutePath(szFile, szPath, MAX_PATH))
	{
		return;
	}
*/
	const char *szPath = szFile;	
	FILESKINLIST::iterator it = m_vFileList.find(szPath);
	if (it != m_vFileList.end())
	{
		stFileSkin &info = (*it).second;
		info.sinkList.remove(pSink);
		if (info.sinkList.empty())
		{
			m_vFileList.erase(it);
		}
	}
}

// 获得绝对路径
char* CScriptLoader::GetAbsolutePath(LPCSTR szFile, char *szPath, int nSize)
{
	// 如果是相对路径...
	if (szFile[1] != ':')
	{
		getcwd(szPath, nSize);

		int nLen = strlen(szPath) + strlen("\\") + strlen(szFile) + 1;
		if (nLen > nSize)
		{
			szPath[0] = 0;
			return NULL;
		}

		strcat(szPath, "\\");
		strcat(szPath, szFile);
	}
	// 如果是绝对路径...
	else
	{
		strncpy(szPath, szFile, nSize);
	}

	// 将其中的小写字母转换成大写
	core::strupr(szPath);

	return szPath;
}

TiXmlDocument *CScriptLoader::LoadXmlFile(LPCSTR szFileName,BOOL bEncrypt)
{
	TiXmlDocument *pTiXmlDocument = new TiXmlDocument();

	if (pTiXmlDocument== NULL)
	{
		return NULL;
	}
	pTiXmlDocument->LoadFile(szFileName);
	return pTiXmlDocument;
}

TiXmlDocument *CScriptLoader::LoadXmlFile(LPCSTR szFileName,LPCSTR lpBuffData,int nLen)
{
	TiXmlDocument *pTiXmlDocument = new TiXmlDocument(szFileName);

	if (pTiXmlDocument== NULL)
	{
		return NULL;

	}
	 pTiXmlDocument->Parse( lpBuffData );
	 if ( pTiXmlDocument->Error() )
	 {
		delete pTiXmlDocument;
		pTiXmlDocument = NULL;
		 return NULL;
	 }
	 return pTiXmlDocument;
}

CScriptLoader* CScriptLoader::GetInstance()
{
	if (CScriptLoader::_instance == NULL)
	{
		CScriptLoader::_instance = new CScriptLoader;
	}
	return CScriptLoader::_instance;
}

void CScriptLoader::Release()
{
	if (CScriptLoader::_instance != NULL)
	{
		delete CScriptLoader::_instance;
		CScriptLoader::_instance = NULL;
	}
}
