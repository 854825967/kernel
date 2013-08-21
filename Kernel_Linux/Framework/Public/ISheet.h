/* 
 * File:   ISheet.h
 * Author: traveler
 *
 * Created on December 26, 2012, 6:48 PM
 */

#ifndef ISHEET_H
#define	ISHEET_H

#include "ComDefine.h"
#include "VarList.h"
#include <string>
#include <wchar.h>
#include <tr1/CHashMap>
using namespace std;
using namespace tr1; //::CHashMap<std::string, int> string_CHashMap;


typedef struct sheetcolumn {

    sheetcolumn() {
        //    index = 0;
        type = TYPE_UNKWON;
        clmnHead = NULL;
    }

    UI8 type;
    Var * clmnHead;

    struct sheetcolumn & operator =(const struct sheetcolumn & target) {
        type = target.type;
        clmnHead = target.clmnHead;
        return *this;
    }

    bool operator ==(const struct sheetcolumn & target) {
        return (/*index == target.index && */type == target.type);
    }

    bool operator !=(const struct sheetcolumn & target) {
        return (/*index != target.index || */type != target.type);
    }

} SheetColumn;

class ISheet {
public:
    virtual bool InitColumnInfo(const IVarList & clmninfos) = 0;
    virtual UI32 RowCount() = 0;
    virtual bool AddRow(const UI32 nCount = 1) = 0;
    virtual bool InsertRowValue(const IVarList & data = VarList() ) = 0;
    virtual bool DeleteRow(const UI32 nRowNum) = 0;
    
    virtual bool SetValue(UI32 nRow, const char * pStrClmnName, const I32 value) = 0;
    virtual bool SetValue(UI32 nRow, const char * pStrClmnName, const I64 value) = 0;
    virtual bool SetValue(UI32 nRow, const char * pStrClmnName, const char * value) = 0;
    virtual bool SetValue(UI32 nRow, const char * pStrClmnName, const double value) = 0;
    virtual bool SetValue(UI32 nRow, const char * pStrClmnName, const wchar_t * value) = 0;
    virtual bool SetValue(UI32 nRow, const char * pStrClmnName, const CIdentity vale) = 0;
    
    virtual I32 QueryInt(UI32 nRow, const char * pStrClmnName) = 0;
    virtual I64 QueryInt64(UI32 nRow, const char * pStrClmnName) = 0;
    virtual const char * QueryString(UI32 nRow, const char * pStrClmnName) = 0;
    virtual double QueryDouble(UI32 nRow, const char * pStrClmnName) = 0;
    virtual const wchar_t * QueryWideStr(UI32 nRow, const char * pStrClmnName) = 0;
    virtual const CIdentity QueryObject(UI32 nRow, const char * pStrClmnName) = 0;
    
};

#endif	/* ISHEET_H */

