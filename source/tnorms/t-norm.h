/** @file */ 
#ifndef T_NORMS_H
#define T_NORMS_H

#include <iostream>

namespace ksi
{
   struct t_norm 
   {
      virtual double tnorm (const double, const double) const = 0;
      virtual t_norm * clone() const = 0; 
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const = 0; 
      
      virtual ~t_norm() = 0;
   };
}

#endif
