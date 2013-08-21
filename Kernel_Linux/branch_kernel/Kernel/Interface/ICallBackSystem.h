#ifndef _ICALLBACKSYSTEM_H_
#define _ICALLBACKSYSTEM_H_

#include "../../Public/ComDefine.h"
#include "IBase.h"

class ICallBackSystem : public IBase {
public:
    //interface
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const SOCKETCALL pFun) = 0;
    virtual bool AddMsgCall(const char * pLinkType, const UI32 nMsgId, const OBJCALL pFun) = 0;
    virtual bool ExMsgCall(const IKernel * pKernel, const char * pLinkType,
            const UI32 nMsgId, const UI32 nID, const IVarList & args) = 0;
    virtual bool ExMsgCall(const IKernel * pKernel, const char * pLinkType, 
        const UI32 nMsgId, const CIdentity & player, const IVarList & args) = 0;
    virtual bool AddKernelEvent(const char * pLinkType, const UI32 nEventId, const SOCKETCALL pFun) = 0;
    virtual bool ExKernelEvent(const IKernel * pKernel, const char * pLinkType,
            const UI32 nEventId, const UI32 nID, const IVarList & args) = 0;
};

#endif //_ICALLBACKSYSTEM_H_
