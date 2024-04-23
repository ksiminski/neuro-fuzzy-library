/** @file */ 

#ifndef TO_STRING_H
#define TO_STRING_H

#include <string>
#include <vector>

namespace ksi
{
   /* @return The function returns a string representation of a double value in the exponential form.
    * @author Krzysztof Siminski
    * @date 2023-10-09 */ 
   std::string to_string (const double x);

   /* @return The function returns a string representation of an integer value with leading zeroes.
    * @author Krzysztof Siminski
    * @param n number to make a string for
    * @param width width of the window for an integer (filled with zeroes)
    * @date 2024-03-27 */ 
   std::string to_string (const int n, const unsigned int width = 0);

   /* @return The function returns a string representation of a vector of ints with leading zeroes.
    * @author Krzysztof Siminski
    * @param numbers numbers to make a string for
    * @param width width of the window for an integer (filled with zeroes)
    * @param sep separator of numbers
    * @date 2024-03-29 */ 
   std::string to_string (const std::vector<int> & numbers, const unsigned int width = 0, const char sep = '-');

   /* @return The function returns a string representation of a vector of ints with leading zeroes.
    * @author Krzysztof Siminski
    * @param numbers numbers to make a string for
    * @param width width of the window for an integer (filled with zeroes)
    * @param sep separator of numbers
    * @date 2024-03-29 */ 
   std::string to_string (const std::vector<double> & numbers, const char sep = '-');
}


#endif
