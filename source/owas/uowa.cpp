/** @file */ 

#include <algorithm>
#include <iostream>
#include <cmath>
#include "uowa.h"
 
ksi::uowa::uowa()
{
}

ksi::uowa::~uowa()
{
}


std::ostream & ksi::uowa::Print(std::ostream & ss) const
{
   ss << "UOWA";
   return ss;
}

double ksi::uowa::value(std::size_t n) const
{
   return 1.0;
}

ksi::owa* ksi::uowa::clone() const
{
   return new uowa(*this);
}
 