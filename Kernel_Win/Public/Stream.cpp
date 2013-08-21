#include <string>
#include "Stream.h"
#include "Archive.h"

Stream::Stream()
{
    m_pBuff = NEW char[STREAM_LENGTH];
    m_nReadCurrent = 0;
    m_nWriteCurrent = 0;
    m_nMaxLength = STREAM_LENGTH;
}

Stream::~Stream()
{
    if (NULL != m_pBuff)
    {
        delete[] m_pBuff;
        m_pBuff = NULL;
    }
}

bool Stream::ReadArchive(Archive & archive)
{
    UI16 nLen = *(UI16 *)(m_pBuff + m_nReadCurrent);
    if (nLen > m_nWriteCurrent - m_nReadCurrent)
    {
        return false; //消息不完整 等待下次接收完整
    }

    archive.Clear();    
    archive.InBuff((m_pBuff + m_nReadCurrent), nLen);
    m_nReadCurrent += nLen;

    return true;
}

bool Stream::WriteBuff(void * pBuff, UI32 nLength)
{
    if (NULL == pBuff ||
        nLength <= 0 )
    {
        return false;
    }

    if (nLength > m_nMaxLength)
    {
        //这里要打出日志 提示 消息过长
        return false;
    }

    if (nLength > m_nReadCurrent + m_nMaxLength - m_nWriteCurrent)
    {
        //提示缓冲区不足
        return false;
    }

    if (nLength > m_nMaxLength - m_nWriteCurrent)
    {
        memcpy(m_pBuff, m_pBuff + m_nReadCurrent, m_nWriteCurrent - m_nReadCurrent);
        m_nWriteCurrent = m_nWriteCurrent - m_nReadCurrent;
        m_nReadCurrent = 0;
    }

    memcpy(m_pBuff + m_nWriteCurrent, pBuff, nLength);

    m_nWriteCurrent += nLength;

    return true;
}

void * Stream::ReadBuff(UI32 & nLength)
{
    UI32 nPosition = m_nReadCurrent;
    if (m_nWriteCurrent - m_nReadCurrent < nLength)
    {
        if (STREAM_IS_EMPTY == (m_nWriteCurrent - m_nReadCurrent))
        {
            m_nReadCurrent = 0;
            m_nWriteCurrent = 0;
            return NULL;
        }
        
        nLength = m_nWriteCurrent - m_nReadCurrent;
        nPosition = m_nReadCurrent;
        m_nReadCurrent = 0;
        m_nWriteCurrent = 0;
        return m_pBuff + nPosition;
    }
    m_nReadCurrent += nLength;
    return m_pBuff + nPosition;
}

void Stream::Clear()
{
    m_nReadCurrent = 0;
    m_nWriteCurrent = 0;
}