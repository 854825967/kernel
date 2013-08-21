// 定义控制台应用程序的入口点。

#ifdef _DEBUG
//#include "crtdbg.h"
//#include "vld.h"
#endif  //_DEBUG

#include "CoreModuleManage.h"
#include "CallBackSystem.h"
#include "ComIocp.h"
#include "ConnectionPool.h"
#include "PeerManage.h"
#include "Kernel.h"
#include "LogicModuleManage.h"
#include "BaseConfig.h"
#include "./Dump/CDumper.h"

#include <WinSock2.h>



int main(int argc, char * argv[])
{
// #ifdef _DEBUG
//     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
// #endif  //_DEBUG
    CoreModuleManage * pCoreModuleManage = CoreModuleManage::Employ();

    EMPLOY_MODULE(CallBackSystem);
    EMPLOY_MODULE(PeerManage);
    EMPLOY_MODULE(ConnectionPool);
    EMPLOY_MODULE(Kernel);
    EMPLOY_MODULE(LogicModuleManage);
    EMPLOY_MODULE(ComIocp);
    EMPLOY_MODULE(BaseConfig);

    pCoreModuleManage->InitializeCModules();
    pCoreModuleManage->DelayInitializeCModules();
    LogicModuleManage * pLogicModuleManage = (LogicModuleManage *)pCoreModuleManage->GetModule("LogicModuleManage");
//     pLogicModuleManage->ModulesInitialize();
//     pLogicModuleManage->ModulesDelayInitialize();

    ComIocp * pComIocp = (ComIocp *)pCoreModuleManage->GetModule("ComIocp");
    pComIocp->CWork();
    pLogicModuleManage->Destroy();

    return 0;
}
