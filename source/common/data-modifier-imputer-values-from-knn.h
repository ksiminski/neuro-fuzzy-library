/** @file */

#ifndef DATA_MODIFIER_IMPUTER_VALUES_FROM_KNN_H
#define DATA_MODIFIER_IMPUTER_VALUES_FROM_KNN_H

#include "datum.h"
#include "data-modifier.h"
#include "data-modifier-imputer-knn.h"

namespace ksi
{
   /** The class for imputing missing values with values from k nearest neighbours.
    * Each incomplete value is substituted with k data items that inhering 
    * missing values from k nearest neighbours. The 1st data item from the 1st 
    * neighbour, the 2nd from the 2nd neighbour, ..., the k-th from the k-th
    * neighbour.
    * @date 2018-05-13  
    */
   class data_modifier_imputer_values_from_knn : public data_modifier_imputer_knn 
   {
   protected:
      
      
      /** The method returns a vector of pointer to _k neighbours of r-th datum 
       *  in the dataset ds. 
       * @param ds dataset to search neighbours in
       * @param r  index of a datum to find neighbours for
       * @param c  indices of incomplete attributes
       * @param _k number of neighbours to find
       * @return The method returs a vector of pointers to neighbours.
       * @date 2018-05-14 
       */
      std::vector< const ksi::datum* > getNeighbours(const dataset& ds, std::size_t r, const std::vector< std::size_t >& indices_of_missing_attr, int _k);
 
   public:
      data_modifier_imputer_values_from_knn (); 
      data_modifier_imputer_values_from_knn(int k);
      data_modifier_imputer_values_from_knn (const data_modifier_imputer_values_from_knn & dm);
      data_modifier_imputer_values_from_knn (data_modifier_imputer_values_from_knn && dm);
      
      data_modifier_imputer_values_from_knn & operator = (const data_modifier_imputer_values_from_knn & dm);
      data_modifier_imputer_values_from_knn & operator = (data_modifier_imputer_values_from_knn && dm);
      
      virtual ~data_modifier_imputer_values_from_knn();
      virtual data_modifier * clone() const;
 
      /** The method first removes from the dataset incomplete datums.
       * Then calls the modify method in the next data_modifier. 
       * @param  ds dataset to modify
       * @throw ksi::exception if _k not set
       * @author Krzysztof Siminski 
       */
      virtual void modify (dataset & ds);  
      
  
       
   };
}

#endif
