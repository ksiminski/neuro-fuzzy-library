/** @file */ 
 
#include <string>
#include <sstream>

#include "../service/debug.h"
#include "owa.h"


void ksi::owa::set_number_of_data_items(const std::size_t & N)
{
    _N = N;
}

ksi::owa::~owa()
{
}

std::string ksi::owa::print() const
{
   std::stringstream ss;
   Print(ss);
   return ss.str();   
}

ksi::owa::owa() : _N (0)
{
}

ksi::owa::owa(std::size_t N) : _N (N)
{
}

ksi::owa::owa(const ksi::owa& wzor)
{
    _N = wzor._N;
}

ksi::owa::owa(ksi::owa && wzor)
{
    std::swap (_N, wzor._N);
}

ksi::owa & ksi::owa::operator=(const ksi::owa& wzor)
{
    if (this == & wzor)
        return *this;
    
    _N = wzor._N;    
    
    return *this;
}


ksi::owa & ksi::owa::operator=(ksi::owa && wzor)
{
    if (this == & wzor)
       return *this;
    
    std::swap (_N, wzor._N);    
    
    return *this;

}


 
