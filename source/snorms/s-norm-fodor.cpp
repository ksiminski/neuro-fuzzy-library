/** @file */ 
#include <algorithm>
#include <iostream>

#include "s-norm-fodor.h"
#include "s-norm.h"
 
double ksi::s_norm_fodor::snorm (const double a, const double b) const
{
   if (a + b < 1)
      return std::max(a, b);
   else
      return 1.0;
}
 
ksi::s_norm * ksi::s_norm_fodor::clone() const 
{
   return new s_norm_fodor();
}

std::ostream & ksi::s_norm_fodor::Print(std::ostream & ss) const
{
   ss << "Fodor s-norm";
   return ss;
}

ksi::s_norm_fodor::~s_norm_fodor()
{
}

