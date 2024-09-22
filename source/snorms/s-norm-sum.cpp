/** @file */ 

#include "s-norm-sum.h"
#include "s-norm.h"

#include <iostream>

double ksi::s_norm_sum::snorm (const double a, const double b) const
{
   return (a + b) - (a * b);
}

ksi::s_norm * ksi::s_norm_sum::clone() const 
{
   return new s_norm_sum();
}

std::ostream & ksi::s_norm_sum::Print (std::ostream & ss) const
{
   ss << "sum s-norm";
   return ss;
}

ksi::s_norm_sum::~s_norm_sum()
{
}
