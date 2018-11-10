/** @file */ 
 
#include <vector> 
#include <string>
#include <iostream>
#include "consequence-CL.h"
#include "../service/debug.h"


ksi::consequence_CL::consequence_CL(const std::vector<double> & params, double w) : consequence_TSK(params)
{
   _w = w;
}
 
 
ksi::consequence * ksi::consequence_CL::clone() const
{
   return new consequence_CL (_params, _w);
}


ksi::consequence_CL::~consequence_CL()
{
}

double ksi::consequence_CL::getW() const
{
   return _w;
}


void ksi::consequence_CL::reset_differentials()
{
   sum_dE_dw = 0;
}

void ksi::consequence_CL::cummulate_differentials(std::vector< double > X, 
                                                  double partial_differential,
                                                  double secundary_partial_differentials,
                                           double firing
                                                 )
{
   sum_dE_dw += partial_differential; 
}

void ksi::consequence_CL::actualise_parameters(double eta)
{
   double new_w = _w - eta * sum_dE_dw;
   
   if (new_w > 0)
      _w = new_w;
   
   sum_dE_dw = 0.0;
   
}

std::ostream& ksi::consequence_CL::Print(std::ostream& ss)
{
   ss << "linear parameters: ";
   for (auto & d : _params)
      ss << d << "  "; 
   ss << std::endl;
   ss << "support width: " << _w;
      
   return ss;
}

