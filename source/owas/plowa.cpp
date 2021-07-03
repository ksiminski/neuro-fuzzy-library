/** @file */ 

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include "plowa.h"

bool ksi::plowa::are_parameters_valid() const
{
    return _N <= 0 or _pl > _pc or _pl < 0 or _pc < 0;
}


std::string ksi::plowa::print_owa_parameters() const
{
    std::stringstream ss;
    ss << "PLOWA (_N == " << _N << ", _pc == " << _pc << ", _pl == " << _pl << ")";    
    return ss.str();
}

 
ksi::plowa::plowa(const ksi::plowa & wzor) : owa (wzor)
{
   _pc = wzor._pc;
   _pl = wzor._pl;
}

ksi::plowa::plowa(std::size_t N, double pc, double pl) 
  : owa (N), _pc (pc), _pl (pl)
{
  
}

ksi::plowa::plowa(ksi::plowa && wzor) : owa (wzor)
{
   std::swap(_pc, wzor._pc);
   std::swap(_pl, wzor._pl);
}

ksi::plowa & ksi::plowa::operator=(const ksi::plowa & wzor)
{
    if (this == & wzor)
       return *this;
    
    ksi::owa::operator=(wzor);    
   _pc = wzor._pc;
   _pl = wzor._pl;
    
    return *this;
}

ksi::plowa & ksi::plowa::operator=(ksi::plowa && wzor)
{
    if (this == & wzor)
       return *this;
    
    ksi::owa::operator=(wzor);    
    std::swap(_pc, wzor._pc);
    std::swap(_pl, wzor._pl);
    
    return *this;
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
 
