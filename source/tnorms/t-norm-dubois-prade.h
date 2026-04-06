/** @file */ 

#ifndef T_NORM_DUBOIS_PRADE_H
#define T_NORM_DUBOIS_PRADE_H

#include <iostream>
#include "t-norm.h"
#include "t-norm-parametrized.h"


namespace ksi
{
   /** The Dubois-Prade t-norm */
   struct t_norm_dubois_prade : public t_norm_parametrized
   {
      /** The constructor setting a parameter.
       @param s parameter to set */
      t_norm_dubois_prade (double s);
      /** value of T-norm: \f$ T(a, b) =  \frac{ab}{\max (a, b, s)}  \f$<br/>where\f$s\f$ is a parameter of the t-norm */
      virtual double tnorm(const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_dubois_prade();
   };
}

#endif
