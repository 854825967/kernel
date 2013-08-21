#ifndef BUFF_H
#define BUFF_H
#include "ComDefine.h"
#include "INewBuff.h"
#include "CHashMap.h"
#include <vector>
#include <algorithm>
using namespace std;

#define INIT_BUFF_SIZE 4096
#define ERROR_INDEX -1

enum {
    NOT_HERE = 0,
    IN_STACK,
    IN_HEAP,
};

class NewBuffNode {
public:
    UI32 index;
    void * pbuff;
    UI32 size;
    UI8 type;

    inline NewBuffNode() {
        index = ERROR_INDEX;
        pbuff = NULL;
        size = 0;
        type = NOT_HERE;
    }

    inline NewBuffNode & operator =(const NewBuffNode & target) {
        memcpy(this, &target, sizeof (target));
        return *this;
    }
};

UI32 SIZE = 4096;

class NewBuff : public INewBuff {
public:
    //初始化

    NewBuff() {

        m_pHeap = new char[SIZE];
        //偏移量
        m_nStacktail = 0;
        m_nHeaptail = 0;
        //实际量
        m_nCrtStackSize = 0;
        m_nCrtHeapSize = 0;
        //当前容器大小
        m_nMaxStackSize = SIZE; //其实 就是SIZE
        m_nMaxHeapSize = SIZE; //待增长

    }

    ~NewBuff() {

        if (NULL != m_pHeap) {
            delete[] m_pHeap;
            m_pHeap = NULL;
        }
    }

    virtual void * QueryBuff(const UI32 index) {
        if (index < 0 || index > m_hashMapStore.size()) {
            //打日志
            return NULL;
        }
        return m_hashMapStore[index].pbuff;
    }

    virtual const UI32 InsertBuff(const void * pBuff, const UI32 nLen) {
        //当前栈容量
        UI32 rem_StackVolome = m_nMaxStackSize - m_nCrtStackSize;

        NewBuffNode node;
        const void* tempBuff = NULL;

        if (nLen < rem_StackVolome) {
            //栈
            tempBuff = FindSpaceOnStack(nLen);
            if (NULL != tempBuff) {
                node.type = IN_STACK;
                m_nCrtStackSize += nLen;
                m_nStacktail += nLen;
            } else
                return NULL; //打日志
        } else {
            //堆
            tempBuff = FindSpaceOnHeap(nLen);
            if (NULL != tempBuff) {
                node.type = IN_HEAP;
                m_nCrtHeapSize += nLen;
                m_nHeaptail += nLen;
            } else
                return NULL; //打日志
        }

        node.pbuff = (void*) tempBuff;
        memcpy((char *) node.pbuff, (char *) pBuff, nLen);
        node.size = nLen;
        //返回hashMap的key
        UI32 index = m_hashMapStore.size() + 1; //可能有错
        m_hashMapStore.insert(pair<UI32, NewBuffNode > (index, node));
        return index;
    }

    virtual bool DeleteBuff(const UI32 hashmap_key) {
        //找到指定数据删除
        CHashMap<UI32, NewBuffNode>::iterator ifind = m_hashMapStore.find(hashmap_key);
        if (m_hashMapStore.end() == ifind) {
            return false; //索引号错误
        }

        NewBuffNode node = m_hashMapStore[hashmap_key];

        if (IN_STACK == node.type) {
            m_vctStackRcyl.push_back(node);
            m_nCrtStackSize -= node.size;
        }

        if (IN_HEAP == node.type) {
            m_vctHeapRcyl.push_back(node);
            m_nCrtHeapSize -= node.size;
        }

        m_hashMapStore.erase(ifind); //可能出错

        //删除hashmap中的数据
        return true;
    }
private:

    inline void Defraggler(const NewBuffNode & node) {
        if (ERROR_INDEX == node.index || NULL == node.pbuff || 0 == node.size || IN_STACK != node.type) {
            Assert(false);
            return;
        }

        if (IN_STACK == node.type) {
            UI32 len = m_nMaxStackSize - UI32((char *) node.pbuff - m_Stack + node.size);
            memcpy(node.pbuff, node.pbuff + node.size, len);
            m_nStacktail -= node.size;
        } else {
            if (IN_HEAP == node.type) {
                UI32 len = m_nMaxHeapSize - UI32((char*) node.pbuff - m_pHeap + node.size);
                memcpy(node.pbuff, node.pbuff + node.size, len);
                m_nHeaptail -= node.size;
            } else {
                return;
            }
        }


    }

    inline void ClearUpStack() { //清理栈 消除碎片
        //sort(m_vctStackRcyl.begin(), m_vctStackRcyl.end());
        if (m_vctStackRcyl.size() > 0) {
            for (UI32 i = 0; i < m_vctStackRcyl.size(); i++) {
                Defraggler(m_vctStackRcyl[i]);
            }
        } else {
            //打日志
            return;
        }
    }

    const void * FindSpaceOnStack(const UI32 nSize) { //在栈上找空间
        //加个判断
        I32 rem_StacktailSize = m_nMaxStackSize - m_nStacktail;
        if (nSize <= rem_StacktailSize && rem_StacktailSize > 0)//？
        {
            //分配到尾部
            return (void*) (m_Stack + m_nStacktail);
        } else {
            //内存碎片整理
            ClearUpStack();
        }

    }

    inline void ClearUpHeap() { //清理堆 消除碎片
        if (m_vctHeapRcyl.size() > 0) {
            for (UI32 i = 0; i < m_vctHeapRcyl.size(); i++) {
                Defraggler(m_vctHeapRcyl[i]);
            }
        } else {
            //打日志
            return;
        }
    }

    bool AllocSpace(const UI32 size) {
        if (!m_pHeap || 0 == size) {
            return false; //打日志
        }
        char* pBuff = m_pHeap;
        m_pHeap = new char[size];
        memcpy(m_pHeap, pBuff, m_nHeaptail + 1);
        return true;
    }

    const void * FindSpaceOnHeap(const UI32 nSize) { //在堆上找空间
        I32 rem_HeapVolome = m_nMaxHeapSize - m_nCrtHeapSize;

        if (nSize > rem_HeapVolome || rem_HeapVolome <= 0)//有错误
        {
            //需要附加空间
            UI32 tempSize = m_nMaxHeapSize;
            while (nSize > rem_HeapVolome) {
                rem_HeapVolome += SIZE;
                m_nMaxHeapSize += SIZE;
            }
            if (!AllocSpace(m_nMaxHeapSize)) {
                m_nMaxHeapSize = tempSize;
                return NULL; // 打日志
            }
        }
        //不要附加空间
        I32 rem_HeaptailSize = m_nMaxHeapSize - m_nHeaptail + 1;
        if (nSize <= rem_HeaptailSize) {
            return (void*) (m_pHeap + m_nHeaptail + 1);
        } else {
            //碎片整理
            ClearUpHeap();
        }
    }

private:
    //回收站 堆和栈的分开 方便整理
    vector<NewBuffNode> m_vctStackRcyl;
    vector<NewBuffNode> m_vctHeapRcyl;
    //当前buff存储信息
    CHashMap<UI32, NewBuffNode> m_hashMapStore;
    //buff
    char m_Stack[4096];
    char * m_pHeap;
    //当前使用到的位置 分堆的和栈的 分开管理
    UI32 m_nStacktail;
    UI32 m_nHeaptail;

    //记录 堆和栈中数据的实际大小 （去掉回收站的）
    UI32 m_nCrtStackSize;
    UI32 m_nCrtHeapSize;

    //buff容器最大容量
    UI32 m_nMaxStackSize; //其实 就是SIZE
    UI32 m_nMaxHeapSize;
    //当前所有buff总容量 测试用
};

#endif
