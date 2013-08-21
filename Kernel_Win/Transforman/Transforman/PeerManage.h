#ifndef SERVERMANAGE_H
#define SERVERMANAGE_H

#include <string>
#include <hash_map>
using namespace std;
using namespace stdext;

#include "ComDefine.h"
#include "CallBack.h"
#include "ICoreModule.h"
class TiXmlElement;
class CallBackSystem;
class CoreModuleManage;

typedef struct peerinfo 
{
/*    UI8_TYPE nPeerType;*/
    UI32_ID nID;
    char strName[NAME_LENGTH];
    UI32_ID nMsgCallConntainerID;
    UI32_ID nEventCallConntainerID;
}PeerInfo;

//管理连接过来的服务器, 服务器ip,port以及服务器种类
class PeerManage : public ICoreModule
{
public:
    static bool Employ(const char * pStrModuleName);

    virtual bool Initialize();
    virtual bool DelayInitialize();
    virtual bool Destroy();

    UI32_ID GetPeerTypeID(const char * pStrName);
    const char * GetPeerTypeName(const UI32_ID nID);

    bool AddMsgCall(const UI32_ID nPeerCfgID, const UI32_ID nMsgID, const CALLFUN pFun);
    bool ExecMsgCallBack(const UI32_ID nPeerCfgID, const UI32_ID nMsgID, IKernel * pKernel, const UI64 nConID, const VarList & args);
    bool AddEventCall(const UI32_ID nPeerCfgID, const UI32_ID nEventID, const CALLFUN pFun);
    bool ExecEventCallBack(const UI32_ID nPeerCfgID, const UI32_ID nEventID, IKernel * pKernel, const UI64 nConID, const VarList & args);
private:
    PeerManage();
    ~PeerManage();
    bool GetConfig(TiXmlElement * pPeerTypeElm);

private:
    static PeerManage * m_pSelf;
    static CoreModuleManage * m_pCoreModuleManage;
    CallBackSystem * m_pCallBackSystem;

    hash_map<string, UI32_ID> m_hashmapPeerIndex;
    hash_map<UI32_ID, PeerInfo *> m_hashmapPeerInfo;
};

#endif
