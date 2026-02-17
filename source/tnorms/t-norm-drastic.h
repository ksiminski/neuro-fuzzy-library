/** @file */ 

#ifndef T_NORM_DRASTIC_H
#define T_NORM_DRASTIC_H

#include "t-norm.h"

#include <iostream>

namespace ksi
{
   struct t_norm_drastic : public t_norm
   {
    
      /** value of T-norm: \f$ T(a, b) = \min(a, b)\f$ for \f$ a = 1 \f$ or \f$ b = 1 \f$  
          and \f$ T(a, b) =  0 \f$ otherwise*/
      virtual double tnorm (const double, const double) const;
      virtual t_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~t_norm_drastic();
   };
}

#endif
