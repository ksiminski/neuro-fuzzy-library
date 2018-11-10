/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "dis-sigmoidal.h"
 
double ksi::dis_sigmoidal::dis(double e) const
{
   const double EPSILON = 1e-9;
   if (fabs(e) < EPSILON)
      return 0.0;
   else
      return (1.0 / (e * e * (1 + exp (-_alfa * (fabs(e) - _beta)))));
}
 
ksi::dissimilarity * ksi::dis_sigmoidal::clone() const
{
   return new dis_sigmoidal(*this);
}
 
ksi::dis_sigmoidal::dis_sigmoidal(double alpha, double beta) 
   : _alfa(alpha), _beta(beta)
{
   
}

ksi::dis_sigmoidal::~dis_sigmoidal()
{

}

std::ostream & ksi::dis_sigmoidal::Print(std::ostream & ss) const
{
   ss << "sigmoidal loss function (alpha == " << _alfa << ", beta == "
      << _beta << ")";
   return ss;
}

 



