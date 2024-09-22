
#ifndef DATA_MODIFIER_INCOMPLETER_RANDOM_WITHOUT_LAST_H
#define DATA_MODIFIER_INCOMPLETER_RANDOM_WITHOUT_LAST_H

#include "data-modifier.h"
#include "data_modifier_incompleter_random.h"

namespace ksi
{
   /** The class is responsible for incompleting the data completely at random. 
    *  The last attribute is not modified.
    @data   2024-09-22
    @author Krzysztof Siminski 
    */
   class data_modifier_incompleter_random_without_last : public data_modifier_incompleter_random
   {
    public:
      data_modifier_incompleter_random_without_last (const double missing_ratio);
      data_modifier_incompleter_random_without_last (const data_modifier_incompleter_random_without_last & other) = default;
      data_modifier_incompleter_random_without_last (data_modifier_incompleter_random_without_last && other) = default;
      data_modifier_incompleter_random_without_last & operator= (const data_modifier_incompleter_random_without_last & other) = default;
      data_modifier_incompleter_random_without_last & operator= (data_modifier_incompleter_random_without_last && other) = default;
      virtual ~data_modifier_incompleter_random_without_last () = default;
      virtual data_modifier * clone () const override;  // prototype design pattern
      
      virtual void make_tuple_incomplete(datum * p) override;
   };
}


#endif
