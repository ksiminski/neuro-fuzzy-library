/** @file */ 

#ifndef DEBUG_H
#define DEBUG_H

// #include <sstream>
// #include <iostream>
// #include <exception>
// #include <string>
// #include <vector>
// #include <utility>

#include "../auxiliary/definitions.h"
#include "../service/exception.h"



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




#define drukuj(x) std::cerr << __FILE__ << " (" << __LINE__ << ") " << #x << " == " << (x) << std::endl;
#define debug(x)  drukuj(x)

#define NAZWA(x)  #x 

#endif
