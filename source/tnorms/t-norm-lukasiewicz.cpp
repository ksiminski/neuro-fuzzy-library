/** @file */ 
#include <algorithm>
#include "t-norm-lukasiewicz.h"
#include "t-norm.h"

#include <iostream>
 
double ksi::t_norm_lukasiewicz::tnorm (const double a, const double b) const
{
   return std::max(a + b - 1.0, 0.0);
}
 
ksi::t_norm * ksi::t_norm_lukasiewicz::clone() const 
{
   return new t_norm_lukasiewicz();
}

std::ostream & ksi::t_norm_lukasiewicz::Print(std::ostream & ss) const
{
   return ss << "Lukasiewicz t-norm";
}

ksi::t_norm_lukasiewicz::~t_norm_lukasiewicz()
{
}

