/** @file */ 
#include <algorithm>
#include <iostream>

#include "t-norm-fodor.h"
#include "t-norm.h"
 
double ksi::t_norm_fodor::tnorm (const double a, const double b) const
{
   if (a + b > 1)
      return std::min(a, b);
   else
      return 0;
}
 
ksi::t_norm * ksi::t_norm_fodor::clone() const 
{
   return new t_norm_fodor();
}

std::ostream & ksi::t_norm_fodor::Print(std::ostream & ss) const
{
   return ss << "Fodor t-norm";
}

ksi::t_norm_fodor::~t_norm_fodor()
{
}

