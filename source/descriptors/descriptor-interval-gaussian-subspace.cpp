/** @file */ 

#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>

#include "descriptor-interval-gaussian-subspace.h"
#include "descriptor-gaussian-subspace.h"
#include "descriptor-interval-gaussian.h"

#include "../service/debug.h"

#include <iostream>

ksi::descriptor_interval_gaussian_subspace::~descriptor_interval_gaussian_subspace()
{

}

ksi::descriptor* ksi::descriptor_interval_gaussian_subspace::clone() const
{
    return new descriptor_interval_gaussian_subspace (*this);
}

ksi::descriptor_interval_gaussian_subspace::descriptor_interval_gaussian_subspace (double mean, double stddevLower, double stddevUpper, double weight)
: ksi::descriptor_gaussian (mean, stddevLower),
  ksi::descriptor_gaussian_subspace (mean, stddevLower, weight),
  ksi::descriptor_interval_gaussian (mean, stddevLower, stddevUpper)
{
}

double ksi::descriptor_interval_gaussian_subspace::getCoreMean() const
{
   return _mean;
}


ksi::descriptor_interval_gaussian_subspace::descriptor_interval_gaussian_subspace(const ksi::descriptor_interval_gaussian_subspace & wzor) 
: descriptor_gaussian (wzor), 
  descriptor_interval_gaussian(wzor), descriptor_gaussian_subspace (wzor)
{
}

std::ostream& ksi::descriptor_interval_gaussian_subspace::Print(std::ostream& ss) const
{
   ss << "c       == " << _mean << std::endl;
   ss << "s upper == " << _stddevUpper << std::endl;
   ss << "s lower == " << _stddev << std::endl;
   ss << "z       == " << _weight << std::endl;
   return ss; 
   
}

void ksi::descriptor_interval_gaussian_subspace::reset_parameters()
{
   ksi::descriptor_gaussian_subspace::reset_parameters();
   ksi::descriptor_interval_gaussian::reset_parameters();
}

 
