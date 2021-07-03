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

   

