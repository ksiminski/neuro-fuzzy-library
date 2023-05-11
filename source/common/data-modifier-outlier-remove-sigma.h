/** @file */


#ifndef  DATA_MODIFIER_OUTLIER_REMOVE_SIGMA_H
#define  DATA_MODIFIER_OUTLIER_REMOVE_SIGMA_H

#include "data-modifier.h"

namespace ksi
{
   /** Class removes outliers from the data set.
    * An outlier is a data item whose value in at least one dimension outstands the 
    * normal distribution by n sigmas. 
    * The class implements a decorator design pattern.
    * @author Krzysztof Siminski
    * @date   2021-01-07
    */
   class data_modifier_outlier_remove_sigma : public data_modifier
   {
       double _n; ///< multiplier of sigma
   public:
      /** @param n multiplier for sigma */ 
      data_modifier_outlier_remove_sigma(const double n);
      data_modifier_outlier_remove_sigma(const data_modifier_outlier_remove_sigma & dm);
      data_modifier_outlier_remove_sigma(data_modifier_outlier_remove_sigma && dm);
      
      data_modifier_outlier_remove_sigma & operator = (const data_modifier_outlier_remove_sigma & dm);
      data_modifier_outlier_remove_sigma & operator = (data_modifier_outlier_remove_sigma && dm);
      
      virtual ~data_modifier_outlier_remove_sigma();
      virtual data_modifier * clone() const;
 
      /** The method first removes from the dataset all value whose value in any dimension outstands more than _n * sigma of the dimension.
       * Then calls the modify method in the next data_modifier. 
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       * @date   2017-12-30
       */
      virtual void modify (dataset & ds); 
      
    
      
   };
}

#endif
