/** @file */

#ifndef TEMPUS_H
#define TEMPUS_H

#include <string>

namespace ksi
{

   /** @return actual date and time */
   std::string getDateTimeNow();
   
   
   class tempus 
   {
       /** @return a string with data and time 
        @param format a format of returned date and time*/
       static std::string getDateTimeNow(const std::string & format);
   public:
       /** @return a string with data and time in format: "2021-01-23 00:27:14" */
       static std::string getDateTimeNow();
       /** @return a string with data and time in format: "2021-01-23-00-27-14" */
       static std::string getDateTimeNowSafe();
   };
   
}

#endif
