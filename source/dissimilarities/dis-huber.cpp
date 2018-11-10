/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "dis-huber.h"
 
double ksi::dis_huber::dis(double e) const
{
   if (fabs(e) <= _delta)
      return 1.0 / (_delta * _delta);
   else
      return 1.0 / (_delta * fabs (e));
}
 
ksi::dissimilarity * ksi::dis_huber::clone() const
{
   return new dis_huber(*this);
}
 
ksi::dis_huber::dis_huber(double delta) : _delta(delta)
{
}

ksi::dis_huber::~dis_huber()
{

}

std::ostream & ksi::dis_huber::Print(std::ostream & ss) const
{
   ss << "Huber loss function (delta == " << _delta << ")";
   return ss;
}

 



