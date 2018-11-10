/** @file */ 

#ifndef DISTANCE_EUCLIDEAN_INCOMPLETE_H
#define DISTANCE_EUCLIDEAN_INCOMPLETE_H

#include <vector>
#include "number.h"
#include "datum.h"
#include "distance.h"
#include "distance-euclidean.h"

namespace ksi
{
   /** Class for calculating an Euclidean distance between incomplete data.
    * @date 2018-01-04
    * 
     */
   class distance_euclidean_incomplete : virtual public distance_euclidean
   {
   protected:
      
   public:
      virtual ~distance_euclidean_incomplete();  
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p);
      /** method for cloning an object */
      virtual distance * clone ();
   };
}

#endif

