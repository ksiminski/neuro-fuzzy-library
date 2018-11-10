/** @file */ 

#include <iostream>
#include <algorithm>
#include "imp-kleene-dienes.h"
 
double ksi::imp_kleene_dienes::imply (double x, double y) const
{
   return std::max (1.0 - x, y);
}

double ksi::imp_kleene_dienes::G(double F, double w) const
{
   return w * F * F / 0.5;
}
 
ksi::implication * ksi::imp_kleene_dienes::clone() const 
{
   return new imp_kleene_dienes();
}

double ksi::imp_kleene_dienes::dG_dF(double F, double w) const
{
   return w * F;
}

double ksi::imp_kleene_dienes::dG_dw(double F, double w) const
{
   return F * F / 2.0;
}

ksi::imp_kleene_dienes::~imp_kleene_dienes()
{

}

std::ostream& ksi::imp_kleene_dienes::Print(std::ostream& ss) const
{
   ss << "Kleene-Dienes";
   return ss;
}

