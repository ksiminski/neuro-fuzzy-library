/** @file */

#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include <vector>
#include <cmath>

#include "matrix.h"
#include "../service/debug.h"
#include "../descriptors/DescriptorStatistics.h"

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


       /** A method returns a transposed matrix. Input matrix is not modified.
        * @param matrix matrix to transpose
        * @return a transposed matrix, input matrix is not modified
        * @date 2023-11-22
        * @author Konrad Wnuk
        */
       template <typename T = double>
           std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& matrix)
       {
           std::vector<std::vector<T>> result(matrix[0].size(), std::vector<T>(matrix.size()));

           for (std::size_t w = 0; w < matrix.size(); w++)
               for (size_t k = 0; k < matrix[w].size(); k++)
                   result[k][w] = matrix[w][k];
           return result;
       }


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

      /**
        * @return The function returns median and standard deviation of elements in a vector.
        * @param first iterator to the first element
        * @param last iterator to the past-the-end element in the vector
        * @date 2024-11-17
        * @author Konrad Wnuk
        * @throw std::string if the array has no items
        */
      template<typename T = double>
      std::pair<T, T> getMedianAndStandardDeviation(
          const typename std::vector<T>::const_iterator first,
          const typename std::vector<T>::const_iterator last
      ) {
          try {
              T sum = 0;
              T sumSq = 0;
              std::size_t numberOfElements = 0;
              for (auto iter = first; iter != last; ++iter) {
                  sum += *iter;
                  sumSq += (*iter) * (*iter);
                  numberOfElements++;
              }

              if (numberOfElements == 0)
                  throw std::string("The array has no elements!");

              T median;
              std::vector<T> data(first, last);

              if (numberOfElements % 2 == 1) {
                  auto mid = data.begin() + numberOfElements / 2;
                  std::nth_element(data.begin(), mid, data.end());
                  median = *mid;
              }
              else {
                  auto mid1 = data.begin() + numberOfElements / 2 - 1;
                  auto mid2 = data.begin() + numberOfElements / 2;
                  std::nth_element(data.begin(), mid1, data.end());
                  T val1 = *mid1;
                  std::nth_element(data.begin(), mid2, data.end());
                  T val2 = *mid2;
                  median = (val1 + val2) / 2.0;
              }

              return { median, std::sqrt(sumSq / numberOfElements - std::pow(sum / numberOfElements, 2)) };
          }
          CATCH;
      }

      /** @return The function returns mean and standard deviation of elements in a vector.
       * @param first iterator to the first element
       * @param last  iterator to the past-the-end element in the vector
       * @date 2023-11-21
       * @author Konrad Wnuk
       * @throw std::string if the array has no items
       */
      template<typename T = double>
      static
          std::pair<T, T> getMeanAndStandardDeviation(
              const typename std::vector<T>::const_iterator first,
              const typename std::vector<T>::const_iterator last
          ) {
          try {
              T sum{};
              T sumSq{};
              std::size_t counter = 0;
              for (auto iter = first; iter != last; iter++)
              {
                  sum += *iter;
                  sumSq += *iter * *iter;
                  counter++;
              }

              if (counter == 0)
                  throw std::string("The array has no elements!");

              T average = sum / counter;
              return { average, std::sqrt(sumSq / counter - average * average) };
          }
          CATCH;
      }



      /** @return The function returns a vector of values without outliers. Only values inside the interval. 
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

      /**
	   * @brief Calculates the equation of a line given two points.
	   *
	   * This function calculates the equation of a line in the form \f$y = ax + b\f$,
	   * where \f$a\f$ is the slope and \f$b\f$ is the y-constant term, based on two given points.
	   *
	   * @tparam T The data type of the coordinates (default is double)
	   * @param p1 The first point \f$x, y\f$
	   * @param p2 The second point \f$x, y\f$
	   * @return A pair representing the slope and y-constant term of the line
	   *
	   * The slope \f$a\f$ is calculated as:
	   * \f[
	   * a = \frac{{y_2 - y_1}}{{x_2 - x_1}}
	   * \f]
	   *
	   * The y-constant term \f$b\f$ is calculated as:
	   * \f[
	   * b = y_1 - \text{slope} \cdot x_1
	   * \f]
	   *
	   * @date 2023-12-26
	   * @author Konrad Wnuk
	   */
      template<typename T = double>
      static
      std::pair<T, T> calculateLineEquation(const std::pair<T, T>& p1, const std::pair<T, T>& p2) {
          const double slope = (p2.second - p1.second) / (p2.first - p1.first);
          const double constant_term = p1.second - slope * p1.first;

          return std::make_pair(slope, constant_term);
      }

      /**
       * @brief Calculates the value of a definite integral for a linear function within a given range.
	   *
	   * This function calculates the definite integral value of a linear function within the range \f$[x_1, x_2]\f$.
	   * The integral of a linear function is represented as \f$f(x) = \frac{a}{4}x^4 + \frac{b}{3}x^3 - \frac{2ea}{3}x^3 - ebx^2 + \frac{e^2a}{2}x^2 + e^2bx\f$,
       * where \f$(a, b)\f$ is a pair representing the coefficients of the linear function and \f$e\f$ is the expected value of the function
	   *
	   * @tparam T The data type of the coordinates and coefficients (default is double)
	   * @param x1 The lower bound of the integration range
	   * @param x2 The upper bound of the integration range
	   * @param params A pair representing the coefficients \f$(a, b)\f$ of the linear function
	   * @param expected The expected value used in the function
	   * @return The value of the definite integral of the linear function over the specified range
	   *
	   * @date 2023-12-26
	   * @author Konrad Wnuk
	   */
      template<typename T = double>
      static
   	  T calculateLinearDefiniteIntegralValue(const T& x1, const T& x2, const std::pair<T, T>& params, const T& expected) {
          auto f = [params] (const auto& x, const auto& expected)
          {
	       return (params.first * pow(x, 4)) / 4 + (params.second * pow(x, 3) - 2 * expected * params.first * pow(x, 3))  / 3 - expected * params.second * pow(x, 2) + (pow(expected, 2) * params.first * pow(x, 2)) / 2 + pow(expected, 2) * params.second * x;
          };
           
       	  return f(x2, expected) - f(x1, expected);
       }

      /**
	   * @brief Calculates the value of a definite integral for a rectangular function within a given range.
	   *
	   * This function calculates the definite integral value of a rectangular function within the range \f$[x_1, x_2]\f$.
	   * The integral of a rectangular function is represented as \f$f(x) = \frac{x^3}{3} - ex^2 + ex\f$,
	   * where \f$e\f$ is the expected value of the function
	   *
	   * @tparam T The data type of the coordinates and coefficient (default is double)
	   * @param x1 The lower bound of the integration range
	   * @param x2 The upper bound of the integration range
	   * @param expected The expected value used in the function
	   * @return The value of the definite integral of the rectangular function over the specified range
	   *
	   * @date 2023-12-26
	   * @author Konrad Wnuk
	   */
      template<typename T = double>
      static
          T calculateRectangularDefiniteIntegralValue(const T& x1, const T& x2, const T& expected) {
          auto f = [](const auto& x, const auto& expected) {return pow(x, 3) / 3 - expected * pow(x, 2) + pow(expected, 2) * x; };

          return f(x2, expected) - f(x1, expected);
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

