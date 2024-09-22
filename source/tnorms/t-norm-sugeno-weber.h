/** @file */ 

#ifndef T_NORM_SUGENO_H
#define T_NORM_SUGENO_H

#include <iostream>
#include "t-norm.h"
#include "t-norm-parametrized.h"


namespace ksi
{
   struct t_norm_sugeno_weber : public t_norm_parametrized
   {
      /** The constructor setting a parameter.
       @param s parameter to set */
      t_norm_sugeno_weber (double s);
      /** value of T-norm: if \f$s = -1\f$, then \f$T(a, b) = T_D(a,b)\f$, where\f$T_D(\f$ is the drastic T-norm, otherwise  \f$ T(a, b) = \max \left[ 0.0; \frac{a + b - 1 + sab}{1 + s} \right]\f$<br/>where\f$s\f$ is a parameter of the t-norm */
      virtual double tnorm(const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_sugeno_weber();
   };
}

#endif
