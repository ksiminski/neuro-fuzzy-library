/** @file */ 

#ifndef EXCEPTION_H
#define EXCEPTION_H

 
#include <exception>
#include <string>  



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
     "unknown exception");       \
}                                                            \



#define COMMENTED_CATCH(x)                                   \
catch (ksi::exception & ex)                                  \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__, std::string(ex.what()) + std::string(" [" + std::string(x) + "]")); \
}                                                            \
catch (std::exception & ex)                                  \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__, std::string(ex.what()) + std::string(" [" + std::string(x) + "]")); \
}                                                            \
catch (std::string & ex)                                     \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__, ex + " [" + std::string(x) + "]");        \
}                                                            \
catch (...)                                                  \
{                                                            \
   throw ksi::exception (__FILE__, __FUNCTION__, __LINE__,             \
     std::string("unknown expection"  " [") + std::string(x) + "]" );       \
}                                                            \



#endif
