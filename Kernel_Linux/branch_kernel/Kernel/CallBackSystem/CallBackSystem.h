#ifndef _CALLBACKSYSTEM_H_
#define _CALLBACKSYSTEM_H_
#include "../Interface/ICallBackSystem.h"
#include "../../Public/CallBack.h"
#include "../../Public/CHashMap.h"
#include <string>
#include <map>
using namespace std;

class CallBackSystem : public ICallBackSystem {
public:
    static ICallBackSystem * Employ();
    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();
    //interface
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const SOCKETCALL pFun);
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const OBJCALL pFun);
    virtual bool ExMsgCall(const IKernel * pKernel, const char * pLinkType, 
        const UI32 nMsgId, const UI32 nID, const IVarList & args);
    virtual bool ExMsgCall(const IKernel * pKernel, const char * pLinkType, 
        const UI32 nMsgId, const CIdentity & player, const IVarList & args);
    virtual bool AddKernelEvent(const char * pLinkType, const UI32 nEventId, const SOCKETCALL pFun);
    virtual bool ExKernelEvent(const IKernel * pKernel, const char * pLinkType,
        const UI32 nMsgId, const UI32 nID, const IVarList & args);
private:
    CallBackSystem(); 
    ~CallBackSystem();

private:
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * > m_MsgCallPoll;
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * > m_EventCallPool;
    
    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * > m_ObjMsgCallPool;
    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * > m_ObjEventCallPool;
    //Command功能
    //CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * > m_ObjCommandPool;
    
    static CallBackSystem * m_pSelf;
};

#endif //_CALLBACKSYSTEM_H_
