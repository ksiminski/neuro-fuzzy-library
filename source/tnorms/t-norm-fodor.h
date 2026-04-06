/** @file */ 

#ifndef T_NORM_FODOR_H
#define T_NORM_FODOR_H

#include <iostream>
#include "t-norm.h"

namespace ksi
{
   struct t_norm_fodor : public t_norm
   {
      /** value of T-norm: \f$ T(a, b) = \min(a, b)\f$ for \f$ a + b > 1 \f$ 
          and \f$ T(a, b) =  0 \f$ otherwise*/
      virtual double tnorm (const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_fodor();
   };
}

#endif
