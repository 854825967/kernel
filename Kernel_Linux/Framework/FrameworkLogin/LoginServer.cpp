///* 
// * File:   LoginServer.cpp
// * Author: traveler
// * 
// * Created on January 4, 2013, 5:56 PM
// */
//
//#include "LoginServer.h"
//#include "../Public/IKernel.h"
//#include <string>
//using namespace std;
//
//bool LoginServer::Initialize(IKernel * pKernel) {
//
//    return true;
//}
//
//bool LoginServer::DelayInitialize(IKernel * pKernel) {
//    if (string("Login") == pKernel->GetServerType()) {
//        pKernel->AddKernelEventSOCKETCALL("Gate", KERNEL_EVENT_NEW_CONNECTION, \
//            LoginServer::NewGateConnectIn);
//    }
//
//    return true;
//}
//
//bool LoginServer::Destroy(IKernel * pKernel) {
//
//    return true;
//}
//
//I32 LoginServer::NewGateConnectIn(const IKernel* pKernel, const UI32 nPeerID, const UI32, const IVarList&) {
//
//    char log[64] = {0};
//    snprintf(log, 64, "New Connection from Gate PeerID : %d", nPeerID);
//    LOG_DEBUG(log);
//    return 0;
//}
