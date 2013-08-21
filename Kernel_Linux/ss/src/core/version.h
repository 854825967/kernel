//
// core - server core source code.
//
// $Rev$
// $Author$
// $Date$
//
// Define version of kernel.
//


#ifndef __VERSION__H
#define __VERSION__H

#include <linux/version.h>

#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif

#if(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 30))
#define __CORE_EVENTFD__
#define __CORE_TIMERFD__
#define __CORE_SIGNALFD__
#endif

#endif  // __VERSION__H

