/** @file */ 

#ifndef EXCEPTION_H
#define EXCEPTION_H

 
#include <exception>
#include <string>  

#include "../auxiliary/vector-operators.h"


namespace ksi 
{
   class exception : public std::exception 
   {
      std::string _note;
   public:
	   virtual const char * what () const noexcept;
      exception();
      exception(const std::string & note);
      exception(const char * FILE, 
                const char * FUNCTION, 
                const int LINE, 
                const std::string & note);
   };   
}

 

#endif
