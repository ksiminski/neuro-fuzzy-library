/** @file */ 

#ifndef T_NORM_EINSTEIN_H
#define T_NORM_EINSTEIN_H

#include <iostream>
#include "t-norm.h"


namespace ksi
{
   struct t_norm_einstein : public t_norm
   {
      /** value of T-norm: \f$ T(a, b) =  \frac{ab}{2 - (a + b - ab)}\f$ */
      virtual double tnorm (const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_einstein();
   };
}

#endif
