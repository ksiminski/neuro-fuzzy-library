/** @file */ 

#include <iostream>
#include <algorithm>
#include "imp-goedel.h"
 
double ksi::imp_goedel::imply (double x, double y) const
{
   if (x <= y)
      return 1.0;
   else
      return y;
}

double ksi::imp_goedel::G(double F, double w) const
{
   return w * (1.0 - F + 0.5 * F * F);
}
 
ksi::implication * ksi::imp_goedel::clone() const 
{
   return new imp_goedel();
}

double ksi::imp_goedel::dG_dF(double F, double w) const
{
   return w * (F - 1.0);
}

double ksi::imp_goedel::dG_dw(double F, double w) const
{
   return 1.0 - F + F * F / 2.0;
}

ksi::imp_goedel::~imp_goedel()
{

}

std::ostream& ksi::imp_goedel::Print(std::ostream& ss) const
{
   ss << "Goedel";
   return ss;
}

