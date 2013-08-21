//
// core - server core source code.
//
// $Rev: 2917 $
// $Author: $
// $Date: 2012-01-01 17:12:06 +0800 (周日, 2012-01-01) $
//
// common define.
//

#include "core/base/common.h"

#include <ctype.h>

namespace core {

char *strupr(char *str) { 
  char *ptr = str; 

  while (*ptr != '\0') { 
    if (islower(*ptr))  
      *ptr = toupper(*ptr); 
    ptr++; 
  } 

  return str; 
} 

}  // namespace core

