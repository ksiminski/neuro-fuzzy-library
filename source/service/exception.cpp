/** @file */ 



#include <vector>
#include <iostream>
#include <sstream>
#include "../service/exception.h"


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
      << note;// << std::endl;
   
   _note = ss.str();
}



