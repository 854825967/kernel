//
// core - server core source code.
//
// $Rev: 2440 $
// $Author: $
// $Date: 2011-12-13 22:05:03 +0800 (周二, 2011-12-13) $
//
//
// Define class AutoMutex.
//

#ifndef __AUTO__MUTEX__H
#define __AUTO__MUTEX__H

#include "core/base/scoped_mutex.h"

namespace core {

class Mutex;

typedef ScopedMutex<Mutex> AutoMutex;

}  // namespace core

#endif  // __AUTO__MUTEX__H

