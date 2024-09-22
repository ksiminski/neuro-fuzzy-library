/** @file */ 

#ifndef T_NORM_FRANK_H
#define T_NORM_FRANK_H

#include <iostream>
#include "t-norm.h"
#include "t-norm-parametrized.h"


namespace ksi
{
   struct t_norm_frank : public t_norm_parametrized
   {
      /** The constructor setting a parameter.
       @param s parameter to set */
      t_norm_frank (double s);
      /** value of T-norm: \f$ T(a, b) =  \log_s \left[ 1 + \frac{\left(s^a - 1 \right)\left(s^b - 1 \right)}{s - 1}  \right]  \f$<br/>where\f$s\f$ is a parameter of the t-norm */
      virtual double tnorm (const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_frank();
   };
}

#endif
