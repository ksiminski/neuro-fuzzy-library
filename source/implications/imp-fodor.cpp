/** @file */ 

#include <iostream>
#include <algorithm>
#include "imp-fodor.h"
 
double ksi::imp_fodor::imply (double x, double y) const
{
   if (x <= y)
      return 1.0;
   else
      return std::max (1.0 - x, y);
}

double ksi::imp_fodor::G(double F, double w) const
{
   if (F >= 0.5)
      return w * (0.5 - F + F * F);
   else 
      return w * F * (1.0 - F);
}
 
ksi::implication * ksi::imp_fodor::clone() const 
{
   return new imp_fodor();
}

double ksi::imp_fodor::dG_dF(double F, double w) const
{
   if (F >= 0.5)
      return w * (2 * F - 1.0);
   else 
      return w * (1.0 - 2 * F);
}

double ksi::imp_fodor::dG_dw(double F, double w) const
{
   if (F >= 0.5)
      return 0.5  - F + F * F;
   else 
      return F - F * F;
}

ksi::imp_fodor::~imp_fodor()
{

}

std::ostream& ksi::imp_fodor::Print(std::ostream& ss) const
{
   ss << "Fodor";
   return ss;
}

