//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Define class Sorter.
//

#ifndef __SORTER__H
#define __SORTER__H

#include "include/IDatabaseSorter.h"
#include "db_server/client/SorterInterface.h"
#include "db_server/client/TrainTownDaySorter.h"
#include "db_server/client/TrainTownPeriodSorter.h"
#include "db_server/client/TrainTownLastArrangeSorter.h"

class Sorter : public IDatabaseSorter {
 public:
  Sorter() {}
  virtual ~Sorter() {}

  // 清除排序数据
  virtual void ClearSortData(const SortType &type);
  // 是否排序完成
  virtual bool CheckSortComplete(const SortType &type);
  // 排序
  virtual bool Sort(const char *data, size_t size, const SortType &type);
  // 得到排序结果
  virtual bool GetSortResult(const SortType &type, char *data, size_t &size);

 private:
  virtual SorterInterface *GetSorter(const SortType &type);

  TrainTownDaySorter train_town_day_;
  TrainTownPeriodSorter train_town_period_;
  TrainTownLastArrangeSorter train_town_last_arrange_;
};

#endif  // __SORTER__H

