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
      
      uowa (const uowa & wzor);
      uowa (uowa && wzor);
      
      uowa & operator= (const uowa & wzor);
      uowa & operator= (uowa && wzor);
       
      /** @return always 1.0 */
      virtual double value (std::size_t n) const;
      
      /** cloning method */
      virtual owa * clone() const; 
      virtual ~uowa();
      
      virtual std::ostream & Print (std::ostream & ss) const;
      
      virtual std::string print_owa_parameters() const;
      
      /** @return false if parameters are not valid  */
      virtual bool are_parameters_valid() const;
   };
}

#endif
