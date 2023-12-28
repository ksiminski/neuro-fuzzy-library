/** @file */ 

#include <random>
#include <array>

#include "descriptor-triangular.h" 
#include "../auxiliary/utility-math.h"
#include "../service/debug.h"

const std::array<std::string, 7> ksi::descriptor_triangular::triangularLocationDescription
{
    "micro",
	"tiny",
	"small",
	"medium",
	"large",
	"huge",
	"giant"
};

ksi::descriptor_triangular::~descriptor_triangular()
{
}

ksi::descriptor_triangular::descriptor_triangular (double support_min, double core, double support_max)
{
   try 
   {
      if ((support_min > core) or (core > support_max))
      {
         throw std::string {"The condition support_min <= core <= support_max is not satisfied."};
      }
      _support_max = support_max;
      _support_min = support_min;
      _core = core;

      _previous_support_min = _support_min;
      _previous_support_max = _support_max;
      _previous_core = _core;
   }
   CATCH;
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

double ksi::descriptor_triangular::getSupportMin() const
{
   return this->_support_min;
}

double ksi::descriptor_triangular::getSupportMax() const
{
   return this->_support_max;
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

std::ostream& ksi::descriptor_triangular::print(std::ostream& ss) const
{
   ss << "descriptor: triangular" << std::endl;
   
   ss << "   (" << _support_min << ", " << _core << ", " << _support_max << ")";
   return ss;
}

std::ostream& ksi::descriptor_triangular::printLinguisticDescription(std::ostream& ss, const DescriptorStatistics& descStat) const
{
    utility_math utility;

    const double center = (_support_min + _support_max + _core) / 3;

    const auto firstFunctionParam = utility.calculateLineEquation(std::make_pair(_support_min, 0.0), std::make_pair(_core, 1.0));
    const auto secondFunctionParam = utility.calculateLineEquation(std::make_pair(_core, 1.0), std::make_pair(_support_max, 1.0));
    
    const double firstIntegralValue = utility.calculateLinearDefiniteIntegralValue(_support_min, _core, firstFunctionParam, center);
    const double secondIntegralValue = utility.calculateLinearDefiniteIntegralValue(_core, _support_max, secondFunctionParam, center);

    const double radius = sqrt(firstIntegralValue + secondIntegralValue);

    int locationIndex = -(descStat.average - center) / descStat.std_dev + triangularLocationDescription.size() / 2;
    locationIndex = std::min(std::max(locationIndex, 0), int(triangularLocationDescription.size() - 1));
    
    ss << "is " << (radius <= descStat.std_dev ? "strictly " : "loosely ") << triangularLocationDescription[locationIndex];
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
