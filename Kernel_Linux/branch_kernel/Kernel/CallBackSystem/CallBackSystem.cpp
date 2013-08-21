#include "CallBackSystem.h"
CallBackSystem * CallBackSystem::m_pSelf = NULL;

ICallBackSystem * CallBackSystem::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW CallBackSystem;
        if (!m_pSelf->Bron()) {
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }

    return m_pSelf;
}

bool CallBackSystem::Bron() {
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator ibegin = m_MsgCallPoll.begin();
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator iend = m_MsgCallPoll.end();
    while (ibegin != iend) {
        if (ibegin->second != NULL) {
            delete ibegin->second;
            ibegin->second = NULL;
        }
        ibegin++;
    }
    m_MsgCallPoll.clear();

    ibegin = m_EventCallPool.begin();
    iend = m_EventCallPool.end();
    while (ibegin != iend) {
        if (ibegin->second != NULL) {
            delete ibegin->second;
            ibegin->second = NULL;
        }
        ibegin++;
    }
    m_EventCallPool.clear();

    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * >::iterator iobegin = m_ObjMsgCallPool.begin();
    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * >::iterator ioend = m_ObjMsgCallPool.end();
    while (iobegin != ioend) {
        if (iobegin->second != NULL) {
            delete iobegin->second;
            iobegin->second = NULL;
        }
        iobegin++;
    }
    m_ObjMsgCallPool.clear();

    iobegin = m_ObjEventCallPool.begin();
    ioend = m_ObjEventCallPool.end();
    while (iobegin != ioend) {
        if (iobegin->second != NULL) {
            delete iobegin->second;
            iobegin->second = NULL;
        }
        iobegin++;
    }
    m_ObjEventCallPool.clear();

    return true;
}

bool CallBackSystem::Dead() {
    return true;
}

bool CallBackSystem::Initialize() {

    return true;
}

bool CallBackSystem::Destroy() {
    if (NULL != m_pSelf) {
        delete m_pSelf;
        m_pSelf = NULL;
    }

    return true;
}

CallBackSystem::~CallBackSystem() {
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator itor = m_MsgCallPoll.begin();
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator iend = m_MsgCallPoll.end();
    while (itor != iend) {
        if (NULL != itor->second) {

            delete itor->second;
            itor->second = NULL;
        }
        itor++;
    }

    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator itor2 = m_EventCallPool.begin();
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator iend2 = m_EventCallPool.end();
    while (itor2 != iend2) {
        if (NULL != itor2->second) {

            delete itor2->second;
            itor2->second = NULL;
        }
        itor2++;
    }

    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * >::iterator itor3 = m_ObjMsgCallPool.begin();
    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * >::iterator iend3 = m_ObjMsgCallPool.end();
    while (itor3 != iend3) {
        if (NULL != itor3->second) {

            delete itor3->second;
            itor3->second = NULL;
        }
        itor3++;
    }
}

bool CallBackSystem::AddMsgCall(const char * pLinkType, const UI32 nMsgId, const SOCKETCALL pFun) {
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator ifind = m_MsgCallPoll.find(pLinkType);

    if (ifind == m_MsgCallPoll.end()) {
        CallBack<UI32, UI32, SOCKETCALL> * pContainer = NEW CallBack<UI32, UI32, SOCKETCALL>;
        printf("CallBackSystem::AddMsgCall SOKETCALL\n");
        pContainer->AddCall(nMsgId, pFun);
        m_MsgCallPoll.insert(make_pair(pLinkType, pContainer));
        return true;
    }

    ifind->second->AddCall(nMsgId, pFun);

    return true;
}

bool CallBackSystem::AddMsgCall(const char* pLinkType, const UI32 nMsgId, const OBJCALL pFun) {
    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * >::iterator ifind = m_ObjMsgCallPool.find(pLinkType);

    if (ifind == m_ObjMsgCallPool.end()) {
        CallBack<UI32, CIdentity, OBJCALL> * pContainer = NEW CallBack<UI32, CIdentity, OBJCALL>;
        printf("CallBackSystem::AddMsgCall SOKETCALL\n");
        pContainer->AddCall(nMsgId, pFun);
        m_ObjMsgCallPool.insert(make_pair(pLinkType, pContainer));
        return true;
    }

    ifind->second->AddCall(nMsgId, pFun);

    return true;
}

bool CallBackSystem::ExMsgCall(const IKernel * pKernel, const char * pLinkType,
        const UI32 nMsgId, const UI32 nID, const IVarList & args) {
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator ifind = m_MsgCallPoll.find(pLinkType);

    if (ifind == m_MsgCallPoll.end()) {
        return false;
    }

    ifind->second->ExecCallBack(nMsgId, pKernel, nID, nID, args);

    return true;
}

bool CallBackSystem::ExMsgCall(const IKernel * pKernel, const char * pLinkType,
        const UI32 nMsgId, const CIdentity & player, const IVarList & args) {
    CHashMap<string, CallBack<UI32, CIdentity, OBJCALL> * >::iterator ifind = m_ObjMsgCallPool.find(pLinkType);

    if (ifind == m_ObjMsgCallPool.end()) {
        return false;
    }

    ifind->second->ExecCallBack(nMsgId, pKernel, player, CIdentity_INIT(), args);

    return true;
}

bool CallBackSystem::AddKernelEvent(const char * pLinkType, const UI32 nEventId, const SOCKETCALL pFun) {
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator ifind = m_EventCallPool.find(pLinkType);

    if (ifind == m_EventCallPool.end()) {
        CallBack<UI32, UI32, SOCKETCALL> * pContainer = NEW CallBack<UI32, UI32, SOCKETCALL>;
        printf("CallBackSystem::AddKernelEvent\n");
        pContainer->AddCall(nEventId, pFun);
        m_EventCallPool.insert(make_pair(pLinkType, pContainer));
        return true;
    }

    ifind->second->AddCall(nEventId, pFun);

    return true;
}

bool CallBackSystem::ExKernelEvent(const IKernel * pKernel, const char * pLinkType,
        const UI32 nMsgId, const UI32 nID, const IVarList & args) {
    CHashMap<string, CallBack<UI32, UI32, SOCKETCALL> * >::iterator ifind = m_EventCallPool.find(pLinkType);

    if (ifind == m_EventCallPool.end()) {
        return false;
    }

    ifind->second->ExecCallBack(nMsgId, pKernel, nID, nID, args);

    return true;
}

CallBackSystem::CallBackSystem() {

}