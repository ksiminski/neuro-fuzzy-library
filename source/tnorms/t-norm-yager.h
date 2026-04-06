/** @file */ 

#ifndef T_NORM_YAGER_H
#define T_NORM_YAGER_H

#include <iostream>
#include "t-norm.h"
#include "t-norm-parametrized.h"


namespace ksi
{
   struct t_norm_yager : public t_norm_parametrized
   {
      /** The constructor setting a parameter.
       @param s parameter to set */
      t_norm_yager (double s);
      /** value of T-norm: \f$ T(a, b) =  1 - \min \left\{ 1, \left[ (1-a)^s + (1-b)^s  \right]^\frac{1}{s} \right\}  \f$<br/>where\f$s\f$ is a parameter of the t-norm */
      virtual double tnorm (const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_yager();
   };
}

#endif
