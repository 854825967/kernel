/*****************************************************************************
   模块名      : GAME system
   文件名      : GameSys.h
   相关文件    : 
   文件实现功能: 游戏公共函数及宏定义
   作者        : 庄雪锋
   版本        : V0.9  Copyright(C) 2011-2012 Loogia, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2011/06/28  0.1         庄雪锋      创建
******************************************************************************/
#ifndef _GAME_SYS_H_
#define _GAME_SYS_H_

#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include "GameType.h"

#ifdef WIN32
    #define DllExport __declspec(dllexport)
#else     /* VxWorks*/
    #define DllExport
#endif

#ifdef WIN32
#include <WinSock2.h>
#include <winsock.h>
#include <Mswsock.h>
#pragma comment (lib,"ws2_32.lib")
#include "windows.h"
#include <time.h>
#else 
#include "dlfcn.h"
#include <string.h>
#endif

/* maximum size of physical address */
#define MAXSIZE_PHYADDR     16

// 缓冲区最大长度
#define MAX_BUFFER_SIZE		4096

#define MAX_PATH          260

// 将b拷入a中,a和b必须是以/0结尾的字符串(a,b均为数组)
#define mcopy( a, b ) \
	{ \
	u32 len = min( sizeof( a ), strlen( b ) + 1 ); \
	memset( (a), 0, sizeof( a ) ); \
	memcpy( (a), (b), len ); \
	(a)[ len - 1 ] = '\0'; \
}

	// 将b拷入a中,a和b必须是以/0结尾的字符串(a为指针,b为数组)
#define mcopyptr( a, b, alen ) \
	{ \
	u32 len = min( (alen), strlen( b ) + 1 ); \
	memset( (a), 0, (alen) ); \
	memcpy( (a), (b), len ); \
	(a)[ len - 1 ] = '\0'; \
}

enum EDisconnectType
{
	DT_INVALID = 0,
	DT_APP_LAYER_VOLUNTARY,				// 应用层.主动断开
	DT_KERNEL_IOCP_BIND_FAIL,			// 内核层.绑定完成端口失败
	DT_KERNEL_IOCP_GET_STATUS_FAIL,		// 内核层.获取完成端口状态失败
	DT_KERNEL_RECV_FAIL,				// 内核层.调用WSARecv失败
	DT_KERNEL_BUF_TO0_LARGER,			// 内核层.收到单个数据包大于4k
	DT_KERNEL_BUF_EMPTY,				// 内核层.收到数据包长度为0，连接断开
	DT_KERNEL_DECRYPT_FAIL,				// 内核层.解密失败
	DT_KERNEL_PASSIVE_DISCONNECT,		// 内核层.被动断开
	DT_KERNEL_NETWORK_EVENT_ERROR_READ,	// 内核层.SOCKET事件模型(读)错误
	DT_KERNEL_NETWORK_EVENT_ERROR_WRITE,// 内核层.SOCKET事件模型(写)错误
	DT_NUM,
};

/* -----------------------  系统公用函数  ----------------------------- */
#define LOWORD16(l)     ((u16)(l))
#define HIWORD16(l)     ((u16)(((u32)(l) >> 16) & 0xFFFF))
#define MAKEDWORD(l,h)  ((u32)(((u16)(l)) | ((u32)((u16)(h))) << 16))

#ifndef _WINDEF_  /* 为了能够有Windows下使用 */
    #define LOBYTE(w)       ((u8)(w))
    #define HIBYTE(w)       ((u8)(((u16)(w) >> 8) & 0xFF))
    #define MAKEWORD(l,h)  ((u16)(((u8)(l)) | ((u16)((u8)(h))) << 8))
#endif

#ifdef _DEBUG 
	#undef ASSERT
	#define ASSERT(exp)    \
        { \
	      if ( !( exp ) ) \
		  { \
            printf((s8*)"Assert File %s, Line %d (%s)\n", \
	                 __FILE__, __LINE__, (s8*)#exp ); \
		  } \
        }
#else
    #undef ASSERT
    #define ASSERT( exp )    {}
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _GAME_SYS_H_ */
