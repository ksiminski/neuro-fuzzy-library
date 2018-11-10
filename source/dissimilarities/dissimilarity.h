/** @file */ 
#ifndef DISSIMILARITY_H
#define DISSIMILARITY_H

#include <iostream>

namespace ksi
{
   /** Dissimilarity measures (loss functions) defined in
    J. Leski, Fuzzy c-ordered means clustering, Fuzzy Sets and Systems 286 (2016) pp. 114–133 
    @date 2018-05-14
    */
   class dissimilarity
   {
   public:
      /** @return value of dissimilarity measure */
      virtual double dis (double e) const = 0;
      
      /** cloning method */
      virtual dissimilarity * clone() const = 0; 
      virtual ~dissimilarity();
      
      virtual std::ostream & Print (std::ostream & ss) const = 0;
      
      /** @return name of modifiers in chain */
      virtual std::string print () const ;
   };
}

#endif
