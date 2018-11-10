/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "dis-square.h"
 
double ksi::dis_square::dis(double e) const
{
    return e;
}
 
ksi::dissimilarity * ksi::dis_square::clone() const
{
   return new dis_square(*this);
}
 
ksi::dis_square::dis_square()
{
   
}

ksi::dis_square::~dis_square()
{

}

std::ostream & ksi::dis_square::Print(std::ostream & ss) const
{
   ss << "square loss function";
   return ss;
}

 



