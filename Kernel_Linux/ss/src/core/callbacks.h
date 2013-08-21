//
// core - server core source code.
//
// $Rev: 5305 $
// $Author: $
// $Date: 2012-03-05 17:00:56 +0800 (鍛ㄤ竴, 2012-03-05) $
//
// Define some callback.
//

#ifndef __CALLBACK__H
#define __CALLBACK__H

#include "core/function/function.h"

namespace core {

class TCPConnection;
class ConnectionTask;

typedef function::Function0<void> SignalCallback;

// TODO: modify to return a bool, to make sure logic connects successfully.
typedef function::Function0<ConnectionTask *> ConnectionEstablishedCallback;
typedef function::Function1<void, TCPConnection *> ConnectionDestroyedCallback;

typedef function::Function0<void> ServerStopCallback;

}  // namespace core

#endif  // __CALLBACK__H

