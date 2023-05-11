/** @file */

#include <vector>
#include <algorithm>
#include <cmath>

#include "data-modifier.h"
#include "data-modifier-filter.h"
#include "../service/debug.h"

ksi::data_modifier* ksi::data_modifier_filter::clone() const
{
    return new ksi::data_modifier_filter(*this);
}


ksi::data_modifier_filter::data_modifier_filter(std::size_t index, std::function<bool (double value)> filter) : data_modifier()
{
   description = "filter";
   _index = index;
   _filter = filter;
}


void ksi::data_modifier_filter::modify(ksi::dataset & ds)
{
   try
   {
      // no i tu sie zaczyna zabawa :-) 
      size_t nAttributes = ds.getNumberOfAttributes();
      size_t nDataItems = ds.getNumberOfData();
      
      if (_index < 0 or _index >= nDataItems)
          return;
      
      dataset result;
      
      for (size_t i = 0; i < nDataItems; i++)
      {
          if (_filter(ds.get(i, _index)))
              result.addDatum(*ds.getDatum(i));
      }
      
      ds = result;
      
      // and call pNext modifier
      if (pNext)
         pNext->modify(ds);
      
   }
   CATCH;   
}





