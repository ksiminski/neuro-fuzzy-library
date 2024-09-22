/** @file */ 

#ifndef S_NORM_EINSTEIN_H
#define S_NORM_EINSTEIN_H

#include <iostream>
#include "s-norm.h"


namespace ksi
{
   /**
    * @author Dawid Suchy
    * @date 2022-03-15
    */
   struct s_norm_einstein : public s_norm
   {
      /** value of S-norm: \f$ S(a, b) =  \frac{a + b}{1 + ab}\f$ */
      virtual double snorm (const double, const double) const;
      virtual s_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~s_norm_einstein();
   };
}

#endif
