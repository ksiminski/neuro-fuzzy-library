/** @file */ 

#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>
#include "../common/dataset.h"
#include "../descriptors/descriptor-gaussian.h"
#include "partitioner.h"
#include "partition.h"
#include "fcm_generic.h"
#include "fcm-T.h"
#include "../service/debug.h"


ksi::fcm_generic::fcm_generic(const ksi::metric& metric_object)
{
    _pMetric = metric_object.clone();
}
  
std::string ksi::fcm_generic::getAbbreviation() const
{
   return std::string ("fcm_generic+" + _pMetric->getAbbreviation());
}
   
ksi::partitioner * ksi::fcm_generic::clone() const
{
   auto p = new ksi::fcm_generic(*this);
   
   return p;
}

ksi::fcm_generic::fcm_generic(const ksi::fcm_generic& wzor) : fcm_T<double>(wzor)
{
    _pMetric = wzor._pMetric->clone();
//     debug(_nClusters);
}

ksi::fcm_generic::fcm_generic(ksi::fcm_generic && wzor) : fcm_T<double>(wzor)
{
    std::swap(_pMetric, wzor._pMetric);
}


ksi::fcm_generic::fcm_generic(const int number_of_clusters, const int number_of_clustering_iterations, const ksi::metric& metric_object) : fcm_T<double> (number_of_clusters, number_of_clustering_iterations)
{
    _pMetric = metric_object.clone();
//     debug(number_of_clusters);
}
 
ksi::fcm_generic& ksi::fcm_generic::operator=(const ksi::fcm_generic & wzor)
{
   if (this == &wzor)
      return *this;
   
   ksi::fcm_T<double>::operator=(wzor);  
   _pMetric = wzor._pMetric->clone();
   
   return *this;
}

ksi::fcm_generic& ksi::fcm_generic::operator=(ksi::fcm_generic && wzor)
{
   if (this == &wzor)
      return *this;
   
   ksi::fcm_T<double>::operator=(wzor); 
   
   std::swap(_pMetric, wzor._pMetric);
   
   return *this;
}

ksi::fcm_generic::~fcm_generic()
{
}

double ksi::fcm_generic::calculateDistance(const std::vector<double>& x, const std::vector<double>& y)
{
    return _pMetric->calculateDistance(x, y);
}
