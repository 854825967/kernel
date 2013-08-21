/* 
 * File:   IBase.h
 * Author: traveler
 *
 * Created on December 18, 2012, 1:53 PM
 */

#ifndef IBASE_H
#define	IBASE_H

class IBase {
public:
    virtual bool Bron() = 0;
    virtual bool Initialize() = 0;
    virtual bool Dead() = 0;
    virtual bool Destroy() = 0;
};

#endif	/* IBASE_H */

