/** @file */ 

#include <algorithm>
#include <vector>
#include <sstream>
#include <string>

#include "../partitions/partition.h"
#include "../service/debug.h"
#include "../common/extensional-fuzzy-number-gaussian.h"
#include "../common/datum.h"
#include "../common/dataset.h"



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

std::string ksi::partition::print_partition_matrix()
{
    std::stringstream ss;
    for (const auto & cluster : U)
    {
        for (const auto & item : cluster)
            ss << item << '\t';
        ss << std::endl;
    }
    
    return ss.str();
}


std::string ksi::partition::print_crisp_membership_for_data(const ksi::dataset& ds)
{
    try 
    {
        std::stringstream ss; 
        std::size_t nItems = U[0].size();
        std::size_t nCluster = U.size();
        if (nItems != ds.getNumberOfData())
        {
            std::stringstream errors;
            errors << "Number of data items (" << ds.getNumberOfData() << ") and number of column in membership matrix (" << nItems << ") do not match!";
            throw errors.str();
        }
        
        for (std::size_t i = 0; i < nItems; i++)
        {
            ss << ds.getDatum(i)->to_string() << "\t";
            
            std::size_t max_cluster_number = 0;
            for (std::size_t c = 1; c < nCluster; c++)
            {
                if (U[max_cluster_number][i] < U[c][i])
                {
                    max_cluster_number = c;
                }
            }
            if (U[max_cluster_number][i] == 0)
               ss << "NOISE" << std::endl;
            else
               ss << max_cluster_number << std::endl;
        }
        return ss.str();
    }
    CATCH;
}
