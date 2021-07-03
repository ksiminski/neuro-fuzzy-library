/** @file */ 

#include <string>
#include <sstream>
#include <cmath>
#include "../metrics/metric.h"
#include "../metrics/metric-euclidean.h"
#include "../metrics/metric-euclidean-incomplete.h"
#include "../service/debug.h"

std::string ksi::metric_euclidean_incomplete::getAbbreviation() const
{
    return {"euclidean_incomplete"};
}


ksi::metric_euclidean_incomplete::~metric_euclidean_incomplete()
{
}

std::shared_ptr<ksi::metric> ksi::metric_euclidean_incomplete::clone() const
{
   return std::shared_ptr<ksi::metric> (new ksi::metric_euclidean_incomplete(*this));
}

double ksi::metric_euclidean_incomplete::calculateDistance(
   const ksi::datum & l, 
   const ksi::datum & p) const
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

double ksi::metric_euclidean_incomplete::calculateDistance(const std::vector<double>& l, const std::vector<double>& p) const
{
    try 
    {
        throw std::string ("This method cannot be used with vector of double, because it is impossible to put missing values in a vector.");
    }
    CATCH;
    
    return 0.0;
}

