#ifndef CALLBACK_H
#define CALLBACK_H

#include "CallBackDefine.h"

#include <map>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class CallBack
{
public:
    CallBack()
    {

    }

    ~CallBack()
    {
        map< T,vector< CALLFUN > * >::iterator itor = m_mapContainer.begin();
        map< T,vector< CALLFUN > * >::iterator iEnd = m_mapContainer.end();

        while (itor != iEnd)
        {
            if (NULL != itor->second)
            {
                delete itor->second;
                itor->second = NULL;
            }
            itor++;
        }
    }

    bool AddCall(const T nMsgId, const CALLFUN pFun)
    {
        map< T,vector< CALLFUN > * >::iterator iFind = m_mapContainer.find(nMsgId);

        vector< CALLFUN > * pVct;

        if (iFind == m_mapContainer.end())
        {
            pVct = NEW vector< CALLFUN > ;
            m_mapContainer.insert(make_pair(nMsgId, pVct));
        }
        else
        {
            pVct = iFind->second;
        }

        vector< CALLFUN >::iterator itor = std::find(pVct->begin(), pVct->end(), pFun );
        if (itor != pVct->end())
        {
            LOG_ERROR("This call is exist");
            return false;
        }

        pVct->push_back(pFun);
        return true;
    }

    bool ExecCallBack(const T nMsgId, IKernel * pKernel, const UI64 nUserID, const VarList & args)
    {
        map< T,vector< CALLFUN > * >::iterator iFind = m_mapContainer.find(nMsgId);

        if (iFind == m_mapContainer.end())
        {
            LOG_ERROR("This call is not exist");
            return false;
        }

        vector< CALLFUN > * pVct = iFind->second;
        vector< CALLFUN >::iterator itor = pVct->begin();
        vector< CALLFUN >::iterator iEnd = pVct->end();

        while (itor != iEnd)
        {
            (*itor)(pKernel, nUserID, args);
            itor++;
        }

        return true;
    }

private:
    map< T,vector< CALLFUN > * > m_mapContainer;
};
#endif  //MSGCALLBACK_H