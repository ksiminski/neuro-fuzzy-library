/** @file */

#include <string>
#include <chrono>

#include "tempus.h"

 

std::string ksi::getDateTimeNow()
{
    return ksi::tempus::getDateTimeNow();
} 


std::string ksi::tempus::getDateTimeNow()
{
    return getDateTimeNow("%Y-%m-%d %H:%M:%S");
}

std::string ksi::tempus::getDateTimeNowSafe()
{
    return getDateTimeNow("%Y-%m-%d-%H-%M-%S");   
}


std::string ksi::tempus::getDateTimeNow(const std::string& format)
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buffer[100] = {0};
    std::strftime(buffer, sizeof(buffer), format.c_str(), std::localtime(& now));
    return buffer;
}


