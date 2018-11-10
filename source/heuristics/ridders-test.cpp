/** @file */

#include <string>
#include <cmath>

#include "../service/debug.h"
#include "../auxiliary/utility-math.h"
#include "ridders.h"
#include "ridders-test.h"

double ksi::ridders_test::f(double x)
{
   //return x * x * x - x - 5;
   
   return pow(tan(x), tan(x)) - 1000;
}
 
 
ksi::ridders * ksi::ridders_test::clone() const
{
   return new ridders_test (*this);
}
