//
// core - server core source code.
//
// $Rev: 3464 $
// $Author: $
// $Date: 2012-01-10 16:07:38 +0800 (鍛ㄤ簩, 2012-01-10) $
//
// Define protocol format.
//

#ifndef __PROTOCOL__H
#define __PROTOCOL__H

#include "core/base/types.h"

namespace core {

namespace protocol {

typedef uint32 ProtocolHead;

static const uint32 kProtocolHeadSize = sizeof(uint16);
static const uint32 kProtocolSizeMask = 0x4FFF;

inline const ProtocolHead *ProtocolHeadCast(const char *protocol) {
  return (ProtocolHead *)protocol;
}

inline ProtocolHead *ProtocolHeadCast(char *protocol) {
  return (ProtocolHead *)protocol;
}

inline void SetProtocolHead(char *protocol, ProtocolHead head) {
  *ProtocolHeadCast(protocol) = head;
}

inline char *GetProtocolData(char *protocol) {
  return protocol + kProtocolHeadSize;
}

inline uint32 GetPacketSize(const char *protocol) {
  return ((*ProtocolHeadCast(protocol) & kProtocolSizeMask) + kProtocolHeadSize);
}

}  // namespace protocol

}  // namespace core

#endif  // __PROTOCOL__H

