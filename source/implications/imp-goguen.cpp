/** @file */ 

#include <iostream>
#include <algorithm>
#include "imp-goguen.h"
 
double ksi::imp_goguen::imply (double x, double y) const
{
   if (x == 0)
      return 1.0;
   else
      return std::min (y / x, 1.0);
}

double ksi::imp_goguen::G(double F, double w) const
{
   return w * (1.0 - 0.5 * F);
}
 
ksi::implication * ksi::imp_goguen::clone() const 
{
   return new imp_goguen();
}

double ksi::imp_goguen::dG_dF(double F, double w) const
{
   return - 0.5 * w;
}

double ksi::imp_goguen::dG_dw(double F, double w) const
{
   return 1.0 - F / 2.0;
}

ksi::imp_goguen::~imp_goguen()
{

}

std::ostream& ksi::imp_goguen::Print(std::ostream& ss) const
{
   ss << "Goguen";
   return ss;
}


