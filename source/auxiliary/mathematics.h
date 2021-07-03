/** @file */

#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <cmath>
#include "../common/extensional-fuzzy-number-gaussian.h"

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
   
   
}
#endif
