#include "Header.h"
#include "UserData.h"
#include "DataProcUser.h"
#include "IDBClient.h"

#define  USERSAVETIME 300000
// 构造函数
CUserData::CUserData(s64 qwUserID, s32 lActorID, LPVOID dwServerID, CDataProcUser *pDataProcUser)
{
	m_qwUserID = qwUserID;
	m_lActorID = lActorID;
	m_dwServerID = dwServerID;
	m_bSaving = FALSE;
	m_dwLastSave = GetTickCount();
	m_bDataSaveOK = FALSE;
	m_pDataProcUser = pDataProcUser;
	// 4分钟检查一次
	g_pTimeAxis->SetTimer(0,USERSAVETIME, this,INFINITY_CALL,  "CUserData::CUserData");
}

// 析构函数
CUserData::~CUserData()
{
	g_pTimeAxis->KillTimer(0, this);
	m_pDataProcUser->DelUser(m_qwUserID, this);
}

// 数据库请求返回回调函数
void CUserData::OnRet(s32 nIndex, s64 qwUserID, s32 nRequestID, LPSTR pInData, s32 nInLen,
					  s32 nReturn, LPSTR pOutData, s32 nOutLen)
{
	if (nReturn != DBRET_OK)
	{
		if (DBRET_ERROR_LOGIC == -1)
		{
			g_pTrace->TraceErrorLn("CUserData::OnRet失败, UserID = %ld, ActorID = %d , RequestID=%d, Return=%d! ,错误信息：%s",
				qwUserID,m_lActorID, nRequestID, nReturn,pOutData);
		}
		else
		{
			g_pTrace->TraceErrorLn("CUserData::OnRet失败, UserID=%ld, RequestID=%d, Return=%d! ,%s",
				qwUserID, nRequestID, nReturn);

		}
	}

	if (nRequestID == REQUESTID_ACTOR_LOGOUT)
	{
		g_pTrace->TraceLn("CUserData::OnRet用户退出:  UserID = %ld, ActorID = %d , RequestID=%d, Return=%d! ,返回信息：%s",
			qwUserID,m_lActorID, nRequestID, nReturn,pOutData);
		delete this;
	}
}

// 定时器回调
void CUserData::OnTimer(u32 dwTimerID)
{
	g_pTimeAxis->KillTimer(0, this);

	g_pTrace->TraceErrorLn("由于没有定时收到玩家间隔保存包, 强制处理下线, UserID=%ld, ActorID=%d!",
		m_qwUserID, m_lActorID);

	char pOutData[4096] = {0};
	s32 nOutLen = 4096;

	SActorLogout_Set temp;
	temp.qwUserID = m_qwUserID;
	temp.lActorID = m_lActorID;

	if (FALSE == Save(REQUESTID_ACTOR_LOGOUT, (LPSTR)&temp, sizeof(temp), pOutData, nOutLen))
	{
		g_pTrace->TraceLn("CUserData::OnTimer失败, 保存失败!");
	}
}

// 是否正在存盘
BOOL CUserData::IsSaving(void)
{
	return m_bSaving;
}

// 获取服务器ID
LPVOID CUserData::GetServerID(void)
{
	return m_dwServerID;
}

// 设置服务器ID
void CUserData::SetServerID(LPVOID dwServerID)
{
	m_dwServerID = dwServerID;
}

// 保存数据
BOOL CUserData::Save(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
					 LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_bSaving)
	{
		g_pTrace->TraceLn("CUserData::Save失败, UserID=%ld正在存盘...!", m_qwUserID);
		return FALSE;
	}

	// 更新角色数据
	if (REQUESTID_ACTOR_UPDATE == nRequestID)
	{
		if (nInDataLen != sizeof(SActorUpdate_Set))
		{
			g_pTrace->TraceLn("CUserData::Save失败, %d!=sizeof(SActorUpdate_Set)!", nInDataLen);
			return FALSE;
		}

		u8 lLevelLod = m_UpdateSet.bLevel;
		BOOL bUpdataLevel = FALSE;
		// 缓存数据
		memcpy(&m_UpdateSet, pInData, nInDataLen);

		if (m_UpdateSet.qwUserID != m_qwUserID || m_UpdateSet.lActorID != m_lActorID)
		{
			g_pTrace->TraceLn("CUserData::Save失败, 数据非法!");
			return FALSE;
		}

		if (lLevelLod != m_UpdateSet.bLevel)
		{
			bUpdataLevel = TRUE;
		}

		SActorUpdate_Get *pGet = (SActorUpdate_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		nOutDataLen = sizeof(SActorUpdate_Get);

		// 定时存盘处理
		TimeSave(bUpdataLevel);
		// 重置4分钟超时定时器
		g_pTimeAxis->KillTimer(0, this);
		g_pTimeAxis->SetTimer(0, USERSAVETIME, this,INFINITY_CALL, "CUserData::Save");
	}
	// 更新角色物品
	else if (REQUESTID_GOODS_UPDATE == nRequestID)
	{
		if (nInDataLen != sizeof(SGoodsUpdate_Set))
		{
			g_pTrace->TraceLn("CUserData::Save失败, %d!=sizeof(SGoodsUpdate_Set)!", nInDataLen);
			return FALSE;
		}

		// 缓存数据
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

		// 没有找到数据则追加
		if (it == m_GoodsSet.end())
		{
			m_GoodsSet.push_back((*pGoods));
		}

		SGoodsUpdate_Get *pGet = (SGoodsUpdate_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		nOutDataLen = sizeof(SGoodsUpdate_Get);
	}
	// 更新交互数据
	else if (REQUESTID_INTERACT_SAVE == nRequestID)
	{
		if (nInDataLen != sizeof(SInteractSave_Set))
		{
			g_pTrace->TraceLn("CUserData::Save失败, %d!=sizeof(SInteractSave_Set)!", nInDataLen);
			return FALSE;
		}

		// 缓存数据
		memcpy(&m_InteractSet, pInData, nInDataLen);

		if (m_InteractSet.lTypeID != 0 || m_InteractSet.lServerID != 0
			|| m_InteractSet.lOwnerID != m_lActorID)
		{
			g_pTrace->TraceLn("CUserData::Save失败, 存储交互数据非法!");
			return FALSE;
		}

		SInteractSave_Get *pGet = (SInteractSave_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		pGet->szDes[0] = 0;
		nOutDataLen = sizeof(SInteractSave_Get);
	}
	// 玩家下线
	else if (REQUESTID_ACTOR_LOGOUT == nRequestID)
	{
		m_bSaving = TRUE;

		// 如果交互数据已经加载则进行保存
		if (m_InteractSet.lOwnerID != 0)
		{
			if (FALSE == g_pDBEngine->Request(0, REQUESTID_INTERACT_SAVE, m_qwUserID,
				(char*)&m_InteractSet, sizeof(m_InteractSet), this))
			{
				g_pTrace->TraceLn("CUserData::Save失败, 交互数据保存失败!");
				return FALSE;
			}

			//			g_pTrace->TraceLn("UserID=%ld, 开始保存交互数据!", m_qwUserID);
		}

		// 开始保存数据库
		list<SGoodsUpdate_Set>::iterator it = m_GoodsSet.begin();
		for (; it != m_GoodsSet.end(); ++it)
		{
			SGoodsUpdate_Set *pTemp = &(*it);
			if (FALSE == g_pDBEngine->Request(0, REQUESTID_GOODS_UPDATE, m_qwUserID,
				(char*)pTemp, sizeof(SGoodsUpdate_Set), this))
			{
				g_pTrace->TraceLn("CUserData::Save失败, 物品更新保存失败!");
				return FALSE;
			}

			//			g_pTrace->TraceLn("UserID=%d, 开始保存容器%d物品%d个!",
			//				m_qwUserID, pTemp->lContainerID, pTemp->lGoodsNum);
		}

		// 如果玩家基本数据已经加载则进行保存
		if (m_UpdateSet.qwUserID != 0)
		{
			if (FALSE == g_pDBEngine->Request(0, REQUESTID_ACTOR_UPDATE, m_qwUserID,
				(char*)&m_UpdateSet, sizeof(m_UpdateSet), this))
			{
				g_pTrace->TraceLn("CUserData::Save失败, 玩家更新保存失败!");
				return FALSE;
			}

			//			g_pTrace->TraceLn("UserID=%d, 开始保存基本数据!", m_qwUserID);
		}

		if (FALSE == g_pDBEngine->Request(0, nRequestID, m_qwUserID, pInData, nInDataLen, this))
		{
			g_pTrace->TraceLn("CUserData::Save失败, 下线请求保存失败!");
			return FALSE;
		}

		//		g_pTrace->TraceLn("UserID=%d, 开始保存下线请求!", m_qwUserID);

		SActorLogout_Get *pGet = (SActorLogout_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		pGet->szDes[0] = 0;
		nOutDataLen = sizeof(SActorLogout_Get);

		// 删除超时定时器
		g_pTimeAxis->KillTimer(0, this);
	}
	// 保存自定义玩家数据
	//else if (REQ_VESTIB_USERDEFINED_SAVE == nRequestID)
	//{
	//	if (nInDataLen != sizeof(SUserDefinedSave_Set))
	//	{
	//		g_pTrace->TraceLn("CUserData::Save失败, %d!=sizeof(SUserDefinedSave_Set)!", nInDataLen);
	//		return FALSE;
	//	}

	//	// 缓存数据
	//	memcpy(&m_DefinedSet, pInData, nInDataLen);

	//	if (m_DefinedSet.lActorID != m_lActorID)
	//	{
	//		g_pTrace->TraceLn("CUserData::Save失败, 保存自定义玩家数据数据非法!");
	//		return FALSE;
	//	}
	//	
	//	SUserDefinedSave_Get *pGet = (SUserDefinedSave_Get*)pOutData;
	//	pGet->lReturn = DBRET_OK;
	//	nOutDataLen = sizeof(SUserDefinedSave_Get);
	//}
	// 玩家切换场景数据保存OK
	else if (REQ_VESTIB_USER_SAVE_OK == nRequestID)
	{
		m_bDataSaveOK = TRUE;
	}
	else
	{
		g_pTrace->TraceLn("CUserData::Save失败, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

// 装载数据
BOOL CUserData::Load(s32 nRequestID, LPSTR pInData, s32 nInDataLen, LPSTR pOutData, s32 &nOutDataLen)
{
	if (TRUE == m_bSaving)
	{
		g_pTrace->TraceLn("CUserData::Load失败, UserID=%d正在存盘...!", m_qwUserID);
		return FALSE;
	}

	// 角色登录
	if (REQUESTID_ACTOR_LOGIN == nRequestID)
	{
		//角色切换完场景后，要把这个标志置为FALSE
		m_bDataSaveOK = FALSE;

		// 角色数据不存在
		if (m_UpdateSet.qwUserID == 0)
		{
			return FALSE;
		}

		if (nInDataLen != sizeof(SActorLogin_Set))
		{
			g_pTrace->TraceLn("CUserData::Load失败, 角色登录%d!=sizeof(SActorLogin_Set)!", nInDataLen);
			return FALSE;
		}

		if ((u32)nOutDataLen < sizeof(SActorLogin_Get))
		{
			g_pTrace->TraceLn("CUserData::Load失败, 角色登录%d<sizeof(SActorLogin_Get)!", nOutDataLen);
			return FALSE;
		}

		// 更新数据
		SActorLogin_Get *pLoginGet = (SActorLogin_Get*)pOutData;
		pLoginGet->lReturn = DBRET_OK;
		memcpy((char*)pLoginGet + sizeof(s32),
			(LPCSTR)&m_UpdateSet + sizeof(s64) + sizeof(s32),
			sizeof(m_UpdateSet) - sizeof(s64) - sizeof(s32));
		nOutDataLen = sizeof(SActorLogin_Get);
	}
	// 获取角色物品
	else if (REQUESTID_GOODS_GET == nRequestID)
	{
		// 角色数据不存在
		if (m_UpdateSet.qwUserID == 0)
		{
			return FALSE;
		}

		if (nInDataLen != sizeof(SGoodsGet_Set))
		{
			g_pTrace->TraceLn("CUserData::Load失败, 获取角色物品%d!=sizeof(SGoodsGet_Set)!", nInDataLen);
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
					g_pTrace->TraceLn("CUserData::Load失败, 获取角色物品nOutDataLen=%d!", nOutDataLen);
					return FALSE;
				}

				memcpy(pOutData, &goodsGet, sizeof(goodsGet));
				memcpy(pOutData + sizeof(goodsGet), pTemp->szGoodsBuf, pTemp->lGoodsNum * sizeof(SGoodsGet_GetSet));
				nOutDataLen = sizeof(SGoodsGet_Get) + pTemp->lGoodsNum * sizeof(SGoodsGet_GetSet);
				return TRUE;
			}
		}

		//		g_pTrace->TraceErrorLn("CUserData::Load失败, 没有找到缓存角色物品, 容器=%d!", pSet->lContainerID);
		//		g_pTrace->TraceLn("CUserData::Load失败, 没有找到缓存角色物品, 容器=%d!", pSet->lContainerID);
		return FALSE;
	}
	// 读取交互数据
	else if (REQUESTID_INTERACT_LOAD == nRequestID)
	{
		// 交互数据不存在
		if (m_InteractSet.lOwnerID == 0)
		{
			return FALSE;
		}

		if (nInDataLen != sizeof(SInteractLoad_Set))
		{
			g_pTrace->TraceLn("CUserData::Load失败, 获取交互数据%d!=sizeof(SInteractLoad_Set)!", nInDataLen);
			return FALSE;
		}

		// 更新数据
		SInteractLoad_Get *pGet = (SInteractLoad_Get*)pOutData;
		pGet->lReturn = DBRET_OK;
		memcpy((char*)(pGet->DataBuffer),
			(LPCSTR)&(m_InteractSet.DataBuffer),
			sizeof(m_InteractSet.DataBuffer));
		nOutDataLen = sizeof(SInteractLoad_Get);
	}
	// 读取自定义玩家数据
	// 	else if (REQ_VESTIB_USERDEFINED_LOAD == nRequestID)
	// 	{
	// 		if (nInDataLen != sizeof(SUserDefinedLoad_Set))
	// 		{
	// 			g_pTrace->TraceLn("CUserData::Load失败, 读取自定义玩家数据%d!=sizeof(SUserDefinedLoad_Set)!", nInDataLen);
	// 			return FALSE;
	// 		}
	// 
	// 		if (nOutDataLen < sizeof(SUserDefinedLoad_Get))
	// 		{
	// 			g_pTrace->TraceLn("CUserData::Load失败, 读取自定义玩家数据%d<sizeof(SUserDefinedLoad_Get)!", nOutDataLen);
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
		g_pTrace->TraceErrorLn("CUserData::Load失败, RequestID=%d!", nRequestID);
		//g_pTrace->TraceLn("CUserData::Load失败, RequestID=%d!", nRequestID);
		return FALSE;
	}

	return TRUE;
}

//返回TRUE表示切换场景数据保存OK，用于踢人
BOOL CUserData::IsDataSaveOK(void)
{
	return m_bDataSaveOK;
}

//踢玩家
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
		g_pTrace->TraceLn("CUserData::KickUser失败, 保存失败!");
	}
}

// 定时存盘处理
void CUserData::TimeSave(BOOL bUpdateLevel)
{
	// 1小时处理一次定时存盘
	DWORD dwCurrent = GetTickCount();
	if (dwCurrent - m_dwLastSave > 0 && dwCurrent - m_dwLastSave < g_dwSaveTimes )
	{
		// 非升级状态 才判断是否返回
		if (bUpdateLevel == FALSE)
		{
			return;
		}
	}

	m_dwLastSave = dwCurrent;

	//	g_pTrace->TraceLn("UserID=%ld, 开始定时存盘...", m_qwUserID);

	// 如果交互数据已经加载则进行保存
	if (m_InteractSet.lOwnerID != 0)
	{
		if (FALSE == g_pDBEngine->Request(0, REQUESTID_INTERACT_SAVE, m_qwUserID,
			(char*)&m_InteractSet, sizeof(m_InteractSet), this))
		{
			g_pTrace->TraceLn("CUserData::TimeSave失败, 交互数据保存失败!");
			return;
		}

		//		g_pTrace->TraceLn("UserID=%d, 开始保存交互数据!", m_qwUserID);
	}

	// 开始保存数据库
	list<SGoodsUpdate_Set>::iterator it = m_GoodsSet.begin();
	for (; it != m_GoodsSet.end(); ++it)
	{
		SGoodsUpdate_Set *pTemp = &(*it);
		if (FALSE == g_pDBEngine->Request(0, REQUESTID_GOODS_UPDATE, m_qwUserID,
			(char*)pTemp, sizeof(SGoodsUpdate_Set), this))
		{
			g_pTrace->TraceLn("CUserData::TimeSave失败, 物品更新保存失败!");
			return;
		}

		//		g_pTrace->TraceLn("UserID=%d, 开始保存容器%d物品%d个!",
		//			m_qwUserID, pTemp->lContainerID, pTemp->lGoodsNum);
	}

	// 如果玩家基本数据已经加载则进行保存
	if (m_UpdateSet.qwUserID != 0)
	{
		if (FALSE == g_pDBEngine->Request(0, REQUESTID_ACTOR_UPDATE, m_qwUserID,
			(char*)&m_UpdateSet, sizeof(m_UpdateSet), this))
		{
			g_pTrace->TraceLn("CUserData::TimeSave失败, 玩家更新保存失败!");
			return;
		}

		//		g_pTrace->TraceLn("UserID=%d, 开始保存基本数据!", m_qwUserID);
	}
}

