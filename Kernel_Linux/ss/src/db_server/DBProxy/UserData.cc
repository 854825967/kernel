#include "Header.h"
#include "UserData.h"
#include "DataProcUser.h"
#include "IDBClient.h"

#define  USERSAVETIME 300000
// ���캯��
CUserData::CUserData(s64 qwUserID, s32 lActorID, LPVOID dwServerID, CDataProcUser *pDataProcUser)
{
	m_qwUserID = qwUserID;
	m_lActorID = lActorID;
	m_dwServerID = dwServerID;
	m_bSaving = FALSE;
	m_dwLastSave = GetTickCount();
	m_bDataSaveOK = FALSE;
	m_pDataProcUser = pDataProcUser;
	// 4���Ӽ��һ��
	g_pTimeAxis->SetTimer(0,USERSAVETIME, this,INFINITY_CALL,  "CUserData::CUserData");
}

// ��������
CUserData::~CUserData()
{
	g_pTimeAxis->KillTimer(0, this);
	m_pDataProcUser->DelUser(m_qwUserID, this);
}

// ���ݿ����󷵻ػص�����
void CUserData::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
					  s32 nReturn, LPSTR pOutData, s32 nOutLen)
{
	if (nReturn != DBRET_OK)
	{
		if (DBRET_ERROR_LOGIC == -1)
		{
			g_pTrace->TraceErrorLn("CUserData::OnRetʧ��, UserID = %ld, ActorID = %d , RequestID=%d, Return=%d! ,������Ϣ��%s",
				qwUserID,m_lActorID, nRequestID, nReturn,pOutData);
		}
		else
		{
			g_pTrace->TraceErrorLn("CUserData::OnRetʧ��, UserID=%ld, RequestID=%d, Return=%d! ,%s",
				qwUserID, nRequestID, nReturn);

		}
	}

	if (nRequestID == REQUESTID_ACTOR_LOGOUT)
	{
		g_pTrace->TraceLn("CUserData::OnRet�û��˳�:  UserID = %ld, ActorID = %d , RequestID=%d, Return=%d! ,������Ϣ��%s",
			qwUserID,m_lActorID, nRequestID, nReturn,pOutData);
		delete this;
	}
}

// ��ʱ���ص�
void CUserData::OnTimer(u32 dwTimerID)
{
	g_pTimeAxis->KillTimer(0, this);

	g_pTrace->TraceErrorLn("����û�ж�ʱ�յ���Ҽ�������, ǿ�ƴ�������, UserID=%ld, ActorID=%d!",
		m_qwUserID, m_lActorID);

	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	SActorLogout_Set temp;
	temp.qwUserID = m_qwUserID;
	temp.lActorID = m_lActorID;

	if (FALSE == Save(REQUESTID_ACTOR_LOGOUT, (LPSTR)&temp, sizeof(temp), pOutData, nOutLen))
	{
		g_pTrace->TraceLn("CUserData::OnTimerʧ��, ����ʧ��!");
	}
}

// �Ƿ����ڴ���
BOOL CUserData::IsSaving(void)
{
	return m_bSaving;
}

// ��ȡ������ID
LPVOID CUserData::GetServerID(void)
{
	return m_dwServerID;
}

// ���÷�����ID
void CUserData::SetServerID(LPVOID dwServerID)
{
	m_dwServerID = dwServerID;
}

// ��������
BOOL CUserData::Save(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
					 LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_bSaving)
	{
		g_pTrace->TraceLn("CUserData::Saveʧ��, UserID=%ld���ڴ���...!", m_qwUserID);
		return FALSE;
	}

	// ���½�ɫ����
	if (REQUESTID_ACTOR_UPDATE == nRequestID)
	{
		if (nInDataLen != sizeof(SActorUpdate_Set))
		{
			g_pTrace->TraceLn("CUserData::Saveʧ��, %d!=sizeof(SActorUpdate_Set)!", nInDataLen);
			return FALSE;
		}

		u8 lLevelLod = m_UpdateSet.bLevel;
		BOOL bUpdataLevel = FALSE;
		// ��������
		memcpy(&m_UpdateSet, pInData, nInDataLen);

		if (m_UpdateSet.qwUserID != m_qwUserID || m_UpdateSet.lActorID != m_lActorID)
		{
			g_pTrace->TraceLn("CUserData::Saveʧ��, ���ݷǷ�!");
			return FALSE;
		}

		if (lLevelLod != m_UpdateSet.bLevel)
		{
			bUpdataLevel = TRUE;
		}

		SActorUpdate_Get *pGet = (SActorUpdate_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		nOutDataLen = sizeof(SActorUpdate_Get);

		// ��ʱ���̴���
		TimeSave(bUpdataLevel);
		// ����4���ӳ�ʱ��ʱ��
		g_pTimeAxis->KillTimer(0, this);
		g_pTimeAxis->SetTimer(0, USERSAVETIME, this,INFINITY_CALL, "CUserData::Save");
	}
	// ���½�ɫ��Ʒ
	else if (REQUESTID_GOODS_UPDATE == nRequestID)
	{
		if (nInDataLen != sizeof(SGoodsUpdate_Set))
		{
			g_pTrace->TraceLn("CUserData::Saveʧ��, %d!=sizeof(SGoodsUpdate_Set)!", nInDataLen);
			return FALSE;
		}

		// ��������
		SGoodsUpdate_Set *pGoods = (SGoodsUpdate_Set*)pInData;
		list<SGoodsUpdate_Set>::iterator it = m_GoodsSet.begin();
		for (; it != m_GoodsSet.end(); ++it)
		{
			SGoodsUpdate_Set *pTemp = &(*it);
			if (pTemp->byContainerID == pGoods->byContainerID)
			{
				memcpy(pTemp, pInData, sizeof(SGoodsUpdate_Set));
				break;
			}
		}

		// û���ҵ�������׷��
		if (it == m_GoodsSet.end())
		{
			m_GoodsSet.push_back((*pGoods));
		}

		SGoodsUpdate_Get *pGet = (SGoodsUpdate_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		nOutDataLen = sizeof(SGoodsUpdate_Get);
	}
	// ���½�������
	else if (REQUESTID_INTERACT_SAVE == nRequestID)
	{
		if (nInDataLen != sizeof(SInteractSave_Set))
		{
			g_pTrace->TraceLn("CUserData::Saveʧ��, %d!=sizeof(SInteractSave_Set)!", nInDataLen);
			return FALSE;
		}

		// ��������
		memcpy(&m_InteractSet, pInData, nInDataLen);

		if (m_InteractSet.lTypeID != 0 || m_InteractSet.lServerID != 0
			|| m_InteractSet.lOwnerID != m_lActorID)
		{
			g_pTrace->TraceLn("CUserData::Saveʧ��, �洢�������ݷǷ�!");
			return FALSE;
		}

		SInteractSave_Get *pGet = (SInteractSave_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		pGet->szDes[0] = 0;
		nOutDataLen = sizeof(SInteractSave_Get);
	}
	// �������
	else if (REQUESTID_ACTOR_LOGOUT == nRequestID)
	{
		m_bSaving = TRUE;

		// ������������Ѿ���������б���
		if (m_InteractSet.lOwnerID != 0)
		{
			if (FALSE == g_pDBEngine->Request(0, REQUESTID_INTERACT_SAVE, m_qwUserID,
				(char*)&m_InteractSet, sizeof(m_InteractSet), this))
			{
				g_pTrace->TraceLn("CUserData::Saveʧ��, �������ݱ���ʧ��!");
				return FALSE;
			}

			//			g_pTrace->TraceLn("UserID=%ld, ��ʼ���潻������!", m_qwUserID);
		}

		// ��ʼ�������ݿ�
		list<SGoodsUpdate_Set>::iterator it = m_GoodsSet.begin();
		for (; it != m_GoodsSet.end(); ++it)
		{
			SGoodsUpdate_Set *pTemp = &(*it);
			if (FALSE == g_pDBEngine->Request(0, REQUESTID_GOODS_UPDATE, m_qwUserID,
				(char*)pTemp, sizeof(SGoodsUpdate_Set), this))
			{
				g_pTrace->TraceLn("CUserData::Saveʧ��, ��Ʒ���±���ʧ��!");
				return FALSE;
			}

			//			g_pTrace->TraceLn("UserID=%d, ��ʼ��������%d��Ʒ%d��!",
			//				m_qwUserID, pTemp->lContainerID, pTemp->lGoodsNum);
		}

		// �����һ��������Ѿ���������б���
		if (m_UpdateSet.qwUserID != 0)
		{
			if (FALSE == g_pDBEngine->Request(0, REQUESTID_ACTOR_UPDATE, m_qwUserID,
				(char*)&m_UpdateSet, sizeof(m_UpdateSet), this))
			{
				g_pTrace->TraceLn("CUserData::Saveʧ��, ��Ҹ��±���ʧ��!");
				return FALSE;
			}

			//			g_pTrace->TraceLn("UserID=%d, ��ʼ�����������!", m_qwUserID);
		}

		if (FALSE == g_pDBEngine->Request(0, nRequestID, m_qwUserID, pInData, nInDataLen, this))
		{
			g_pTrace->TraceLn("CUserData::Saveʧ��, �������󱣴�ʧ��!");
			return FALSE;
		}

		//		g_pTrace->TraceLn("UserID=%d, ��ʼ������������!", m_qwUserID);

		SActorLogout_Get *pGet = (SActorLogout_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		pGet->szDes[0] = 0;
		nOutDataLen = sizeof(SActorLogout_Get);

		// ɾ����ʱ��ʱ��
		g_pTimeAxis->KillTimer(0, this);
	}
	// �����Զ����������
	//else if (REQ_VESTIB_USERDEFINED_SAVE == nRequestID)
	//{
	//	if (nInDataLen != sizeof(SUserDefinedSave_Set))
	//	{
	//		g_pTrace->TraceLn("CUserData::Saveʧ��, %d!=sizeof(SUserDefinedSave_Set)!", nInDataLen);
	//		return FALSE;
	//	}

	//	// ��������
	//	memcpy(&m_DefinedSet, pInData, nInDataLen);

	//	if (m_DefinedSet.lActorID != m_lActorID)
	//	{
	//		g_pTrace->TraceLn("CUserData::Saveʧ��, �����Զ�������������ݷǷ�!");
	//		return FALSE;
	//	}
	//	
	//	SUserDefinedSave_Get *pGet = (SUserDefinedSave_Get*)pOutData;
	//	pGet->lReturn = DBRET_OK;
	//	nOutDataLen = sizeof(SUserDefinedSave_Get);
	//}
	// ����л��������ݱ���OK
	else if (REQ_VESTIB_USER_SAVE_OK == nRequestID)
	{
		m_bDataSaveOK = TRUE;
	}
	else
	{
		g_pTrace->TraceLn("CUserData::Saveʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

// װ������
BOOL CUserData::Load(s32 nRequestID, LPSTR pInData, s32 nInDataLen, LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_bSaving)
	{
		g_pTrace->TraceLn("CUserData::Loadʧ��, UserID=%d���ڴ���...!", m_qwUserID);
		return FALSE;
	}

	// ��ɫ��¼
	if (REQUESTID_ACTOR_LOGIN == nRequestID)
	{
		//��ɫ�л��곡����Ҫ�������־��ΪFALSE
		m_bDataSaveOK = FALSE;

		// ��ɫ���ݲ�����
		if (m_UpdateSet.qwUserID == 0)
		{
			return FALSE;
		}

		if (nInDataLen != sizeof(SActorLogin_Set))
		{
			g_pTrace->TraceLn("CUserData::Loadʧ��, ��ɫ��¼%d!=sizeof(SActorLogin_Set)!", nInDataLen);
			return FALSE;
		}

		if ((u32)nOutDataLen < sizeof(SActorLogin_Get))
		{
			g_pTrace->TraceLn("CUserData::Loadʧ��, ��ɫ��¼%d<sizeof(SActorLogin_Get)!", nOutDataLen);
			return FALSE;
		}

		// ��������
		SActorLogin_Get *pLoginGet = (SActorLogin_Get*)pOutData;
		pLoginGet->lReturn = DBRET_OK;
		memcpy((char*)pLoginGet + sizeof(s32),
			(LPCSTR)&m_UpdateSet + sizeof(s64) + sizeof(s32),
			sizeof(m_UpdateSet) - sizeof(s64) - sizeof(s32));
		nOutDataLen = sizeof(SActorLogin_Get);
	}
	// ��ȡ��ɫ��Ʒ
	else if (REQUESTID_GOODS_GET == nRequestID)
	{
		// ��ɫ���ݲ�����
		if (m_UpdateSet.qwUserID == 0)
		{
			return FALSE;
		}

		if (nInDataLen != sizeof(SGoodsGet_Set))
		{
			g_pTrace->TraceLn("CUserData::Loadʧ��, ��ȡ��ɫ��Ʒ%d!=sizeof(SGoodsGet_Set)!", nInDataLen);
			return FALSE;
		}

		SGoodsGet_Set *pSet = (SGoodsGet_Set*)pInData;
		list<SGoodsUpdate_Set>::iterator it = m_GoodsSet.begin();
		for (; it != m_GoodsSet.end(); ++it)
		{
			SGoodsUpdate_Set *pTemp = &(*it);
			if (pSet->byContainerID == pTemp->byContainerID)
			{
				SGoodsGet_Get goodsGet;
				goodsGet.lReturn = DBRET_OK;
				goodsGet.lGoodsNum = pTemp->lGoodsNum;

				if (nOutDataLen <(s32)( sizeof(SGoodsGet_Get) + pTemp->lGoodsNum * sizeof(SGoodsGet_GetSet)))
				{
					g_pTrace->TraceLn("CUserData::Loadʧ��, ��ȡ��ɫ��ƷnOutDataLen=%d!", nOutDataLen);
					return FALSE;
				}

				memcpy(pOutData, &goodsGet, sizeof(goodsGet));
				memcpy(pOutData + sizeof(goodsGet), pTemp->szGoodsBuf, pTemp->lGoodsNum * sizeof(SGoodsGet_GetSet));
				nOutDataLen = sizeof(SGoodsGet_Get) + pTemp->lGoodsNum * sizeof(SGoodsGet_GetSet);
				return TRUE;
			}
		}

		//		g_pTrace->TraceErrorLn("CUserData::Loadʧ��, û���ҵ������ɫ��Ʒ, ����=%d!", pSet->lContainerID);
		//		g_pTrace->TraceLn("CUserData::Loadʧ��, û���ҵ������ɫ��Ʒ, ����=%d!", pSet->lContainerID);
		return FALSE;
	}
	// ��ȡ��������
	else if (REQUESTID_INTERACT_LOAD == nRequestID)
	{
		// �������ݲ�����
		if (m_InteractSet.lOwnerID == 0)
		{
			return FALSE;
		}

		if (nInDataLen != sizeof(SInteractLoad_Set))
		{
			g_pTrace->TraceLn("CUserData::Loadʧ��, ��ȡ��������%d!=sizeof(SInteractLoad_Set)!", nInDataLen);
			return FALSE;
		}

		// ��������
		SInteractLoad_Get *pGet = (SInteractLoad_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		memcpy((char*)(pGet->DataBuffer),
			(LPCSTR)&(m_InteractSet.DataBuffer),
			sizeof(m_InteractSet.DataBuffer));
		nOutDataLen = sizeof(SInteractLoad_Get);
	}
	// ��ȡ�Զ����������
	// 	else if (REQ_VESTIB_USERDEFINED_LOAD == nRequestID)
	// 	{
	// 		if (nInDataLen != sizeof(SUserDefinedLoad_Set))
	// 		{
	// 			g_pTrace->TraceLn("CUserData::Loadʧ��, ��ȡ�Զ����������%d!=sizeof(SUserDefinedLoad_Set)!", nInDataLen);
	// 			return FALSE;
	// 		}
	// 
	// 		if (nOutDataLen < sizeof(SUserDefinedLoad_Get))
	// 		{
	// 			g_pTrace->TraceLn("CUserData::Loadʧ��, ��ȡ�Զ����������%d<sizeof(SUserDefinedLoad_Get)!", nOutDataLen);
	// 			return FALSE;
	// 		}
	// 
	// 		SUserDefinedLoad_Get *pLoadGet = (SUserDefinedLoad_Get*)pOutData;
	// 		pLoadGet->lReturn = DBRET_OK;
	// 		memcpy(pLoadGet->DataBuffer, m_DefinedSet.DataBuffer, sizeof(pLoadGet->DataBuffer));
	// 		nOutDataLen = sizeof(SUserDefinedLoad_Get);
	// 	}
	else
	{
		g_pTrace->TraceErrorLn("CUserData::Loadʧ��, RequestID=%d!", nRequestID);
		//g_pTrace->TraceLn("CUserData::Loadʧ��, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

//����TRUE��ʾ�л��������ݱ���OK����������
BOOL CUserData::IsDataSaveOK(void)
{
	return m_bDataSaveOK;
}

//�����
void CUserData::KickUser(void)
{
	g_pTimeAxis->KillTimer(0, this);

	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	SActorLogout_Set temp;
	temp.qwUserID = m_qwUserID;
	temp.lActorID = m_lActorID;

	if (FALSE == Save(REQUESTID_ACTOR_LOGOUT, (char*)&temp, sizeof(temp), pOutData, nOutLen))
	{
		g_pTrace->TraceLn("CUserData::KickUserʧ��, ����ʧ��!");
	}
}

// ��ʱ���̴���
void CUserData::TimeSave(BOOL bUpdateLevel)
{
	// 1Сʱ����һ�ζ�ʱ����
	DWORD dwCurrent = GetTickCount();
	if (dwCurrent - m_dwLastSave > 0 && dwCurrent - m_dwLastSave < g_dwSaveTimes )
	{
		// ������״̬ ���ж��Ƿ񷵻�
		if (bUpdateLevel == FALSE)
		{
			return;
		}
	}

	m_dwLastSave = dwCurrent;

	//	g_pTrace->TraceLn("UserID=%ld, ��ʼ��ʱ����...", m_qwUserID);

	// ������������Ѿ���������б���
	if (m_InteractSet.lOwnerID != 0)
	{
		if (FALSE == g_pDBEngine->Request(0, REQUESTID_INTERACT_SAVE, m_qwUserID,
			(char*)&m_InteractSet, sizeof(m_InteractSet), this))
		{
			g_pTrace->TraceLn("CUserData::TimeSaveʧ��, �������ݱ���ʧ��!");
			return;
		}

		//		g_pTrace->TraceLn("UserID=%d, ��ʼ���潻������!", m_qwUserID);
	}

	// ��ʼ�������ݿ�
	list<SGoodsUpdate_Set>::iterator it = m_GoodsSet.begin();
	for (; it != m_GoodsSet.end(); ++it)
	{
		SGoodsUpdate_Set *pTemp = &(*it);
		if (FALSE == g_pDBEngine->Request(0, REQUESTID_GOODS_UPDATE, m_qwUserID,
			(char*)pTemp, sizeof(SGoodsUpdate_Set), this))
		{
			g_pTrace->TraceLn("CUserData::TimeSaveʧ��, ��Ʒ���±���ʧ��!");
			return;
		}

		//		g_pTrace->TraceLn("UserID=%d, ��ʼ��������%d��Ʒ%d��!",
		//			m_qwUserID, pTemp->lContainerID, pTemp->lGoodsNum);
	}

	// �����һ��������Ѿ���������б���
	if (m_UpdateSet.qwUserID != 0)
	{
		if (FALSE == g_pDBEngine->Request(0, REQUESTID_ACTOR_UPDATE, m_qwUserID,
			(char*)&m_UpdateSet, sizeof(m_UpdateSet), this))
		{
			g_pTrace->TraceLn("CUserData::TimeSaveʧ��, ��Ҹ��±���ʧ��!");
			return;
		}

		//		g_pTrace->TraceLn("UserID=%d, ��ʼ�����������!", m_qwUserID);
	}
}

