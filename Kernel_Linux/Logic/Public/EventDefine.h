/* 
 * File:   EventDefine.h
 * Author: traveler
 *
 * Created on December 17, 2012, 8:41 PM
 */

#ifndef EVENTDEFINE_H
#define	EVENTDEFINE_H

enum KERNEL_EVENT {
    /*
     * 网络模块的回调
     */
    /* 主动连接成功 args: 
     * 0 UI32 nEventid=KERNEL_EVENT_CONNECT_SUCCESS 
     * 1 const char * pStrLinkType
     * 2 UI16 nSocket
     */
    KERNEL_EVENT_CONNECT_SUCCESS = 10000,

    /* 新的连接进来 args:
     * 0 UI32 nEventid = KERNEL_EVENT_NEW_CONNECTTION
     * 1 const char * pStrLinkType
     * 2 UI16 nSocket
     */
    KERNEL_EVENT_NEW_CONNECTION,

    /* 链接断开（意外断开) args: 
     * 0 UI32 nEventid = KERNEL_EVENT_CONNECTION_BREAK
     * 1 const char * pStrLinkType
     * 2 UI16 nSocket
     */
    KERNEL_EVENT_CONNECTION_BREAK,

    /* 链接断开（正常断开) args: 
     * 0 UI32 nEventid = KERNEL_EVENT_CONNECTION_BREAK
     * 1 const char * pStrLinkType
     * 2 UI16 nSocket
     */
    KERNEL_EVENT_CONNECTION_EOF,

    /* 断开链接（主动断开）
     * 0 UI32 nEventid = KERNEL_EVENT_CONNECTION_CLOSE
     * 1 const char * pStrLinkType
     * 2 UI16 nSocket 
     */
    KERNEL_EVENT_CONNECTION_CLOSE,

};

#endif	/* EVENTDEFINE_H */
