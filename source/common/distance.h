/** @file */ 

#ifndef DISTANCE_H
#define DISTANCE_H

#include <vector>
#include "number.h"
#include "datum.h"

namespace ksi
{
   /** Class for calculating a distance between data.
    * @date 2018-01-04
    * 
     */
   class distance 
   {
   protected:
      
   public:
      virtual ~distance ();
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p) = 0;
      /** method for cloning an object */
      virtual distance * clone () = 0;
   };
}

#endif

