/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "dis-log.h"
 
double ksi::dis_log::dis(double e) const
{
   const double EPSILON = 1e-9;
   double e2 = e * e;
   if (fabs(e) < EPSILON)
      return 0.0;
   else
      return log10 ((1.0 + e2) / e2) ;
}
 
ksi::dissimilarity * ksi::dis_log::clone() const
{
   return new dis_log(*this);
}
 
ksi::dis_log::dis_log()
{
   
}

ksi::dis_log::~dis_log()
{

}

std::ostream & ksi::dis_log::Print(std::ostream & ss) const
{
   ss << "logarithmic loss function";
   return ss;
}

 



