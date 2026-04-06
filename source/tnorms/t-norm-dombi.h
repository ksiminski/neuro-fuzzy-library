/** @file */ 

#ifndef T_NORM_DOMBI_H
#define T_NORM_DOMBI_H

#include <iostream>
#include "t-norm.h"
#include "t-norm-parametrized.h"


namespace ksi
{
   /** The Dombi t-norm family. */
   struct t_norm_dombi : public t_norm_parametrized
   {
      /** The constructor setting a parameter.
       @param s parameter to set */
      t_norm_dombi (double s);
      /** value of T-norm: \f$ T(a, b) = \frac{1}{1 + \left[ \left( \frac{1}{a} - 1 \right)^s + \left( \frac{1}{b} - 1 \right)^s \right]^\frac{1}{s}} \f$<br/>where\f$s\f$ is a parameter of the t-norm */
      virtual double tnorm(const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_dombi();
   };
}

#endif
