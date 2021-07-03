/** @file */  
#include <algorithm>
#include <vector>
#include "partition.h"
#include "../service/debug.h"
#include "../common/extensional-fuzzy-number-gaussian.h"




void ksi::partition::addCluster(const cluster & c)
{
   clusters.push_back(new ksi::cluster(c));
}

void ksi::partition::addCluster(ksi::cluster* p)
{
   if (p)
      clusters.push_back(p);
}

ksi::partition::partition()
{
}


ksi::partition::~partition()
{
   for (auto & p : clusters)
       delete p;
}

ksi::partition::partition(const ksi::partition & part)
{
   for (auto & p : part.clusters)
      clusters.push_back(new ksi::cluster(*p));
   
   U = part.U;
   V = part.V;
}

ksi::partition::partition(ksi::partition && part)
{
   std::swap (clusters, part.clusters);
   std::swap (U, part.U);
   std::swap (V, part.V);
}

ksi::partition& ksi::partition::operator=(const ksi::partition & part)
{
   if (this == & part)
      return * this;
   
   for (auto & p : clusters)
      delete p;
   
   for (auto & p : part.clusters)
      addCluster(p);
   
   U = part.U;
   V = part.V;
   
   return * this;
}


ksi::partition& ksi::partition::operator=(ksi::partition && part)
{
   if (this == & part)
      return * this;
   
   std::swap (clusters, part.clusters);
   
   std::swap (U, part.U);
   std::swap (V, part.V);
   
   return *this;
}

ksi::partition & ksi::partition::operator+=(const ksi::partition & right)
{
    for (auto p : right.clusters)
        addCluster(*p);
    return *this;
}


namespace ksi 
{
   std::ostream& operator<<(std::ostream& ss,  const ksi::partition& part)
   {
      int counter = 1;
      for (auto & p : part.clusters)
      {
         ss << "cluster " << counter++ << std::endl;
         ss << *p << std::endl << std::endl;
      }
      return ss;
   }
}


ksi::cluster* ksi::partition::getCluster(std::size_t index)
{
   if (clusters.size() == 0)
      return nullptr; 
   if (index < 0 or index > clusters.size())
      return nullptr;
   else
      return clusters[index];
}

std::size_t ksi::partition::getNumberOfClusters() const
{
   return clusters.size();
}

std::vector<std::vector<double>> ksi::partition::getClusterCentres() const
{
   return V;
}

 

std::vector<std::vector<double>> ksi::partition::getPartitionMatrix() const
{
   return U;
}

void ksi::partition::setClusterCentres(const std::vector<std::vector<double>> & cluster_centres)
{
   V = cluster_centres;
}

void ksi::partition::setClusterCentres(const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & cluster_centres)
{
    V = ksi::ext_fuzzy_number_gaussian::matrix_of_extensional_fuzzy_number_2_double(cluster_centres);
}


void ksi::partition::setPartitionMatrix(const std::vector<std::vector<double>> & partition_matrix)
{
   U = partition_matrix;
}

void ksi::partition::setPartitionMatrix(const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian> >& partition_matrix)
{
    U = ksi::ext_fuzzy_number_gaussian::matrix_of_extensional_fuzzy_number_2_double(partition_matrix);
}


