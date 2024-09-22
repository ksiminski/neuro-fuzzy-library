/** @file */ 

#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>

#include "../common/dataset.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../partitions/partitioner.h"
#include "../partitions/partition.h"
#include "../partitions/fcm.h"
#include "../partitions/fcm_generic.h"
#include "../metrics/metric-euclidean.h"
#include "../service/debug.h"


ksi::fcm::fcm() : fcm_generic(ksi::metric_euclidean())
{
   
}

ksi::fcm::fcm(const int number_of_clusters, const int number_of_clustering_iterations) : fcm_generic (number_of_clusters, number_of_clustering_iterations, ksi::metric_euclidean())
{
}


std::string ksi::fcm::getAbbreviation() const
{
   return std::string ("fcm");
}

ksi::partitioner * ksi::fcm::clone() const
{
   return new ksi::fcm(*this);
}

ksi::fcm::fcm(const ksi::fcm& wzor) : fcm_generic(wzor)
{
//     debug(_nClusters);
}

ksi::fcm& ksi::fcm::operator=(const ksi::fcm & wzor)
{
   if (this == &wzor)
      return *this;
   
   ksi::fcm_generic::operator=(wzor);   
   
   return *this;
}


ksi::fcm::~fcm()
{
}

