/** @file */ 

#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <random>

#include "descriptor-gaussian.h"
#include "../service/debug.h" 

#include <iostream>

ksi::descriptor_gaussian::~descriptor_gaussian()
{

}

void ksi::descriptor_gaussian::reset_differentials()
{
   sum_dE_dmean = sum_dE_dstddev = 0.0;
}


ksi::descriptor_gaussian::descriptor_gaussian (double mean, double stddev)
{
   _previous_mean = _mean = mean;
   _previous_stddev = _stddev = stddev;
}

double ksi::descriptor_gaussian::getCoreMean() const
{
   return _mean;
}

double ksi::descriptor_gaussian::getFuzzification() const
{
    return _stddev;
}


double ksi::descriptor_gaussian::getMembership (double x)
{
   try
   {
      if (_stddev <= 0.0)
      {
          std::stringstream ss;
          ss << "illegal value of fuzzyfication of a gaussian set: " << NAZWA(_stddev) << " == " << _stddev; 
          throw ss.str();
      }
      double diff = x - _mean;
      return last_membership = std::exp ( - (diff * diff) / (2 * _stddev * _stddev) );
   }
   CATCH;
}


void ksi::descriptor_gaussian::cummulate_differentials(
   double x, double partial_differentials)
{
   double common = (x - _mean) / (_stddev * _stddev);
   sum_dE_dmean += (partial_differentials * common);
   sum_dE_dstddev += (partial_differentials * common * (x - _mean) / (_stddev));
}


std::vector<double> ksi::descriptor_gaussian::getDifferentials (double x)
{
   try 
   {
      if (_stddev <= 0.0)
         throw std::string("negative fuzzyfication of a gaussian set");
      
      double diff = x - _mean;
      
      double wspolna = getMembership(x) * diff / (_stddev * _stddev);
      return { wspolna, wspolna * diff / _stddev };       
   }
   CATCH;
}

ksi::descriptor * ksi::descriptor_gaussian::clone() const 
{
   return new descriptor_gaussian(*this);
}

std::ostream & ksi::descriptor_gaussian::Print(std::ostream & ss) const
{
   ss << "c == " << _mean << std::endl;
   ss << "s == " << _stddev << std::endl;
   
   return ss;
}

ksi::descriptor_gaussian::descriptor_gaussian(const ksi::descriptor_gaussian & wzor) : descriptor(wzor)
{
   _mean = wzor._mean;
   _stddev = wzor._stddev;
   _previous_mean = wzor._previous_mean;
   _previous_stddev = wzor._previous_stddev;   
   
   sum_dE_dmean = wzor.sum_dE_dmean;
   sum_dE_dstddev = wzor.sum_dE_dstddev;
   
}

 
std::string ksi::descriptor_gaussian::toString() const 
{
   std::stringstream ss;
   Print(ss);
   return ss.str();
}

void ksi::descriptor_gaussian::actualise_parameters(double eta)
{
   //debug(_mean);
   //debug(sum_dE_dmean);
   _mean -= (eta * sum_dE_dmean);
   
   sum_dE_dmean = 0.0;
   
   double new_stddev = _stddev - eta * sum_dE_dstddev;
   if (new_stddev > 0.0)
      _stddev = new_stddev;
   sum_dE_dstddev = 0.0;
}

std::vector<double> ksi::descriptor_gaussian::getMAconsequenceParameters() const
{
   return { _mean - _stddev, _mean, _mean + _stddev };
}

void ksi::descriptor_gaussian::reset_parameters()
{
   _mean = _previous_mean;
   _stddev = _previous_stddev;   
}

ksi::ext_fuzzy_number_gaussian ksi::descriptor_gaussian::getGranule() const
{
    try 
    {
        return ksi::ext_fuzzy_number_gaussian (_mean, _stddev);
    }
    CATCH;
}

double ksi::descriptor_gaussian::getRandomValue(std::default_random_engine& engine)
{
    std::normal_distribution<double> distro (_mean, _stddev);
    return distro(engine);
}
