//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Define interface SorterInterface.
//

#ifndef __SORTER__INTERFACE__H
#define __SORTER__INTERFACE__H

class SorterInterface {
 public:
  virtual ~SorterInterface() {}

  virtual SortType GetSorterType() const = 0;

  virtual void ClearSortData() = 0;

  virtual bool CheckSortComplete() const = 0;

  virtual bool Sort(const char *data, size_t size) = 0;

  virtual bool GetSortResult(char *data, size_t &size) = 0;
};

#endif  // __SORTER__INTERFACE__H

