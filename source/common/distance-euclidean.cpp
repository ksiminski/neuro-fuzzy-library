/** @file */ 

#include <string>
#include <sstream>
#include <cmath>
#include "distance.h"
#include "distance-euclidean.h"
#include "../service/debug.h"

ksi::distance_euclidean::~distance_euclidean()
{
}

ksi::distance* ksi::distance_euclidean::clone()
{
   return new ksi::distance_euclidean();
}

double ksi::distance_euclidean::calculateDistance(
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
      for (std::size_t a = 0; a < lsize; a++)
      {
         if (l.at(a)->exists() and p.at(a)->exists())
         {
            double roznica = l.at(a)->getValue() - p.at(a)->getValue();
            suma += (roznica * roznica);
         }
      }
      return sqrt (suma);
   }
   CATCH;
}


