/** @file */ 

#ifndef T_NORM_MIN_H
#define T_NORM_MIN_H

#include <iostream>
#include "t-norm.h"

namespace ksi
{
   struct t_norm_min : public t_norm
   {
      /** value of T-norm: \f$ T(a, b) = \min(a, b) \f$ */
      virtual double tnorm (const double, const double) const;
      virtual t_norm * clone() const ;
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_min();
   };
}

#endif
