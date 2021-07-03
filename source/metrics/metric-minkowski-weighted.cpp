/** @file */ 

#include <string>
#include <sstream>
#include <cmath>

#include "../metrics/metric.h"
#include "../metrics/metric-minkowski.h"
#include "../metrics/metric-minkowski-weighted.h"
#include "../service/debug.h"

std::string ksi::metric_minkowski_weighted::getAbbreviation() const
{
    return {"minkowski_weighted"};
}


ksi::metric_minkowski_weighted::~metric_minkowski_weighted()
{
}

ksi::metric_minkowski_weighted::metric_minkowski_weighted(double m, const std::vector<double> & weights) : ksi::metric_minkowski (m), _weights(weights)
{
}


std::shared_ptr<ksi::metric> ksi::metric_minkowski_weighted::clone() const
{
   return std::shared_ptr<ksi::metric> (new ksi::metric_minkowski_weighted(*this));
}

double ksi::metric_minkowski_weighted::calculateDistance(const ksi::datum & l, const ksi::datum & p) const
{
   try
   {
       return calculateDistance(l.getVector(), p.getVector());
   }
   CATCH;
}

double ksi::metric_minkowski_weighted::calculateDistance(const std::vector<double>& l, const std::vector<double>& p) const
{
    try 
    {
        auto lsize = l.size();
        auto psize = p.size();
        auto wsize = _weights.size();
        
        if (lsize != psize)
        {
            std::stringstream ss;
            ss << "Numbers of attributes do not match:" << std::endl;
            ss << " for left:  " << lsize << std::endl;
            ss << " for right: " << psize << std::endl;
            
            throw ksi::exception (ss.str());
        }
        if (lsize != wsize)
        {
            std::stringstream ss;
            ss << "Incorrect number of weights:" << std::endl;
            ss << " left argument:   " << lsize << std::endl;
            ss << " right argument:  " << psize << std::endl;
            ss << " weights:         " << wsize << std::endl;
            
            throw ksi::exception (ss.str());
        }

        double suma = 0.0;
        for (std::size_t a = 0; a < lsize; a++)
        {
            suma += _weights[a] * pow( std::fabs(l[a] - p[a]) , _m);
        }
        return pow (suma, 1.0 / _m);
    }
    CATCH;
}

