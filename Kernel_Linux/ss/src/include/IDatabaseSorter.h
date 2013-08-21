//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Define interface IDatabaseSorter.
//

#ifndef __IDATABASE__SORTER__H
#define __IDATABASE__SORTER__H

#include <string.h>

enum SortType {
  SORT_TYPE_TRAIN_TOWN_DAY = 0,       // 试练塔每日排名
  SORT_TYPE_TRAIN_TOWN_PERIOD,        // 试练塔每届排名
  SORT_TYPE_TRAIN_LAST_ARRANGE,       // 试练塔上届排名
  SORT_TYPE_MAX,
};

class IDatabaseSorter {
 public:
  virtual ~IDatabaseSorter() {}

  // 清除排序数据
  virtual void ClearSortData(const SortType &type) = 0;
  // 是否排序完成
  virtual bool CheckSortComplete(const SortType &type) = 0;
  // 排序
  virtual bool Sort(const char *data, size_t size, const SortType &type) = 0;
  // 得到排序结果
  virtual bool GetSortResult(const SortType &type, char *data, size_t &size) = 0;
};

#endif  // __IDATABASE__SORTER__H

