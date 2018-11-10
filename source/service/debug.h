/** @file */ 

#ifndef DEBUG_H
#define DEBUG_H

#include <sstream>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <utility>



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



#define CATCH                                                \
catch (ksi::exception & ex)                                  \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__, ex.what()); \
}                                                            \
catch (std::exception & ex)                                  \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__, ex.what()); \
}                                                            \
catch (std::string & ex)                                     \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__, ex);        \
}                                                            \
catch (...)                                                  \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__,             \
                                 "unknown expection");       \
}                                                            \

/*
namespace ksi 
{
   template <class T>
   std::ostream & operator << (std::ostream & ss, const std::vector<T> & we)
   {
      ss << "[  ";
      for (const auto & d : we)
         ss << d << "  ";
      ss << "]";
      return ss;
   }
} 
*/


namespace ksi 
{
   //std::ostream & operator << (std::ostream & ss, const std::vector<double> & we);
   //std::ostream & operator << (std::ostream & ss, const std::vector<std::pair<double, double>> & we);
   //std::ostream & operator << (std::ostream & ss, const std::pair<double, double> & we);

}


#define debug(x) std::cerr << __FILE__ << " (" << __LINE__ << ") " << #x << " == " << (x) << std::endl;

#endif