//
// core - server core source code.
//
// $Rev: 9911 $
// $Author: $
// $Date: 2012-08-28 19:48:18 +0800 (鍛ㄤ簩, 2012-08-28) $
//
// Define class Compress.
// Compress provide some interface.
//

#ifndef __COMPRESS__H
#define __COMPRESS__H

namespace core {

class Compress {
 public:
  virtual ~Compress() {}
  virtual int GetMaxCompressSize(int size) = 0;
  virtual int GetMaxUncompressSize(int size) = 0;

  virtual bool DoCompress(const char *in, int in_size, char *out, int &out_size) = 0;
  virtual bool UnDocompress(const char *in, int in_size, char *out, int &out_size) = 0;
};

}  // namespace core

#endif  // __ENCRYPT__H

