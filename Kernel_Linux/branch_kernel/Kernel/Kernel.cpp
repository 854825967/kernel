#include "Kernel.h"
#include "../Public/Tools.h"
#include "../Public/Archive.h"
#include "../Public/CXmlConfig.h"
#include "../Public/CIniConfig.h"
#include "./Config/ConfigManage.h"
#include "./CallBackSystem/CallBackSystem.h"
#include "LogicManage/LogicManage.h"
#include "NetSystem/NetSystem.h"
#include "ObjectManage/ObjectManage.h"
#include "HeartBeatManage/HeartBeatManage.h"
#include "LogSystem/LogSystem.h"


Kernel * Kernel::m_pSelf = NULL;
IConfigManage * Kernel::m_pConfigManage = NULL;
ICallBackSystem * Kernel::m_pCallBackSystem = NULL;
ILogicManage * Kernel::m_pLogicManage = NULL;
INetSystem * Kernel::m_pNetSystem = NULL;
IObjectManage * Kernel::m_pObjectManage = NULL;
IHeartBeatManage * Kernel::m_pHeartBeatManage = NULL;
ILogSystem * Kernel::m_pLogSystem = NULL;

Kernel::Kernel() {

}

Kernel::~Kernel() {
    
}

IKernel * Kernel::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW Kernel;
        if (!m_pSelf->Bron()) {
            Assert(false);
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

bool Kernel::Bron() {
    return true;
}

bool Kernel::Dead() {
    return true;
}

bool Kernel::Initialize() {
    if (NULL == (m_pConfigManage = ConfigManage::Employ()) ||
            NULL == (m_pCallBackSystem = CallBackSystem::Employ()) ||
            NULL == (m_pLogicManage = LogicManage::Employ()) ||
            NULL == (m_pNetSystem = NetSystem::Employ()) ||
            NULL == (m_pObjectManage = ObjectManage::Employ()) ||
            NULL == (m_pHeartBeatManage = HeartBeatManage::Employ()) ||
            NULL == (m_pLogSystem = LogSystem::Employ())) {

        Assert(false);
        return false;
    }

    return true;
}

bool Kernel::Destroy() {
    if(m_pSelf != NULL) {
        delete m_pSelf;
        m_pSelf = NULL;
    }
    return true;
}

//配置

const char * Kernel::GetPath() const {
    return GetAppPath();
}

const UI32 Kernel::GetServerID() const {
    const CIniConfig * pconfig = m_pConfigManage->GetConfig(KERNEL_CONFIG_BASE_INI);
    const char * pStrID = pconfig->GetStringConfig("Base", "ServerID");
    if ("" == string(pStrID)) {
        Assert(false);
        return NULL;
    }

    return StringAsInt(pStrID);
}

const char * Kernel::GetServerType() const {
    const CIniConfig * pconfig = m_pConfigManage->GetConfig(KERNEL_CONFIG_BASE_INI);
    const char * pStrType = pconfig->GetStringConfig("Base", "Type");
    if ("" == string(pStrType)) {
        Assert(false);
        return NULL;
    }

    return pStrType;
}

bool Kernel::GetIniConfig(const char * pStrPath, CIniConfig & iniconfig) const {
    char FilePath[256];
    memset(FilePath, 0, 256);
    snprintf(FilePath, 256, "%s/./%s", GetAppPath(), pStrPath);

    return iniconfig.LoadConfig(FilePath);
}

bool Kernel::GetXmlConfig(const char * pStrPath/*相对与引擎执行文件的路径*/, CXmlConfig & xmlconfig) const {
    return true;
}

//逻辑模块之间
ILogicModule * Kernel::FindModule(const char * pModuleName) const {
    return m_pLogicManage->FindModule(pModuleName);
}

//log system
bool Kernel::Echo(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const {
    return m_pLogSystem->Echo(pStrLog, pStrFile, nLine, pFunName);
}

bool Kernel::Trace(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const {
    return m_pLogSystem->Trace(pStrLog, pStrFile, nLine, pFunName);
}

bool Kernel::Debug(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const {
    return m_pLogSystem->Debug(pStrLog, pStrFile, nLine, pFunName);
}

bool Kernel::Error(const char * pStrLog, const char * pStrFile, UI32 nLine, const char * pFunName) const {
    return m_pLogSystem->Error(pStrLog, pStrFile, nLine, pFunName);
}

//bind link with player
bool Kernel::Register(const UI32 nLinkID, const CIdentity & player) const {
    return m_pObjectManage->Register(nLinkID, player);
}

//注册回调

bool Kernel::AddHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun,
        const UI64 nFrequency, const UI32 nMaxBeatCount, const bool beatatonce) const {

    return m_pHeartBeatManage->AddHeartBeat(obj, pBeatFun, nFrequency, nMaxBeatCount, beatatonce);
}

bool Kernel::DelHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) const {

    return m_pHeartBeatManage->DelHeartBeat(obj, pBeatFun);
}

bool Kernel::IsExistsHeartBeat(const CIdentity & obj, const BEATFUN pBeatFun) const {

    return m_pHeartBeatManage->IsExistsHeartBeat(obj, pBeatFun);
}

bool Kernel::AddMsgCall(const char * pLinkType, const UI32 nMsgId, const SOCKETCALL pFun) const {
    return m_pCallBackSystem->AddMsgCall(pLinkType, nMsgId, pFun);
}

bool Kernel::AddMsgCall(const char * pLinkType, const UI32 nMsgId, const OBJCALL pFun) const {
    return m_pCallBackSystem->AddMsgCall(pLinkType, nMsgId, pFun);
}

bool Kernel::AddKernelEvent(const char * pLinkType, const UI32 nEventId, const SOCKETCALL pFun) const {
    m_pCallBackSystem->AddKernelEvent(pLinkType, nEventId, pFun);
    return true;
}

bool Kernel::SendMsg(const UI32 nLinkID, const IArchive & msg) const {

    return m_pNetSystem->Send(nLinkID, msg);
}

bool Kernel::SendMsg(const CIdentity player, const IArchive& msg) const {
    const UI32 nLinkID = m_pObjectManage->QueryLinkID(player);
    if (0 == nLinkID) {
//        Assert(false);
        return false;
    }

    return SendMsg(nLinkID, msg);
}

bool Kernel::BroadCastByLinkType(const char* pLinkType, const IArchive & msg, const IVarList & blacklist) const {
    return m_pNetSystem->BroadCast(pLinkType, msg, blacklist);
}

bool Kernel::SendMsg(const UI32 nLinkID, const IVarList & msg) const {
    UI32 nCount = msg.Count();
    Archive achmsg;
    for (UI32 i = 0; i < nCount; i++) {
        switch (msg.Type(i)) {
            case TYPE_INT:
                achmsg << msg.GetInt(i);
                break;
            case TYPE_INT64:
                achmsg << msg.GetInt64(i);
                break;
            case TYPE_STRING:
                achmsg << msg.GetString(i);
                break;
            case TYPE_WIDESTR:
                achmsg << msg.GetWideStr(i);
                break;
            case TYPE_DOUBLE:
                achmsg << msg.GetDouble(i);
                break;
            default:
            {
                Assert(false); //不知到是什么类型
                return false;
            }
        }
    }

    return m_pNetSystem->Send(nLinkID, achmsg);
}

bool Kernel::SendMsg(const CIdentity player, const IVarList & msg) const {
    const UI32 nLinkID = m_pObjectManage->QueryLinkID(player);
    if (0 == nLinkID) {
        Assert(false);
        return false;
    }

    return SendMsg(nLinkID, msg);
}

bool Kernel::BroadCastByLinkType(const char* pLinkType, const IVarList& msg, const IVarList & blacklist) const {
    UI32 nCount = msg.Count();
    Archive achmsg;
    for (UI32 i = 0; i < nCount; i++) {
        switch (msg.Type(i)) {
            case TYPE_INT:
                achmsg << msg.GetInt(i);
                break;
            case TYPE_INT64:
                achmsg << msg.GetInt64(i);
                break;
            case TYPE_STRING:
                achmsg << msg.GetString(i);
                break;
            case TYPE_WIDESTR:
                achmsg << msg.GetWideStr(i);
                break;
            case TYPE_DOUBLE:
                achmsg << msg.GetDouble(i);
                break;
            default:
            {
                Assert(false); //不知到是什么类型
                return false;
            }
        }
    }

    return m_pNetSystem->BroadCast(pLinkType, achmsg, blacklist);
}

bool Kernel::Close(const UI32 nLinkID) const {
    return m_pNetSystem->Close(nLinkID);
}
