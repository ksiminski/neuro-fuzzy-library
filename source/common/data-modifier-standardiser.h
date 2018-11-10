/** @file */


#ifndef  DATA_MODIFIER_STANDARDISER_H
#define  DATA_MODIFIER_STANDARDISER_H

#include "data-modifier.h"

namespace ksi
{
   /** Class for normalisation of data to value from range [0, 1].
    * The class implements a decorator design pattern.
    * @author Krzysztof Siminski
    * @date   2017-12-30
    */
   class data_modifier_standardiser : public data_modifier
   {
   public:
      data_modifier_standardiser();
      data_modifier_standardiser(const data_modifier_standardiser& dm);
      data_modifier_standardiser(data_modifier_standardiser && dm);
      
      data_modifier_standardiser & operator = (const data_modifier_standardiser & dm);
      data_modifier_standardiser & operator = (data_modifier_standardiser && dm);
      
      virtual ~data_modifier_standardiser();
      virtual data_modifier * clone() const;
 
      /** The method first calls the modify method in the next data_modifier. 
       * Then it standarises values of each attribute to \f$N = 0\f$ and \f$\sigma = 1\f$ (each attribute separatedly). 
       * If all values of an attribute are the same, 
       * the attribute will be standarised to value 0.0.
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       * @date   2017-12-30
       */
      virtual void modify (dataset & ds); 
      
    
      
   };
}

#endif