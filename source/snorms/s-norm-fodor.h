/** @file */ 

#ifndef S_NORM_FODOR_H
#define S_NORM_FODOR_H

#include <iostream>
#include "s-norm.h"

namespace ksi
{
   /**
    * @author Dawid Suchy
    * @date 2022-03-15
    */
   struct s_norm_fodor : public s_norm
   {
      /** value of S-norm: \f$ S(a, b) = \max(a, b)\f$ for \f$ a + b < 1 \f$
          and \f$ S(a, b) =  1 \f$ otherwise*/
      virtual double snorm (const double, const double) const;
      virtual s_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~s_norm_fodor();
   };
}

#endif
