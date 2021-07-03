/** @file */ 

#include <algorithm>
#include <string>
#include "descriptor-trapezoidal.h"
#include "../service/debug.h"

#include <iostream>



ksi::descriptor_trapezoidal::~descriptor_trapezoidal()
{

}


ksi::descriptor_trapezoidal::descriptor_trapezoidal (double support_min, double core_min, double core_max, double support_max)
{
   _support_min = support_min;
   _support_max = support_max;
   _core_min = core_min; 
   _core_max = core_max;
   
   _previous_support_min = support_min;
   _previous_support_max = support_max;
   _previous_core_min = core_min; 
   _previous_core_max = core_max;
   
}

ksi::descriptor_trapezoidal::descriptor_trapezoidal (const ksi::descriptor_trapezoidal & wzor)
{
   _support_min = wzor._support_min;
   _support_max = wzor._support_max;
   _core_min = wzor._core_min; 
   _core_max = wzor._core_max;
   
   _previous_support_min = wzor._previous_support_min;
   _previous_support_max = wzor._previous_support_max;
   _previous_core_min = wzor._previous_core_min; 
   _previous_core_max = wzor._previous_core_max;
   
}

double ksi::descriptor_trapezoidal::getCoreMean() const
{
   return (_core_min + _core_max) / 2.0;
}


double ksi::descriptor_trapezoidal::getMembership (double x)
{
   try
   {
      if (_support_min > _core_min)
         throw std::string ("minimum support < min core in a trapezoidal fuzzy set");
      if (_core_max > _support_max)
         throw std::string ("maximum core > max support in a trapezoidal fuzzy set");
      
      if (x <= _support_min or x >= _support_max)
         return last_membership = 0.0;
      else if (x >= _core_min and x <= _core_max)
         return last_membership = 1.0;
      else if (_support_min < x and x < _core_min)
         return last_membership = (x - _support_min) / (_core_min - _support_min);
      else 
         return last_membership = (_support_max - x) / (_support_max - _core_max);
   }
   CATCH;
}

std::vector<double> ksi::descriptor_trapezoidal::getDifferentials (double x)
{
   try
   {
      if (_support_min > _core_min)
         throw std::string ("minimum support < min core in a trapezoidal fuzzy set");
      if (_core_max > _support_max)
         throw std::string ("maximum core > max support in a trapezoidal fuzzy set");
   
      if (x <= _support_min or x >= _support_max)
         return { 0.0, 0.0, 0.0, 0.0 };
      else if (x >= _core_min and x <= _core_max)
         return { 0.0, 0.0, 0.0, 0.0 };
      else if (_support_min < x and x < _core_min)
      {
         double denom = ((_core_min - _support_min) * (_core_min - _support_min));
         return { (- x - _core_min) / denom,    // d membership / d _support_min
                  (-x + _support_min) / denom,  // d membership / d _core_min
                  0.0,                          // d membership / d _core_max
                  0.0                           // d membership / d _support_max
             };
      }
      else
      {
         double denom = (_support_max - _core_max) * (_support_max - _core_max);
         return { 0.0,                        // d membership / d _support_min
                  0.0,                        // d membership / d _core_min   
                  (x - _support_max) / denom, // d membership / d _core_max
                  (x - _core_max) / denom     // d membership / d _support_max
             };
      }
   }
   CATCH;
}

ksi::descriptor * ksi::descriptor_trapezoidal::clone() const
{
   return new descriptor_trapezoidal(*this);
}

std::ostream& ksi::descriptor_trapezoidal::Print(std::ostream& ss) const
{
   ss << "(" << _support_min << ", " << _core_min << ", " 
      << _core_max << ", " << _support_max << ")";
   return ss;
}

std::vector< double > ksi::descriptor_trapezoidal::getMAconsequenceParameters() const
{
   return { _support_min, (_core_min + _core_max) / 2.0, _support_max };
}

void ksi::descriptor_trapezoidal::reset_parameters()
{
   _support_max = _previous_support_max;
   _support_min = _previous_support_min;
   _core_max = _previous_core_max;
   _core_min = _previous_core_min;
}
 
double ksi::descriptor_trapezoidal::getRandomValue(std::default_random_engine& engine)
{
    std::uniform_real_distribution<double> distro (_support_min, _support_max);
    return distro (engine);
}
 
