/** @file */

#include <iostream>
#include <vector>
#include <string>
#include "utility-string.h"


std::vector<std::string> ksi::utility_string::splitString(std::string s, const char separator)
{
   std::vector<std::string> slowa;
   
   int size = s.size();
   int poczatek = 0; 
   int koniec   = 0;
   
   bool jestZnak = false;
   
   for (int  i = 0 ; i < size; i++)
   {
      if (jestZnak)
      {
         if ((s[i] == separator)) // koniec
         {
            koniec = i - 1;
            jestZnak = false;
            
            std::string slowo = s.substr(poczatek, koniec - poczatek + 1);
            slowa.push_back(slowo);
         }
      }
      else // byly spacje
      {
         if ((s[i] != separator)) 
         {
            poczatek = i;
            jestZnak = true;
         }
      }
   }
   
   // doszlismy do konca, trzeba sprawdzic, czy nie bylo napisu
   if (jestZnak)
   {
      std::string slowo = s.substr(poczatek);
      slowa.push_back(slowo);
   }         
   
   return slowa;
}



std::string ksi::utility_string::trimString(std::string s)
{
    std::string white (" \t\f\v\n\r");
    std::string::size_type pos = s.find_last_not_of (white);
    if (pos != std::string::npos)
    {
       s.erase(pos + 1);
       pos = s.find_first_not_of(white);
       if (pos != std::string::npos)
          s.erase(0, pos);
    }
    else
       s.erase(s.begin(), s.end());

    return s;
}

std::string ksi::utility_string::replaceString(
   const std::string & original, 
   const std::string & from, 
   const std::string & to)
{
   std::string result (original);
   std::size_t fromLength = from.length();
   
   std::size_t found = std::string::npos;
   std::size_t start = 0;
   do 
   {
      found = result.find (from, start);
      if (found != std::string::npos)
      {
         result.replace(found, fromLength, to);
         start = found + 1;
      }
   } while (found != std::string::npos);
   
   return result;
}
 
