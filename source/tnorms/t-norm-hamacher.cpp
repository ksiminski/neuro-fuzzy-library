/** @file */ 
#include <algorithm>
#include <cmath>
#include <iostream>

#include "t-norm.h"
#include "t-norm-parametrized.h"
#include "t-norm-hamacher.h"

std::ostream & ksi::t_norm_hamacher::Print(std::ostream & ss) const
{
   return ss << "Hamacher (s = " << _parameter << ") t-norm";
}

ksi::t_norm * ksi::t_norm_hamacher::clone() const
{
   return new t_norm_hamacher(_parameter);
}

ksi::t_norm_hamacher::t_norm_hamacher(double s) : t_norm_parametrized(s)
{
}

double ksi::t_norm_hamacher::tnorm(const double a, const double b) const
{
   if (a == 0 and b == 0 and _parameter == 0)
      return 0;
   else 
      return (a * b) / (_parameter + (1.0 - _parameter) * (a + b - a * b));
}

ksi::t_norm_hamacher::~t_norm_hamacher()
{
}
