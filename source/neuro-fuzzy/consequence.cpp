/** @file */ 
 
 
#include <iostream>
#include "consequence.h"
#include "../service/debug.h"


ksi::consequence::~consequence()
{
}

double ksi::consequence::getW() const 
{
   return 0;
}

void ksi::consequence::cummulate_differentials(std::vector< double > X, 
                                               double partial_differential,
                                               double secundary_partial_differentials,
                                               double firing
                                              )
{
   // nothing
}


void ksi::consequence::reset_differentials()
{
   // nothing
}


void ksi::consequence::actualise_parameters(double eta)
{
   // nothing
}

void ksi::consequence::setLinearParameters(std::vector< double >& coefficients)
{
   // nothing
}


namespace ksi 
{
   std::ostream & operator << (std::ostream & ss, const consequence & con)
   {
      ss << "abstract consequence";
      return ss;
   }
}