/** @file */ 
#include <algorithm>
#include <iostream>

#include "s-norm-einstein.h"
#include "s-norm.h"
 
double ksi::s_norm_einstein::snorm (double a, double b) const
{
   return (a + b) / (1 + (a * b));
}
 
ksi::s_norm * ksi::s_norm_einstein::clone() const 
{
   return new s_norm_einstein();
}

std::ostream & ksi::s_norm_einstein::Print (std::ostream & ss) const
{
   ss << "Einstein s-norm";
   return ss;
}

ksi::s_norm_einstein::~s_norm_einstein()
{
}

