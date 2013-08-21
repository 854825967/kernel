#include <iostream>
using namespace std;

#include "Sheet.h"
#include "VarList.h"

Sheet::Sheet()
{
    m_nColumnCount = 0;
    m_nMaxtSize = INITIAL_SHEET_SIZE;
    m_nCurrentSize = 0;
    m_pData = NULL;
}

Sheet::Sheet(const VarList & column)
{

}

Sheet::~Sheet()
{
    if (NULL != m_pData)
    {
        //delete[] m_pData;
    }
}

bool Sheet::AddColumn(const char * pstrColumn, UI8 nType)
{
    hash_map<string, UI8>::iterator iFind = m_hmapColumnIndex.find(pstrColumn);
    if (iFind != m_hmapColumnIndex.end())
    {
        //这里要打日志 提示列名重复
        return false;
    }

    SheetColumn column;
    column.index = m_nColumnCount++;
    column.type = nType;

    m_hmapColumnIndex.insert(make_pair(pstrColumn, column.index));
    m_hmapColumn.insert(make_pair(column.index, column));

    return true;
}

bool Sheet::SheetPrint()    //测试用
{
    return true;
}

bool Sheet::AllotSheetSpace(const I32 nCount)
{
    if (nCount + m_nCurrentSize <= m_nMaxtSize)
    {
        m_nCurrentSize+=nCount;
        return true;
    }

    while (nCount + m_nCurrentSize > m_nMaxtSize)
    {
        m_nMaxtSize += INITIAL_SHEET_SIZE;
    }
    
    I32 nStackSize = m_nMaxtSize - INITIAL_SHEET_SIZE;

    if (NULL == m_pData)
    {
        m_pData = NEW VarData[nStackSize];
        memset(m_pData, 0, nStackSize * sizeof(VarData));
    }
    else
    {
        VarData * p = m_pData;
        m_pData = NEW VarData[nStackSize];
        if (NULL == m_pData)
        {
            //这里要打日志,提示分配内存失败
            return false;
        }

        memset(m_pData, 0, nStackSize * sizeof(VarData));
        memcpy(m_pData, p, (m_nCurrentSize-INITIAL_SHEET_SIZE) * sizeof(VarData));
        delete[] p;
    }

    m_nCurrentSize+=nCount;

    return true;
}

bool Sheet::InsertRow(const I32 nRow, const VarList & rowValue)
{
    if (false == AllotSheetSpace(nRow * m_nColumnCount))
    {
        //这里要打日志 提示分配空间失败
        return false;
    }


    return true;
}

const UI8 Sheet::GetColumnType(const char * pstrColumn)
{
    if (NULL == pstrColumn)
    {
        return COLUMN_NOT_EXSITS;
    }

    hash_map<string, UI8>::iterator ifind = m_hmapColumnIndex.find(pstrColumn);

    if (ifind == m_hmapColumnIndex.end())
    {
        return COLUMN_NOT_EXSITS;
    }

    UI8 nIndex = ifind->second;

    return m_hmapColumn[nIndex].type;   
}

const UI8 Sheet::GetColumnIndex(const char * pstrColumn)
{
    if (NULL == pstrColumn)
    {
        return COLUMN_NOT_EXSITS;
    }

    hash_map<string, UI8>::iterator ifind = m_hmapColumnIndex.find(pstrColumn);

    if (ifind == m_hmapColumnIndex.end())
    {
        return COLUMN_NOT_EXSITS;
    }
    
    return ifind->second;
}

I32 Sheet::GetPosition(const UI8 nColumn, const I32 nRow, const UI8 nType)
{
    SheetColumn column = FindColumn(nColumn);
    if (COLUMN_NOT_EXSITS == column.index || column.type != nType)
    {
        return MATE_NOT_EXSITS;
    }

    UI32 nPosition = nRow * m_nColumnCount + column.index;

    if (nPosition > m_nCurrentSize)
    {
        return MATE_NOT_EXSITS;
    }

    return nPosition;
}

const SheetColumn Sheet::FindColumn(const UI8 nColumn)
{
    SheetColumn column;
    if (nColumn > m_nColumnCount)
    {
        column.index = COLUMN_NOT_EXSITS;
        return column;
    }
    
    hash_map<UI8, SheetColumn>::iterator ifindcolumn = m_hmapColumn.find(nColumn);

    column = ifindcolumn->second;

    return column;
}

bool Sheet::SetInt(const char * pstrColumn, const I32 nRow, const I32 nValue)
{

    return true;
}

const I32 Sheet::QueryInt(const char * pstrColumn, const I32 nRow)
{

    return 0;
}

bool Sheet::SetString(const char * pstrColumn, const I32 nRow, const char * pString)
{
    return true;
}

const char * Sheet::QueryString(const char * pstrColumn, const I32 nRow)
{
    return NULL;
}

