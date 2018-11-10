/** @file */ 

#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>

#include "descriptor-interval-gaussian.h"
#include "../service/debug.h"

#include <iostream>

ksi::descriptor_interval_gaussian::~descriptor_interval_gaussian()
{

}

ksi::descriptor* ksi::descriptor_interval_gaussian::clone() const
{
    return new descriptor_interval_gaussian (*this);
}

ksi::descriptor_interval_gaussian::descriptor_interval_gaussian (
   double mean, 
   double stddevLower, 
   double stddevUpper) : descriptor_gaussian (mean, stddevLower)
{
   _previous_stddevUpper = _stddevUpper = stddevUpper;
}

double ksi::descriptor_interval_gaussian::getCoreMean() const
{
   return _mean;
}
 

std::ostream& ksi::descriptor_interval_gaussian::Print(std::ostream& ss) const
{
   ss << "c       == " << _mean << std::endl;
   ss << "s upper == " << _stddevUpper << std::endl;
   ss << "s lower == " << _stddev << std::endl;
   
   return ss; 
}

ksi::descriptor_interval_gaussian::descriptor_interval_gaussian(const ksi::descriptor_interval_gaussian & wzor) : descriptor_gaussian(wzor)
{
   _stddevUpper = wzor._stddevUpper;
   _previous_stddevUpper = wzor._previous_stddevUpper;
}

void ksi::descriptor_interval_gaussian::reset_parameters()
{
   ksi::descriptor_gaussian::reset_parameters();
   _stddevUpper = _previous_stddevUpper;
}


 
// std::string ksi::descriptor_interval_gaussian::toString() const 
// {
//    std::stringstream ss;
//    Print(ss);
//    return ss.str();
// }
 
 

