/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "dis-sigmoidal-linear.h"
 
double ksi::dis_sigmoidal_linear::dis(double e) const
{
   const double EPSILON = 1e-9;
   if (fabs(e) < EPSILON)
      return 0.0;
   else
      return (1.0 / (fabs(e) * (1 + exp (-_alfa * (fabs(e) - _beta)))));
}
 
ksi::dissimilarity * ksi::dis_sigmoidal_linear::clone() const
{
   return new dis_sigmoidal_linear(*this);
}
 
ksi::dis_sigmoidal_linear::dis_sigmoidal_linear(double alpha, double beta) 
   : _alfa(alpha), _beta(beta)
{
   
}

ksi::dis_sigmoidal_linear::~dis_sigmoidal_linear()
{

}

std::ostream & ksi::dis_sigmoidal_linear::Print(std::ostream & ss) const
{
   ss << "sigmoidal linear loss function (alpha == " << _alfa << ", beta == "
      << _beta << ")";
   return ss;
}

 



