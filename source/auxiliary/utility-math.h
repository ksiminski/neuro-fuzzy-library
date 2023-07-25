/** @file */

#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include <vector>
#include <cmath>

#include "../service/debug.h"

namespace ksi
{

   class utility_math
   {
       
   public:
       
       /** @return return a sing of x: +1 for positive, -1 for negative, 0 for zero
           @date 2021-01-28
           @param x a value to return sign of */
       static 
       int signum (const double x);
       
       /** @return The function returns true, if absolute difference between a and b is less than EPSILON == 0.00001
        @param a value to compare
        @param b value to compare 
        @date 2020-10-13
        */
       static 
       bool double_equal(const double a, const double b);

       
   public:
      /** @return The function returns k-th smallest element in an unsorted vector. 
       *  The function has average complexity O(n).
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

      
      /** @return The function returns median of elements in a vector. 
        * @param first iterator to the first element 
        * @param last  iterator to the past-the-end element in the vector 
        * @param k     k-th smallest  (starts with 0) 
        */
      
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

      /** @return The function returns average of elements in a vector. 
        * @param first iterator to the first element 
        * @param last  iterator to the past-the-end element in the vector 
        * @param k     k-th smallest  (starts with 0) 
        * @date 2019-03-10
        * @throw std::string if the array has no items
        */
      template<typename T = double>
      static 
      T getAverage (const typename std::vector<T>::iterator first, 
                    const typename std::vector<T>::iterator last)
      {
          try 
          {
            T sum {}; 
            std::size_t counter = 0;
            for (auto iter = first; iter != last; iter++)
            {
                sum += *iter;
                counter++;
            }
            
            if (counter == 0)
                throw std::string ("The array has no elements!");
            
            return sum / counter;
          }
          CATCH;
      }
      
      /** @return The function returns standard deviation of elements in a vector. 
        * @param first iterator to the first element 
        * @param last  iterator to the past-the-end element in the vector 
        * @param k     k-th smallest  (starts with 0) 
        * @date 2019-03-10
        * @throw std::string if the array has no items
        */
      template<typename T = double>
      static 
      T getStandardDeviation (const typename std::vector<T>::iterator first, 
                              const typename std::vector<T>::iterator last)
      {
          try 
          {
            T sum {};    // sum of items
            T sumSq {};  // sum of squares of items
            std::size_t counter = 0;
            for (auto iter = first; iter != last; iter++)
            {
                sum += *iter;
                sumSq += *iter * *iter;
                counter++;
            }
            
            if (counter == 0)
                throw std::string ("The array has no elements!");
            
            auto average = sum / counter;
            return sqrt (sumSq / counter - average * average);
          }
          CATCH;
      }
      
      /** @return The function returns a vector of values without outliers. Only values inside the interval 
       * \f[ (m - 3\sigma, m + 3\sigma) \f]
       * where <br/>
       * \f$ m \f$ -- mean values<br/>
       * \f$ \sigma \f$ -- standard deviation<br/>
        * @param first iterator to the first element 
        * @param last  iterator to the past-the-end element in the vector 
        * @return a vector of values inside the interval
        * @date 2021-01-16 
        */
      template<typename T = double>
      static
      std::vector<T> remove3sigmaExcess (const typename std::vector<T>::iterator first, 
                                         const typename std::vector<T>::iterator last)
      {
          try 
          {
              std::vector<T> result;
              
              auto average = getAverage(first, last);
              auto stddev  = getStandardDeviation(first, last);
              
              auto left  = average - 3 * stddev;
              auto right = average + 3 * stddev;
              
             for (auto iter = first; iter != last; iter++)
             {
                 T v = *iter;
                 if (left < v and v < right)
                     result.push_back(v);
             }
             
             return result;
          }
          CATCH;
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
