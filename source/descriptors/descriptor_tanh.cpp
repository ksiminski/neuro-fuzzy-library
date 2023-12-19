/** @file */ 

#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <cmath>

#include "descriptor_tanh.h"
#include "../service/debug.h"

#include <iostream>

const std::array<std::string, 7> ksi::descriptor_tanh::tanhLocationDescription
{
    "micro",
        "tiny",
        "small",
        "medium",
        "large",
        "huge",
        "giant"
};

const std::array<std::string, 5> ksi::descriptor_tanh::fuzzyDescription
{
    "hardly",       // (INFINITY, 5>
	"mildly",       // (5; 2>
	"moderately",   // (0.5 ; 2)
	"distinctly",   // <0.5; 0.2)
	"stepwise"      // <0.2; 0)
};

ksi::descriptor_tanh::descriptor_tanh (const double crosspoint, const double slope)
{
   _previous_cross = _cross = crosspoint;
   _previous_slope = _slope = slope;
}

ksi::descriptor_tanh::descriptor_tanh (const ksi::descriptor_tanh & wzor)
{
   _cross = wzor._cross;
   _slope = wzor._slope;
   
   _previous_cross = wzor._previous_cross;
   _previous_slope = wzor._previous_slope;
}

double ksi::descriptor_tanh::getCoreMean() const
{
   return std::nan("");
}


double ksi::descriptor_tanh::getMembership (const double x) 
{
   try
   {
      return last_membership = 0.5 + 0.5 * std::tanh(_slope * (x - _cross)); 
   }
   CATCH;
}

std::vector<double> ksi::descriptor_tanh::getDifferentials (double x)
{
   double memb = getMembership(x);
   double common = 0.5 * (1 - memb * memb);
   return { - common * _slope,       // d membership / d _cross
              common * (x - _cross)  // d membership / d _slope
          };
}

ksi::descriptor * ksi::descriptor_tanh::clone() const
{
   return new descriptor_tanh(*this);
}

ksi::descriptor_tanh::~descriptor_tanh()
{

}

std::ostream& ksi::descriptor_tanh::Print(std::ostream& ss) const
{
   ss << "descriptor: hyperbolic tangent" << std::endl;
   
   ss << "   crosspoint == " << _cross << std::endl;
   ss << "   slope      == " << _slope << std::endl;
   return ss;
}

std::ostream& ksi::descriptor_tanh::prettyPrint(std::ostream& ss, const DescriptorStatistics& descStat) const
{
    if (_slope != 0.0)
    {
        int locationIndex = -(descStat.average - _cross) / descStat.std_dev + tanhLocationDescription.size() / 2;
        locationIndex = std::min(std::max(locationIndex, 0), int(tanhLocationDescription.size() - 1));

        int slopeIndex;
        double product =  abs(_slope * descStat.std_dev);
        if (product >= 5)
            slopeIndex = 0;
        else if (product >= 2)
            slopeIndex = 1;
        else if (product > 0.5)
            slopeIndex = 2;
        else if (product > 0.2)
            slopeIndex = 3;
        else
            slopeIndex = 4;
        
        ss << "is " << fuzzyDescription[slopeIndex] << ' ' << (_slope > 0.0 ? "greater" : "less") << " than " << tanhLocationDescription[locationIndex];
    }
    else
        ss << " half for all";

    return ss;
}

std::vector< double > ksi::descriptor_tanh::getMAconsequenceParameters() const
{
   return { _cross, _cross + _slope, _cross + 2 * _slope };
}


void ksi::descriptor_tanh::reset_parameters()
{
   _cross = _previous_cross;
   _slope = _previous_slope;
}


double ksi::descriptor_tanh::getRandomValue(std::default_random_engine& engine)
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

 
