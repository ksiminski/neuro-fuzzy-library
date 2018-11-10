/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "plowa.h"
 
ksi::plowa::plowa(const ksi::plowa & wzor)
{
   _N = wzor._N;
   _pc = wzor._pc;
   _pl = wzor._pl;
}

ksi::plowa::plowa(std::size_t N, double pc, double pl) 
  : _N (N), _pc (pc), _pl (pl)
{
  
}


ksi::plowa::~plowa()
{
}


std::ostream & ksi::plowa::Print(std::ostream & ss) const
{
   ss << "PLOWA";
   return ss;
}

double ksi::plowa::value(std::size_t k) const
{
   return std::max ( std::min (  (_pc * _N - k) / (2 * _pl * _N) + 0.5  , 1.0)   , 0.0 );
}

ksi::owa* ksi::plowa::clone() const
{
   return new plowa(*this);
}
 