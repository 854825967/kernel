//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 5052 $
// $Author: than $
// $Date: 2012-02-27 15:39:19 +0800 (鍛ㄤ竴, 2012-02-27) $
//
// Define class CConnectStateSink.
//

#include "ConnectStateSink.h"

#include "GateWayServiceMgr.h"
#include "IConnectSink.h"
#include "ConnectSinkMgr.h"

CConnectStateSink::CConnectStateSink() {}

CConnectStateSink::~CConnectStateSink() {}

core::ConnectionTask *CConnectStateSink::OnAccept() {
  CRunStateSink *pRunStateSink = static_cast<CRunStateSink*>(g_GateWayServiceMgr->GetConnectSinkPool()->GetARunSink());
  if(NULL == pRunStateSink) {
    // g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("pRunStateSink is NULL!");
    return NULL;
  }

  if(FALSE == pRunStateSink->StartConnectSink(
		g_GateWayServiceMgr->GetConnectSinkMgr()->GetConnectIndex())) {
    // g_GateWayServiceMgr->GetServerLog()->TraceErrorLn("pRunStateSink StartConnectSink() failed!");
    return NULL;
  }

  return pRunStateSink;
}

