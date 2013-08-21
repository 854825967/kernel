#ifndef TOOLS_H
#define TOOLS_H

#include "ComDefine.h"
#include "VarList.h"
#include <string>
using namespace std;

//#define RAND_MAX1 (RAND_MAX + 1)
#define RAND_MAX1 RAND_MAX

inline const Cthread_id GetCurrentThreadID() {
#if defined __LINUX_32__ || defined __LINUX_64__
    return syscall(__NR_gettid);
#endif //__LINUX_32__ || __LINUX_64__
    
#if defined __WIN_32__ || defined __WIN_64__
    //这里到时候要加上
#endif //__WIN_32__ || defined __WIN_64__
}

inline const char * GetAppPath() {
    static char * pStrPath = NULL;

    if (NULL == pStrPath) {
        pStrPath = NEW char[256];
        char link[256];
        memset(link, 0, 256);
        memset(pStrPath, 0, 256);
#if defined __LINUX_32__ || defined __LINUX_64__
        sprintf(link, "/proc/self/exe", getpid());
        int nCount = readlink(link, pStrPath, 256);
        if (nCount >= 265) {
            Assert(false);
        }
        //pStrPath[nCount] = 0;
        pStrPath = dirname(pStrPath);
#endif //__LINUX_32__ || defined __LINUX_64__
    }

    return pStrPath;
}

inline UI64 GetCurrentTimeTick() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

inline I32 RandomInt(I32 scale) {
    if ((scale <= 0) || (scale > RAND_MAX1)) {
        return 0;
    }

    return int(float(::rand()) / float(RAND_MAX1) * float(scale));
}

inline float RandomFloat(float scale) {
    if (scale <= 0.0f) {
        return 0.0f;
    }

    return (float(::rand()) / float(RAND_MAX1) * scale);
}

inline I32 RandomBigInt(I32 scale) {
    if ((scale <= 0) || (scale > (RAND_MAX1 * RAND_MAX1))) {
        return 0;
    }

    return int(float(::rand() * RAND_MAX1 + ::rand())
            / float(RAND_MAX1 * RAND_MAX1) * float(scale));
}

inline string IntAsString(I32 value) {
    char str[32];
    memset(str, 0, 32);
    snprintf(str, 32, "%d", value);

    return string(str);
}

inline string Int64AsString(I64 value) {
    char str[32];
    memset(str, 0, 32);
#if defined __LINUX_64__ || defined __WIN_64__
    snprintf(str, 32, "%ld", value);
#endif //defined __LINUX_64__ || defined __WIN_64__

#if defined __LINUX_32__ || defined __WIN_32__
    snprintf(str, 32, "%I64u", value);
#endif //defined __LINUX_32__ || defined __WIN_32__    

    return string(str);
}

inline string FloatAsString(float value, UI8 decimals = 0) {
    char str[64];
    memset(str, 0, 64);

    if (0 == decimals) {
        snprintf(str, 64, "%f", double(value));
    } else {
        switch (decimals) {
            case 1:
                snprintf(str, 64, "%.01f", double(value));
                break;
            case 2:
                snprintf(str, 64, "%.02f", double(value));
                break;
            case 3:
                snprintf(str, 64, "%.03f", double(value));
                break;
            case 4:
                snprintf(str, 64, "%.04f", double(value));
                break;
            case 5:
                snprintf(str, 64, "%.05f", double(value));
                break;
            default:
                snprintf(str, 64, "%f", double(value));
                break;
        }
    }

    return string(str);
}

inline string WideStrAsString(const wchar_t * value) {
    string val = "";
    if (NULL == value) {
        Assert(value);
        return val;
    }
    size_t size = wcslen(value) * sizeof (wchar_t);
    char *pc = NULL;
    if (!(pc = (char*) malloc(size))) {
        return val;
    }
    size_t destlen = wcstombs(pc, value, size);
    /*转换不为空时，返回值为-1。如果为空，返回值0*/
    if (destlen == (size_t) (0)) {
        return val;
    }
    val = pc;
    delete pc;
    return val;
}

inline UI64 atoui64(const char *value) {
    Assert(value);
    return atoll(value);
}

inline UI64 StringAsUI64(const char * value) {
    Assert(value);
    return atoui64(value);
}

inline I32 StringAsInt(const char * value) {
    Assert(value);
    return atoi(value);
}

inline float StringAsFloat(const char * value) {
    Assert(value);
    return (float) atof(value);
}

inline wstring StringAsWideStr(const char * value/*, UI32 CodePage*/) {
    std::wstring widevalue = L"";

    if (NULL == value) {
        Assert(value);
        return widevalue;
    }

    size_t size_of_wc;
    setlocale(LC_CTYPE, "");
    size_t destlen = mbstowcs(0, value, 0);
    if (destlen == (size_t) (-1)) {
        return widevalue;
    }
    size_of_wc = destlen + 1;
    wchar_t * pw = NEW wchar_t[size_of_wc];
    mbstowcs(pw, value, size_of_wc);
    widevalue = pw;
    delete[] pw;
    return widevalue;
}

inline bool SafeSplitString(const char * pStr, const char * delim, IVarList & res) {
    if (NULL == pStr || 0 == strlen(pStr) || NULL == delim) {
        Assert(false);
        return false;
    }

    UI32 nSize = strlen(pStr) + 1;
    char * pCopy = NEW char[nSize];
    memcpy(pCopy, pStr, nSize);

    char * pres = strtok(pCopy, delim);
    if (NULL == pres) {
        res << pStr;
        delete pCopy;
        return true;
    }

    res << pres;
    while (pres != NULL) {
        pres = strtok(NULL, delim);
        if (NULL == pres) {
            delete pCopy;
            return true;
        }
        res << pres;
    }

    delete[] pCopy;
    return true;
}

#endif //TOOLS_H
