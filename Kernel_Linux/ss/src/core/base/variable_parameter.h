//
// core - server core source code.
//
// $Rev: 2353 $
// $Author: $
// $Date: 2011-12-08 18:05:59 +0800 (鍛ㄥ洓, 2011-12-08) $
//
// Define class Logger.
//
// Micro GET_VARIABLE_PARAMETERS is designed to dispose the variable parameters list,
// build a charactor string using the std-c type va_list.
//

#ifndef __GET__VARIABLE__PARAMETERS
#define __GET__VARIABLE__PARAMETERS

#include <stdarg.h>

namespace core {

#define GET_VARIABLE_PARAMETERS(str, str_len, pat)    \
  do{	\
    va_list ap;     \
    bzero(str, str_len);     \
    va_start(ap, pat);      \
    vsnprintf(str, str_len - 1, pat, ap);    \
    va_end(ap);     \
  }while(false)

}  // namespace core


#endif	// __GET__VARIABLE__PARAMETERS

