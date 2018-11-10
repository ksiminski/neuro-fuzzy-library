/** @file */

#ifndef DATA_MODIFIER_IMPUTER_H
#define DATA_MODIFIER_IMPUTER_H

#include "data-modifier.h"

namespace ksi
{
   /** The class for imputing missing values with a constant.
    * The original full data items have weight 1.0.
    * The imputed data items have lower weights:
    * \f[ w = \frac{A - M}{A} = 1 - \frac{M}{A},  \f] 
    * where <br/>
    * <ul>
    *   <li>\f$ w \f$</li> weight assigned to a data item
    *   <li>\f$ A\f$</li> number of all attributes in a data item
    *   <li>\f$ M\f$</li> number of missing attributes in a data item
    * </ul>
    */
   class data_modifier_imputer : public data_modifier 
   {
      /** value to impute the missing values with */
      double _value;
   public:
      data_modifier_imputer ();
      /** @param value a value the missing values are imputed with */
      data_modifier_imputer (double value);
      data_modifier_imputer (const data_modifier_imputer& dm);
      data_modifier_imputer (data_modifier_imputer && dm);
      
      data_modifier_imputer & operator = (const data_modifier_imputer & dm);
      data_modifier_imputer & operator = (data_modifier_imputer && dm);
      
      virtual ~data_modifier_imputer();
      virtual data_modifier * clone() const;
 
      /** The method first calls the modify method in the next data_modifier.
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       * @date   2017-12-31
       */
      virtual void modify (dataset & ds);  
      
     
      
   };
}

#endif