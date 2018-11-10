/** @file */ 

#include <string>
#include <sstream>
#include <cmath>
#include "distance.h"
#include "distance-euclidean.h"
#include "distance-euclidean-incomplete.h"
#include "../service/debug.h"

ksi::distance_euclidean_incomplete::~distance_euclidean_incomplete()
{
}

ksi::distance* ksi::distance_euclidean_incomplete::clone()
{
   return new ksi::distance_euclidean_incomplete();
}

double ksi::distance_euclidean_incomplete::calculateDistance(
   const ksi::datum & l, 
   const ksi::datum & p)
{
   try
   {
      // wyznaczam odleglosc euklidesowa:
      
      auto lsize = l.getNumberOfAttributes();
      auto psize = p.getNumberOfAttributes();
      
      if (lsize != psize)
      {
         std::stringstream ss;
         ss << "Numbers of attributes do not match:" << std::endl;
         ss << " for left:  " << lsize << std::endl;
         ss << " for right: " << psize << std::endl;
         
         throw ksi::exception (ss.str());
      }

      double suma = 0.0;
      int nCommonAttributes = 0;
      for (std::size_t a = 0; a < lsize; a++)
      {
         if (l.at(a)->exists() and p.at(a)->exists())
         {
            nCommonAttributes++;
            double roznica = l.at(a)->getValue() - p.at(a)->getValue();
            suma += (roznica * roznica);
         }
      }
      return sqrt (suma * lsize / nCommonAttributes);
   }
   CATCH;
}


