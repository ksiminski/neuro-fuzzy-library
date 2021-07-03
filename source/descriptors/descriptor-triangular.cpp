/** @file */ 

#include <random>
#include "descriptor-triangular.h"

ksi::descriptor_triangular::~descriptor_triangular()
{

}


ksi::descriptor_triangular::descriptor_triangular (double support_min, double core, double support_max)
{
   _support_max = support_max;
   _support_min = support_min;
   _core = core;
   
   _previous_support_min = _support_min;
   _previous_support_max = _support_max;
   _previous_core = _core;
   
}

ksi::descriptor_triangular::descriptor_triangular(const ksi::descriptor_triangular & wzor)
{
   _support_max = wzor._support_max;
   _support_min = wzor._support_min;
   _core = wzor._core;
   
   _previous_support_min = wzor._previous_support_min;
   _previous_support_max = wzor._previous_support_max;
   _previous_core = wzor._previous_core;
   
}


double ksi::descriptor_triangular::getCoreMean() const
{
   return _core;
}
      

double ksi::descriptor_triangular::getMembership (double x)
{
   if (x < _support_min or x > _support_max)
      return last_membership = 0.0;
   else if (x < _core)
   {
      return last_membership = (x - _support_min) / (_core - _support_min);
   }
   else if (x > _core)
   {
      return last_membership = (_support_max - x) / (_support_max - _core); 
   }
   else
      return last_membership = 1.0;
}

ksi::descriptor * ksi::descriptor_triangular::clone() const
{
   return new descriptor_triangular(*this);
}

std::vector<double> ksi::descriptor_triangular::getDifferentials(double x)
{
   if (x < _support_min or x > _support_max)
      return { 0.0, 0.0, 0.0} ;
   else if (x < _core)
   {
      double denom = ((_core - _support_min) * (_core - _support_min));
      return { (- x - _core) / denom,           // d membership / d _support_min
               (-x + _support_min) / denom,     // d membership / d _core
               0.0                              // d membership / d _support_max
             };
   }
   else if (x > _core)
   {
      double denom = (_support_max - _core) * (_support_max - _core);
      return { 0.0,                        // d membership / d _support_min
               (x - _support_max) / denom, // d membership / d _core
               (x - _core) / denom         // d membership / d _support_max
             };
   }
   else
      return { 0.0, 0.0, 0.0} ;
}

std::ostream& ksi::descriptor_triangular::Print(std::ostream& ss) const
{
   ss << "(" << _support_min << ", " << _core << ", " << _support_max << ")";
   return ss;
}

std::vector< double > ksi::descriptor_triangular::getMAconsequenceParameters() const
{
   return { _support_min, _core, _support_max };
}

void ksi::descriptor_triangular::reset_parameters()
{
   _support_max = _previous_support_max;
   _support_min = _previous_support_min;
   _core        = _previous_core;
}

double ksi::descriptor_triangular::getRandomValue(std::default_random_engine& engine)
{
    std::uniform_real_distribution<double> distro (_support_min, _support_max);
    
    return distro(engine);
}
