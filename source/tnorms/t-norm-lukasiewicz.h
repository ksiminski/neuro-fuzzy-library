/** @file */ 

#ifndef T_NORM_LUKASIEWICZ_H
#define T_NORM_LUKASIEWICZ_H

#include <iostream>
#include "t-norm.h"

namespace ksi
{
   struct t_norm_lukasiewicz : public t_norm
   {
      /** value of T-norm: \f$ T(a, b) = \max(a + b - 1, 0) \f$ */
      virtual double tnorm (double, double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_lukasiewicz(); 
   };
}

#endif
