/** @file */ 

#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numbers>

#include "./descriptor_arctan.h"
#include "../service/debug.h"

#include <iostream>

ksi::descriptor_arctan::descriptor_arctan (const double crosspoint, const double slope)
{
   _previous_cross = _cross = crosspoint;
   _previous_slope = _slope = slope;
}

ksi::descriptor_arctan::descriptor_arctan (const ksi::descriptor_arctan & wzor)
{
   _cross = wzor._cross;
   _slope = wzor._slope;
   
   _previous_cross = wzor._previous_cross;
   _previous_slope = wzor._previous_slope;
}

double ksi::descriptor_arctan::getCoreMean() const
{
   return std::nan("");
}


double ksi::descriptor_arctan::getMembership (const double x) 
{
   try
   {
      return last_membership = 0.5 + (std::numbers::inv_pi_v<double>) * std::atan(_slope * (x - _cross)); 
   }
   CATCH;
}

std::vector<double> ksi::descriptor_arctan::getDifferentials (double x)
{
   double sxc = _slope * (x - _cross);
   double sxc2 = sxc * sxc;
   double common = (std::numbers::inv_pi_v<double>) / ((sxc2 + 1));
   return { - common * _slope,       // d membership / d _cross
              common * (x - _cross)  // d membership / d _slope
          };
}

ksi::descriptor * ksi::descriptor_arctan::clone() const
{
   return new descriptor_arctan(*this);
}

ksi::descriptor_arctan::~descriptor_arctan()
{
}

std::ostream& ksi::descriptor_arctan::Print(std::ostream& ss) const
{
   ss << "descriptor: arcus tangent" << std::endl;
   
   ss << "   crosspoint == " << _cross << std::endl;
   ss << "   slope      == " << _slope << std::endl;
   return ss;
}

std::vector< double > ksi::descriptor_arctan::getMAconsequenceParameters() const
{
   return { _cross, _cross + _slope, _cross + 2 * _slope };
}


void ksi::descriptor_arctan::reset_parameters()
{
   _cross = _previous_cross;
   _slope = _previous_slope;
}


double ksi::descriptor_arctan::getRandomValue(std::default_random_engine& engine)
{
    throw std::string {"[not implemented yet]"};
    /*
    const double K = 0.9;
    const double COEFF = log ((1.0 - K) / K);
    
    double delta = (-1.0 / _slope) * COEFF;
    
    std::uniform_real_distribution<double> distro (_cross - delta, _cross + delta);
    return distro(engine);
    */
    return 0.0;
}

