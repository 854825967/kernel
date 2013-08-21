#include "Header.h"
#include "ServerClientSink.h"
#include "IDBClient.h"
#include "IDBStruct.h"
#include "ServerService.h"
#include "SocketService.h"

enum TIMER_ID
{
	enTimer_ID_KeepAlive = 1,	//���������
	enTimer_ID_C_Close,			//�Ự�ر�
};


#define  TIME_KEEPALIVE		300 * 1000	//�����������ʱ��������λ������


// �������к�
s32 CServerClientSink::s_lIndex = 0;

// ���캯��
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

// ��������
CServerClientSink::~CServerClientSink()
{
	// �������ͳ����Ϣ
	g_pServerLog->TraceLn("---------------ǰ�û�������������ʼ---------------");
	g_pServerLog->TraceLn("Ӧ�÷����� IP[%s] PORT[%d], ��ʱ%d��!", m_szIP, m_wPort,
		(GetTickCount() - m_PTTime) / 1000);
	for (s32 i = 0; i < (s32)m_PTTest.capacity(); i++)
	{
		if (m_PTTest[i] > 0)
		{
			g_pServerLog->TraceLn("����ID=%d, ����=%d", i, m_PTTest[i]);
		}
	}
	g_pServerLog->TraceLn("---------------ǰ�û���������������---------------");

	if (m_UserMap.size() > 0)
	{
		g_pServerLog->TraceErrorLn("Ӧ�÷����� IP[%s] PORT[%d] ��ʣ�� %d ���û�д������!", m_szIP, m_wPort, m_UserMap.size());
		//g_pServerLog->TraceLn("Ӧ�÷����� IP[%s] PORT[%d] ��ʣ�����û�д������!", m_szIP, m_wPort);
	}

	g_ServerService.GetTimerAxis()->KillTimer(enTimer_ID_KeepAlive, (ITimerHandler*)this);
	g_ServerService.GetTimerAxis()->KillTimer(enTimer_ID_C_Close, (ITimerHandler*)this);

	g_pServerLog->TraceErrorLn("Ӧ�÷����� IP[%s] PORT[%d] �Ͽ�����!", m_szIP, m_wPort);
	//g_pServerLog->TraceLn("Ӧ�÷����� IP[%s] PORT[%d] �Ͽ�����!", m_szIP, m_wPort);

	m_pVestibule->DelColloquy(this);
}

// �������ݴ���
void CServerClientSink::OnRecieve(LPCSTR Buf, s32 nLen)
{
	if (TRUE == m_bClosed)
	{
		g_pServerLog->TraceLn("CServerClientSink::OnRecieveʧ��, �ͻ����Ѿ��Ͽ�ȴ���յ�����!");
	}

	if (Buf == NULL || (u32)nLen < sizeof(u32) || nLen < 0)
	{
		g_pServerLog->TraceLn("CServerClientSink::OnRecieveʧ��, ���ݷǷ�!");
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
		g_pServerLog->TraceLn("CServerClientSink::OnRecieveʧ��, IP=%s, Cmd=%d!", m_szIP, dwCmd);
	}
}

// ���ӳɹ�����(�߼��߳�)
void CServerClientSink::OnConnectionOK() 
{
	if (m_pVestibule->GetColloquyNum() >= MAX_CONNECT_NUM)
	{
		g_pServerLog->TraceErrorLn("CSocketService::OnConnectionEstablishedʧ��, ǰ�û��Ѵﵽ���������!");
		// �Ͽ�DBClient����
		CloseConnection();
		return;
	}

	// ����������ʱ��
	Start();

	u32 dwCmd = VESTIBULE_WARN_CONNECTED;
	Send((LPCSTR)&dwCmd, sizeof(u32));

	// ��ӻỰ
	m_pVestibule->AddColloquy(this);

	string strPeer = GetPeerString();
	g_pServerLog->TraceLn("Զ��%s ����OK, ��������=%d!",
		strPeer.c_str(), m_pVestibule->GetColloquyNum());
	return;
}

// �ر����Ӵ���
void CServerClientSink::OnCloseConnection(bool force)
{
	if(force == true) {
		delete this;
		return;
	}

	string strPeer = GetPeerString();
	g_pServerLog->TraceLn("CServerClientSink::OnCloseConnection�ر�,%s", strPeer.c_str());
	if (TRUE == m_bClosed)
	{
		g_pServerLog->TraceLn("CServerClientSink::OnCloseConnection�ظ��ر�,%s", strPeer.c_str());
		return;
	}

	//���滺������
	if (g_ServerService.GetDBProxy() != NULL)
	{
		g_ServerService.GetDBProxy()->CloseServer((LPVOID) this);
	}

	char szBuffer[MAX_BUFFER_SIZE] = {0};
	s32 nBufLen = 0;
	s32 iReqIndex = 0;
	s32 nRequestID = REQUESTID_ACTOR_LOGOUT;

	// ���б��������û��������ߴ���
	map<s64, s32>::iterator it = m_UserMap.begin();
	for (; it != m_UserMap.end(); ++it)
	{
		SActorLogout_Set temp;
		temp.qwUserID = (*it).first;
		temp.lActorID = (*it).second;

		// ��ʽ: iReqIndex + nRequestID + qwUserID + nDataLen + pData
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

// ���ݿ�������󷵻ػص�����
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
		g_pServerLog->TraceLn("CServerClientSink::OnRetʧ��, �Ҳ������к�!");
	}

	char buffer[MAX_BUFFER_SIZE] = {0};
	memset(buffer, 0,sizeof(buffer));
	char *temp = buffer;
	s32 nBufSize = 0;

	memcpy(temp, &nReturn, sizeof(nReturn));
	temp += sizeof(nReturn);
	nBufSize += sizeof(nReturn);

	// �����Ƿ�������ı�־, ���ڴ���ְ�����
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
		g_pServerLog->TraceLn("CServerClientSink::OnRetʧ��, qwUserID: %ld, nRequestID: %d, nBufSize: %d", 
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

		// ѹ��Return
		memcpy(buffer, &nReturn, sizeof(nReturn));
		// ѹ���Ƿ��������־
		memcpy(buffer + sizeof(nReturn), &bEnd, sizeof(bEnd));
		// ѹ��ʣ������
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

// ��ʱ���ص�
void CServerClientSink::OnTimer(u32 dwTimerID)
{
	if (enTimer_ID_KeepAlive == dwTimerID)
	{
		if (FALSE == m_bKeepAlive)
		{
			g_ServerService.GetTimerAxis()->KillTimer(enTimer_ID_KeepAlive, (ITimerHandler*)this);
			g_pServerLog->TraceLn("CServerClientSink::OnTimer ��ʱ���ر�������");
			CloseConnection();
		}
		else
		{
			m_bKeepAlive = FALSE;
		}
	}
	else if (enTimer_ID_C_Close == dwTimerID)
	{
		// ����������󶼴�����, ���ͷ��Լ�
		if (0 == m_RequestMap.size() && 0 == m_UserMap.size())
		{
			g_pServerLog->TraceLn("CServerClientSink::OnTimer ��ʱ��ɾ��������");
			// �Ͽ��˿ͻ�������
			// CloseConnection();
			if(this->CheckDisconnected())
				delete this;
		}
	}
}

// ����û�����ص�����
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
		g_pServerLog->TraceLn("CServerClientSink::AddUserʧ��, ����ظ�, UserID=%ld, ActorID=%d!",
			qwUserID, lActorID);
		return;
	}

	m_UserMap[qwUserID] = lActorID;
}

// ɾ���û�����ص�����
void CServerClientSink::DelUser(s64 qwUserID)
{
	map<s64, s32>::iterator it = m_UserMap.find(qwUserID);
	if (it == m_UserMap.end())
	{
		g_pServerLog->TraceLn("CServerClientSink::DelUserʧ��, �û�������, UserID=%ld!", qwUserID);
		return;
	}

	m_UserMap.erase(qwUserID);
}

//����
void CServerClientSink::Start(void)
{
	g_ServerService.GetTimerAxis()->SetTimer(enTimer_ID_KeepAlive,TIME_KEEPALIVE, (ITimerHandler*)this,INFINITY_CALL,  "CServerClientSink::Start");
}

// ���ݿ�������
void CServerClientSink::RequestDB(LPCSTR pBuf, s32 nLen)
{
	if (g_ServerService.GetDBProxy() == NULL)
	{
		return;
	}

	if (NULL == pBuf || nLen <= 0 || nLen <= 16)
	{
		g_pServerLog->TraceLn("CServerClientSink::RequestDBʧ��, ���ݷǷ�, nLen=%d!", nLen);
		return;
	}

	// ��ʽ: iReqIndex + nRequestID + qwUserID + nDataLen + pData
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
		g_pServerLog->TraceLn("CServerClientSink::RequestDBʧ��, ���ݷǷ�, nLen=%d, DataLen=%d!", nLen, nDataLen);
		return;
	}
	s32 uidIndex = s_lIndex++;
	m_RequestMap[uidIndex] = iReqIndex;

	if (FALSE == g_ServerService.GetDBProxy()->Request(uidIndex, nRequestID, qwUserID,
		(LPSTR)pBuf, nDataLen, this, (LPVOID)this))
	{
		g_pServerLog->TraceLn("CServerClientSink::RequestDBʧ��, ����Ƿ�, RequestID=%d!", nRequestID);

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


