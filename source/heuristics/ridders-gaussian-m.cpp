/** @file */

#include <string>
#include <cmath>
#include <vector>
#include <utility>

#include "../service/debug.h"
#include "../auxiliary/utility-math.h"
#include "ridders.h"
#include "ridders-gaussian-m.h"

double ksi::ridders_gaussian_m::f(double m)
{
   double result = 0.0;
   for (auto p : _points)
   {
      double _x = p.first;
      double _ux = p.second;
      
      double roz = _x - m;
      double _fx = exp (- (roz * roz) / (2 * _s * _s ));
      
      result += ((_fx - _ux) * roz * _fx / (_s * _s));
   }
   
   return result;
}
 
 
ksi::ridders * ksi::ridders_gaussian_m::clone() const  
{
   return new ksi::ridders_gaussian_m (*this);
}

ksi::ridders_gaussian_m::~ridders_gaussian_m()
{
}

ksi::ridders_gaussian_m::ridders_gaussian_m(const std::vector<std::pair<double, double>> & points, double s)
{
   _points = points;
   _s = s;
}

ksi::ridders_gaussian_m::ridders_gaussian_m(const ksi::ridders_gaussian_m& wzor) : ridders (wzor)
{
   _points = wzor._points;
   _s = wzor._s;
}

ksi::ridders_gaussian_m::ridders_gaussian_m(ksi::ridders_gaussian_m && wzor) : ridders (wzor)
{
   std::swap (_points, wzor._points);
   std::swap (_s, wzor._s);
}

ksi::ridders_gaussian_m & ksi::ridders_gaussian_m::operator=(const ksi::ridders_gaussian_m & wzor)
{
    if (this == & wzor)
       return *this;
    
    ksi::ridders::operator= (wzor);
    
    _points = wzor._points;
    _s = wzor._s;
    
    return *this;
}

ksi::ridders_gaussian_m & ksi::ridders_gaussian_m::operator=(ksi::ridders_gaussian_m && wzor)
{
   if (this == & wzor)
      return *this;
   
   ksi::ridders::operator= (wzor);
   
   std::swap(_points, wzor._points);
   std::swap (_s, wzor._s);
   
   return *this;
   
}


