/** @file */ 

#ifndef UOWA_H
#define UOWA_H

#include <iostream>
#include "owa.h"

namespace ksi
{
   /** Uniform OWA
    * The function has always value 0
    * \f[  \alpha (k) = 1 \f]
    @date 2018-05-20
    */
   struct uowa : virtual public owa
   {
    
   public:
      uowa ();
       
      /** @return always 1.0 */
      virtual double value (std::size_t n) const;
      
      /** cloning method */
      virtual owa * clone() const; 
      virtual ~uowa();
      
      virtual std::ostream & Print (std::ostream & ss) const;
   };
}

#endif
