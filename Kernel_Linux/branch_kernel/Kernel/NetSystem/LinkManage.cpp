#include "LinkManage.h"
#include <unistd.h>
using namespace std;

LinkManage::LinkManage() {
    m_current = 0;
}

LinkManage::~LinkManage() {

}

bool LinkManage::IsExsitType(const char* pLinkType) {
    vector<string>::iterator iend = m_alltype.end();
    vector<string>::iterator ifind = find(m_alltype.begin(), iend, pLinkType);
    if (ifind == iend) {
        return false;
    }

    return true;
}

LinkInfo * LinkManage::NewLink(const UI16 nSocket, const char * pLinkType /*= NULL*/) {
    LinkInfo * pLinkInfo = NULL;

    if (pLinkType != NULL && !IsExsitType(pLinkType)) {
        //类型不存在
        Assert(false);
        return NULL;
    }

    if (NULL != FindLinkBySocket(nSocket)) {
        Assert(false);
        //这里输出日志
        return NULL;
    }

    if (!m_recycle.empty()) {
        pLinkInfo = m_recycle[0];
        m_recycle.erase(m_recycle.begin());
    } else {
        if (m_current + 1 >= MAX_PEER_COUNTS) {
            Assert(false);
            return NULL;
        }
        pLinkInfo = m_peers + m_current++;
    }

    if (pLinkType != NULL) {
        //分类型存储所有链接
        CHashMap<string, vector<LinkInfo *> >::iterator ifind = m_alllink.find(pLinkType);
        if (ifind == m_alllink.end()) {
            Assert(false);
            pLinkInfo->Reset();
            RecycleLink(pLinkInfo);
            return NULL;
        }

        vector<LinkInfo *>::iterator itor = find(ifind->second.begin(), ifind->second.end(), pLinkInfo);
        if (itor != ifind->second.end()) {
            Assert(false); //该peerinfo已经被使用了 而且没被正确回收   说明代码有问题 要检查
            ifind->second.erase(itor);
            pLinkInfo->Reset();
            RecycleLink(pLinkInfo);
            return NULL;
        } else {
            ifind->second.push_back(pLinkInfo);
        }

        pLinkInfo->SetRemoteType(pLinkType);
    }

    pLinkInfo->m_socket = nSocket;
    m_QuickPosition.insert(make_pair(nSocket, pLinkInfo));
    pLinkInfo->m_closeit = false;
    return pLinkInfo;
}

bool LinkManage::AddLinkType(const char * pLinkType) {
    if (NULL == pLinkType) {
        Assert(false);
        return false;
    }

    vector<string>::iterator ifindv = find(m_alltype.begin(), m_alltype.end(), pLinkType);
    CHashMap<string, vector<LinkInfo *> >::iterator ifindm = m_alllink.find(pLinkType);
    if (ifindm != m_alllink.end() || ifindv != m_alltype.end()) {
        Assert(false); //类型已经存在
        if (!(ifindm != m_alllink.end() && ifindv != m_alltype.end())) {
            Assert(false); //逻辑出问题了 
        }

        return false;
    }

    m_alltype.push_back(pLinkType);
    vector<LinkInfo *> vct;
    m_alllink.insert(make_pair(pLinkType, vct));

    return true;
}

bool LinkManage::RecycleLink(LinkInfo * & pLinkInfo) {
    if (NULL == pLinkInfo) {
        Assert(false);
        return false;
    }
    //这里要多判断一次 如果该peerinfo是有类型的，要从对应类型的容器里剔除这个回收的链接
    vector<LinkInfo *>::iterator ifind = find(m_recycle.begin(), m_recycle.end(), pLinkInfo);
    if (ifind != m_recycle.end()) {
        Assert(false);
        //发现已经被回收了
        return false;
    }

    m_recycle.push_back(pLinkInfo);
    m_QuickPosition.erase(pLinkInfo->m_socket);

    if (string(pLinkInfo->m_remotetype) != "") {
        //从分类容器里剔除被回收的端信息
        CHashMap<string, vector<LinkInfo *> >::iterator _ifind = m_alllink.find(pLinkInfo->m_remotetype);
        if (_ifind == m_alllink.end()) {
            Assert(false); //类型不存在
        } else {
            vector<LinkInfo *>::iterator itor = find(_ifind->second.begin(), _ifind->second.end(), pLinkInfo);
            if (itor == _ifind->second.end()) {
                Assert(false); //没有正确收容或者提前被剔除了
            } else {
                _ifind->second.erase(itor);
            }
        }
    }

    close(pLinkInfo->m_socket);
    pLinkInfo->m_recvstream.Clear();
    pLinkInfo->m_sendstream.Clear();
    pLinkInfo->Reset();
    pLinkInfo = NULL;
    return true;
}

const vector<LinkInfo *> * LinkManage::GetTypeOfLinks(const char * pLinkType) {
    if (pLinkType != NULL && !IsExsitType(pLinkType)) {
        //类型不存在
        Assert(false);
        return NULL;
    }

    CHashMap<string, vector<LinkInfo *> >::iterator ifind = m_alllink.find(pLinkType);
    if (ifind == m_alllink.end()) {
        Assert(false);
        return NULL;
    }

    return &(ifind->second);
}

LinkInfo * LinkManage::FindLinkBySocket(const UI16 nSocket) {
    CHashMap<UI16, LinkInfo *>::iterator ifind = m_QuickPosition.find(nSocket);
    if (ifind == m_QuickPosition.end()) {
        //LOG_ECHO(name, 256, "No link info about sockt : %d", nSocket);
        return NULL;
    }

    return ifind->second;
}


