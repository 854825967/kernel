//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev: 5052 $
// $Author: than $
// $Date: 2012-02-27 15:39:19 +0800 (鍛ㄤ竴, 2012-02-27) $
//
// Define class CConnectStateSink.
//

#ifndef __CCONNECT__STATE__SINK__H
#define __CCONNECT__STATE__SINK__H

#include "DErrorCode.h"
#include "core/connection_task.h"

class CConnectStateSink {
 public:
  CConnectStateSink();
  ~CConnectStateSink();

  core::ConnectionTask *OnAccept();
};

#endif  // __CCONNECT__STATE__SINK__H

