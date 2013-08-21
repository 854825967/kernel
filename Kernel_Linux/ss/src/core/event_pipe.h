//
// core - server core source code.
//
// $Rev$
// $Author$
// $Date$
//
// Define of EventPipe.
//


#ifndef __EVENT__PIPE__H
#define __EVENT__PIPE__H

#include "core/version.h"

#ifdef __CORE_EVENTFD__
#include <sys/eventfd.h>
#include <fcntl.h>
#else
#include <unistd.h>
#endif

namespace core {

inline void CreateEventPipe(int fds[2]) {
#ifdef __CORE_EVENTFD__
  int fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if(fd < 0) {
    CoreLog(FATAL, "%s:%d (%s) Failed in EventPipe",
        __FILE__, __LINE__, __FUNCTION__);
    abort();
  }
  fds[0] = fds[1] = fd;
#else
  if(pipe(fds) < 0) {
    CoreLog(FATAL, "%s:%d (%s) Failed in EventPipe",
        __FILE__, __LINE__, __FUNCTION__);
    abort();
  }
#endif
}

inline void CloseEventPipe(int fds[2]) {
  close(fds[0]);
#ifndef __CORE_EVENTFD__
  close(fds[1]);
#endif
}

inline int EventPipeReadfd(int fds[2]) { return fds[0]; }
inline int EventPipeWritefd(int fds[2]) { return fds[1]; }

}  // namespace core

#endif  // __EVENT__PIPE__H

