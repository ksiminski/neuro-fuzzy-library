/** @file */ 

#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <utility>

#include "descriptor-gaussian.h"
#include "descriptor-gaussian-subspace.h"
#include "../service/debug.h"
 

#include <iostream>

ksi::descriptor_gaussian_subspace::~descriptor_gaussian_subspace()
{

}


ksi::descriptor_gaussian_subspace::descriptor_gaussian_subspace (
   double mean, double stddev, double weight) : ksi::descriptor_gaussian (mean, stddev)
{
   _previous_weight = _weight = weight;
}

double ksi::descriptor_gaussian_subspace::getCoreMean() const
{
   return _mean;
}


ksi::descriptor_gaussian_subspace::descriptor_gaussian_subspace(const ksi::descriptor_gaussian_subspace & wzor): descriptor(wzor), descriptor_gaussian(wzor)
{
   _weight = wzor._weight;
   _weight_expo = wzor._weight_expo;
   
   _previous_weight = wzor._previous_weight;
}

ksi::descriptor_gaussian_subspace::descriptor_gaussian_subspace(double mean, double stddev, double weight, double weight_exponent): descriptor_gaussian(mean, stddev)
{
   _previous_weight = _weight = weight;
   _weight_expo = weight_exponent;
}


ksi::descriptor * ksi::descriptor_gaussian_subspace::clone() const
{
   return new descriptor_gaussian_subspace(*this);
}

// std::string ksi::descriptor_gaussian_subspace::toString() const 
// {
//    std::stringstream ss;
//    Print(ss);
//    return ss.str();
// }

std::ostream& ksi::descriptor_gaussian_subspace::Print(std::ostream& ss) const
{
   ss << "c == " << _mean   << std::endl;
   ss << "s == " << _stddev << std::endl;
   ss << "z == " << _weight << std::endl;
   return ss;
}

double ksi::descriptor_gaussian_subspace::getWeight() const
{
   return _weight;
}


void ksi::descriptor_gaussian_subspace::setWeight(double weight)
{
   _weight = weight;
}
 
void ksi::descriptor_gaussian_subspace::cummulate_differentials(double x, double partial_differentials)
{
   double common = (x - _mean) / (_stddev * _stddev);
   sum_dE_dmean += (partial_differentials * common);
   sum_dE_dstddev += (partial_differentials * common * (x - _mean) / (_stddev));
   
   auto zf = std::pow(_weight, _weight_expo);
   auto mi = getMembership(x);
   
   auto roznica = (x - _mean);
   auto skladnik = exp (- roznica * roznica / (2 * _stddev * _stddev));
   
   auto dzielnik = zf * mi;
   
   sum_dE_dweight += (partial_differentials * (skladnik - 1.0) / dzielnik);
   
}
 
void ksi::descriptor_gaussian_subspace::actualise_parameters(double eta)
{
   _mean -= (eta * sum_dE_dmean);
   sum_dE_dmean = 0.0;
   
   double new_stddev = _stddev - eta * sum_dE_dstddev;
   if (new_stddev > 0.0)
      _stddev = new_stddev;
   sum_dE_dstddev = 0.0;
   
   double new_weight = _weight - eta * sum_dE_dweight;
   if (new_weight >= 0.0 and new_weight <= 1.0)
      _weight = new_weight;
   sum_dE_dweight = 0.0;
   
}

void ksi::descriptor_gaussian_subspace::reset_parameters()
{
   ksi::descriptor_gaussian::reset_parameters();
   _weight = _previous_weight;
}

// ksi::descriptor_gaussian_subspace::descriptor_gaussian_subspace(
//    double mean, std::pair<double, double> stddevLowerUpper, double weight) 
//    : descriptor_gaussian(mean, stddevLowerUpper.first, stddevLowerUpper.second)
// {
//    _weight = weight;
// }

// ksi::descriptor_gaussian_subspace::descriptor_gaussian_subspace(
//    double mean, 
//    std::pair<double, double> stddevLowerUpper, 
//    double weight, 
//    double weight_exponent) : descriptor_gaussian (mean, stddevLowerUpper.first, stddevLowerUpper.second)
// {
//     _weight = weight;
//    _weight_expo = weight_exponent;
// }
