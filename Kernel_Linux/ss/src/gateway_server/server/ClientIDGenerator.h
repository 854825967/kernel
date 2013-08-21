/******************************************************************
** 文件名:	ClientIDGenerator.h
** 版  权:	(C)  
** 创建人:	庄雪锋
** 日  期:	2011-08-01
** 版  本:	0.1
** 描  述:	客户端ID 生产器
** 应  用:  服务器
** 备  注:  

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef _CLIENTIDGENERATOR_H_
#define _CLIENTIDGENERATOR_H_
#include "DServerDef.h"
 

// 客户端ID 生产器
class ClientIDGenerator  
{
public:
	ClientIDGenerator() : m_dwGatewayID(0){}
	~ClientIDGenerator(){}
public:
	static ClientIDGenerator* getInstance()
	{
		if (!_instance)
		{
			_instance = new ClientIDGenerator;			
		}
		return _instance;
	}

	ClientID Generate(u32 dwIndex)
	{ 
    u32 tempID = (this->m_dwGatewayID & 0xFF) << 24;
    tempID += dwIndex & 0xFFFFFF;
    return tempID;
	};

  ClientIDInfo *GetClientIDInfo(ClientID client)
  {
    static ClientIDInfo clientInfo;
    clientInfo.nGatewayID = (client & 0xFF000000) >> 24;
    clientInfo.nConnIndex = client & 0xFFFFFF;
    return &clientInfo;
  }

	u32 GetGatewayID() { return m_dwGatewayID; }

	void  SetGatewayID(u32 id) { m_dwGatewayID=id; }

private:
	u32 m_dwGatewayID;
public:
	static ClientIDGenerator*	_instance;		/// 实例静态指针
};

#endif //_CLIENTIDGENERATOR_H_
