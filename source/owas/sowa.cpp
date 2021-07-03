/** @file */ 

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>

#include "../owas/owa.h"
#include "../owas/sowa.h"
#include "../service/debug.h"


bool ksi::sowa::are_parameters_valid() const
{
    return _N > 0;
}


std::string ksi::sowa::print_owa_parameters() const
{
    std::stringstream ss;
    ss << "SOWA (_N == " << _N << ", _pc == " << _pc << ", _pa == " << _pa << ")";    
    return ss.str();
}


ksi::sowa::sowa(const ksi::sowa & wzor) : owa (wzor)
{
   _pc = wzor._pc;
   _pa = wzor._pa;
}

ksi::sowa::sowa(double pc, double pa) 
: _pc (pc), _pa (pa)
{ 
}

ksi::sowa::sowa(std::size_t N, double pc, double pa) 
: owa (N), _pc (pc), _pa (pa)
{ 
}

ksi::sowa::sowa(ksi::sowa && wzor) : owa (wzor)
{
    std::swap(_pc, wzor._pc);
    std::swap(_pa, wzor._pa);
}

ksi::sowa & ksi::sowa::operator=(const ksi::sowa& wzor)
{
    if (this == & wzor)
       return *this;
    
    ksi::owa::operator=(wzor);    
    _pc = wzor._pc;
    _pa = wzor._pa;
    
    return *this;
}

ksi::sowa & ksi::sowa::operator=(ksi::sowa && wzor)
{
    if (this == & wzor)
       return *this;
    
    ksi::owa::operator=(wzor);    
    std::swap(_pc, wzor._pc);
    std::swap(_pa, wzor._pa);
    
    return *this;
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
//     debug(k);
//     debug(_N);
//     debug(_pc);
//     debug(_pa);
//     debug(1.0 / ( 1 + exp ( 2.944 * (k - _pc * _N) / (_pa * _N) ) ));
    
    
   return 1.0 / ( 1 + exp ( 2.944 * (k - _pc * _N) / (_pa * _N) ) ); 
}

ksi::owa* ksi::sowa::clone() const
{
   return new sowa (*this);
}
 
