/** @file */ 

#include <iostream>
#include <algorithm>

#include "implication.h"
#include "imp-lukasiewicz.h"

 
double ksi::imp_lukasiewicz::imply (double x, double y) const
{
   return std::min (1.0 - x + y, 1.0);
}

double ksi::imp_lukasiewicz::G(double F, double w) const
{
   return w * F * (1.0 - F / 2.0);
}
 
ksi::implication * ksi::imp_lukasiewicz::clone() const 
{
   return new imp_lukasiewicz();
}


double ksi::imp_lukasiewicz::dG_dF(double F, double w) const
{
   return w * (1 - F);
}

double ksi::imp_lukasiewicz::dG_dw(double F, double w) const
{
   return F * (1 - F / 2.0);
}

ksi::imp_lukasiewicz::~imp_lukasiewicz()
{

}

std::ostream& ksi::imp_lukasiewicz::Print(std::ostream& ss) const
{
   ss << "Lukasiewicz";
   return ss;
}

