/** @file */


#ifndef  DATA_MODIFIER_FILTER_H
#define  DATA_MODIFIER_FILTER_H

#include <functional>

#include "data-modifier.h"

namespace ksi
{
   /** Filter for data sets.
    * The class implements a decorator design pattern.
    * @author Krzysztof Siminski
    * @date   2021-04-14
    */
   class data_modifier_filter : public data_modifier
   {
       /// Filtering function returns true if the predicate for the value pointed by the index is true.
       std::function<bool (double value)> _filter; 
       /// index of attribute to filter
       /// If index is out of range nothing is done. 
       std::size_t _index;
   public:
      data_modifier_filter(std::size_t index, std::function<bool (double value)> filter);
      data_modifier_filter(const data_modifier_filter& dm) = default;
      data_modifier_filter(data_modifier_filter && dm) = default;
      
      data_modifier_filter & operator = (const data_modifier_filter & dm)  = default;
      data_modifier_filter & operator = (data_modifier_filter && dm)  = default;
      
      virtual ~data_modifier_filter() = default;
      virtual data_modifier * clone() const;
 
      /** The method filters values in the dataset then first calls the modify method in the next data_modifier. 
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       * @date   2021-04-14
       */
      virtual void modify (dataset & ds); 
   };
}

#endif
