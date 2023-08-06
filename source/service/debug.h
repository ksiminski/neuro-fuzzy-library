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





#define drukuj(x) std::cerr << __FILE__ << " (" << __LINE__ << ") " << #x << " == " << (x) << std::endl;
#define debug(x)  drukuj(x)

#define NAZWA(x)  #x 

#endif
