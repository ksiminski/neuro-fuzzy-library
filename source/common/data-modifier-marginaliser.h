/** @file */

#ifndef DATA_MODIFIER_MARGINALISER_H
#define DATA_MODIFIER_MARGINALISER_H

#include "data-modifier.h"

namespace ksi
{
   class data_modifier_marginaliser : public data_modifier 
   {
   public:
      data_modifier_marginaliser();
      data_modifier_marginaliser(const data_modifier_marginaliser& dm);
      data_modifier_marginaliser(data_modifier_marginaliser && dm);
      
      data_modifier_marginaliser & operator = (const data_modifier_marginaliser & dm);
      data_modifier_marginaliser & operator = (data_modifier_marginaliser && dm);
      
      virtual ~data_modifier_marginaliser();
      virtual data_modifier * clone() const;
 
      /** The method first calls the modify method in the next data_modifier.
       * The method removes from the dataset incomplete datums.
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       * @date   2017-12-31
       */
      virtual void modify (dataset & ds); 
      
   };
}

#endif 
