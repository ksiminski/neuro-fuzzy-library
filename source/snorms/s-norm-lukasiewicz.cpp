/** @file */ 
#include <algorithm>
#include "s-norm-lukasiewicz.h"
#include "s-norm.h"

#include <iostream>
 
double ksi::s_norm_lukasiewicz::snorm (const double a, const double b) const
{
   return std::min(a + b, 1.0);
}
 
ksi::s_norm * ksi::s_norm_lukasiewicz::clone() const 
{
   return new s_norm_lukasiewicz();
}

std::ostream & ksi::s_norm_lukasiewicz::Print(std::ostream & ss) const
{
   ss << "Lukasiewicz s-norm";
   return ss;
}

ksi::s_norm_lukasiewicz::~s_norm_lukasiewicz()
{
}

