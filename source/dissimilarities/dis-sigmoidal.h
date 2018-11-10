/** @file */ 

#ifndef DIS_SIGMOIDAL_H
#define DIS_SIGMOIDAL_H

#include <iostream>
#include "dissimilarity.h"

namespace ksi
{
   /** Dissimilarity measures (loss functions) defined in
    J. Leski, Fuzzy c-ordered means clustering, Fuzzy Sets and Systems 286 (2016) pp. 114–133 
    eq (B.7)
    @date 2018-05-14
    */
   struct dis_sigmoidal : virtual public dissimilarity
   {
   protected:
      double _alfa;
      double _beta;
   public:
      dis_sigmoidal (double alpha, double beta);
      
      /** \f[ h (x) =  0, \quad   x = 0  \f] 
          \f[ h(x)  =  \frac{1}{x^2 \left[ 1 + \exp \left( -\alpha (|x| - \beta )\right) \right]}, \quad x \neq 0 \f] 
       */
      virtual double dis (double e) const;
      /** cloning method */
      virtual dissimilarity * clone() const; 
      
      virtual ~dis_sigmoidal();
      
      virtual std::ostream & Print (std::ostream & ss) const;
   };
}

#endif
