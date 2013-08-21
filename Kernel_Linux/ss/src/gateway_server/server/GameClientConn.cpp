#include "GameClientConn.h"
#include "GateWayServiceMgr.h"
#include "GameClientMgr.h"
#include "ClientIDGenerator.h"
#include "IConnectSink.h"
#include "ConnectSinkMgr.h"
#include "IDataArchive.h"
#include "IDBStruct.h"
#include "ILog.h"
#include "VestibuleRunSink.h"

CGameClientConn::CGameClientConn(const InetAddress &server_address, const std::string &name)
       : TCPClient(server_address, name), m_pGameClientMgr(NULL), m_bISRun(FALSE),
       m_dwGameID(-1)  
{
	m_bISRun = FALSE;
	m_dwGameID = -1;
	m_pGameClientMgr = NULL;

	server_address.GetAddressInfo(this->m_lpszAppIP, sizeof(this->m_lpszAppIP), this->m_wPort);
}

CGameClientConn::~CGameClientConn(void)
{
	
} 

void CGameClientConn::Release()
{
	delete this;
}

BOOL CGameClientConn::Create(CGameClientMgr *pGameClientMgr, u32 dwGameID)
{
	if(m_bISRun == FALSE)
	{
		IServerKernel *pServerKernel = g_GateWayServiceMgr->GetServerKernel();
		if (pServerKernel == NULL)
		{
			return FALSE;
		}

		m_pGameClientMgr = pGameClientMgr;
		m_dwGameID = dwGameID;

		if(pServerKernel->StartClient(this) == true) {
			return TRUE;
		}
	}

	return FALSE;
}

void CGameClientConn::OnRecieve(const char *Buf, int nLen)
{
	if (Buf == NULL || (size_t)nLen < sizeof(SGateWayMsgHead)) 
	{
		return;
	}

	SGateWayMsgHead *phead = (SGateWayMsgHead *)Buf;
	int nOffset = sizeof(SGateWayMsgHead);
	switch(phead->m_wKeyRoot)
	{
	case GATEWAY_SCMSG_APPSERVERINFO:
		{
			SAppServerInfo *pMsg = (SAppServerInfo *)Buf;
 
			// 向网关发送本服信息 
			memcpy(&m_SAppServerInfo,pMsg,sizeof(SAppServerInfo));
			g_GateWayServiceMgr->GetServerLog()->TraceLn("连接游戏服务器Id = %d IP =%s 端口 =%d 成功!",
					m_dwGameID, m_lpszAppIP, m_wPort );
			m_pGameClientMgr->AddGameConn(this);
			m_bISRun = TRUE;
		}
		break;
	case GATEWAY_SCMSG_SENDTO_SCENE:			// 场景服发送消息给客户端
		{
			CDataArchive dataArchive((void*)(Buf+nOffset), nLen-nOffset);
			ClientID* pClientID = (ClientID*)(Buf+nOffset);
			// ClientIDInfo* pClientIDInfo = (ClientIDInfo*)pClientID;
			ClientIDInfo* pClientIDInfo = ClientIDGenerator::getInstance()->GetClientIDInfo(*pClientID);
      if( NULL != pClientIDInfo )
      {
        nOffset += sizeof(ClientID);
        // this->SendData((LPCSTR)(Buf+nOffset), nLen-nOffset);
        IConnectSink *pConnectSink = g_GateWayServiceMgr->GetConnectSinkMgr()->GetConnectSink(
            pClientIDInfo->nConnIndex);
        if(pConnectSink) {
          pConnectSink->SendData((LPCSTR)(Buf+nOffset), nLen-nOffset);
        } else {
          g_GateWayServiceMgr->GetServerLog()->TraceLn("pConnectSink is NULL");
        }
      }
		}
		break;
	case GATEWAY_SCBATCHMSG_SENDTO_SCENE:		// 场景服广播的消息
		{
			// 1+2+4+ 1
			if (nLen < 8)
			{
				g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
						"网关接收到非法的广播数据：广播数据至少8个字节, 字节数 :%d",nLen);
				return;
			}
			u16* pwClientNum = (u16*)(Buf+nOffset);
			nOffset += sizeof(u16);
 
			s32 buffoff= nOffset + (*pwClientNum)*sizeof(ClientID);
			// 放到客户端的消息的长度
			s32 buffLen = nLen - buffoff;
			if (buffLen <=0)
			{
				g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
						"网关接收到非法的广播数据 buffLen = %d",buffLen);
				return;
			}

 			if(*pwClientNum >= CLIENT_CONNECT_MAX_NUM)
 			{
 				return;
 			}

			s32 nSocketsNum = 0;
 
			for( s32 i = 0; i < *pwClientNum; ++i )
			{
				ClientID* pClientID = (ClientID*)(Buf+nOffset);
				// ClientIDInfo* pClientIDInfo = (ClientIDInfo*)pClientID;
        ClientIDInfo* pClientIDInfo = ClientIDGenerator::getInstance()->GetClientIDInfo(*pClientID);
        if( NULL != pClientIDInfo ) {
          nOffset += sizeof(ClientID);

          IConnectSink* pConnectSink = g_GateWayServiceMgr->GetConnectSinkMgr()->GetConnectSink(pClientIDInfo->nConnIndex);
          if(pConnectSink) {
            pConnectSink->SendData(Buf+buffoff, buffLen);
            nSocketsNum++;
          }
        }
			}
		}
		break; 
	case GATEWAY_SCBATCHMSG_SENDTO_CLIENT:
		{
			SBatchMsgToClient *msg = (SBatchMsgToClient *)Buf;
		
			IConnectSink		*m_pRunBuf[MAX_CONNECT_NUM];
			memset(m_pRunBuf,0,sizeof(m_pRunBuf));
			s32 nRunNum = MAX_CONNECT_NUM;
			g_GateWayServiceMgr->GetConnectSinkMgr()->GetAllCSink_ByState(m_pRunBuf,nRunNum,enConnState_Running);
			for (s32 i = 0 ; i < nRunNum; i++ )
			{
				IConnectSink *pRunCSink = m_pRunBuf[i];
				if (pRunCSink == NULL)
				{
					continue;
				}
				pRunCSink->SendData(msg->pData,msg->nDataLen);
			}
		}
		break;
	case GATEWAY_SCMSG_CHANGE_SCENE_SERVER:
		{
			SChangeZone* msg = (SChangeZone *)Buf;

			BOOL bFind = FALSE;

			// 切换至新场景服
			ClientIDInfo* pClientIDInfo = ClientIDGenerator::getInstance()->GetClientIDInfo(msg->lIdenID);
			if( NULL != pClientIDInfo )
			{
				IConnectSink* pConnectSink = g_GateWayServiceMgr->GetConnectSinkMgr()->GetConnectSink(pClientIDInfo->nConnIndex);
				if( NULL != pConnectSink )
				{
					pConnectSink->OnMessage( enConnSink_NextZone, Buf, nLen );
					bFind = TRUE;
				}
				else
				{
					g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
							"[找到错误]网关找不到userId = %ld的对应的客户端Id的链接",
							msg->qwUserID);
				}
			}
			else
			{
				g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
						"[找到错误]网关找不到userId = %ld对应的客户端Id的相关信息", 
						msg->qwUserID);
			}

			if(!bFind)
			{
				// 如果是切换场景服，则向前端请求跳转完成
				SLoginUserJumpFinish_Set JumpFinishSet;
				JumpFinishSet.qwUserID = msg->qwUserID;
				memcpy( JumpFinishSet.szRand, msg->szRand, sizeof(JumpFinishSet.szRand) );
				memcpy( JumpFinishSet.ValidationCode, msg->ValidationCode, sizeof(msg->ValidationCode) );
				IVestibule *pVestibule = g_GateWayServiceMgr->GetVestibule(msg->qwUserID);
				BOOL bRet = pVestibule->Request(0, REQ_VESTIB_LOGIN_USER_JUMP_FINISH, 
					msg->qwUserID, (char *) &JumpFinishSet, 
					sizeof(JumpFinishSet), &g_VestibuleRunSink);

				if (FALSE == bRet)
				{
					g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
							"[GATEWAY_SCMSG_CHANGE_SCENE_SERVER] " \
							"向前端发送帐号验证请求失败, UserDBID: %ld", msg->qwUserID);
					return;
				}
			}
		}
		break;
	case GATEWAY_OR_SCENE_ACTOR_LOGOUT:
		{
			SKickoutClient* msg = (SKickoutClient*)Buf;
			ClientIDInfo* pClientIDInfo = ClientIDGenerator::getInstance()->GetClientIDInfo(msg->lIdenID);
			if( NULL != pClientIDInfo )
			{
				IConnectSink* pConnectSink = g_GateWayServiceMgr->GetConnectSinkMgr()->GetConnectSink(pClientIDInfo->nConnIndex);
				if( NULL != pConnectSink )
				{
					pConnectSink->CloseConnects( (CLOSE_CONN)(msg->dwReason) );
				}
			}
		}
		break;
	case GATEWAY_SCMSG_AGAIN_SELECT_SECENE:
		{
			SAgainSelectScene* packet = (SAgainSelectScene*)Buf;
			ClientIDInfo* pClientIDInfo = ClientIDGenerator::getInstance()->GetClientIDInfo(packet->lIdenID);
			if( NULL != pClientIDInfo )
			{
				IConnectSink* pConnectSink = g_GateWayServiceMgr->GetConnectSinkMgr()->GetConnectSink(pClientIDInfo->nConnIndex);
				if( NULL != pConnectSink )
				{
					pConnectSink->OnMessage(enConnSink_AgainSelectSceneSvr,Buf,nLen);
				}
			}
		}
		break;
	default:
		break;
	}
}

void CGameClientConn::OnCloseConnection(bool force)
{
	m_bISRun = FALSE;
	g_GateWayServiceMgr->GetServerLog()->TraceLn("断开场景服务器Id[%d] IP[%s] 成功!",
			m_dwGameID, m_lpszAppIP);

	// 断开和该场景服连接的所有客户端
	IConnectSink* pConnectSinks[MAX_CONNECT_NUM];
	memset(pConnectSinks, 0, sizeof(pConnectSinks));
	int nNum = MAX_CONNECT_NUM;
	g_GateWayServiceMgr->GetConnectSinkMgr()->GetAllCSink_ByState(pConnectSinks, nNum, enConnState_Running);

	for(int i = 0; i < nNum; ++i)
	{
		IConnectSink* pClientConnect = pConnectSinks[i];
		if(NULL != pClientConnect)
		{
			if(pClientConnect->GetGameID() == m_dwGameID)
			{
				pClientConnect->CloseConnects(enClose_Conn_Max);
			}
		}
	}

	this->Stop();
	this->Start();
}

ConnectionTask *CGameClientConn::OnConnectionEstablished() {
	return this;
}

void CGameClientConn::OnConnectionOK()
{
	// 应用服务器发送信息
	SGateWayLoginServer msg;
	strncpy(msg.szIP, g_GateWayServiceMgr->GetServerIP(), sizeof(msg.szIP));
	msg.wProt = g_GateWayServiceMgr->GetServerPort();   
 	msg.nGateWayID = g_GateWayServiceMgr->GetGateWayID();
	// this->SendData((LPCSTR)&msg,sizeof(msg));
	this->Send((LPCSTR)&msg,sizeof(msg));
}


BOOL CGameClientConn::SendData(const char *Buf, int nLen) {
  if(m_bISRun == FALSE) return FALSE;
  this->Send(Buf, nLen);
  return TRUE;
}
