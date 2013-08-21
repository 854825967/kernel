#ifndef SHEET_H
#define SHEET_H


#include "ComDefine.h"
#include <string>
#include "IVarList.h"
#include "ISheet.h"
#include "Buff.h"
using namespace std;
#define COLUMN_NAME_MAX_LEN 64

template<UI32 COLUMN_COUNT, UI32 MAX_ROWS = 128 >
        class Sheet : public ISheet {
public:

    Sheet() {
        InitSheet();
    }

    Sheet(const IVarList & clmnInfos) {
        InitSheet();
        InitColumnInfo(clmnInfos);
    }

    ~Sheet() {
        if (NULL != m_pData) {
            delete m_pData;
            m_pData = NULL;
        }
    }

    virtual UI32 RowCount() {
        return m_nCurrentRowCount;
    }
    
    virtual bool InitColumnInfo(const IVarList & clmninfos) {
        if (clmninfos.Count() != m_nClmnCount * 2) {
            Assert(false);
        }

        for (UI16 i = 0; i < m_nClmnCount; i++) {
            UI8 clmnType = clmninfos.GetInt(i * 2 + 1);
            const char * pStrClmnName = clmninfos.GetString(i * 2);

            if (NULL == pStrClmnName || strlen(pStrClmnName) == 0) {
                Assert(false);
            }

            SheetColumn column;
            column.clmnHead = m_Data + (i * m_nStackRows);
            column.type = clmnType;
            m_hmapColumn.insert(make_pair(pStrClmnName, column));
            memcpy(m_ColumnName[i], pStrClmnName, COLUMN_NAME_MAX_LEN - 1);
            snprintf(m_ColumnName[i], COLUMN_NAME_MAX_LEN - 1, "%s", pStrClmnName);
            m_ColumnName[i][COLUMN_NAME_MAX_LEN - 1] = 0;
        }
    }

    virtual bool AddRow(const UI32 nCount = 1) {
        if (!CheckVolume(nCount)) {
            if (!AllocVolume(nCount)) {
                Assert(false);
                return false;
            }
        }

        for (UI32 i = 0; i < nCount; i++) {
            if (!InsertRowValue()) {
                Assert(false);
                return false;
            }
        }

        return true;
    }

    virtual bool InsertRowValue(const IVarList & data = VarList()) {
        UI32 nValueCount = data.Count();
        if (nValueCount != m_nClmnCount && nValueCount != 0) {
            Assert(false);
            return false;
        }


        m_nCurrentRowCount++;
        for (UI32 i = 0; i < m_nClmnCount; i++) {
            Var * pData = FindTable(m_nCurrentRowCount - 1, m_ColumnName[i]);
            if (NULL == pData) {
                Assert(false);
                m_nCurrentRowCount--;
                return false;
            }

            if (nValueCount != 0) {
                switch (data.Type(i)) {
                        //                    case TYPE_BOOL:
                        //                        SetDataValue(*pData, data.GetBool)
                        //                        break;c
                    case TYPE_INT:
                        SetDataValue(*pData, data.GetInt(i));
                        break;
                    case TYPE_INT64:
                        SetDataValue(*pData, data.GetInt64(i));
                        break;
                    case TYPE_STRING:
                    {
                        const char * pStrVal = data.GetString(i);
                        UI32 nStrPos = m_Buff.InsertBuff(pStrVal, strlen(pStrVal) + 1);
                        SetDataString(*pData, nStrPos);
                    }
                        break;
                    case TYPE_WIDESTR:
                    {
                        const wchar_t * pWStrVal = data.GetWideStr(i);
                        UI32 nWStrPos = m_Buff.InsertBuff(pWStrVal, (wcslen(pWStrVal) + 1) * sizeof(wchar_t));
                        SetDataString(*pData, nWStrPos);
                    }
                        break;
                    case TYPE_DOUBLE:
                        SetDataValue(*pData, data.GetDouble(i));
                        break;
                    case TYPE_OBJECT:
                        SetDataValue(*pData, data.GetObject(i));
                        break;
                }
            }
        }

        return true;
    }

    virtual bool DeleteRow(const UI32 nRowNum) {
        if(nRowNum >= m_nCurrentRowCount) {
            Assert(false);
            return false;
        }
        
        if(nRowNum == m_nCurrentRowCount - 1) {
            m_nCurrentRowCount --;
            return true;
        }
        
        for(UI32 i=0; i<m_nClmnCount;i++) {
            Var * pLastData = FindTable(m_nCurrentRowCount-1, 
                    m_ColumnName[i]);
            Var * pDeleteData = FindTable(nRowNum, m_ColumnName[i]);
            memcpy(pDeleteData, pLastData, sizeof(Var));
        }
        
        m_nCurrentRowCount --;
        
        return true;
    }

    virtual bool SetValue(const UI32 nRow, const char * pStrClmnName, const I32 value) {

        Var * pData = FindTable(nRow, pStrClmnName, TYPE_INT);
        if (NULL == pData) {
            Assert(false);
            return false;
        }

        SetDataValue(*pData, value);

        return true;
    }

    virtual bool SetValue(const UI32 nRow, const char * pStrClmnName, const I64 value) {

        Var * pData = FindTable(nRow, pStrClmnName, TYPE_INT64);
        if (NULL == pData) {
            Assert(false);
            return false;
        }

        SetDataValue(*pData, value);
        return true;
    }

    virtual bool SetValue(const UI32 nRow, const char * pStrClmnName, const char * value) {

        Var * pData = FindTable(nRow, pStrClmnName, TYPE_STRING);
        if (NULL == pData) {
            Assert(false);
            return false;
        }

        UI32 nStrPos = m_Buff.InsertBuff(value, strlen(value) + 1);
        SetDataString(*pData, nStrPos);

        return true;
    }

    virtual bool SetValue(const UI32 nRow, const char * pStrClmnName, const double value) {

        Var * pData = FindTable(nRow, pStrClmnName, TYPE_DOUBLE);
        if (NULL == pData) {
            Assert(false);
            return false;
        }

        SetDataValue(*pData, value);
        return true;
    }

    virtual bool SetValue(const UI32 nRow, const char * pStrClmnName, const wchar_t * value) {

        Var * pData = FindTable(nRow, pStrClmnName, TYPE_WIDESTR);
        if (NULL == pData) {
            Assert(false);
            return false;
        }

        UI32 nWStrPos = m_Buff.InsertBuff(value, (wcslen(value) + 1) * sizeof (wchar_t));
        SetDataString(*pData, nWStrPos);

        return true;
    }

    virtual bool SetValue(const UI32 nRow, const char * pStrClmnName, const CIdentity value) {

        Var * pData = FindTable(nRow, pStrClmnName, TYPE_INT);
        if (NULL == pData) {
            Assert(false);
            return false;
        }

        SetDataValue(*pData, value);
        return true;
    }

    virtual I32 QueryInt(UI32 nRow, const char * pStrClmnName) {
        Var * pData = FindTable(nRow, pStrClmnName, TYPE_INT);
        if (NULL == pData) {
            Assert(false);
            return 0;
        }

        return pData->intValue;
    }

    virtual I64 QueryInt64(UI32 nRow, const char * pStrClmnName) {
        Var * pData = FindTable(nRow, pStrClmnName, TYPE_INT64);
        if (NULL == pData) {
            Assert(false);
            return 0;
        }

        return pData->int64Value;
    }

    virtual const char * QueryString(UI32 nRow, const char * pStrClmnName) {
        Var * pData = FindTable(nRow, pStrClmnName, TYPE_STRING);
        if (NULL == pData) {
            Assert(false);
            return NULL;
        }

        return (char *) m_Buff.GetBuffHead(pData->strIndex);
    }

    virtual double QueryDouble(UI32 nRow, const char * pStrClmnName) {
        Var * pData = FindTable(nRow, pStrClmnName, TYPE_DOUBLE);
        if (NULL == pData) {
            Assert(false);
            return 0;
        }

        return pData->doubleValue;
    }

    virtual const wchar_t * QueryWideStr(UI32 nRow, const char * pStrClmnName) {
        Var * pData = FindTable(nRow, pStrClmnName, TYPE_WIDESTR);
        if (NULL == pData) {
            Assert(false);
            return NULL;
        }

        return (wchar_t *) m_Buff.GetBuffHead(pData->wstrIndex);
    }

    virtual const CIdentity QueryObject(UI32 nRow, const char * pStrClmnName) {
        Var * pData = FindTable(nRow, pStrClmnName, TYPE_WIDESTR);
        if (NULL == pData) {
            Assert(false);
            return CIdentity_INIT();
        }

        return CIdentity_INIT(pData->int64Value);
    }

private:

    inline void InitSheet() {
        m_nClmnCount = COLUMN_COUNT;
        m_nStackRows = MAX_ROWS;
        m_pData = NULL;
        m_nMaxtRowCount = m_nStackRows;
        m_nCurrentRowCount = 0;
        //m_nCurrentSize = 0;
    }

    Var * FindTable(const UI32 nRow, const char * pStrClmnName, UI8 type = TYPE_UNKWON) {
        //这里缺少判断是栈上数据 还是在堆上
        if (m_nCurrentRowCount <= nRow) { //行索引是从0开始 所以等于也不行
            Assert(false);
            return NULL;
        }

        CHashMap<string, SheetColumn>::iterator itor = m_hmapColumn.find(pStrClmnName);

        if (TYPE_UNKWON == type) {
            type = itor->second.type;
            (itor->second.clmnHead + nRow)->type = type;
        }

        if (itor == m_hmapColumn.end() || itor->second.type != type) {
            Assert(false);
            return NULL;
        }

        return itor->second.clmnHead + nRow;
    }

    bool CheckVolume(const UI32 nNewRowCount) {

        return true;
    }

    bool AllocVolume(const UI32 nNewRowCount) {

        return true;
    }

protected:
    //预先使用栈 栈不够用了 在用分配堆 提高效率
    Var m_Data[COLUMN_COUNT * MAX_ROWS];
    char m_ColumnName[COLUMN_COUNT][COLUMN_NAME_MAX_LEN];
    //预先使用栈 栈不够用了 在用分配堆 提高效率
    //栈不够用的时候 用堆
    UI32 m_nStackRows; //栈上又多少行容量
    Var * m_pData; //堆头指针

    UI32 m_nClmnCount; //列数
    UI32 m_nMaxtRowCount; //当前容器最大容量(最大容量 减去 堆大小 就为栈的个数）
    UI32 m_nCurrentRowCount; //当前数据的最大行数
    //UI32 m_nCurrentSize; //当前成员个数(有多少列 * 有多少行)

    Buff m_Buff;

    CHashMap<string, SheetColumn> m_hmapColumn;
};
#endif
