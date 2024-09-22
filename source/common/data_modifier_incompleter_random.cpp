
#include <chrono>
#include <random>

#include "data-modifier.h"
#include "data_modifier_incompleter.h"
#include "data_modifier_incompleter_random.h"

ksi::data_modifier_incompleter_random::data_modifier_incompleter_random (const double missing_ratio) : _missing_ratio(missing_ratio)
{
   random_engine = std::default_random_engine (std::chrono::system_clock::now().time_since_epoch().count());
   distribution = std::uniform_real_distribution<double> (0.0, 1.0);
}

std::string ksi::data_modifier_incompleter_random::print() const
{
   return std::string {"data incompleter at random of all attributes"};
}

void ksi::data_modifier_incompleter_random::modify(dataset& ds)
{
   number_of_data_items = ds.getNumberOfData();
   number_of_attributes = ds.getNumberOfAttributes();
   
   for (std::size_t i = 0; i < number_of_data_items; ++i)
   {
      auto pDatum = ds.getDatumNonConst(i);
      make_tuple_incomplete(pDatum);
   }
}

void ksi::data_modifier_incompleter_random::make_tuple_incomplete(datum* pDatum)
{
   make_tuple_incomplete_range(pDatum, 0, number_of_attributes);
}

void ksi::data_modifier_incompleter_random::make_tuple_incomplete_range(datum* pDatum, const std::size_t begin, const std::size_t end)
{
   for (std::size_t i = begin; i < end; ++i)
   {
      auto random_value = distribution(random_engine);
      if (random_value < _missing_ratio)
         pDatum->make_attribute_incomplete(i);
   }
}

ksi::data_modifier * ksi::data_modifier_incompleter_random::clone () const
{
   // prototype design pattern
   return new ksi::data_modifier_incompleter_random(*this);
}



