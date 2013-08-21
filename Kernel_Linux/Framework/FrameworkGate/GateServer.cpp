///* 
// * File:   Gate.cpp
// * Author: traveler
// * 
// * Created on January 4, 2013, 5:56 PM
// */
//
//#include "GateServer.h"
//#include "../Public/EventDefine.h"
//#include "../Public/IKernel.h"
//#include <string>
//using namespace std;
//
//GateServer * GateServer::m_pSelf = NULL;
//
//bool GateServer::Initialize(IKernel * pKernel) {
//    m_nLoginSrvPeerID = 0;
//    m_pSelf = this;
//    Assert(m_pSelf != NULL);
//
//    return true;
//}
//
//bool GateServer::DelayInitialize(IKernel * pKernel) {
//    if (string("Gate") == pKernel->GetServerType()) {
//        pKernel->AddKernelEventSOCKETCALL("Login", KERNEL_EVENT_CONNECT_SUCCESS, \
//            GateServer::ConnectedToLoginServer); //代表连接Gate服务器成功 给的回调
//    }
//    return true;
//}
//
//bool GateServer::Destroy(IKernel * pKernel) {
//
//    return true;
//}
//
//UI32 GateServer::GetLoginServerPeerID() {
//    return m_nLoginSrvPeerID;
//}
//
//I32 GateServer::ConnectedToLoginServer(const IKernel * pKernel, const UI32 nLoginServerPeerID, const UI32 nNotUse, const IVarList & args) {
//    m_pSelf->m_nLoginSrvPeerID = nLoginServerPeerID;
//    return 0;
//}
