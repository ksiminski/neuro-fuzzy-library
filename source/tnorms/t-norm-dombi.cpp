/** @file */ 
#include <algorithm>
#include <cmath>
#include <iostream>

#include "t-norm.h"
#include "t-norm-parametrized.h"
#include "t-norm-dombi.h"


std::ostream & ksi::t_norm_dombi::Print(std::ostream& ss) const
{
   return ss << "Dombi (s = " << _parameter << ") t-norm";
}

ksi::t_norm * ksi::t_norm_dombi::clone() const
{
   return new t_norm_dombi (_parameter);
}

ksi::t_norm_dombi::t_norm_dombi(double s) : t_norm_parametrized (s)
{
}

double ksi::t_norm_dombi::tnorm(const double a, const double b) const
{
   if (a == 0 or b == 0)
      return 0;
   if (_parameter == 0)
   {
      if (std::max(a, b) == 1)
         return std::min(a, b);
      else
         return 0; 
   }

   auto as = std::pow ( (1.0 / a) - 1.0  , _parameter);
   auto bs = std::pow ( (1.0 / b) - 1.0  , _parameter);
   
   return 1.0 / (1.0 + std::pow (as + bs, 1.0 / _parameter));
}

ksi::t_norm_dombi::~t_norm_dombi()
{
}

