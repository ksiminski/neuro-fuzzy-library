/** @file */ 

#ifndef S_NORM_MAX_H
#define S_NORM_MAX_H

#include <iostream>
#include "s-norm.h"

namespace ksi
{
   /**
    * @author Dawid Suchy
    * @date 2022-03-15
    */
   struct s_norm_max : public s_norm
   {
      /** value of S-norm: \f$ S(a, b) = \max(a, b) \f$ */
      virtual double snorm (const double, const double) const;
      virtual s_norm * clone() const ;
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~s_norm_max();
   };
}

#endif
