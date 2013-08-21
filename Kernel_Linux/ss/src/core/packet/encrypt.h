//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Define class Encrypt.
// Encrypt provide some interface.
//

#ifndef __ENCRYPT__H
#define __ENCRYPT__H

namespace core {

class Encrypt {
 public:
  virtual ~Encrypt() {}
  virtual bool SetKey(const char *key, int size) = 0;

  virtual int GetMaxEncryptSize(int size) = 0;
  virtual int GetMaxDecryptSize(int size) = 0;

  virtual bool DoEncrypt(const char *in, int in_size, char *out, int &out_size) = 0;
  virtual bool DoDecrypt(const char *in, int in_size, char *out, int &out_size) = 0;
};

}  // namespace core

#endif  // __ENCRYPT__H

