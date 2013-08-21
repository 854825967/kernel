/* 
 * File:   IConfigManage.h
 * Author: traveler
 *
 * Created on December 18, 2012, 3:42 PM
 */

#ifndef ICONFIGMANAGE_H
#define	ICONFIGMANAGE_H

#include "IBase.h"
#include "../../Public/ComDefine.h"

enum {
    KERNEL_CONFIG_GLOBLA_INI = 0,
    KERNEL_CONFIG_BASE_INI,
};

class CIniConfig;

class IConfigManage : public IBase {
public:
    virtual const CIniConfig * GetConfig(const UI8 nConfigID) = 0;
};

#endif	/* ICONFIGMANAGE_H */

