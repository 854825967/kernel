#include "Header.h"
#include "ServerClientSink.h"
#include "IDBClient.h"
#include "IDBStruct.h"
#include "ServerService.h"
#include "SocketService.h"

enum TIMER_ID
{
	enTimer_ID_KeepAlive = 1,	//心跳包检查
	enTimer_ID_C_Close,			//会话关闭
};


#define  TIME_KEEPALIVE		300 * 1000	//检查心跳包的时间间隔，单位：毫秒


// 请求序列号
s32 CServerClientSink::s_lIndex = 0;

// 构造函数
CServerClientSink::CServerClientSink(CSocketService *pVestibule)
{
	m_pVestibule = pVestibule;
	m_bClosed = FALSE;
	BOOL bConnected = FALSE;
	m_PTTest.resize(2048);
	m_PTTime = GetTickCount();
	memset(&m_PTTest[0], 0, m_PTTest.capacity() * sizeof(int));
	m_bKeepAlive = TRUE;
}

// 析构函数
CServerClientSink::~CServerClientSink()
{
	// 输出性能统计信息
	g_pServerLog->TraceLn("---------------前置机性能评测结果开始---------------");
	g_pServerLog->TraceLn("应用服务器 IP[%s] PORT[%d], 耗时%d秒!", m_szIP, m_wPort,
		(GetTickCount() - m_PTTime) / 1000);
	for (s32 i = 0; i < (s32)m_PTTest.capacity(); i++)
	{
		if (m_PTTest[i] > 0)
		{
			g_pServerLog->TraceLn("请求ID=%d, 次数=%d", i, m_PTTest[i]);
		}
	}
	g_pServerLog->TraceLn("---------------前置机性能评测结果结束---------------");

	if (m_UserMap.size() > 0)
	{
		g_pServerLog->TraceErrorLn("应用服务器 IP[%s] PORT[%d] 还剩余 %d 玩家没有处理存盘!", m_szIP, m_wPort, m_UserMap.size());
		//g_pServerLog->TraceLn("应用服务器 IP[%s] PORT[%d] 还剩余玩家没有处理存盘!", m_szIP, m_wPort);
	}

	g_ServerService.GetTimerAxis()->KillTimer(enTimer_ID_KeepAlive, (ITimerHandler*)this);
	g_ServerService.GetTimerAxis()->KillTimer(enTimer_ID_C_Close, (ITimerHandler*)this);

	g_pServerLog->TraceErrorLn("应用服务器 IP[%s] PORT[%d] 断开连接!", m_szIP, m_wPort);
	//g_pServerLog->TraceLn("应用服务器 IP[%s] PORT[%d] 断开连接!", m_szIP, m_wPort);

	m_pVestibule->DelColloquy(this);
}

// 接收数据处理
void CServerClientSink::OnRecieve(LPCSTR Buf, s32 nLen)
{
	if (TRUE == m_bClosed)
	{
		g_pServerLog->TraceLn("CServerClientSink::OnRecieve失败, 客户端已经断开却又收到数据!");
	}

	if (Buf == NULL || (u32)nLen < sizeof(u32) || nLen < 0)
	{
		g_pServerLog->TraceLn("CServerClientSink::OnRecieve失败, 数据非法!");
		return;
	}

	u32 dwCmd = *((u32*)Buf);
	if (VESTIB_COMMAND_REQUEST == dwCmd)
	{
		RequestDB(Buf + sizeof(u32), nLen - sizeof(u32));
	}
	else if (VESTIB_COMMAND_KeepAlive == dwCmd)
	{
		m_bKeepAlive = TRUE;
	}
	else
	{
		g_pServerLog->TraceLn("CServerClientSink::OnRecieve失败, IP=%s, Cmd=%d!", m_szIP, dwCmd);
	}
}

// 连接成功处理(逻辑线程)
void CServerClientSink::OnConnectionOK() 
{
	if (m_pVestibule->GetColloquyNum() >= MAX_CONNECT_NUM)
	{
		g_pServerLog->TraceErrorLn("CSocketService::OnConnectionEstablished失败, 前置机已达到最大连接数!");
		// 断开DBClient连接
		CloseConnection();
		return;
	}

	// 启动心跳定时器
	Start();

	u32 dwCmd = VESTIBULE_WARN_CONNECTED;
	Send((LPCSTR)&dwCmd, sizeof(u32));

	// 添加会话
	m_pVestibule->AddColloquy(this);

	string strPeer = GetPeerString();
	g_pServerLog->TraceLn("远端%s 连接OK, 总连接数=%d!",
		strPeer.c_str(), m_pVestibule->GetColloquyNum());
	return;
}

// 关闭连接处理
void CServerClientSink::OnCloseConnection(bool force)
{
	if(force == true) {
		delete this;
		return;
	}

	string strPeer = GetPeerString();
	g_pServerLog->TraceLn("CServerClientSink::OnCloseConnection关闭,%s", strPeer.c_str());
	if (TRUE == m_bClosed)
	{
		g_pServerLog->TraceLn("CServerClientSink::OnCloseConnection重复关闭,%s", strPeer.c_str());
		return;
	}

	//保存缓存数据
	if (g_ServerService.GetDBProxy() != NULL)
	{
		g_ServerService.GetDBProxy()->CloseServer((LPVOID) this);
	}

	char szBuffer[MAX_BUFFER_SIZE] = {0};
	s32 nBufLen = 0;
	s32 iReqIndex = 0;
	s32 nRequestID = REQUESTID_ACTOR_LOGOUT;

	// 所有本服务器用户处理下线存盘
	map<s64, s32>::iterator it = m_UserMap.begin();
	for (; it != m_UserMap.end(); ++it)
	{
		SActorLogout_Set temp;
		temp.qwUserID = (*it).first;
		temp.lActorID = (*it).second;

		// 格式: iReqIndex + nRequestID + qwUserID + nDataLen + pData
		nBufLen = 0;
		memcpy(szBuffer + nBufLen, &iReqIndex, sizeof(s32));
		nBufLen += sizeof(s32);
		memcpy(szBuffer + nBufLen, &nRequestID, sizeof(s32));
		nBufLen += sizeof(s32);
		memcpy(szBuffer + nBufLen, &temp.qwUserID, sizeof(s64));
		nBufLen += sizeof(s64);
		s32 lTempLen = sizeof(temp);
		memcpy(szBuffer + nBufLen, &lTempLen, sizeof(s32));
		nBufLen += sizeof(s32);
		memcpy(szBuffer + nBufLen, &temp, sizeof(temp));
		nBufLen += sizeof(temp);

		RequestDB(szBuffer, nBufLen);
	}

	m_bClosed = TRUE;

	g_ServerService.GetTimerAxis()->KillTimer(enTimer_ID_C_Close, (ITimerHandler*)this);
	g_ServerService.GetTimerAxis()->SetTimer(enTimer_ID_C_Close ,1000, (ITimerHandler*)this,INFINITY_CALL, "CServerClientSink::OnCloseConnect");
}

// 数据库代理请求返回回调函数
void CServerClientSink::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
							  s32 nReturn, LPSTR pOutData, s32 nOutLen)
{
	s32 tempIndex = 0;
	map<s32, s32>::iterator it = m_RequestMap.find(nIndex);
	if (it != m_RequestMap.end())
	{
		tempIndex = (*it).second;
		m_RequestMap.erase(it);
	}
	else
	{
		g_pServerLog->TraceLn("CServerClientSink::OnRet失败, 找不到序列号!");
	}

	char buffer[MAX_BUFFER_SIZE] = {0};
	memset(buffer, 0,sizeof(buffer));
	char *temp = buffer;
	s32 nBufSize = 0;

	memcpy(temp, &nReturn, sizeof(nReturn));
	temp += sizeof(nReturn);
	nBufSize += sizeof(nReturn);

	// 留出是否结束包的标志, 用于处理分包发送
	temp += sizeof(BOOL);
	nBufSize += sizeof(BOOL);

	memcpy(temp, &tempIndex, sizeof(tempIndex));
	temp += sizeof(tempIndex);
	nBufSize += sizeof(tempIndex);

	memcpy(temp, &qwUserID, sizeof(qwUserID));
	temp += sizeof(qwUserID);
	nBufSize += sizeof(qwUserID);

	memcpy(temp, &nRequestID, sizeof(nRequestID));
	temp += sizeof(nRequestID);
	nBufSize += sizeof(nRequestID);

	memcpy(temp, &nReturn, sizeof(nReturn));
	temp += sizeof(nReturn);
	nBufSize += sizeof(nReturn);

	memcpy(temp, &nInLen, sizeof(nInLen));
	temp += sizeof(nInLen);
	nBufSize += sizeof(nInLen);

	if ((nBufSize + nInLen + 4) > 4000)
	{
		g_pServerLog->TraceLn("CServerClientSink::OnRet失败, qwUserID: %ld, nRequestID: %d, nBufSize: %d", 
			qwUserID, nRequestID, nBufSize);
		return;
	}

	memcpy(temp, pInData, nInLen);
	temp += nInLen;
	nBufSize += nInLen;

	memcpy(temp, &nOutLen, sizeof(nOutLen));
	temp += sizeof(nOutLen);
	nBufSize += sizeof(nOutLen);

	while (nOutLen >= 0)
	{
		s32 lLen = 0;
		BOOL bEnd = FALSE;

		if ((nBufSize + nOutLen) <= 4000)
		{
			lLen = nOutLen;
			bEnd = TRUE;
		}
		else
		{
			lLen = 4000 - nBufSize;
			bEnd = FALSE;
		}

		// 压入Return
		memcpy(buffer, &nReturn, sizeof(nReturn));
		// 压入是否结束包标志
		memcpy(buffer + sizeof(nReturn), &bEnd, sizeof(bEnd));
		// 压入剩余数据
		memcpy(temp, pOutData, lLen);
		temp += lLen;
		nBufSize += lLen;
		nOutLen -= lLen;
		pOutData += lLen;

		Send(buffer,nBufSize);

		temp = buffer + sizeof(nReturn) + sizeof(bEnd);
		nBufSize = sizeof(nReturn) + sizeof(bEnd);

		if (nOutLen <= 0)
		{
			break;
		}
	}
}

// 定时器回调
void CServerClientSink::OnTimer(u32 dwTimerID)
{
	if (enTimer_ID_KeepAlive == dwTimerID)
	{
		if (FALSE == m_bKeepAlive)
		{
			g_ServerService.GetTimerAxis()->KillTimer(enTimer_ID_KeepAlive, (ITimerHandler*)this);
			g_pServerLog->TraceLn("CServerClientSink::OnTimer 定时器关闭了连接");
			CloseConnection();
		}
		else
		{
			m_bKeepAlive = FALSE;
		}
	}
	else if (enTimer_ID_C_Close == dwTimerID)
	{
		// 如果所有请求都处理完, 则释放自己
		if (0 == m_RequestMap.size() && 0 == m_UserMap.size())
		{
			g_pServerLog->TraceLn("CServerClientSink::OnTimer 定时器删除了连接");
			// 断开此客户端链接
			// CloseConnection();
			if(this->CheckDisconnected())
				delete this;
		}
	}
}

// 添加用户处理回调函数
void CServerClientSink::AddUser(s64 qwUserID, s32 lActorID)
{
	if (TRUE == m_bClosed)
	{
		g_pServerLog->TraceLn("CServerClientSink::AddUser, TRUE == m_bClosed, UserID=%ld, ActorID=%d!",
			qwUserID, lActorID);
		return;
	}

	map<s64, s32>::iterator it = m_UserMap.find(qwUserID);
	if (it != m_UserMap.end())
	{
		g_pServerLog->TraceLn("CServerClientSink::AddUser失败, 添加重复, UserID=%ld, ActorID=%d!",
			qwUserID, lActorID);
		return;
	}

	m_UserMap[qwUserID] = lActorID;
}

// 删除用户处理回调函数
void CServerClientSink::DelUser(s64 qwUserID)
{
	map<s64, s32>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		g_pServerLog->TraceLn("CServerClientSink::DelUser失败, 用户不存在, UserID=%ld!", qwUserID);
		return;
	}

	m_UserMap.erase(qwUserID);
}

//开启
void CServerClientSink::Start(void)
{
	g_ServerService.GetTimerAxis()->SetTimer(enTimer_ID_KeepAlive,TIME_KEEPALIVE, (ITimerHandler*)this,INFINITY_CALL,  "CServerClientSink::Start");
}

// 数据库请求处理
void CServerClientSink::RequestDB(LPCSTR pBuf, s32 nLen)
{
	if (g_ServerService.GetDBProxy() == NULL)
	{
		return;
	}

	if (NULL == pBuf || nLen <= 0 || nLen <= 16)
	{
		g_pServerLog->TraceLn("CServerClientSink::RequestDB失败, 数据非法, nLen=%d!", nLen);
		return;
	}

	// 格式: iReqIndex + nRequestID + qwUserID + nDataLen + pData
	s32 iReqIndex = 0;
	s32 nRequestID = 0;
	s64 qwUserID = 0;
	s32 nDataLen = 0;

	memcpy(&iReqIndex, pBuf, sizeof(s32));
	pBuf += sizeof(s32);
	memcpy(&nRequestID, pBuf, sizeof(s32));
	pBuf += sizeof(s32);
	memcpy(&qwUserID, pBuf, sizeof(qwUserID));
	pBuf += sizeof(qwUserID);
	memcpy(&nDataLen, pBuf, sizeof(s32));
	pBuf += sizeof(s32);

	if (nDataLen != nLen - 20)
	{
		g_pServerLog->TraceLn("CServerClientSink::RequestDB失败, 数据非法, nLen=%d, DataLen=%d!", nLen, nDataLen);
		return;
	}
	s32 uidIndex = s_lIndex++;
	m_RequestMap[uidIndex] = iReqIndex;

	if (FALSE == g_ServerService.GetDBProxy()->Request(uidIndex, nRequestID, qwUserID,
		(LPSTR)pBuf, nDataLen, this, (LPVOID)this))
	{
		g_pServerLog->TraceLn("CServerClientSink::RequestDB失败, 请求非法, RequestID=%d!", nRequestID);

		char pOutData[MAX_BUFFER_SIZE] = {0};
		s32 nOutLen = 0;
		OnRet(uidIndex, qwUserID, nRequestID, (LPSTR)pBuf, nDataLen, VESTIBULE_RET_REQ_FAILED,
			pOutData, nOutLen);
	}

	if (nRequestID < (s32)m_PTTest.capacity())
	{
		m_PTTest[nRequestID]++;
	}
}


