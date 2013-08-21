/* 
 * File:   IConsole.h
 * Author: traveler
 *
 * Created on January 15, 2013, 6:40 PM
 */

#ifndef ICONSOLE_H
#define	ICONSOLE_H
#include "IBase.h"

class IConsole : public IBase {
public:
    virtual bool Command(const char *) = 0;
};

#endif	/* ICONSOLE_H */

