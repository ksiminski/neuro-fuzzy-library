/** @file */ 

#ifndef ERROR_MAE_H
#define ERROR_MAE_H

#include <vector>
#include <utility>
#include "error-calculator.h"
#include "../common/number.h"

namespace ksi
{
   /** Class for calculating mean absolute error (MAE). */
   class error_MAE : virtual public error_calculator
   {
   public:
      virtual ~error_MAE();
      
      /** The method clones this object.
       * @return a pointer to a cloned object */
      virtual error_calculator * clone () const;
      
      
      /** The method calculates a mean absolute error (MAE):
       * \f[  E_{\mathrm{MAE}} =  \frac{1}{N} \sum^N_{i = 1} \left| a_i - b_i \right|    \f]
       * @param expected vector with expected values \f$ \{a_i\} \f$
       * @param elaborated vector with corresponding elaborated values \f$ \{b_i\} \f$
       * @throw ksi::exception with std::string message thrown when dimensions of input vectors do not match.
       */
      virtual double getError(const std::vector<double> & expected,
                              const std::vector<double> & elaborated);
      
     
      
   };
}

#endif

