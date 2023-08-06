/** @file */



#include <cmath>

#include "../common/extensional-fuzzy-number-gaussian.h"
#include "../auxiliary/mathematics.h" 


double ksi::square_root(const double & radicand)
{
   return sqrt(radicand);
}

ksi::ext_fuzzy_number_gaussian ksi::square_root (const ksi::ext_fuzzy_number_gaussian & radicand)
{
   return ksi::ext_fuzzy_number_gaussian::sqrt(radicand);
}

double ksi::power(const double & base, const double & exponent)
{
   return pow(base, exponent);
}

ksi::ext_fuzzy_number_gaussian ksi::power (const ksi::ext_fuzzy_number_gaussian & base, const double & exponent)
{
   return ksi::ext_fuzzy_number_gaussian::pow(base, exponent);
}

// 

namespace ksi
{
   /** The function saturates the input value within the interval [-half_of_saturation_brandwidth, +half_of_saturation_brandwidth]. Minimal brandwith is defined with minimal_half_of_saturation_brandwidth.
       @param input_value the value to saturate
       @param half_of_saturation_brandwidth
       @param minimal_half_of_saturation_brandwidth
       @return \f$ f(x) = 2 a \left(-\frac{1}{2} +\frac{1}{1 + \exp\left({- \frac{2x}{a}}\right)}\right)\f$, where \f$a\f$ is max(half_of_saturation_brandwidth, minimal_half_of_saturation_brandwidth).
       @date 2023-07-30
       @author Krzysztof Siminski
       */
   double saturate(const double input_value,
                   const double half_of_saturation_brandwidth,
                   const double minimal_half_of_saturation_brandwidth)
   {
      try 
      {
         double deviation = std::max(std::fabs(minimal_half_of_saturation_brandwidth), std::fabs(half_of_saturation_brandwidth));
         double saturated = 2 * deviation * (-0.5 + 1.0 / (1 + std::exp(-2 * input_value / deviation)));
      
         return saturated;
      }
      CATCH;
   } 

}
