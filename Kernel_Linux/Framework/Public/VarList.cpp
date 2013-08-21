#include "Buff.h"

#include <wchar.h>
#include "VarList.h"

VarList::VarList() {
    m_nCurrent = 0;
    m_nMaxSize = STACK_SIZE;
    m_pData = NULL;
    m_pBuff = NULL;
}

VarList::~VarList() {
    if (m_pBuff != NULL) {
        delete m_pBuff;
    }

    if (m_pData != NULL) {
        delete[] m_pData;
    }
}

bool VarList::RellocHeap() {


    return true;
}

bool VarList::AllocSpace() {
    if (m_nCurrent + 1 <= m_nMaxSize) {
        return true;
    }

    while (m_nCurrent + 1 > m_nMaxSize) {
        m_nMaxSize += STACK_SIZE;
    }

    if (NULL == m_pData) {
        m_pData = NEW Var[m_nMaxSize - STACK_SIZE];
        printf("VarList::AllocSpace\n");
        if (NULL == m_pData) {
            return false;
        }
    } else {
        Var * pData = m_pData;
        m_pData = NEW Var[m_nMaxSize - STACK_SIZE];
        printf("VarList::AllocSpace\n");
        if (NULL == m_pData) {
            return false;
        }

        memcpy(m_pData, pData, (m_nCurrent - STACK_SIZE) * sizeof (Var));
    }

    return true;
}

UI32 VarList::Count() const {
    return m_nCurrent;
}

bool VarList::Clear() {
    m_nCurrent = 0;
    return true;
}

UI8_TYPE VarList::Type(const UI32_INDEX nIndex) const {
    if (nIndex >= m_nCurrent) {
        Assert(false);
        return 0;
    }

    if (nIndex < STACK_SIZE) {
        return m_Stack[nIndex].type;
    } else {
        return m_pData[nIndex - STACK_SIZE].type;
    }

    return TYPE_UNKWON;
}

bool VarList::AddInt(const I32 nValue) {
    if (m_nCurrent < STACK_SIZE) {
        SetDataType(m_Stack[m_nCurrent], TYPE_INT);
        SetDataValue(m_Stack[m_nCurrent], nValue);
        m_nCurrent++;
        return true;
    }

    if (false == AllocSpace()) {
        return false;
    }

    SetDataType(m_pData[m_nCurrent - STACK_SIZE], TYPE_INT);
    SetDataValue(m_pData[m_nCurrent - STACK_SIZE], nValue);
    m_nCurrent++;

    return true;
}

bool VarList::AddDouble(const double dValue) {
    if (m_nCurrent < STACK_SIZE) {
        SetDataType(m_Stack[m_nCurrent], TYPE_DOUBLE);
        SetDataValue(m_Stack[m_nCurrent], dValue);
        m_nCurrent++;
        return true;
    }

    if (false == AllocSpace()) {
        return false;
    }

    SetDataType(m_pData[m_nCurrent - STACK_SIZE], TYPE_DOUBLE);
    SetDataValue(m_pData[m_nCurrent - STACK_SIZE], dValue);
    m_nCurrent++;

    return true;
}

bool VarList::AddString(const char * pString) {
    if (NULL == m_pBuff) {
        m_pBuff = NEW Buff;
    }

    UI32_INDEX nIndex = m_pBuff->InsertBuff(pString, (strlen(pString) + 1) * sizeof (char));
    if (ERROR_INDEX == nIndex) {
        Assert(false);
        return false;
    }

    if (m_nCurrent < STACK_SIZE) {
        SetDataType(m_Stack[m_nCurrent], TYPE_STRING);
        SetDataString(m_Stack[m_nCurrent], nIndex);
        m_nCurrent++;
        return true;
    }

    if (false == AllocSpace()) {
        return false;
    }

    SetDataType(m_Stack[m_nCurrent], TYPE_STRING);
    SetDataString(m_Stack[m_nCurrent], nIndex);
    m_nCurrent++;

    return true;
}

bool VarList::AddInt64(const I64 n64Value) {
    if (m_nCurrent < STACK_SIZE) {
        SetDataType(m_Stack[m_nCurrent], TYPE_INT64);
        SetDataValue(m_Stack[m_nCurrent], n64Value);
        m_nCurrent++;
        return true;
    }

    if (false == AllocSpace()) {
        return false;
    }

    SetDataType(m_pData[m_nCurrent - STACK_SIZE], TYPE_INT64);
    SetDataValue(m_pData[m_nCurrent - STACK_SIZE], n64Value);
    m_nCurrent++;

    return true;
}

bool VarList::AddWideStr(const wchar_t * pWideStr) {
    if (NULL == m_pBuff) {
        m_pBuff = NEW Buff;
    }

    UI32_INDEX nIndex = m_pBuff->InsertBuff(pWideStr, (wcslen(pWideStr) + 1) * sizeof (wchar_t));
    if (ERROR_INDEX == nIndex) {
        Assert(false);
        return false;
    }

    if (m_nCurrent < STACK_SIZE) {
        SetDataType(m_Stack[m_nCurrent], TYPE_WIDESTR);
        SetDataWideStr(m_Stack[m_nCurrent], nIndex);
        m_nCurrent++;
        return true;
    }

    if (false == AllocSpace()) {
        return false;
    }

    SetDataType(m_Stack[m_nCurrent], TYPE_WIDESTR);
    SetDataWideStr(m_Stack[m_nCurrent], nIndex);
    m_nCurrent++;

    return true;
}

bool VarList::AddObject(const CIdentity obj) {
    if (m_nCurrent < STACK_SIZE) {
        SetDataType(m_Stack[m_nCurrent], TYPE_OBJECT);
        SetDataValue(m_Stack[m_nCurrent], obj);
        m_nCurrent++;
        return true;
    }

    if (false == AllocSpace()) {
        return false;
    }

    SetDataType(m_pData[m_nCurrent - STACK_SIZE], TYPE_OBJECT);
    SetDataValue(m_pData[m_nCurrent - STACK_SIZE], obj);
    m_nCurrent++;

    return true;
}

bool VarList::SetInt(const I32 nIndex, const I32 nValue) {

    return true;
}

bool VarList::SetDouble(const I32 nIndex, const double dValue) {

    return true;
}

bool VarList::SetString(const I32 nIndex, const char * pString) {

    return true;
}

bool VarList::SetInt64(const I32 nIndex, const I64 n64Value) {

    return true;
}

bool VarList::SetWideStr(const I32 nIndex, const wchar_t * pWideStr) {

    return true;
}

bool VarList::SetObject(const I32 nIndex, const CIdentity obj) {

    return true;
}

const I32 VarList::GetInt(const I32 nIndex) const {
    if (nIndex >= m_nCurrent) {
        Assert(false);
        return 0;
    }

    if (nIndex < STACK_SIZE) {
        if (m_Stack[nIndex].type != TYPE_INT) {
            Assert(false);
            return 0;
        }
        return m_Stack[nIndex].intValue;
    }

    if (m_pData[nIndex - STACK_SIZE].type != TYPE_INT) {
        Assert(false);
        return 0;
    }

    return m_pData[nIndex - STACK_SIZE].intValue;
}

const double VarList::GetDouble(const I32 nIndex) const {
    if (nIndex >= m_nCurrent) {
        Assert(false);
        return 0;
    }

    if (nIndex < STACK_SIZE) {
        if (m_Stack[nIndex].type != TYPE_DOUBLE) {
            Assert(false);
            return 0;
        }
        return m_Stack[nIndex].doubleValue;
    }

    if (m_pData[nIndex - STACK_SIZE].type != TYPE_DOUBLE) {
        Assert(false);
        return 0;
    }

    return m_pData[nIndex - STACK_SIZE].doubleValue;
}

const char * VarList::GetString(const I32 nIndex) const {
    if (nIndex >= m_nCurrent) {
        Assert(false);
        return NULL;
    }

    UI32_INDEX nStrIndex = ERROR_INDEX;

    if (nIndex < STACK_SIZE) {
        if (m_Stack[nIndex].type != TYPE_STRING) {
            Assert(false);
            return NULL;
        }
        nStrIndex = m_Stack[nIndex].strIndex;
    } else {
        if (m_pData[nIndex - STACK_SIZE].type != TYPE_STRING) {
            Assert(false);
            return NULL;
        }
        nStrIndex = m_pData[nIndex - STACK_SIZE].strIndex;
    }

    return (const char *) m_pBuff->GetBuffHead(nStrIndex);
}

const I64 VarList::GetInt64(const I32 nIndex) const {
    if (nIndex >= m_nCurrent) {
        Assert(false);
        return 0;
    }

    if (nIndex < STACK_SIZE) {
        if (m_Stack[nIndex].type != TYPE_INT64) {
            Assert(false);
            return 0;
        }
        return m_Stack[nIndex].int64Value;
    }

    if (m_pData[nIndex - STACK_SIZE].type != TYPE_INT64) {
        Assert(false);
        return 0;
    }

    return m_pData[nIndex - STACK_SIZE].int64Value;
}

const wchar_t * VarList::GetWideStr(const I32 nIndex) const {
    if (nIndex >= m_nCurrent) {
        Assert(false);
        return 0;
    }

    UI32_INDEX nWStrIndex = ERROR_INDEX;

    if (nIndex < STACK_SIZE) {
        if (m_Stack[nIndex].type != TYPE_WIDESTR) {
            Assert(false);
            return NULL;
        }
        nWStrIndex = m_Stack[nIndex].wstrIndex;
    } else {
        if (m_pData[nIndex - STACK_SIZE].type != TYPE_WIDESTR) {
            Assert(false);
            return NULL;
        }

        nWStrIndex = m_pData[nIndex - STACK_SIZE].wstrIndex;
    }

    return (const wchar_t *)m_pBuff->GetBuffHead(nWStrIndex);
}

const CIdentity VarList::GetObject(const I32 nIndex) const {
    if (nIndex >= m_nCurrent) {
        Assert(false);
        return CIdentity_INIT();
    }

    if (nIndex < STACK_SIZE) {
        if (m_Stack[nIndex].type != TYPE_OBJECT) {
            Assert(false);
            return CIdentity_INIT();
        }
        return CIdentity_INIT(m_Stack[nIndex].int64Value);
    }

    if (m_pData[nIndex - STACK_SIZE].type != TYPE_OBJECT) {
        Assert(false);
        return CIdentity_INIT();
    }

    return CIdentity_INIT(m_pData[nIndex - STACK_SIZE].int64Value);
}
