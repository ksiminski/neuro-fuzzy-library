/** @file */ 

#include <iostream>
#include <algorithm>
#include "imp-reichenbach.h"
#include "../service/debug.h"
 
double ksi::imp_reichenbach::imply (double x, double y) const
{
   return 1.0 - x + x * y;
}

double ksi::imp_reichenbach::G(double F, double w) const
{
   return w * F / 0.5;
}
 
ksi::implication * ksi::imp_reichenbach::clone() const 
{
   return new imp_reichenbach();
}

double ksi::imp_reichenbach::dG_dF(double F, double w) const
{
   return w / 2.0;
}

double ksi::imp_reichenbach::dG_dw(double F, double w) const
{
   return F / 2.0;
}

ksi::imp_reichenbach::~imp_reichenbach()
{

}

std::ostream& ksi::imp_reichenbach::Print(std::ostream& ss) const
{
   ss << "Reichenbach";
   return ss;
}

