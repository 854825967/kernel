#include "Buff.h"

Buff::Buff()
{
    m_pBuff = NEW char[INIT_BUFF_SIZE];
    m_nMaxSize = INIT_BUFF_SIZE;
    m_nCurrentSize = 0;
    m_nBuffCount = 0;
}

Buff::~Buff()
{
    if (m_pBuff != NULL)
    {
        delete[] m_pBuff;
    }
}

bool Buff::AllocSpace(const UI32 nLen)
{
    UI32 nNeedLen = m_nCurrentSize + nLen + sizeof(UI32);

    if (nNeedLen<= m_nMaxSize)
    {
        return true;
    }

    while (nNeedLen > m_nMaxSize)
    {
        m_nMaxSize += INIT_BUFF_SIZE;
    }

    char * pBuff = m_pBuff;
    m_pBuff = NEW char[m_nMaxSize];

    if (NULL == m_pBuff)
    {
        //这里 要打印日志 目前没这个功能
        return false;
    }

    if (0 == m_nCurrentSize)
    {
        delete[] pBuff;
        return true;
    }

    memcpy(m_pBuff, pBuff, m_nCurrentSize);

    delete[] pBuff;

    return true;
}

const void * Buff::GetBuffHead(const UI32_INDEX nIndex)
{
    if (ERROR_INDEX == nIndex ||
        nIndex >= m_vctIndex.size() ||
        false == m_vctIndex[nIndex].isues)
    {
        //记录不存在的索引
        LOG_ERROR("Buff::GetBuffHead : index is not exists");
        return false;
    }

    return m_vctIndex[nIndex].pbuff;
}

const UI32_INDEX Buff::GetUseAbleIndex()
{
    return m_vctIndexRcyl.empty()?m_nBuffCount:m_vctIndexRcyl[HEAD];
}

bool Buff::RecordLength(const void * pNode, const UI32 nLen)
{
    *((UI32 *)pNode - 1) = nLen;

    return true;
}

void * Buff::GetNodePoint()
{
    return m_pBuff + m_nCurrentSize + sizeof(UI32);
}

const UI32_INDEX Buff::InsertBuff(const void * pBuff, const UI32 nLen)
{
    if (!AllocSpace(nLen))
    {
        //这里要打日志
        return ERROR_INDEX;
    }

    const UI32_INDEX nIndex = GetUseAbleIndex();
    void * pNode = GetNodePoint();
    if (!RecordLength(pNode, nLen))
    {
        //打印日志
        return ERROR_INDEX;
    }
    
    memcpy((char *)pNode, (char *)pBuff, nLen);

    if (m_vctIndexRcyl.empty())
    {
        BuffNode buffnode;
        buffnode.index = nIndex;
        buffnode.isues = true;
        buffnode.pbuff = pNode;
        m_vctIndex.push_back(buffnode);

        //如果回收站里面没有东西 则说明是新增长的索引
    }
    else
    {
        m_vctIndexRcyl.erase(m_vctIndexRcyl.begin());
        m_vctIndex[nIndex].isues = true;
        m_vctIndex[nIndex].pbuff = pNode;
    }

    m_nCurrentSize += nLen + sizeof(UI32);
    m_nBuffCount++;

    return nIndex;
}

bool Buff::DeleteBuff(const UI32_INDEX nIndex)
{
    if (ERROR_INDEX == nIndex ||
        nIndex >= m_vctIndex.size() ||
        false == m_vctIndex[nIndex].isues)
    {
        //记录不存在的索引
        return false;
    }

    char * pBuff = (char *)m_vctIndex[nIndex].pbuff - sizeof(UI32);
    m_vctIndex[nIndex].pbuff = NULL;
    m_vctIndex[nIndex].isues = false;

    UI32 nOffset = *(int *)pBuff + sizeof(UI32);
    UI32 nLen = m_nCurrentSize - (UI32)(pBuff - m_pBuff) - nOffset;
    if (nLen == 0)
    {
        return true;
    }
    memcpy(pBuff, pBuff + nOffset, nLen);
    m_nBuffCount--;
    m_nCurrentSize -= nOffset;

    UI32 nCount = m_vctIndex.size();

    for (UI32 i=nIndex; i<nCount; i++)
    {
        if (m_vctIndex[i].isues)
        {
            m_vctIndex[i].pbuff = (char *)m_vctIndex[i].pbuff - nOffset;
        }
    }

    return true;
}
