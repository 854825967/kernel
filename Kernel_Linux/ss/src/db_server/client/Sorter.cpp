//
// Copyright(C) 2011-2012 Loogia, All rights reserved.
//
// $Rev$
// $Author$
// $Date$
//
// Define class Sorter.
//

#include "db_server/client/Sorter.h"

void Sorter::ClearSortData(const SortType &type) {
  SorterInterface *sorter = this->GetSorter(type);
  if(sorter) {
    sorter->ClearSortData();
  }
}

bool Sorter::CheckSortComplete(const SortType &type) {
  SorterInterface *sorter = this->GetSorter(type);
  if(sorter) {
    return sorter->CheckSortComplete();
  }
  return false;
}

bool Sorter::Sort(const char *data, size_t size, const SortType &type) {
  SorterInterface *sorter = this->GetSorter(type);
  if(sorter) {
    return sorter->Sort(data, size);
  }
  return false;
}

bool Sorter::GetSortResult(const SortType &type, char *data, size_t &size) {
  SorterInterface *sorter = this->GetSorter(type);
  if(sorter) {
    return sorter->GetSortResult(data, size);
  }
  return false;
}

SorterInterface *Sorter::GetSorter(const SortType &type) {
  switch(type) {
    case SORT_TYPE_TRAIN_TOWN_DAY:
      return &this->train_town_day_;
    case SORT_TYPE_TRAIN_TOWN_PERIOD:
      return &this->train_town_period_;
    case SORT_TYPE_TRAIN_LAST_ARRANGE:
      return &this->train_town_last_arrange_;
    default :
      return NULL;
  }
}

