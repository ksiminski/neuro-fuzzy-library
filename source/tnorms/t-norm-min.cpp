/** @file */ 
#include <algorithm>
#include <iostream>

#include "t-norm-min.h"
#include "t-norm.h"

 
double ksi::t_norm_min::tnorm (double a, double b) const
{
   return std::min(a, b);
}
 
ksi::t_norm * ksi::t_norm_min::clone() const 
{
   return new t_norm_min();
}

std::ostream & ksi::t_norm_min::Print(std::ostream & ss) const
{
   ss << "minimum t-norm";
   return ss;
}

ksi::t_norm_min::~t_norm_min()
{
}

