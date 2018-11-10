/** @file */ 
 
#include <string>
#include <sstream>

#include "owa.h"

ksi::owa::~owa()
{

}

std::string ksi::owa::print() const
{
   std::stringstream ss;
   Print(ss);
   return ss.str();   
}


 
