#ifndef CBDEFINE_H
#define CBDEFINE_H

#include "ComDefine.h"
#include <string>
using namespace std;

class VarList;
class IKernel;

typedef I32 (__cdecl *CALLFUN)(IKernel *, const UI64, const VarList &); //后期这里 按照需求来该 callfun的定义

enum
{
    CALLBACK_TYPE_MESSAGE = 0,
    CALLBACK_TYPE_EVENT = 1,
};

typedef struct _event
{
    string strName;
    UI8_TYPE nObjectType;

    inline bool operator==(const struct _event & target)
    {
        if (this->strName == target.strName &&
            this->nObjectType == target.nObjectType)
        {
            return true;
        }

        return false;
    }
}Event;


#endif