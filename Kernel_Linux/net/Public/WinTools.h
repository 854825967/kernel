#ifndef WINTOOLS_H
#define WINTOOLS_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

inline bool GetAcceptExFun(LPFN_ACCEPTEX & acceptfun) {
    GUID GuidAcceptEx = WSAID_ACCEPTEX;
    DWORD dwBytes = 0;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx, 
        sizeof(GuidAcceptEx), &acceptfun, sizeof(acceptfun), 
        &dwBytes, NULL, NULL);

    if (NULL == acceptfun) {
        ECHO_ERROR("Get AcceptEx fun error, error code : %d", ::WSAGetLastError());
        return false;
    }

    return true;
}

inline bool GetConnectExFun(LPFN_CONNECTEX & connectfun) {
    GUID GuidConnectEx = WSAID_CONNECTEX;
    DWORD dwBytes = 0;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidConnectEx, 
        sizeof(GuidConnectEx), &connectfun, sizeof(connectfun), 
        &dwBytes, NULL, NULL);

    if (NULL == connectfun) {
        ECHO_ERROR("Get ConnectEx fun error, error code : %d", ::WSAGetLastError());
        return false;
    }

    return true;
}

inline const char * GetAppPath()
{
    static char * pStr = NULL;

    if (NULL == pStr)
    {
        pStr = NEW char[256];
        GetModuleFileName(NULL, pStr, 256);
        PathRemoveFileSpec(pStr);
    }

    return pStr;
}


#ifdef __cplusplus
};
#endif //__cplusplus

#endif