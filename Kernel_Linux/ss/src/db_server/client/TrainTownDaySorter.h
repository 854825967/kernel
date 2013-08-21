//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Define class TrainTownDaySorter.
//

#ifndef __TRAIN__TOWN__DAY__SORTER__H
#define __TRAIN__TOWN__DAY__SORTER__H

#include "include/GameSys.h"
#include "include/IDatabaseSorter.h"
#include "db_server/client/SorterInterface.h"
#include "common/IDBStruct.h"

class TrainTownDaySorter : public SorterInterface {
 public:
  TrainTownDaySorter() : sort_complete_(false), data_length_(0) {}
  virtual ~TrainTownDaySorter() {}

  virtual SortType GetSorterType() const {
    return SORT_TYPE_TRAIN_TOWN_DAY;
  }

  // 清除排序数据
  virtual void ClearSortData() {
    this->sort_complete_ = false;
    this->data_length_ = 0;
  }

  // 是否排序完成
  virtual bool CheckSortComplete() const {
    return this->sort_complete_;
  }

  // 排序
  virtual bool Sort(const char *data, size_t size) {
    if(size > MAX_BUFFER_SIZE || size % sizeof(SCenterDBActorArrange_Get) != 0 ||
        size < sizeof(SCenterDBActorArrange_Get)) {
      return false;
    } else {
      memcpy(this->data_buffer_, data, size);
      this->data_length_ = size;
      this->sort_complete_ = true;
      return true;
    }
  }

  // 得到排序结果
  virtual bool GetSortResult(char *data, size_t &size) {
    if(size >= this->data_length_) {
      memcpy(data, this->data_buffer_, this->data_length_);
      size = this->data_length_;
      return true;
    }
    return false;
  }

 private:
  bool sort_complete_;
  char data_buffer_[MAX_BUFFER_SIZE];
  size_t data_length_;
};

#endif // __TRAIN__TOWN__DAY__SORTER__H

