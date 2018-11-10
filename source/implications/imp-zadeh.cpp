/** @file */ 

#include <algorithm>
#include <iostream>
#include "imp-zadeh.h"
 
double ksi::imp_zadeh::imply (double x, double y) const
{
   return std::max (1.0 - x, std::min (x, y));
}

double ksi::imp_zadeh::G(double F, double w) const
{
   if (F >= 0.5)
      return w * (F - 0.5);
   else
      return 0.0;
}
 
ksi::implication * ksi::imp_zadeh::clone() const 
{
   return new imp_zadeh();
}

double ksi::imp_zadeh::dG_dF(double F, double w) const
{
   if (F >= 0.5)
      return w;
   else
      return 0;
}

double ksi::imp_zadeh::dG_dw(double F, double w) const
{
   if (F >= 0.5)
      return F - 0.5;
   else
      return 0;
}

ksi::imp_zadeh::~imp_zadeh()
{

}

std::ostream& ksi::imp_zadeh::Print(std::ostream& ss) const
{
   ss << "Zadeh";
   return ss;
}




