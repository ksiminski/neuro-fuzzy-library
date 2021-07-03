/** @file */ 


#include <iostream>
#include <string>
#include "descriptor.h"
#include "../service/debug.h"

std::string ksi::descriptor::toString() const
{
   return std::string ("[empty description]");
}

void ksi::descriptor::cummulate_differentials(double x, double partial_differentials)
{
   // nothing :-)
}

void ksi::descriptor::setWeight(double weight)
{
   // nothing :-)
}


ksi::descriptor::~descriptor()
{

}

void ksi::descriptor::reset_differentials()
{

}


void ksi::descriptor::actualise_parameters(double eta)
{
   //
}

namespace ksi 
{
   std::ostream & operator << (std::ostream & ss, const descriptor & d)
   {
      ss << "abstract descriptor" << std::endl;
      return ss;
   }
}

double ksi::descriptor::getWeight() const
{
   return 1.0;
}

double ksi::descriptor::getMembershipUpper(double x)
{
   return getMembership(x);
}

ksi::ext_fuzzy_number_gaussian ksi::descriptor::getGranule() const
{
    try 
    {
        throw std::string ("not implemented!");
    }
    CATCH;
}


double ksi::descriptor::getFuzzification() const
{
    try 
    {
        throw std::string {"It is not possible to get fuzzification of the descriptor."};
    }
    CATCH;
}
