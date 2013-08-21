/* 
 * File:   IBuff.h
 * Author: traveler
 *
 * Created on January 11, 2013, 3:26 PM
 */

#ifndef INEWBUFF_H
#define	INEWBUFF_H
#include "ComDefine.h"

class INewBuff {
public:
    virtual const UI32 InsertBuff(const void * pBuff, const UI32 nLen)=0 ;
    virtual void * QueryBuff(const UI32 ) = 0;
    virtual bool DeleteBuff(const UI32 )=0;
};


#endif	/* IBUFF_H */

