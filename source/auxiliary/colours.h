/** @file */

#ifndef COLOURS_H
#define COLOURS_H

#include <string>
#include <iostream>

#define COLOURS \
    X(red,     31, 41) \
    X(green,   32, 42) \
    X(yellow,  33, 43) \
    X(blue,    34, 44) \
    X(magenta, 35, 45) \
    X(cyan,    36, 46) \
    X(white,   37, 47) \
    X(default, 39, 49) 
    
 
      
namespace ksi
{

   enum class eColour
   {
#define X(kolor,pismo,tlo) DRUK_ ## kolor,
       COLOURS
#undef X 
#define X(kolor,pismo,tlo) TLO_ ## kolor,
       COLOURS
#undef X        

#define X(kolor,pismo,tlo) DRUK_JASNY_ ## kolor,
       COLOURS
#undef X 
#define X(kolor,pismo,tlo) TLO_JASNY_ ## kolor,
       COLOURS
#undef X 
       
       
   }; 
   
   
   std::ostream & operator<< (std::ostream & ss, const eColour & col);
   
}
#endif
