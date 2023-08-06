/** @file */

#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <cmath>
#include "../common/extensional-fuzzy-number-gaussian.h"
#include "../service/exception.h"

namespace ksi
{
   /** Just a square root of a double */
   double square_root(const double & radicand);
   /** @return square root of a gaussian extensional fuzzy number */
   ksi::ext_fuzzy_number_gaussian square_root (const ksi::ext_fuzzy_number_gaussian & radicand);
   
   /** Just a power of a double */
   double power(const double & base, const double & exponent);

   /** @return power of a gaussian extensional fuzzy number */
   ksi::ext_fuzzy_number_gaussian power (const ksi::ext_fuzzy_number_gaussian & base, const double & exponent);
   
   /** The function saturates the input value within the interval [-half_of_saturation_brandwidth, +half_of_saturation_brandwidth]. Minimal brandwith is defined with minimal_half_of_saturation_brandwidth.
    @param input_value the value to saturate 
    @param half_of_saturation_brandwidth 
    @param minimal_half_of_saturation_brandwidth 
    @return \f$ f(x) = 2 a \left(-\frac{1}{2} +\frac{1}{1 + \exp\left({- \frac{2x}{a}}\right)}\right)\f$, where \f$a\f$ is max(half_of_saturation_brandwidth, minimal_half_of_saturation_brandwidth).
    @date 2023-07-30
    @author Krzysztof Siminski
    */
   double saturate (const double input_value,
                    const double half_of_saturation_brandwidth, 
                    const double minimal_half_of_saturation_brandwidth);
}
#endif
