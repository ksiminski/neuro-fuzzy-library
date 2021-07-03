/** @file */ 

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include "uowa.h"

bool ksi::uowa::are_parameters_valid() const
{
    return true;
}


std::string ksi::uowa::print_owa_parameters() const
{
    std::stringstream ss;
    ss << "UOWA (_N == " << _N << ")";    
    return ss.str();
}

 
ksi::uowa::uowa()
{
}

ksi::uowa::~uowa()
{
}

ksi::uowa::uowa(const ksi::uowa& wzor)
{
}

ksi::uowa::uowa(ksi::uowa && wzor)
{
}

ksi::uowa & ksi::uowa::operator=(ksi::uowa && wzor)
{
   if (this == & wzor)
       return *this;
    
   ksi::owa::operator=(wzor);    
    
   return *this;
}

ksi::uowa & ksi::uowa::operator=(const ksi::uowa& wzor)
{
   if (this == & wzor)
       return *this;
    
   ksi::owa::operator=(wzor);    
    
   return *this;
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
 
