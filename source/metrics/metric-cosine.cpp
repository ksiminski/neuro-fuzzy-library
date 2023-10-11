/** @file */ 

#include <string>
#include <sstream>
#include <cmath>

#include "../metrics/metric.h"
#include "../metrics/metric-cosine.h"
#include "../service/debug.h"

std::string ksi::metric_cosine::getAbbreviation() const
{
    return { "cosine" };
}


ksi::metric_cosine::~metric_cosine()
{
}

std::shared_ptr<ksi::metric> ksi::metric_cosine::clone() const
{
   return std::shared_ptr<ksi::metric> (new ksi::metric_cosine(*this));
}

double ksi::metric_cosine::calculateDistance(const ksi::datum & l, const ksi::datum & p) const
{
   try
   {
       return calculateDistance(l.getVector(), p.getVector());
   }
   CATCH;
}


double ksi::metric_cosine::calculateDistance(const std::vector<double>& l, const std::vector<double>& p) const
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

      double iloczyn_wektorowy = 0.0;
      double l_modul = 0.0;
      double p_modul = 0.0;
      for (std::size_t a = 0; a < lsize; a++)
      {
        iloczyn_wektorowy += (l[a]*p[a]);
        l_modul += (l[a]*l[a]);
        p_modul += (p[a]*p[a]);
         
      }
      double suma = 1.0-(iloczyn_wektorowy/(l_modul*l_modul*p_modul*p_modul));
      return suma;
   }
   CATCH;
}