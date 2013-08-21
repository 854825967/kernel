#ifndef _LINKMANAGE_H_
#define _LINKMANAGE_H_

#include "../../Public/ComDefine.h"
#include "../../Public/CHashMap.h"
#include "LinkInfo.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define MAX_PEER_COUNTS 4096

class LinkManage {
public:
    LinkManage();
    ~LinkManage();
    bool AddLinkType(const char * pLinkType);
    LinkInfo * NewLink(const UI16 nSocket, const char * pLinkType = NULL);
    bool RecycleLink(LinkInfo * & pLinkInfo);
    LinkInfo * FindLinkBySocket(const UI16 nSocket);

    bool IsExsitType(const char * pLinkType);
    const vector<LinkInfo *> * GetTypeOfLinks(const char * pLinkType);
private:
    //存储所有存在的类型
    vector<string> m_alltype;
    //分类型存储所有链接
    CHashMap<string, vector<LinkInfo *> > m_alllink;
    //端管理
    vector<LinkInfo *> m_recycle;
    //方便快速查找
    CHashMap<UI16, LinkInfo *> m_QuickPosition;
    UI16 m_current;
    LinkInfo m_peers[MAX_PEER_COUNTS];
};

#endif //_LINKMANAGE_H_
