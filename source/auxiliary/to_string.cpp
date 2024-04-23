

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../auxiliary/to_string.h"

std::string ksi::to_string (const double x)
{
   std::stringstream ss;
   ss << std::scientific << x;
   return ss.str();
}

std::string ksi::to_string (const int n, const unsigned int width)
{
   std::stringstream ss;
   ss << std::setw(width) << std::setfill('0') << n;
   return ss.str();
}

std::string ksi::to_string (const std::vector<double> & numbers, const char sep)
{
   std::stringstream ss;
   auto size = numbers.size();
   for (std::size_t i = 0; i < size - 1; ++i)
   {
      ss << numbers[i] << sep;
   }
   if (size > 0)
      ss << numbers.back();
   
   return ss.str();
}

std::string ksi::to_string (const std::vector<int> & numbers, const unsigned int width, const char sep)
{
   std::stringstream ss;
   auto size = numbers.size();
   for (std::size_t i = 0; i < size - 1; ++i)
   {
      ss << std::setw(width) << std::setfill('0') << numbers[i] << sep;
   }
   if (size > 0)
      ss << std::setw(width) << std::setfill('0') << numbers.back();
   
   return ss.str();
}
