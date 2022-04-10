/** @file */ 

#ifndef S_NORM_LUKASIEWICZ_H
#define S_NORM_LUKASIEWICZ_H

#include <iostream>
#include "s-norm.h"

namespace ksi
{
   struct s_norm_lukasiewicz : public s_norm
   {
      /** value of S-norm: \f$ S(a, b) = \min(a + b, 1) \f$ */
      virtual double snorm (double, double) const;
      virtual s_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~s_norm_lukasiewicz(); 
   };
}

#endif
