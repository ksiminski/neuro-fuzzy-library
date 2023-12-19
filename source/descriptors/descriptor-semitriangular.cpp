/** @file */ 


#include <vector>
#include <cmath>
#include <random>
#include <array>

#include "descriptor.h"
#include "descriptor-semitriangular.h"

const std::array<std::string, 7> ksi::descriptor_semitriangular::semitriangularLocationDescription
{
    "micro",
        "tiny",
        "small",
        "medium",
        "large",
        "huge",
        "giant"
};

const std::array<std::string, 5> ksi::descriptor_semitriangular::fuzzyDescription
{
    "hardly",       // (INFINITY, 10>
	"mildly",       // (10; 4>
	"moderately",   // (1 ; 4)
	"distinctly",   // <1; 0.4)
	"stepwise"      // <0.4; 0>
};

ksi::descriptor_semitriangular::~descriptor_semitriangular()
{

}


ksi::descriptor_semitriangular::descriptor_semitriangular (double support_extremum, double core)
{
   _previous_support_extremum = _support_extremum = support_extremum;
   _previous_core = _core = core;
}

ksi::descriptor_semitriangular::descriptor_semitriangular (const ksi::descriptor_semitriangular & wzor)
{
   _previous_core = wzor._previous_core;
   _previous_support_extremum = wzor._previous_support_extremum;
   
   _core = wzor._core;
   _support_extremum = wzor._support_extremum;
   
}

void ksi::descriptor_semitriangular::reset_parameters()
{  
   _core = _previous_core;
   _support_extremum = _previous_support_extremum;
}

double ksi::descriptor_semitriangular::getCoreMean() const
{
   return std::nan("");
}

double ksi::descriptor_semitriangular::getMembership (double x)
{
   // lewy czy prawy?
   if (_core < _support_extremum) // lewy
   {
      if (x < _core)
         return last_membership = 1;
      else if (x > _support_extremum)
         return last_membership = 0;
      else
      {
         return last_membership = (_support_extremum - x) / (_support_extremum - _core);
      }
   }
   else // prawy
   {
      if (x < _support_extremum)
         return last_membership = 0;
      else if (x > _core)
         return last_membership = 1;
      else 
      {
         return last_membership = (x - _support_extremum) / (_core - _support_extremum);
      }
   }
}

double ksi::descriptor_semitriangular::getRandomValue(std::default_random_engine & engine)
{
    // lewy czy prawy?
   if (_core < _support_extremum) // lewy
   {
       std::uniform_real_distribution<double> distro (_core - (_support_extremum - _core), _support_extremum);
       return distro(engine);
   }
   else // prawy
   {
       std::uniform_real_distribution<double> distro (_support_extremum, _core + (_core - _support_extremum));
       return distro(engine);
   }
}


std::ostream& ksi::descriptor_semitriangular::prettyPrint(std::ostream& ss, const DescriptorStatistics& descStat) const
{
    const double cross = (_support_extremum + _core) / 2;

    int locationIndex = -(descStat.average - cross) / descStat.std_dev + semitriangularLocationDescription.size() / 2;
    locationIndex = std::min(std::max(locationIndex, 0), int(semitriangularLocationDescription.size() - 1));

    int slopeIndex;
    double product = abs(((_support_extremum - _core) / 2) * descStat.std_dev);
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

    ss << "is " << fuzzyDescription[slopeIndex] << ' ' << (_support_extremum < _core ? "greater" : "less") << " than " << semitriangularLocationDescription[locationIndex];

    return ss;
}

std::vector< double > ksi::descriptor_semitriangular::getMAconsequenceParameters() const
{
   if (_core < _support_extremum) // lewy
   {
      return { _core - (_support_extremum - _core), _core, _support_extremum };
   }
   else // prawy
   {
      return { _support_extremum, _core, _core + (_core - _support_extremum) };
   }
   
}


std::vector<double> ksi::descriptor_semitriangular::getDifferentials (double x)
{
   // lewy czy prawy?
   if (_core < _support_extremum) // lewy
   {
      if (x < _core)
         return { 0.0, 0.0};
      else if (x > _support_extremum)
         return { 0.0, 0.0};
      else
      {
         double denom = (_support_extremum - _core) * (_support_extremum - _core);
         
         return { 
                  (x - _core ) / denom,   // d membership / d _support_extremum
                  (x - _support_extremum) / denom   // d membership / d _core  
                }; 
      }
   }
   else // prawy
   {
      if (x < _support_extremum)
         return { 0.0, 0.0};
      else if (x > _core)
         return { 0.0, 0.0};
      else 
      {
         double denom = (_support_extremum - _core) * (_support_extremum - _core);
         
         return { 
                  (x - _core ) / denom,   // d membership / d _support_extremum
                  (x - _support_extremum) / denom   // d membership / d _core  
                }; 
      }
   }
}

ksi::descriptor * ksi::descriptor_semitriangular::clone() const
{
   return new descriptor_semitriangular(*this);
}

std::ostream& ksi::descriptor_semitriangular::Print(std::ostream& ss) const
{
   ss << "descriptor: semitriangular" << std::endl;
   if (_core < _support_extremum) // lewy
   {
      ss << "   mi (" << _core << ") == 0" << std::endl;
      ss << "   mi (" << _support_extremum << ") == 1" << std::endl;
   }
   else // prawy
   {
      ss << "   mi (" << _support_extremum << ") == 1" << std::endl;
      ss << "   mi (" << _core << ") == 0" << std::endl;
   }
   return ss;
}


 
