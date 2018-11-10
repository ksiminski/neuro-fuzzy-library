/** @file */

#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include <vector>
#include "../service/debug.h"

namespace ksi
{

   class utility_math
   {
   public:
      /** The function return k-th smallest element in an unsorted vector. 
       *  The function had average complexity O(n).
        * @param first iterator to the first element 
        * @param last  iterator to the past-the-end element in the vector 
        * @param k     k-th smallest  (starts with 0) 
        */
      
      template<typename T = double>
      static 
      T k_th_element (const typename std::vector<T>::iterator first, 
                      const typename std::vector<T>::iterator last,
                      std::size_t k
                     )
      {
         if (first + 1 < last)
         {
            auto osiowy = *first;
            auto s = first;
            
            for (auto i = first + 1; i != last; i++)
            {
               if (*i < osiowy)
               {
                  s++;
                  std::swap (*s, *i);
               }
            }
            std::swap (*first, *s);
            
            if (k == s - first)
               return *s;
            else if (k < s - first)
               return k_th_element<T>(first, s, k);
            else
               return k_th_element<T>(s + 1, last, k - (s - first + 1));
         }
         return *first;
      }
      
      template<typename T = double>
      static 
      T getMedian (const typename std::vector<T>::iterator first, 
                   const typename std::vector<T>::iterator last)
      {
         auto size = last - first; 
         if (size % 2) // odd
         {
            return ksi::utility_math::k_th_element<T>(first, last, size / 2);
         }
         else // even
         {
            auto median_right = ksi::utility_math::k_th_element<T>(first, last,
                                                               (size / 2));
            auto median_left = ksi::utility_math::k_th_element<T>(first, last,
                                                               (size / 2) - 1);
            return (median_left + median_right) / 2.0;
         }
      }
   }; 
   
   /** Class for representation of a pair: double, std::size_t with operator< .*/
   class distance_index
   {
   public:
      double distance;
      std::size_t index;
      
      bool operator < (const distance_index & right);
      
   };
}
#endif
