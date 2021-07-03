/** @file */ 

#include <string>
#include <sstream>
#include <cmath>

#include "../metrics/metric.h"
#include "../metrics/metric-euclidean.h"
#include "../service/debug.h"

std::string ksi::metric_euclidean::getAbbreviation() const
{
    return { "euclidean"};
}


ksi::metric_euclidean::~metric_euclidean()
{
}

std::shared_ptr<ksi::metric> ksi::metric_euclidean::clone() const
{
   return std::shared_ptr<ksi::metric> (new ksi::metric_euclidean(*this));
}

double ksi::metric_euclidean::calculateDistance(const ksi::datum & l, const ksi::datum & p) const
{
   try
   {
       return calculateDistance(l.getVector(), p.getVector());
   }
   CATCH;
}


double ksi::metric_euclidean::calculateDistance(const std::vector<double>& l, const std::vector<double>& p) const
{
   try
   {
      // wyznaczam odleglosc euklidesowa:
      
      auto lsize = l.size();
      auto psize = p.size();
      
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
            double roznica = l[a] - p[a];
            suma += (roznica * roznica);
         
      }
      return sqrt (suma);
   }
   CATCH;
}
