/** @file */ 
#include <algorithm>
#include <cmath>
#include <iostream>

#include "t-norm.h"
#include "t-norm-parametrized.h"
#include "t-norm-frank.h"

ksi::t_norm_frank::~t_norm_frank()
{
}

ksi::t_norm_frank::t_norm_frank(double parameter) : t_norm_parametrized (parameter)
{
}

ksi::t_norm * ksi::t_norm_frank::clone() const
{
   return new t_norm_frank(_parameter);
}

std::ostream & ksi::t_norm_frank::Print(std::ostream& ss) const
{
   return ss << "Frank (s = " << _parameter << ") t-norm";
}

double ksi::t_norm_frank::tnorm(const double a, const double b) const
{
   if (_parameter == 0)
      return std::min(a, b);
   else if (_parameter == 1)
      return a * b;
   return log10 ( 1 + (std::pow(_parameter, a) - 1.0) * (std::pow(_parameter, b) - 1.0) / (_parameter - 1.0) ) / log10 (_parameter);
}

