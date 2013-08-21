#include "MultiSys.h"
#include "CNet.h"

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) INet * GET_NET_FUN(const u8 threadcount, const u16 sockcount) {
    CNet * p = NEW CNet(threadcount, sockcount);
    return p;
}

__declspec(dllexport) void RETURN_NET_FUN(INet * p) {
    delete p;
}

#ifdef __cplusplus
};
#endif
