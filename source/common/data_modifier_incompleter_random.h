
#ifndef DATA_MODIFIER_INCOMPLETER_RANDOM_H
#define DATA_MODIFIER_INCOMPLETER_RANDOM_H

#include <random> 

#include "datum.h"
#include "dataset.h"
#include "data-modifier.h"
#include "data_modifier_incompleter.h"

namespace ksi
{
   /** The class is responsible for incompleting the data completely at random.
    @data   2024-09-22
    @author Krzysztof Siminski 
    */
   class data_modifier_incompleter_random : public data_modifier_incompleter
   {
    public:
      data_modifier_incompleter_random (const double missing_ratio);
      data_modifier_incompleter_random (const data_modifier_incompleter_random & other) = default;
      data_modifier_incompleter_random (data_modifier_incompleter_random && other) = default;
      data_modifier_incompleter_random & operator= (const data_modifier_incompleter_random & other) = default;
      data_modifier_incompleter_random & operator= (data_modifier_incompleter_random && other) = default;
      virtual ~data_modifier_incompleter_random () = default;
      virtual data_modifier * clone () const override;  // prototype design pattern
      
      virtual std::string print() const override;
      virtual void modify (dataset & ds) override;   
      
   protected:
      virtual void make_tuple_incomplete_range (datum * pDatum, const std::size_t begin, const std::size_t end);
      std::size_t number_of_attributes;
      
   private:
      double _missing_ratio; 
      std::default_random_engine random_engine;
      std::uniform_real_distribution<double> distribution;
      std::size_t number_of_data_items;
      
      virtual void make_tuple_incomplete(datum * pDatum);
   };
}


#endif
