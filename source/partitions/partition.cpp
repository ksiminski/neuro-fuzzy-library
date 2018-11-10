/** @file */  
#include <algorithm>
#include <vector>
#include "partition.h"

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
}

ksi::partition::partition(ksi::partition && part)
{
   std::swap (clusters, part.clusters);
}

ksi::partition& ksi::partition::operator=(const ksi::partition & part)
{
   if (this != & part)
      return * this;
   
   for (auto & p : clusters)
      delete p;
   
   for (auto & p : part.clusters)
      addCluster(p);
   
   return * this;
}


ksi::partition& ksi::partition::operator=(ksi::partition && part)
{
   if (this != & part)
      return * this;
   
   std::swap (clusters, part.clusters);
   
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
   if (index < 0 or index > clusters.size())
      return nullptr;
   else
      return clusters[index];
}

