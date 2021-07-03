/** @file */

#ifndef DATA_MODIFIER_IMPUTER_KNN_AVERAGE_H
#define DATA_MODIFIER_IMPUTER_KNN_AVERAGE_H

#include "datum.h"
#include "data-modifier.h"
#include "data-modifier-imputer-knn.h"

namespace ksi
{
   /** The class for imputing missing values with an average of existing 
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
    *  @date 2018-01-04 
       */
   class data_modifier_imputer_knn_average : public data_modifier_imputer_knn 
   {
   protected:
      
 
   public:
      data_modifier_imputer_knn_average (); 
      data_modifier_imputer_knn_average(int k);
      data_modifier_imputer_knn_average (const data_modifier_imputer_knn_average & dm);
      data_modifier_imputer_knn_average (data_modifier_imputer_knn_average && dm);
      
      data_modifier_imputer_knn_average & operator = (const data_modifier_imputer_knn_average & dm);
      data_modifier_imputer_knn_average & operator = (data_modifier_imputer_knn_average && dm);
      
      virtual ~data_modifier_imputer_knn_average();
      virtual data_modifier * clone() const;
 
      /** The method first imputes data.
       * Then calls the modify method in the next data_modifier. 
       * @param  ds dataset to modify
       * @throw ksi::exception if _k not set
       * @author Krzysztof Siminski
       * @date   2017-12-31
       */
      virtual void modify (dataset & ds);  
 
      
   };
}

#endif
