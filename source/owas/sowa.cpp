/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "sowa.h"
 
ksi::sowa::sowa(const ksi::sowa & wzor)
{
   _N = wzor._N;
   _pc = wzor._pc;
   _pa = wzor._pa;
}

ksi::sowa::sowa(std::size_t N, double pc, double pa) 
  : _N (N), _pc (pc), _pa (pa)
{ 
}

ksi::sowa::~sowa()
{
}

std::ostream & ksi::sowa::Print(std::ostream & ss) const
{
   ss << "SOWA";
   return ss;
}

double ksi::sowa::value(std::size_t k) const
{
   return 1.0 / ( 1 + exp ( 2.944 * (k - _pc * _N) / (_pa * _N) ) ); 
}

ksi::owa* ksi::sowa::clone() const
{
   return new sowa (*this);
}
 