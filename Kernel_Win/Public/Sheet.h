#ifndef SHEET_H
#define SHEET_H

#include <map>
#include <hash_map>
#include <string>
#include "ComDefine.h"
using namespace std;
using namespace stdext;

#define NEW_ROW 1
#define MATE_NOT_EXSITS -1
#define COLUMN_NOT_EXSITS -1
#define NULL_STRING -1
#define INITIAL_SHEET_SIZE 16
#define INITIAL_STRING_SIZE 256

class VarList;

typedef struct sheetcolumn 
{
    UI8 index;
    UI8 type;

    struct sheetcolumn & operator = (const struct sheetcolumn & target)
    {
        index = target.index;
        type = target.type;

        return *this;
    }

    bool operator == (const struct sheetcolumn & target)
    {
        if (index == target.index &&
            type == target.type)
        {
            return true;
        }

        return false;
    }

}SheetColumn;

class Sheet
{
public:
    Sheet();
    Sheet(const VarList & column);
    ~Sheet();

    bool SheetPrint();  //打印出表 测试用

    //初始化表的列名
    bool InitializeColumn(const VarList & columnNames, const VarList & columnTypes);

    //新增一行
    bool InsertRow(const I32 nRow, const VarList & rowValue);
    
    //设定值
    bool SetBool(const char * pstrColumn,const I32 nRow, const bool bValue);
    bool SetInt(const char * pstrColumn, const I32 nRow, const I32 nValue);
    bool SetInt64(const char * pstrColumn, const I32 nRow, const UI64 i64Value);
    bool SetString(const char * pstrColumn, const I32 nRow, const char * pString);
    bool SetWideStr(const char * pstrColumn, const I32 nRow, const wchar_t * pwstrValue);
    bool SetDouble(const char * pstrColumn, const I32 nRow, const double dbValue);
    //SetObject 后期加上

    //查值
    const bool QueryBool(const char * pstrColumn, const I32 nRow);
    const I32 QueryInt(const char * pstrColumn, const I32 nRow);
    const I64 QueryInt64(const char * pstrColumn, const I32 nRow);
    const char * QueryString(const char * pstrColumn, const I32 nRow);
    const wchar_t * QueryWideStr(const char * pstrColumn, const I32 nRow);
    const double QueryDouble(const char * pstrColumn, const I32 nRow);
    //QueryQbject 后期加上

protected:
    //以下方法不暴露
    bool AddColumn(const char * pstrColumn, UI8 nType);
    //通过列名获取列索引
    const UI8 GetColumnIndex(const char * pstrColumn);
    //通过列名获取类型
    const UI8 GetColumnType(const char * pstrColumn);
    //定位当前行列索引
    I32 GetPosition(const UI8 nColumn, const I32 nRow, const UI8 nType);
    //获取列索引
    const SheetColumn FindColumn(const UI8 nColumn);
    //检测表空间大小是否够用 不够用分配新空间
    bool AllotSheetSpace(const I32 nCount);
    //检测字符串保存区大小 不够用分配新空间
    bool AllotStrBuffSpace(const char * pstrBuff, I32 & nPosition);
private:
    //预先使用栈 栈不够用了 在用分配堆 提高效率
    //表大小
    VarData m_Data[INITIAL_SHEET_SIZE];
    VarData * m_pData;
    UI32 m_nMaxtSize; //当前容器最大容量
    UI32 m_nCurrentSize; //当前成员个数(有多少列 * 有多少行)

    UI8 m_nColumnCount;
    hash_map<string, UI8> m_hmapColumnIndex;
    hash_map<UI8, SheetColumn> m_hmapColumn;
};

#endif