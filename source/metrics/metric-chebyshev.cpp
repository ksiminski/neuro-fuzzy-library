/** @file */ 

#include <string>
#include <sstream>
#include <cmath>

#include "../metrics/metric.h"
#include "../metrics/metric-chebyshev.h"
#include "../service/debug.h"

std::string ksi::metric_chebyshev::getAbbreviation() const
{
    return { "Chebyshev" };
}


ksi::metric_chebyshev::~metric_chebyshev()
{
}

std::shared_ptr<ksi::metric> ksi::metric_chebyshev::clone() const
{
   return std::shared_ptr<ksi::metric> (new ksi::metric_chebyshev(*this));
}

double ksi::metric_chebyshev::calculateDistance(const ksi::datum & l, const ksi::datum & p) const
{
   try
   {
       return calculateDistance(l.getVector(), p.getVector());
   }
   CATCH;
}


double ksi::metric_chebyshev::calculateDistance(const std::vector<double>& l, const std::vector<double>& p) const
{
   try
   {
      // wyznaczam odleglosc Chebyszewa:
      
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
            double roznica = fabs(l[a] - p[a]);
            if(roznica>suma){suma=roznica;};
      }
      return suma;
   }
   CATCH;
}
