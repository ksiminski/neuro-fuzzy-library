
#include <utility>

#include "data-modifier.h"
#include "data_modifier_incompleter_random.h"
#include "data_modifier_incompleter_random_without_last.h"

ksi::data_modifier_incompleter_random_without_last::data_modifier_incompleter_random_without_last (const double missing_ratio) : ksi::data_modifier_incompleter_random(missing_ratio)
{
}

void ksi::data_modifier_incompleter_random_without_last::make_tuple_incomplete(datum* pDatum)
{
   make_tuple_incomplete_range(pDatum, std::size_t{0}, number_of_attributes - 1);
}
 
ksi::data_modifier * ksi::data_modifier_incompleter_random_without_last::clone () const
{
   // prototype design pattern
   return new ksi::data_modifier_incompleter_random_without_last(*this);
}



