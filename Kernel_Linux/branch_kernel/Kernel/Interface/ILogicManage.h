/* 
 * File:   ILogicManage.h
 * Author: traveler
 *
 * Created on December 18, 2012, 6:14 PM
 */

#ifndef ILOGICMANAGE_H
#define	ILOGICMANAGE_H
#include "IBase.h"

class ILogicModule;

class ILogicManage : public IBase {
public:
    virtual ILogicModule * FindModule(const char * pStrModuleName) = 0;
};


#endif	/* ILOGICMANAGE_H */

