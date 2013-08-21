#include <string>
#include "Archive.h"
#include "VarList.h"

Archive::Archive()
{
    m_nStreamMaxSize = UPDATE_STAGE;
    m_pRoot = NEW char[UPDATE_STAGE];
    m_pStream = m_pRoot + sizeof(UI32);
    *(UI32 *)m_pRoot = sizeof(UI32);
    m_nCurrentInIndex = 0;
    m_nCurrentOutIndex = 0;
}

Archive::~Archive()
{
    delete[] m_pRoot;
}

bool Archive::InBuff(void * pBuff, I32 nLength)
{
    if (NULL == pBuff ||
        0 == nLength)
    {
        return false;
    }

    m_nCurrentInIndex = 0;
    m_nCurrentOutIndex = 0;
    AllotSpace(nLength);

    memcpy(m_pRoot, pBuff, nLength);
    m_nCurrentInIndex = nLength - sizeof(UI32);

    return true;
}

bool Archive::Clear()
{
    m_nCurrentInIndex = 0;
    m_nCurrentOutIndex = 0;
    *(UI32 *)m_pRoot = 0;
    return true;
}

bool Archive::FormartToVarList(VarList & args)
{
    UI8_TYPE nType = GetNextType();
    if (TYPE_UNKWON == nType)
    {
        return false;
    }

    while (TYPE_UNKWON != nType)
    {
        switch (nType)
        {
        case TYPE_INT:
            args << OutI32();
            break;
        case TYPE_INT64:
            args << OutI64();
            break;
        case TYPE_STRING:
            args << OutString();
            break;
        case TYPE_WIDESTR:
            args << OutWideStr();
            break;
        case TYPE_DOUBLE:
            args << OutDouble();
            break;
        }

        nType = GetNextType();
    }
    return true;
}

void * Archive::GetStream() const
{
    return m_pRoot;
}

UI32 Archive::Length() const
{
    return *(UI32 *)m_pRoot;
}

bool Archive::AllotSpace(const UI32 nIncreaseLength)
{
    if (m_nCurrentInIndex + nIncreaseLength < m_nStreamMaxSize - sizeof(UI32))
    {
        return true;
    }

    while (m_nCurrentInIndex + nIncreaseLength >= m_nStreamMaxSize - sizeof(UI32))
    {
        m_nStreamMaxSize += UPDATE_STAGE;
    }

    char * pOldBlock = m_pRoot;
    m_pRoot = NEW char[m_nStreamMaxSize];//����Ҫ��Ӽ���ڴ��Ƿ����ɹ����ж�.
    if (sizeof(UI32) == *(UI32 *)pOldBlock)
    {
        *(UI32 *)m_pRoot = sizeof(UI32);
    }
    else
    {
        memcpy(m_pRoot, pOldBlock, *(UI32 *)pOldBlock);
    }
    m_pStream = m_pRoot + sizeof(UI32);

    delete[] pOldBlock;

    return true;
}

/*=================����=====================*/
bool Archive::In(const I32 nValue)
{
    UI8 type = TYPE_INT;
    *((UI8 *)(m_pStream + m_nCurrentInIndex)) = type;
    m_nCurrentInIndex += sizeof(UI8);
    *((I32 *)(m_pStream + m_nCurrentInIndex)) = nValue;
    m_nCurrentInIndex += sizeof(I32);

    *(UI32 *)m_pRoot = m_nCurrentInIndex + sizeof(UI32);
    
    return true;
}

bool Archive::In(const I64 llValue)
{
    UI8 type = TYPE_INT64;
    *((UI8 *)(m_pStream + m_nCurrentInIndex)) = type;
    m_nCurrentInIndex += sizeof(UI8);
    *((I64 *)(m_pStream + m_nCurrentInIndex)) = llValue;
    m_nCurrentInIndex += sizeof(I64);

    *(UI32 *)m_pRoot = m_nCurrentInIndex + sizeof(UI32);

    return true;
}

bool Archive::In(const char *pString, const UI32 nStrSize)
{
    *((UI8 *)(m_pStream + m_nCurrentInIndex)) = TYPE_STRING;
    m_nCurrentInIndex += sizeof(UI8);

    *((UI16 *)(m_pStream + m_nCurrentInIndex)) = nStrSize;
    m_nCurrentInIndex += sizeof(UI16);

    memcpy((m_pStream + m_nCurrentInIndex), pString, nStrSize);
    m_nCurrentInIndex += nStrSize;

    *(UI32 *)m_pRoot = m_nCurrentInIndex + sizeof(UI32);

    return true;
}

bool Archive::In(const wchar_t * pWideStr, const UI32 nWideStrSize)
{
    *((UI8 *)(m_pStream + m_nCurrentInIndex)) = TYPE_WIDESTR;
    m_nCurrentInIndex += sizeof(UI8);

    *((UI16 *)(m_pStream + m_nCurrentInIndex)) = nWideStrSize;
    m_nCurrentInIndex += sizeof(UI16);

    memcpy((m_pStream + m_nCurrentInIndex), pWideStr, nWideStrSize);
    m_nCurrentInIndex += nWideStrSize;

    *(UI32 *)m_pRoot = m_nCurrentInIndex + sizeof(UI32);

    return true;
}

bool Archive::In(const double dValue)
{
    UI8 type = TYPE_DOUBLE;
    *((UI8 *)(m_pStream + m_nCurrentInIndex)) = type;
    m_nCurrentInIndex += sizeof(UI8);
    *((double *)(m_pStream + m_nCurrentInIndex)) = dValue;
    m_nCurrentInIndex += sizeof(double);

    *(UI32 *)m_pRoot = m_nCurrentInIndex + sizeof(UI32);

    return true;
}

Archive & Archive::operator << (const UI32 nValue)
{
    AllotSpace(sizeof(UI8) + sizeof(I32));

    In((I32)nValue);
    return *this;
}

Archive & Archive::operator << (const UI64 llValue)
{
    AllotSpace(sizeof(UI8) + sizeof(I32));

    In((I64)llValue);
    return *this;
}

Archive & Archive::operator << (const I32 nValue)
{
    AllotSpace(sizeof(UI8) + sizeof(I32));

    In(nValue);
    return *this;
}

Archive & Archive::operator << (const I64 llValue)
{
    AllotSpace(sizeof(UI8) + sizeof(I32));

    In(llValue);
    return *this;
}

Archive & Archive::operator << (const char * pString)
{
    UI32 nStrSize = strlen(pString) + 1;
    AllotSpace(sizeof(UI8) + sizeof(UI16) + nStrSize);

    In(pString, nStrSize);
    return *this;
}

Archive & Archive::operator << (const wchar_t * pWideStr)
{
    UI32 nWideStrSize = (wcslen(pWideStr) + 1) * sizeof(wchar_t);
    AllotSpace(sizeof(UI8) + sizeof(UI16) + nWideStrSize);

    In(pWideStr, nWideStrSize);
    return *this;
}

Archive & Archive::operator << (const double dValue)
{
    AllotSpace(sizeof(UI8) + sizeof(double));

    In(dValue);
    return *this;
}

/*===============����=================*/
UI8 Archive::GetNextType()
{
    if (m_nCurrentOutIndex >= m_nCurrentInIndex)
    {
        return TYPE_UNKWON;
    }

    return *(UI8 *)(m_pStream + m_nCurrentOutIndex);
}

const I32 Archive::OutI32()
{
    if (m_nCurrentOutIndex >= m_nCurrentInIndex)
    {
        return -1;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ������� ��������  ���ֵײ��... ��������ݴ��ж��˷�Ч�� ���ҵײ��϶�������ʹ�úþͿ��԰ٷ�֮�ٲ�����ĵز�
    }
    
    if (TYPE_INT != *((UI8 *)(m_pStream + m_nCurrentOutIndex)))
    {
        return -1;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ������� ��������
    }

    m_nCurrentOutIndex += (sizeof(UI8) + sizeof(I32));

    return *((I32 *)(m_pStream + m_nCurrentOutIndex - sizeof(I32)));
}

const I64 Archive::OutI64()
{
    if (m_nCurrentOutIndex >= m_nCurrentInIndex)
    {
        return -1;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ������� ��������
    }

    if (TYPE_INT64 != *((UI8 *)(m_pStream + m_nCurrentOutIndex)))
    {
        return -1;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ������� ��������
    }

    m_nCurrentOutIndex += (sizeof(UI8) + sizeof(I64));

    return *((I64 *)(m_pStream + m_nCurrentOutIndex - sizeof(I64)));
}

const char * Archive::OutString()
{
    if (m_nCurrentOutIndex >= m_nCurrentInIndex)
    {
        return NULL;  //���ڷ��ֲ��� �� �����⵽����NULL  ���п����ǳ������� ��������
    }

    if (TYPE_STRING != *((UI8 *)(m_pStream + m_nCurrentOutIndex)))
    {
        return NULL;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ������� ��������
    }

    UI16 nStrLen = *((UI16 *)(m_pStream + m_nCurrentOutIndex + sizeof(UI8)));

    m_nCurrentOutIndex += (sizeof(UI8) + sizeof(UI16) + nStrLen);
    
    return (const char *)(m_pStream + m_nCurrentOutIndex - nStrLen);
}

const wchar_t * Archive::OutWideStr()
{
    if (m_nCurrentOutIndex >= m_nCurrentInIndex)
    {
        return NULL;  //���ڷ��ֲ��� �� �����⵽����NULL  ���п����ǳ������� ��������
    }

    if (TYPE_WIDESTR != *((UI8 *)(m_pStream + m_nCurrentOutIndex)))
    {
        return NULL;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ������� ��������
    }

    UI16 nWideStrLen = *((UI16 *)(m_pStream + m_nCurrentOutIndex + sizeof(UI8)));

    m_nCurrentOutIndex += (sizeof(UI8) + sizeof(UI16) + nWideStrLen);

    return (const wchar_t *)(m_pStream + m_nCurrentOutIndex - nWideStrLen);
}

const double Archive::OutDouble()
{
    if (m_nCurrentOutIndex >= m_nCurrentInIndex)
    {
        return -1;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ�������
    }

    if (TYPE_DOUBLE != *((UI8 *)(m_pStream + m_nCurrentOutIndex)))
    {
        return -1;  //���ڷ��ֲ��� �� �����⵽����-1  ���п����ǳ�������
    }

    m_nCurrentOutIndex += (sizeof(UI8) + sizeof(double));

    return *((double *)(m_pStream + m_nCurrentOutIndex - sizeof(double)));
}

bool Archive::operator >> (I32 & nValue)
{
    nValue = OutI32();

    return true;
}

bool Archive::operator >> (I64 & llValue)
{
    llValue = OutI64();

    return true;
}

bool Archive::operator >> (const char * & pString)
{
    pString = OutString();

    return true;
}

bool Archive::operator >> (double & dValue)
{
    dValue = OutDouble();

    return true;
}

bool Archive::operator >> (float & fValue)
{
    fValue = OutDouble();

    return true;
}
