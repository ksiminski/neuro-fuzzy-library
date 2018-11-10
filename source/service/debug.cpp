/** @file */ 

#include <vector>
#include <iostream>
#include "debug.h"


const char* ksi::exception::what() const noexcept
{
   return _note.c_str();
}

ksi::exception::exception(const std::string & note)
{
   _note = note;
}

ksi::exception::exception()
{
   
}

ksi::exception::exception(const char * FILE, 
                          const char * FUNCTION, 
                          const int LINE, 
                          const std::string & note)
{
   std::stringstream ss;
   ss << "(" << FILE << " : " << LINE << ") method: " << FUNCTION << std::endl 
      << "\t" << note << std::endl;
   
   _note = ss.str();
}


namespace ksi 
{
   /*
   std::ostream & operator << (std::ostream & ss, const std::vector<double> & we)
   {
      ss << "[  ";
      for (const auto & d : we)
         ss << d << "  ";
      ss << "]";
      return ss;
   }
   */
   /*
   std::ostream & operator << (std::ostream & ss, const std::vector<std::pair<double, double>> & we)
   {
      ss << "[  ";
      for (const auto & d : we)
         ss << d << "  ";
      ss << "]";
      return ss;
   }
   */
   /*
   std::ostream & operator << (std::ostream & ss, const std::pair<double, double> & we)
   {
      ss << "{ " << we.first << ", " << we.second << " }";
      return ss;
   }
   */
}
