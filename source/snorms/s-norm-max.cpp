/** @file */ 
#include <algorithm>
#include <iostream>

#include "s-norm-max.h"
#include "s-norm.h"

 
double ksi::s_norm_max::snorm (const double a, const double b) const
{
   return std::max(a, b);
}
 
ksi::s_norm * ksi::s_norm_max::clone() const 
{
   return new s_norm_max();
}

std::ostream & ksi::s_norm_max::Print(std::ostream & ss) const
{
   ss << "maximum s-norm";
   return ss;
}

ksi::s_norm_max::~s_norm_max()
{
}

