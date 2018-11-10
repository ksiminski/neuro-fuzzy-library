/** @file */

#include <string>
#include <cmath>
#include <vector>
#include <utility>

#include "../service/debug.h"
#include "../auxiliary/utility-math.h"
#include "ridders.h"
#include "ridders-gaussian-s.h"

double ksi::ridders_gaussian_s::f(double s)
{
   double result = 0.0;
   if (s == 0.0)
      return -1;
   for (auto p : _points)
   {
      double _x = p.first;
      double roz = _x - _m;
      double _fx = exp (- (roz * roz) / (2 * s * s ));
      double _ux = p.second;
      
      result += ((_fx - _ux) * roz * roz * _fx);
   }
   //debug(result);
   return result;
}
 
 ksi::ridders * ksi::ridders_gaussian_s::clone() const  
{
   return new ksi::ridders_gaussian_s (*this);
}

ksi::ridders_gaussian_s::~ridders_gaussian_s()
{
}

ksi::ridders_gaussian_s::ridders_gaussian_s(const std::vector<std::pair<double, double>> & points, double m)
{
   _points = points;
   _m = m;
}

ksi::ridders_gaussian_s::ridders_gaussian_s(const ksi::ridders_gaussian_s & wzor) : ridders (wzor)
{
   _points = wzor._points;
   _m = wzor._m;
}

ksi::ridders_gaussian_s::ridders_gaussian_s (ksi::ridders_gaussian_s && wzor) : ridders (wzor)
{
   std::swap (_points, wzor._points);
   std::swap (_m, wzor._m);
}

ksi::ridders_gaussian_s & ksi::ridders_gaussian_s::operator=(const ksi::ridders_gaussian_s & wzor)
{
    if (this == & wzor)
       return *this;
    
    ksi::ridders::operator= (wzor);
    
    _points = wzor._points;
    _m = wzor._m;
    
    return *this;
}

ksi::ridders_gaussian_s & ksi::ridders_gaussian_s::operator= (ksi::ridders_gaussian_s && wzor)
{
   if (this == & wzor)
      return *this;
   
   ksi::ridders::operator= (wzor);
   
   std::swap(_points, wzor._points);
   std::swap (_m, wzor._m);
   
   return *this;
   
}


