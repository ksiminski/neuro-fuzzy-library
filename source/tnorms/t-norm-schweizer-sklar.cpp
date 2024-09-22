/** @file */ 
#include <algorithm>
#include <cmath>
#include <iostream>

#include "t-norm.h"
#include "t-norm-parametrized.h"
#include "t-norm-schweizer-sklar.h"

std::ostream & ksi::t_norm_schweizer_sklar::Print(std::ostream& ss) const
{
   return ss << "Schweizer-Sklar (s = " << _parameter << ") t-norm";
}

ksi::t_norm * ksi::t_norm_schweizer_sklar::clone() const
{
   return new t_norm_schweizer_sklar(_parameter);
}

ksi::t_norm_schweizer_sklar::t_norm_schweizer_sklar(double s) : t_norm_parametrized (s)
{
}

double ksi::t_norm_schweizer_sklar::tnorm(const double a, const double b) const
{
   if (_parameter == 0)
      return a * b;

   auto ap = std::pow (a, _parameter);
   auto bp = std::pow (b, _parameter);
   auto od_p = 1.0 / _parameter;
   
   return std::pow(std::max (0.0, (ap + bp - 1)), od_p); 
}

ksi::t_norm_schweizer_sklar::~t_norm_schweizer_sklar()
{
}

