/** @file */

#include <chrono>

#include "../auxiliary/clock.h"


 

std::chrono::high_resolution_clock::time_point ksi::clock::start()
{
   return _start = _zegar.now();
}

std::chrono::high_resolution_clock::time_point ksi::clock::stop()
{
   return _stop = _zegar.now();
}

std::size_t ksi::clock::elapsed_seconds()
{
   return (std::chrono::duration_cast<std::chrono::seconds>(_stop - _start)).count();
}

std::size_t ksi::clock::elapsed_milliseconds()
{
    return (std::chrono::duration_cast<std::chrono::milliseconds>(_stop - _start)).count();
}

