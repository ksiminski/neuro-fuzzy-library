/** @file */ 

#ifndef DIS_SQUARE_H
#define DIS_SQUARE_H

#include <iostream>
#include "dissimilarity.h"

namespace ksi
{
   /** Dissimilarity measures (loss functions)  
    @date 2018-08-30
    */
   struct dis_square : virtual public dissimilarity
   {
    
   public:
      dis_square ();
      /** \f[ h(x)  =  x \f] 
       */
      virtual double dis (double e) const;
      /** cloning method */
      virtual dissimilarity * clone() const; 
      
      virtual ~dis_square();
      
      virtual std::ostream & Print (std::ostream & ss) const;
   };
}

#endif
