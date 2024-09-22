/** @file */ 
#include <algorithm>
#include <iostream>

#include "t-norm-einstein.h"
#include "t-norm.h"
 
double ksi::t_norm_einstein::tnorm (const double a, const double b) const
{
   return (a * b) / (2 - (a + b - a * b));
}
 
ksi::t_norm * ksi::t_norm_einstein::clone() const 
{
   return new t_norm_einstein();
}

std::ostream & ksi::t_norm_einstein::Print (std::ostream & ss) const
{
   return ss << "Einstein t-norm";
}

ksi::t_norm_einstein::~t_norm_einstein()
{
}

