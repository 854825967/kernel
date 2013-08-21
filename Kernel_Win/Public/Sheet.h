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

    bool SheetPrint();  //��ӡ���� ������

    //��ʼ���������
    bool InitializeColumn(const VarList & columnNames, const VarList & columnTypes);

    //����һ��
    bool InsertRow(const I32 nRow, const VarList & rowValue);
    
    //�趨ֵ
    bool SetBool(const char * pstrColumn,const I32 nRow, const bool bValue);
    bool SetInt(const char * pstrColumn, const I32 nRow, const I32 nValue);
    bool SetInt64(const char * pstrColumn, const I32 nRow, const UI64 i64Value);
    bool SetString(const char * pstrColumn, const I32 nRow, const char * pString);
    bool SetWideStr(const char * pstrColumn, const I32 nRow, const wchar_t * pwstrValue);
    bool SetDouble(const char * pstrColumn, const I32 nRow, const double dbValue);
    //SetObject ���ڼ���

    //��ֵ
    const bool QueryBool(const char * pstrColumn, const I32 nRow);
    const I32 QueryInt(const char * pstrColumn, const I32 nRow);
    const I64 QueryInt64(const char * pstrColumn, const I32 nRow);
    const char * QueryString(const char * pstrColumn, const I32 nRow);
    const wchar_t * QueryWideStr(const char * pstrColumn, const I32 nRow);
    const double QueryDouble(const char * pstrColumn, const I32 nRow);
    //QueryQbject ���ڼ���

protected:
    //���·�������¶
    bool AddColumn(const char * pstrColumn, UI8 nType);
    //ͨ��������ȡ������
    const UI8 GetColumnIndex(const char * pstrColumn);
    //ͨ��������ȡ����
    const UI8 GetColumnType(const char * pstrColumn);
    //��λ��ǰ��������
    I32 GetPosition(const UI8 nColumn, const I32 nRow, const UI8 nType);
    //��ȡ������
    const SheetColumn FindColumn(const UI8 nColumn);
    //����ռ��С�Ƿ��� �����÷����¿ռ�
    bool AllotSheetSpace(const I32 nCount);
    //����ַ�����������С �����÷����¿ռ�
    bool AllotStrBuffSpace(const char * pstrBuff, I32 & nPosition);
private:
    //Ԥ��ʹ��ջ ջ�������� ���÷���� ���Ч��
    //���С
    VarData m_Data[INITIAL_SHEET_SIZE];
    VarData * m_pData;
    UI32 m_nMaxtSize; //��ǰ�����������
    UI32 m_nCurrentSize; //��ǰ��Ա����(�ж����� * �ж�����)

    UI8 m_nColumnCount;
    hash_map<string, UI8> m_hmapColumnIndex;
    hash_map<UI8, SheetColumn> m_hmapColumn;
};

#endif