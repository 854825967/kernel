/* 
 * File:   Gate.h
 * Author: traveler
 *
 * Created on January 4, 2013, 5:56 PM
 */

#ifndef GATE_H
#define	GATE_H

#include "../FrameworkInterface/IGate.h"

class Gate : public IGate {
public:
    virtual bool Initialize(IKernel * pKernel);
    virtual bool DelayInitialize(IKernel * pKernel);
    virtual bool Destroy(IKernel * pKernel);
    
private:

};

#endif	/* GATE_H */

