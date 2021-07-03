/** @file */

#ifndef DATA_MODIFIER_IMPUTER_KNN_MEDIAN_H
#define DATA_MODIFIER_IMPUTER_KNN_MEDIAN_H

#include "datum.h"
#include "data-modifier.h"
#include "data-modifier-imputer-knn.h"
#include "../service/debug.h"

namespace ksi
{
   /** The class for imputing missing values with an median of existing 
    *  k values of the attribute. 
    * The original full data items have weight 1.0.
    * The imputed data items have lower weights:
    * \f[ w = \frac{A - M}{A} = 1 - \frac{M}{A},  \f] 
    * where <br/>
    * <ul>
    *   <li>\f$ w \f$</li> weight assigned to a data item
    *   <li>\f$ A\f$</li> number of all attributes in a data item
    *   <li>\f$ M\f$</li> number of missing attributes in a data item
    * </ul>
    *  @date 2018-01-06 
       */
   class data_modifier_imputer_knn_median : public data_modifier_imputer_knn 
   {
   protected:
       
 
   public:
      data_modifier_imputer_knn_median (); 
      data_modifier_imputer_knn_median(int k);
      data_modifier_imputer_knn_median (const data_modifier_imputer_knn_median & dm);
      data_modifier_imputer_knn_median (data_modifier_imputer_knn_median && dm);
      
      data_modifier_imputer_knn_median & operator = (const data_modifier_imputer_knn_median & dm);
      data_modifier_imputer_knn_median & operator = (data_modifier_imputer_knn_median && dm);
      
      virtual ~data_modifier_imputer_knn_median();
      virtual data_modifier * clone() const;
 
      /** The method imputes data.
       * Then calls the modify method in the next data_modifier. 
       * @param  ds dataset to modify
       * @author Krzysztof Siminski 
       * @throw ksi::exception if _k not set
       */
      virtual void modify (dataset & ds);  
      
 
      
   };
}

#endif
