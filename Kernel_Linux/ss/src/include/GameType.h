/*****************************************************************************
   模块名      : GMAE type 
   文件名      : GameType.h
   相关文件    : 
   文件实现功能: 游戏宏定义
   作者        : 庄雪锋
   版本        : V0.1  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2011/06/28  0.1         庄雪锋      创建
******************************************************************************/
#ifndef _GAME_TYPE_H_
#define _GAME_TYPE_H_

#include <stdio.h>

#ifndef _MSC_VER
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	  /* Type definition */
/*-----------------------------------------------------------------------------
系统公用文件，开发人员严禁修改
------------------------------------------------------------------------------*/


#ifdef _MSC_VER
typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
#else
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#endif

typedef u8 BYTE;
typedef u16 WORD;
typedef u32 DWORD;

#ifndef _MSC_VER
#ifndef LPSTR
#define LPSTR   char *
#endif
#ifndef LPCSTR
#define LPCSTR  const char *
#ifndef NULL
#define NULL	0
#endif
#ifndef LPVOID
#define LPVOID	u64
#endif
#endif
#endif

#ifndef _MSC_VER
typedef int BOOL;
typedef struct tagPOINT
{
    s32  x;
    s32  y;
} POINT;

typedef s64 LONGLONG;
typedef u64 ULONGLONG;
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif



#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _GAME_TYPE_H_ */

