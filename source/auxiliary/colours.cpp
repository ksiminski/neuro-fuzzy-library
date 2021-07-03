/** @file */


#include <string>
#include <iostream>

#include "../auxiliary/colours.h"

    
#ifdef __unix  
      
namespace ksi
{



   std::ostream & operator<< (std::ostream & ss, const eColour & col)
   {
       switch (col)
       {
#define X(kolor,pismo,tlo) case eColour::DRUK_ ## kolor : ss << "\u001b[" << pismo << "m"; break;
       COLOURS
#undef X 
#define X(kolor,pismo,tlo) case eColour::TLO_ ## kolor : ss << "\u001b[" << tlo << "m"; break;
       COLOURS
#undef X 

#define X(kolor,pismo,tlo) case eColour::DRUK_JASNY_ ## kolor : ss << "\u001b[" << pismo << ";1m"; break;
       COLOURS
#undef X 
#define X(kolor,pismo,tlo) case eColour::TLO_JASNY_ ## kolor : ss << "\u001b[" << tlo << ";1m"; break;
       COLOURS
#undef X 
           default : break;

       }
        
       return ss;
   }
}

#else

namespace ksi
{
   std::ostream & operator<< (std::ostream & ss, const eColour & col)
   {
       ss << "";
       return ss;
   }
}


#endif 
