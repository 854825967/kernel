#ifndef CALLBACK_H
#define CALLBACK_H

#include "ComDefine.h"

#include <map>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T1, typename T2, typename CALLFUN>
class CallBack {
public:

    CallBack() {
        m_mapContainer.clear();
    }

    ~CallBack() {
        typename map< T1, vector< CALLFUN > * >::iterator itor = m_mapContainer.begin();
        typename map< T1, vector< CALLFUN > * >::iterator iEnd = m_mapContainer.end();

        while (itor != iEnd) {
            if (NULL != itor->second) {
                delete itor->second;
                itor->second = NULL;
            }
            itor++;
        }
    }

    bool AddCall(const T1 ID, const CALLFUN pFun) {
        typename map< T1, vector< CALLFUN > * >::iterator iFind = m_mapContainer.find(ID);

        vector< CALLFUN > * pVct;

        if (iFind == m_mapContainer.end()) {
            pVct = NEW vector< CALLFUN >;
            printf("AddCall\n");
            m_mapContainer.insert(make_pair(ID, pVct));
        } else {
            pVct = iFind->second;
        }

        typename vector< CALLFUN >::iterator itor = std::find(pVct->begin(), pVct->end(), pFun);
        if (itor != pVct->end()) {
            Assert(false);
            return false;
        }

        pVct->push_back(pFun);
        return true;
    }

    bool ExecCallBack(const T1 nMsgId, const IKernel * pKernel, const T2 ID_1, const T2 ID_2, const IVarList & args) {
        typename map< T1, vector< CALLFUN > * >::iterator iFind = m_mapContainer.find(nMsgId);

        if (iFind == m_mapContainer.end()) {
            return false;
        }

        vector< CALLFUN > * pVct = iFind->second;
        typename vector< CALLFUN >::iterator itor = pVct->begin();
        typename vector< CALLFUN >::iterator iEnd = pVct->end();

        while (itor != iEnd) {
            (*itor)(pKernel, ID_1, ID_2, args);
            itor++;
        }

        return true;
    }

private:
    map< T1, vector< CALLFUN > * > m_mapContainer;
};
#endif  //MSGCALLBACK_H
