/** @file */ 

#ifndef ERROR_CALCULATOR_H
#define ERROR_CALCULATOR_H

#include <vector>
#include <utility>


namespace ksi
{
   /** Abstract class for calculating errors. */
   class error_calculator
   {
   public:
      virtual ~error_calculator();
      
      /** The method clones this object.
       * @return a pointer to a cloned object */
      virtual error_calculator * clone () const = 0;
      
      /** The method calculates an error.
       * @param expected vector with expected values
       * @param elaborated vector with corresponding elaborated values
       * @throw ksi::exception ksi::exception with std::string message thrown when dimensions of input vectors do not match.
       */
      virtual double getError(const std::vector<double> & expected,
                              const std::vector<double> & elaborated) = 0;
      
   };
}

#endif

