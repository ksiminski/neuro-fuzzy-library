/** @file */ 
#ifndef S_NORM_H
#define S_NORM_H

#include <iostream>

namespace ksi
{
   /**
    * @author Dawid Suchy
    * @date 2022-03-15
    */
   struct s_norm 
   {
      virtual double snorm (const double, const double) const = 0;
      virtual s_norm * clone() const = 0; 
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const = 0; 
      
      virtual ~s_norm() = 0;
   };
}

#endif
