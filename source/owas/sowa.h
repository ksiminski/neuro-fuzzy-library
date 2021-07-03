/** @file */ 

#ifndef SOWA_H
#define SOWA_H

#include <iostream>
#include "owa.h"

namespace ksi
{
   /** sigmoidal OWA
    * \f[ \alpha(k) = \frac{1}{ 1 + \exp 
    *         \left[ \frac{2.944}{p_a N} \left( k - p_c N \right) \right] }  \f]
    @date 2018-05-20
    */
   struct sowa : virtual public owa
   {
   protected:
      /** For k in [(_pc - _pa) * _N ; (_pc - _pa) * _N ] value of the 
       * function decreases from 0.95 to 0.05. For k = _pc * _N
       * function equals 0.5.
       */
      double _pc;
      double _pa;
   public:
      /** The constructor sets _N, _pc, and _pa. */
      sowa (std::size_t N, double pc, double pa);
      sowa (double pc, double pa);
      
      sowa (const sowa & wzor);
      sowa (sowa && wzor);
      
      sowa & operator= (const sowa & wzor);
      sowa & operator= (sowa && wzor);
      
      /** @return value of SOWA */
      virtual double value (std::size_t k) const;
      
      /** cloning method */
      virtual owa * clone() const; 
      virtual ~sowa();
      
      virtual std::ostream & Print (std::ostream & ss) const;
      
      virtual std::string print_owa_parameters() const;
      
      /** @return false if parameters are not valid  */
      virtual bool are_parameters_valid() const;
   };
}

#endif
