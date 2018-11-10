/** @file */

#ifndef UTILITY_STRING_H
#define UTILITY_STRING_H

#include <iostream>
#include <vector>
#include <string>

namespace ksi
{

   class utility_string
   {
   public:
      /** The function splits a string into substrings separated by a separator.
        * The separators are not included in substrings. Empty substrings are not
        * returned. 
        * @param s string to split
        * @param separator just a separator
        */
      static std::vector<std::string> splitString (std::string s, const char separator);
      
      
      /** Method for trimming of std::strings. It removes white chars (" \t\f\v\n\r") from beginning and form end of the string. The trimmed string is returned, original string is unchanged.
       @param s string to trim (is not modified by the function)
       @return trimmed copy of input string */
      static std::string trimString (std::string s);
      
      
      /** The method replaces all occurences of the 'from' string with
          the 'to' string. 
         @param original The string to replace substrings in. The parameter is not modified.
         @param from This string is looked for in the original string.
         @param to This string replases all occurences of the 'from' string.
         @return The modified string is returned.
         @date 2018-07-31
          */
      static std::string replaceString (const std::string & original,
                                        const std::string & from,
                                        const std::string & to);
      
      
   }; 
}
#endif
