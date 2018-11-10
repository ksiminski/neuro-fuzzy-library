/** @file */ 
 
#include <string>
#include <sstream>

#include "dissimilarity.h"
 
ksi::dissimilarity::~dissimilarity()
{

}

std::string ksi::dissimilarity::print() const
{
   std::stringstream ss;
   Print(ss);
   return ss.str();  
}


 
