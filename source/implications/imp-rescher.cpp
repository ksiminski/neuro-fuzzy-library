/** @file */ 

#include <iostream>
#include <algorithm>
#include "imp-rescher.h"
 
double ksi::imp_rescher::imply (double x, double y) const
{
   if (x <= y)
      return 1.0;
   else
      return 0;
}

double ksi::imp_rescher::G(double F, double w) const
{
   return w * (1.0 - F);
}
 
ksi::implication * ksi::imp_rescher::clone() const 
{
   return new imp_rescher();
}

double ksi::imp_rescher::dG_dF(double F, double w) const
{
   return - w;
}

double ksi::imp_rescher::dG_dw(double F, double w) const
{
   return 1.0 - F;
}

ksi::imp_rescher::~imp_rescher()
{

}

std::ostream& ksi::imp_rescher::Print(std::ostream& ss) const
{
   ss << "Rescher";
   return ss;
}


