/** @file */ 

#ifndef DISTANCE_EUCLIDEAN_H
#define DISTANCE_EUCLIDEAN_H

#include <vector>
#include "number.h"
#include "datum.h"
#include "distance.h"

namespace ksi
{
   /** Class for calculating a distance between data.
    * @date 2018-01-04
    * 
     */
   class distance_euclidean : virtual public distance 
   {
   protected:
      
   public:
      virtual ~distance_euclidean ();
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p);
      /** method for cloning an object */
      virtual distance * clone ();
   };
}

#endif

