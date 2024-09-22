/** @file */ 

#include "t-norm-product.h"
#include "t-norm.h"

#include <iostream>

double ksi::t_norm_product::tnorm (const double a, const double b) const
{
   return a * b;
}
 
ksi::t_norm * ksi::t_norm_product::clone() const 
{
   return new t_norm_product();
}

std::ostream & ksi::t_norm_product::Print (std::ostream & ss) const
{
   return ss << "product t-norm";
}

ksi::t_norm_product::~t_norm_product()
{
}
