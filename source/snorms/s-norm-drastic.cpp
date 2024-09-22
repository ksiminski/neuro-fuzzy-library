/** @file */ 
#include <algorithm>
#include "s-norm-drastic.h"
#include "s-norm.h"
 
double ksi::s_norm_drastic::snorm (const double a, const double b) const
{
   if (a == 0 || b == 0)
      return std::max(a, b);
   else
      return 1;
}

ksi::s_norm * ksi::s_norm_drastic::clone() const 
{
   return new s_norm_drastic();
}

std::ostream & ksi::s_norm_drastic::Print(std::ostream & ss) const
{
   ss << "drastic s-norm";
   return ss;
}

ksi::s_norm_drastic::~s_norm_drastic()
{
}

