/** @file */ 

#ifndef ERROR_RMSE_H
#define ERROR_RMSE_H

#include <vector>
#include <utility>
#include "error-calculator.h"
#include "../common/number.h"

namespace ksi
{
   /** Class for calculating root mean square error (RMSE). */
   class error_RMSE : virtual public error_calculator
   {
   public:
      virtual ~error_RMSE();
      
      /** The method clones this object.
       * @return a pointer to a cloned object */
      virtual error_calculator * clone () const;
      
      
      /** The method calculates a root mean square error (RMSE):
       * \f[  E_{\mathrm{RMSE}} = \sqrt{ \frac{1}{N} \sum^N_{i = 1} \left( a_i - b_i \right)^2 }   \f]
       * @param expected vector with expected values \f$ \{a_i\} \f$
       * @param elaborated vector with corresponding elaborated values \f$ \{b_i\} \f$
       * @throw ksi::exception with std::string message thrown when dimensions of input vectors do not match.
       */
      virtual double getError(const std::vector<double> & expected,
                              const std::vector<double> & elaborated);
      
      /** The method calculates a root mean square error (RMSE) for interval answer of a system:
       * \f[  E_{\mathrm{RMSE}} = \sqrt{ \frac{1}{N} \sum^N_{i = 1} \left[ \max\left(a_i - \overline{b}_i, a_i - \underline{b}_i \right) \right]^2 }   \f]
       * @param expected vector with expected values \f$ \{a_i\} \f$
       * @param elaborated vector with corresponding elaborated values \f$ \{\left( \underline{b}_i, \overline{b}_i \right)\} \f$
       * @throw ksi::exception with std::string message thrown when dimensions of input vectors do not match.
       * @throw ksi::exception with std::string message thrown when vector of elaborated values holds only non-existing ksi::number's.
       */
      virtual double getError(const std::vector<double> & expected,
                              const std::vector<ksi::number> & elaborated);

      /** The method calculates a root mean square error (RMSE) for interval answer of a system:
       * \f[  E_{\mathrm{RMSE}} = \sqrt{ \frac{1}{N} \sum^N_{i = 1} \left[ \max\left(a_i - \overline{b}_i, a_i - \underline{b}_i \right) \right]^2 }   \f]
       * @param elaborated vector with corresponding elaborated values \f$ \{\left( \underline{b}_i, \overline{b}_i \right)\} \f$
       * @param expected vector with expected values \f$ \{a_i\} \f$
       * @throw ksi::exception with std::string message thrown when dimensions of input vectors do not match.
       * @throw ksi::exception with std::string message thrown when vector of elaborated values holds only non-existing ksi::number's.
       */
      virtual double getError(const std::vector<ksi::number> & elaborated,
                              const std::vector<double> & expected);

      
   };
}

#endif

