#ifndef BUFF_H
#define BUFF_H

#include <vector>
#include "ComDefine.h"
using namespace std;

#define INIT_BUFF_SIZE 1024

typedef struct _buffnode 
{
    bool isues;
    I32 index;
    void * pbuff;
}BuffNode;

class Buff
{
public:
    Buff();
    ~Buff();
    const UI32_INDEX InsertBuff(const void * pBuff, const UI32 nLen);
    const void * GetBuffHead(const UI32_INDEX nIndex); 
    bool DeleteBuff(const UI32_INDEX nIndex);

private:
    bool AllocSpace(const UI32 nLen);
    const UI32_INDEX GetUseAbleIndex();
    bool RecordLength(const void * pNode, const UI32 nLen);
    void * GetNodePoint();

private:
    //����--�ڴ涨λ
    vector<BuffNode> m_vctIndex;
    //��������վ
    vector<UI32> m_vctIndexRcyl;
    //buff
    char * m_pBuff;
    //�ж��ٸ�buff
    UI32 m_nBuffCount;
    //buff�����������
    UI32 m_nMaxSize;
    //��ǰ����buff������
    UI32 m_nCurrentSize;
};

#endif