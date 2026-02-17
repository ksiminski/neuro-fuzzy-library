/** @file */ 

#ifndef S_NORM_DRASTIC_H
#define S_NORM_DRASTIC_H

#include "s-norm.h"

#include <iostream>

namespace ksi
{
   /**
    * @author Dawid Suchy
    * @date 2022-03-15
    */
   struct s_norm_drastic : public s_norm
   {
    
      /** value of S-norm: \f$ S(a, b) = \max(a, b)\f$ for \f$ a = 0 \f$ or \f$ b = 0 \f$  
          and \f$ S(a, b) =  1 \f$ otherwise*/
      virtual double snorm (const double, const double) const;
      virtual s_norm * clone() const ;
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const; 
      
      virtual ~s_norm_drastic();
   };
}

#endif
