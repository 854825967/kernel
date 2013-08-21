/*
 * File:   main.cpp
 * Author: traveler
 *
 * Created on December 7, 2012, 4:13 PM
 */
#define KERNEL_PROCESS


#include "NetSystem/NetSystem.h"
#include "CallBackSystem/CallBackSystem.h"
#include "Config/ConfigManage.h"
#include "LogicManage/LogicManage.h"
#include "HeartBeatManage/HeartBeatManage.h"
#include "Kernel.h"
#include "LogSystem/LogSystem.h"
#include "ObjectManage/ObjectManage.h"
#include "Console/Console.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
//#ifdef _DEBUG
//    getchar();
//#endif //_DEBUG
//0x00007ff326432248

    ILogSystem * pLogSystem = LogSystem::Employ();
    Assert(pLogSystem->Initialize());

    IObjectManage * pObjectManage = ObjectManage::Employ();
    Assert(pObjectManage->Initialize());

    IBase * pConfigManage = ConfigManage::Employ();
    Assert(pConfigManage->Initialize());

    IBase * pCallBackSystem = CallBackSystem::Employ();
    Assert(pCallBackSystem->Initialize());

    IBase * pHeartBeatManage = HeartBeatManage::Employ();
    Assert(pHeartBeatManage->Initialize());

    Kernel * pKernel = (Kernel *) Kernel::Employ();
    Assert(pKernel->Initialize());

    IBase * pLogicManage = LogicManage::Employ();
    Assert(pLogicManage->Initialize());

    IConsole * pConsole = Console::Employ();
    Assert(pConsole->Initialize());
    
    INetSystem * pNetSystem = NetSystem::Employ();
    Assert(pNetSystem->Initialize());

    pNetSystem->MainLoop(30, 50);

    pNetSystem->Destroy();
    pConsole->Destroy();
    pLogicManage->Destroy();
    pKernel->Destroy();
    pHeartBeatManage->Destroy();
    pCallBackSystem->Destroy();
    pConfigManage->Destroy();
    pLogSystem->Destroy();
    
    return 0;
}
