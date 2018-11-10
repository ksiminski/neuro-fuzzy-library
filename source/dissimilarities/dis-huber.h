/** @file */ 

#ifndef DIS_HUBER_H
#define DIS_HUBER_H

#include <iostream>
#include "dissimilarity.h"

namespace ksi
{
   /** Dissimilarity measures (loss functions) defined in
    J. Leski, Fuzzy c-ordered means clustering, Fuzzy Sets and Systems 286 (2016) pp. 114–133 
    eq. (B.6)
    @date 2018-05-14
    */
   struct dis_huber : virtual public dissimilarity
   {
   protected:
      double _delta;
      
   public:
      dis_huber (double delta);
      
      /** \f[ h(x) =  \frac{1}{\delta^2},  \quad   x = 0    \f] 
          \f[ h(x) =  \frac{1}{\delta|x|}, \quad   x \neq 0 \f] 
       */
      virtual double dis (double e) const;
      /** cloning method */
      virtual dissimilarity * clone() const; 
      
      virtual ~dis_huber();
      
      virtual std::ostream & Print (std::ostream & ss) const;
   };
}

#endif
