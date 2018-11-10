/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "dis-log-linear.h"
 
double ksi::dis_log_linear::dis(double e) const
{
   const double EPSILON = 1e-9;
   double e2 = e * e;
   if (fabs(e) < EPSILON)
      return 0.0;
   else
      return log10 ((1.0 + e2) / fabs(e)) ;
}
 
ksi::dissimilarity * ksi::dis_log_linear::clone() const
{
   return new dis_log_linear(*this);
}
 
ksi::dis_log_linear::dis_log_linear()
{
   
}

ksi::dis_log_linear::~dis_log_linear()
{

}

std::ostream & ksi::dis_log_linear::Print(std::ostream & ss) const
{
   ss << "logarithmic linear loss function";
   return ss;
}

 



