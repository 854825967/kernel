#include "VestibuleRunSink.h"
#include "GateWayServiceMgr.h"
#include "ConnectSinkMgr.h"
#include "IConnectSink.h"
#include "ILog.h"

CVestibuleRunSink g_VestibuleRunSink;

CVestibuleRunSink::CVestibuleRunSink(void)
{

}

CVestibuleRunSink::~CVestibuleRunSink(void)
{

}

void CVestibuleRunSink::OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID,
       LPSTR pOutData, s32 nOutDataLen, LPSTR pInData, s32 nInDataLen)
{
	IConnectSink *pConnectSink = g_GateWayServiceMgr->GetConnectSinkMgr()->GetConnectSink(nIndex);
	if (NULL == pConnectSink || enConnState_Running != pConnectSink->GetConnectSinkState())
	{
		if (NULL != pConnectSink)
		{
			g_GateWayServiceMgr->GetServerLog()->TraceErrorLn(
				"CVestibuleRunSink::OnRet(), State error, UserID: %ld, RequestID: %d", 
				qwUserID, nRequestID);
		}

		return;
	}

	pConnectSink->OnRet(nIndex, nRetCode, qwUserID, nRequestID, pOutData, nOutDataLen, pInData, nInDataLen);
}
