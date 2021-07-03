/** @file */ 

#include <algorithm>
#include <string>
#include "descriptor-singleton.h"
#include "../service/debug.h"

#include <iostream>

ksi::descriptor_singleton::descriptor_singleton (double value) 
   : descriptor_trapezoidal(value, value, value, value)
{
}

ksi::descriptor_singleton::descriptor_singleton (const ksi::descriptor_singleton & wzor) : ksi::descriptor_trapezoidal (wzor)
{
}

double ksi::descriptor_singleton::getCoreMean() const
{
   return  _core_max ;
}


double ksi::descriptor_singleton::getMembership (double x)
{
   try
   {
      if (x == _support_max)
         return last_membership = 1.0;
      else
         return last_membership = 0.0;
   }
   CATCH;
}

std::vector<double> ksi::descriptor_singleton::getDifferentials (double x)
{
   return { 0.0 };
}

ksi::descriptor * ksi::descriptor_singleton::clone() const
{
   return new descriptor_singleton(*this);
}

ksi::descriptor_singleton::~descriptor_singleton()
{

}

std::ostream& ksi::descriptor_singleton::Print(std::ostream& ss) const
{
   ss << "(" << _support_min << ")";
   return ss;
}


std::vector< double > ksi::descriptor_singleton::getMAconsequenceParameters() const
{
   return { _core_max - EPSILON, _core_max, _core_max + EPSILON };
}

double ksi::descriptor_singleton::getRandomValue(std::default_random_engine& engine)
{
    return _core_min;
}
