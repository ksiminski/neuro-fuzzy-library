/** @file */

#ifndef VECTOR_OPERATORS_H
#define VECTOR_OPERATORS_H

#include <vector>
#include <iostream>

namespace ksi 
{
//   std::ostream & operator << (std::ostream & ss, const std::vector<double> & we);
   //std::ostream & operator << (std::ostream & ss, const std::vector<std::pair<double, double>> & we);
   //std::ostream & operator << (std::ostream & ss, const std::pair<double, double> & we);
   
   std::ostream & operator << (std::ostream & ss, const std::vector<std::vector<double>> & we);
   
   
//    template <class T>
//    std::ostream & operator<< (std::ostream & ss, const std::vector<T> & we)
//    {
//        ss << " [ " ;
//        for (const auto & w : we)
//            ss << w << " ";
//        ss << "] ";
//        
//        return ss;
//    }
//    
   
   std::vector<double> operator + (const std::vector<double> & l, 
                                   const std::vector<double> & p);

   std::vector<double> operator - (const std::vector<double> & l, 
                                   const std::vector<double> & p);
   
   std::vector<double> operator * (const std::vector<double> & l, 
                                   const double v);
   
   std::vector<double> operator / (const std::vector<double> & l, 
                                   const double v);
   
   std::vector<double> operator + (const std::vector<double> & l, 
                                   const double v);
   
   std::vector<double> & operator += (std::vector<double> & l, 
                                      const std::vector<double> & p);
   
   std::vector<double> & operator -= (std::vector<double> & l, 
                                      const std::vector<double> & p);
   
   std::vector<double> get_uniform_unit_random_vector (const std::size_t size);
   
   /** 
    * The function elaborates a scalar product of two vectors.
    * @throw ksi::exception is thrown if the sized of vectors do not match
    * @date 2021-01-26
    */
   double scalar_product (const std::vector<double> & l,
                          const std::vector<double> & p);
   
   /** @return true of all value in a vector are numbers,
               false if any of values is NaN or infinity.
       @date 2021-04-27 */
   bool is_valid (const std::vector<double> & l);

}

#endif 
