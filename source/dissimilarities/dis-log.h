/** @file */ 

#ifndef DIS_LOG_H
#define DIS_LOG_H

#include <iostream>
#include "dissimilarity.h"

namespace ksi
{
   /** Dissimilarity measures (loss functions) defined in
    J. Leski, Fuzzy c-ordered means clustering, Fuzzy Sets and Systems 286 (2016) pp. 114–133 
    eq (B.6)
    @date 2018-05-14
    */
   struct dis_log : virtual public dissimilarity
   {
    
   public:
      dis_log ();
      /** 
       *  \f[ h (x) =  0, \quad   x = 0  \f] 
       *  \f[ h(x)  =  \frac{\log\left(1 + x^2 \right)}{x^2}, \quad x \neq 0 \f] 
       */
      virtual double dis (double e) const;
      /** cloning method */
      virtual dissimilarity * clone() const; 
      
      virtual ~dis_log();
      
      virtual std::ostream & Print (std::ostream & ss) const;
   };
}

#endif
