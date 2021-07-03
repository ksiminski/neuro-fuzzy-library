/** @file */

#ifndef DATA_MODIFIER_IMPUTER_KNN_H
#define DATA_MODIFIER_IMPUTER_KNN_H

#include "datum.h"
#include "data-modifier.h" 
#include "data-modifier-imputer.h"

namespace ksi
{
   /** The abstract class for imputing missing values values calculated from k nearest neighbours.
    *  @date 2018-01-04
       */
   class data_modifier_imputer_knn : public data_modifier_imputer
   {
   protected:
      /** k nearest neighbours */
      int _k = -1;
      /** The method returns a vector of pointer to _k neighbours of r-th datum 
       *  in the dataset ds. 
       * @param ds dataset to search neighbours in
       * @param r  index of a datum to find neighbours for
       * @param c  index of an incomplete attribute
       * @param _k number of neighbours to find
       * @return The method returs a vector of pointers to neighbours.
       * @date 2018-01-04 
       */
      std::vector< const ksi::datum* > getNeighbours(const dataset& ds, std::size_t r, std::size_t c, int _k);
   public:
      data_modifier_imputer_knn (); 
      data_modifier_imputer_knn(int k);
      data_modifier_imputer_knn (const data_modifier_imputer_knn & dm);
      data_modifier_imputer_knn (data_modifier_imputer_knn && dm);
      
      data_modifier_imputer_knn & operator = (const data_modifier_imputer_knn & dm);
      data_modifier_imputer_knn & operator = (data_modifier_imputer_knn && dm);
      
      virtual ~data_modifier_imputer_knn();
      virtual data_modifier * clone() const = 0;
 
      /** The method removes from the dataset incomplete datums.
       * Then calls the modify method in the next data_modifier. 
       * @param  ds dataset to modify
       * @author Krzysztof Siminski
       */
      virtual void modify (dataset & ds) = 0;  
      
      /** @return name of modifiers in chain */
      virtual std::string print () const override;
 
      
   };
}

#endif
