/** @file */ 
#ifndef OWA_H
#define OWA_H

#include <iostream>

namespace ksi
{
   /** ordered weighted averaging
    @date 2018-05-20
    */
   class owa
   {
   public:
      /** @return value of OWA */
      virtual double value (std::size_t n) const = 0;
      
      /** cloning method */
      virtual owa * clone() const = 0; 
      virtual ~owa();
      
      virtual std::ostream & Print (std::ostream & ss) const = 0;
      
      /** @return name of modifiers in chain */
      virtual std::string print () const ;
   };
}

#endif
