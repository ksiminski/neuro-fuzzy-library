/** @file */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream>
#include <vector>

namespace ksi
{

   /** Template of a method for printing a vector of objects.
    * @date 2018-07-09
    */
   template<class T>
   std::ostream & operator << (std::ostream & ss, const std::vector<T> & w)
   {
      ss << "[ ";
      for (const auto & d : w)
         ss << d << " ";
      ss << "]";
      return ss;
   }
   
   /** Template of a method for printing a pair of objects.
    * @date 2018-07-09
    */
   template<class T, class S>
   std::ostream & operator << (std::ostream & ss, const std::pair<T, S> & we)
   {
      ss << "{ " << we.first << ", " << we.second << " }";
      return ss;
   }

}
#endif
