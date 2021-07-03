/** @file */

#ifndef DATA_MODIFIER_IMPUTER_MEDIAN_H
#define DATA_MODIFIER_IMPUTER_MEDIAN_H

#include "data-modifier.h"
#include "data-modifier-imputer.h"

namespace ksi
{
   /** The class for imputing missing values with an average of existing 
    *  values of the attribute. 
    * The original full data items have weight 1.0.
    * The imputed data items have lower weights:
    * \f[ w = \frac{A - M}{A} = 1 - \frac{M}{A},  \f] 
    * where <br/>
    * <ul>
    *   <li>\f$ w \f$</li> weight assigned to a data item
    *   <li>\f$ A\f$</li> number of all attributes in a data item
    *   <li>\f$ M\f$</li> number of missing attributes in a data item
    * </ul>
    *  @date 2018-01-04
       */
   class data_modifier_imputer_median : public data_modifier_imputer 
   {
      
   public:
      data_modifier_imputer_median (); 
      data_modifier_imputer_median (const data_modifier_imputer_median & dm);
      data_modifier_imputer_median (data_modifier_imputer_median && dm);
      
      data_modifier_imputer_median & operator = (const data_modifier_imputer_median & dm);
      data_modifier_imputer_median & operator = (data_modifier_imputer_median && dm);
      
      virtual ~data_modifier_imputer_median();
      virtual data_modifier * clone() const;
 
      /** The method first removes from the dataset incomplete datums.
       * Then calls the modify method in the next data_modifier. 
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       * @date   2017-12-31
       */
      virtual void modify (dataset & ds);  
 
      
   };
}

#endif
