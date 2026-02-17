/** @file */ 
#include <algorithm>
#include <cmath>
#include <iostream>

#include "t-norm.h"
#include "t-norm-parametrized.h"
#include "t-norm-sugeno-weber.h"
#include "t-norm-drastic.h"

std::ostream & ksi::t_norm_sugeno_weber::Print(std::ostream& ss) const
{
   return ss << "Sugeno-Weber (s = " << _parameter << ") t-norm";
}

ksi::t_norm * ksi::t_norm_sugeno_weber::clone() const
{
   return new t_norm_sugeno_weber (_parameter);
}

ksi::t_norm_sugeno_weber::t_norm_sugeno_weber(double s) : t_norm_parametrized (s)
{
}

double ksi::t_norm_sugeno_weber::tnorm(const double a, const double b) const
{
   if (_parameter == -1.0)
   {
      ksi::t_norm_drastic dr;
      return dr.tnorm(a, b);
   }
   else 
      return std::max (0.0, (a + b - 1.0 + _parameter * a * b) / (1.0 + _parameter));
}

ksi::t_norm_sugeno_weber::~t_norm_sugeno_weber()
{
}

