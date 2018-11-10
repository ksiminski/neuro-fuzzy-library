/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "dis-linear.h"
 
double ksi::dis_linear::dis(double e) const
{
   const double EPSILON = 1e-9;
   if (fabs(e) < EPSILON)
      return 0.0;
   else
      return (1.0 / fabs(e)) ;
}
 
ksi::dissimilarity * ksi::dis_linear::clone() const
{
   return new dis_linear(*this);
}
 
ksi::dis_linear::dis_linear()
{
   
}

ksi::dis_linear::~dis_linear()
{

}

std::ostream & ksi::dis_linear::Print(std::ostream & ss) const
{
   ss << "linear loss function";
   return ss;
}

 



