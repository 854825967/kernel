#include <string>
#include "CStream.h"

CStream::CStream()
{
    m_pBuff = NEW char[STREAM_LENGTH];
    m_nReadCurrent = 0;
    m_nWriteCurrent = 0;
    m_nMaxLength = STREAM_LENGTH;
}

CStream::~CStream()
{
    if (NULL != m_pBuff)
    {
        delete[] m_pBuff;
        m_pBuff = NULL;
    }
}

char * CStream::GetBuff() const{
    return m_pBuff + m_nReadCurrent;
}

u32 CStream::GetLength() const{
    return m_nWriteCurrent - m_nReadCurrent;
}

bool CStream::In(const char * pBuff, u32 nLength) 
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
        if (m_nWriteCurrent != m_nReadCurrent) {
            memcpy(m_pBuff, m_pBuff + m_nReadCurrent, m_nWriteCurrent - m_nReadCurrent);
        }
        m_nWriteCurrent = m_nWriteCurrent - m_nReadCurrent;
        m_nReadCurrent = 0;
    }

    memcpy(m_pBuff + m_nWriteCurrent, pBuff, nLength);

    m_nWriteCurrent += nLength;

    return true;
}

char * CStream::Out(u32 & nLength)
{
    u32 nPosition = m_nReadCurrent;
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
    } else {
        m_nReadCurrent += nLength;
    }

    return m_pBuff + nPosition;
}

void CStream::Clear()
{
    m_nReadCurrent = 0;
    m_nWriteCurrent = 0;
}