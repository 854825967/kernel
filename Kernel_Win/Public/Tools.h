#ifndef TOOLS_H
#define TOOLS_H

#include "ComDefine.h"


inline const char * GetAppPath()
{
    static bool res = false;
    static char * pStr = NULL;
    
    if (false == res)
    {
        pStr = NEW char[256];
        GetModuleFileName(NULL, pStr, 256);
        PathRemoveFileSpec(pStr);
        res = true;
    }

    return pStr;
}

#endif //TOOLS_H