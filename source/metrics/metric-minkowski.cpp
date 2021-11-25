/** @file */ 

#include <string>
#include <sstream>
#include <cmath>

#include "../metrics/metric.h"
#include "../metrics/metric-minkowski.h"
#include "../service/debug.h"

std::string ksi::metric_minkowski::getAbbreviation() const
{
    return {"minkowski"};
}

std::string ksi::metric_minkowski::get_info() const
{
    return {"Minkowski metric: m = " + std::to_string(_m)};
}


ksi::metric_minkowski::~metric_minkowski()
{
}

ksi::metric_minkowski::metric_minkowski(double m) : _m (m)
{
}


std::shared_ptr<ksi::metric> ksi::metric_minkowski::clone() const 
{
   return std::shared_ptr<ksi::metric> (new ksi::metric_minkowski(*this));
}

double ksi::metric_minkowski::calculateDistance(const ksi::datum & l, const ksi::datum & p) const
{
   try
   {
       return calculateDistance(l.getVector(), p.getVector());
   }
   CATCH;
}

double ksi::metric_minkowski::calculateDistance(const std::vector<double>& l, const std::vector<double>& p) const
{
    try 
    {
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
            suma += pow( std::fabs(l[a] - p[a]) , _m);
        }
        return pow (suma, 1.0 / _m);
    }
    CATCH;
}

