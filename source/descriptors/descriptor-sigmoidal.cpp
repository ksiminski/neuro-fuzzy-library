/** @file */ 

#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

#include "descriptor-sigmoidal.h"
#include "../service/debug.h"

#include <iostream>

ksi::descriptor_sigmoidal::descriptor_sigmoidal (double crosspoint, double slope)
{
   _previous_cross = _cross = crosspoint;
   _previous_slope = _slope = slope;
}

ksi::descriptor_sigmoidal::descriptor_sigmoidal (const ksi::descriptor_sigmoidal & wzor)
{
   _cross = wzor._cross;
   _slope = wzor._slope;
   
   _previous_cross = wzor._previous_cross;
   _previous_slope = wzor._previous_slope;
}

double ksi::descriptor_sigmoidal::getCoreMean() const
{
   return std::nan("");
}


double ksi::descriptor_sigmoidal::getMembership (double x)
{
   try
   {
      return last_membership = 1.0 / (1 + exp (- _slope * (x - _cross)));
   }
   CATCH;
}

std::vector<double> ksi::descriptor_sigmoidal::getDifferentials (double x)
{
   double memb = getMembership(x);
   double common = - memb * memb * exp (- _slope * (x - _cross));
   return { common * _slope,       // d membership / d _cross
            common * (_cross - x)  // d membership / d _slope
          };
}

ksi::descriptor * ksi::descriptor_sigmoidal::clone() const
{
   return new descriptor_sigmoidal(*this);
}

ksi::descriptor_sigmoidal::~descriptor_sigmoidal()
{

}

std::ostream& ksi::descriptor_sigmoidal::Print(std::ostream& ss) const
{
   ss << "crosspoint == " << _cross << std::endl;
   ss << "slope      == " << _slope << std::endl;
   return ss;
}

std::vector< double > ksi::descriptor_sigmoidal::getMAconsequenceParameters() const
{
   return { _cross, _cross + _slope, _cross + 2 * _slope };
}


void ksi::descriptor_sigmoidal::reset_parameters()
{
   _cross = _previous_cross;
   _slope = _previous_slope;
}


double ksi::descriptor_sigmoidal::getRandomValue(std::default_random_engine& engine)
{
    const double K = 0.9;
    const double COEFF = log ((1.0 - K) / K);
    
    double delta = (-1.0 / _slope) * COEFF;
    
    std::uniform_real_distribution<double> distro (_cross - delta, _cross + delta);
    return distro(engine);
}

 
