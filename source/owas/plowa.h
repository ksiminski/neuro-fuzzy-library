/** @file */ 

#ifndef PLOWA_H
#define PLOWA_H

#include <iostream>
#include "owa.h"

namespace ksi
{
   /** piecewise-linear OWA
    * \f[ \alpha(k) = 
    *     \max \left\{ \min \left[ \left(  \frac{p_c N - k}{2 p_l N} + 0.5  \right)   , 1 \right]  , 0 \right\}  \f]
    @date 2018-05-20
    */
   struct plowa : virtual public owa
   {
   protected:
      /** For k in [(_pc - _pl) * _N ; (_pc + _pl) * _N ] value of the 
       * function linearly decreases from 1.0 to 0.0. For k = _pc * _N
       * function equals 0.5.
       */
      double _pc;
      double _pl;
   public:
      /** The constructor sets _N, _pc, and _pl. */
      plowa (std::size_t N, double pc, double pl);
      plowa (const plowa & wzor);
      plowa (plowa && wzor);
      
      plowa & operator= (const plowa & wzor);
      plowa & operator= (plowa && wzor);
       
      /** @return value of PLOWA */
      virtual double value (std::size_t k) const;
      
      /** cloning method */
      virtual owa * clone() const; 
      virtual ~plowa();
      
      virtual std::ostream & Print (std::ostream & ss) const;
      
      virtual std::string print_owa_parameters() const;
      
      /** @return false if parameters are not valid  */
      virtual bool are_parameters_valid() const;
   };
}

#endif
