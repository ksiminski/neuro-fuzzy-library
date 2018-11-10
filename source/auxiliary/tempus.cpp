/** @file */

#include <string>
#include <chrono>
#include "tempus.h"

 

std::string ksi::getDateTimeNow()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buffer[100] = {0};
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(& now));
    return buffer;
} 
