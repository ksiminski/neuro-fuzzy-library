/** @file */

#ifndef  DATA_MODIFIER_NORMALISER_H
#define  DATA_MODIFIER_NORMALISER_H

#include "data-modifier.h"

namespace ksi
{
   /** Class for normalisation of data to value from range [0, 1].
    * The class implements a decorator design pattern.
    * @author Krzysztof Siminski
    * @date   2017-12-29
    */
   class data_modifier_normaliser : public data_modifier
   {
   public:
      data_modifier_normaliser();
      data_modifier_normaliser(const data_modifier_normaliser& dm);
      data_modifier_normaliser(data_modifier_normaliser&& dm);
      
      data_modifier_normaliser & operator = (const data_modifier_normaliser & dm);
      data_modifier_normaliser & operator = (data_modifier_normaliser && dm);
      
      virtual ~data_modifier_normaliser();
      virtual data_modifier * clone() const;
 
      /** The method first calls the modify method in the next data_modifier. 
       * Then it normalises values of each attribute to the range [0, 1]
       * (each attribute separatedly). If all values of an attribute are the same, 
       * the attribute will be normalised to value 0.5.
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       * @date   2017-12-29
       */
      virtual void modify (dataset & ds);   
      
   };
}

#endif
