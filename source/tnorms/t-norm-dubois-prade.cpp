/** @file */ 
#include <algorithm>
#include <cmath>
#include <iostream>

#include "t-norm.h"
#include "t-norm-parametrized.h"
#include "t-norm-dubois-prade.h"


std::ostream & ksi::t_norm_dubois_prade::Print(std::ostream& ss) const
{
   return ss << "Dubois-Prade (s = " << _parameter << ") t-norm";
}

ksi::t_norm * ksi::t_norm_dubois_prade::clone() const
{
   return new t_norm_dubois_prade (_parameter);
}

ksi::t_norm_dubois_prade::t_norm_dubois_prade(double s) : t_norm_parametrized (s)
{
}

ksi::t_norm_dubois_prade::~t_norm_dubois_prade()
{
}

double ksi::t_norm_dubois_prade::tnorm(const double a, const double b) const
{
   return (a * b) / (std::max( std::max (a, b), _parameter));
}
