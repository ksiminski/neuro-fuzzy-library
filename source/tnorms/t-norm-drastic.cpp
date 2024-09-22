/** @file */ 
#include <algorithm>
#include "t-norm-drastic.h"
#include "t-norm.h"
 
double ksi::t_norm_drastic::tnorm (const double a, const double b) const
{
   if (a == 1 or b == 1)
      return std::min (a, b);
   else
      return 0;
}
 
ksi::t_norm * ksi::t_norm_drastic::clone() const 
{
   return new t_norm_drastic();
}

std::ostream & ksi::t_norm_drastic::Print(std::ostream & ss) const
{
   return ss << "drastic t-norm";
}

ksi::t_norm_drastic::~t_norm_drastic()
{
}

