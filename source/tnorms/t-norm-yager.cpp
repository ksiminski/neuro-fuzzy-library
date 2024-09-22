/** @file */ 
#include <algorithm>
#include <cmath>
#include <iostream>

#include "t-norm.h"
#include "t-norm-parametrized.h"
#include "t-norm-yager.h"
#include "t-norm-drastic.h"

ksi::t_norm_yager::t_norm_yager(double s) : t_norm_parametrized (s)
{
}

ksi::t_norm_yager::~t_norm_yager()
{
}

ksi::t_norm * ksi::t_norm_yager::clone() const
{
   return new t_norm_yager(_parameter);
}

double ksi::t_norm_yager::tnorm(const double a, const double b) const
{
   if (_parameter == 0)
   {
       ksi::t_norm_drastic d;
       return d.tnorm(a, b);
   }
   else 
       return std::max(0.0, 1 - std::pow( (std::pow(1 - a, _parameter) + std::pow(1 - b, _parameter)) , 1.0 / _parameter));
}

std::ostream & ksi::t_norm_yager::Print(std::ostream& ss) const
{
   return ss << "Yager (s = " << _parameter << ") t-norm"; 
}

 
