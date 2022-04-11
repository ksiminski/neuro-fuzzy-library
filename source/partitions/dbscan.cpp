/** @file */

#include <memory>
#include <vector>
#include <string>

#include "../partitions/dbscan.h"
#include "../metrics/metric.h"
#include "../metrics/metric-euclidean.h"


ksi::dbscan::dbscan()
    : _metric_object(ksi::metric_euclidean().clone())  
{
}

ksi::dbscan::dbscan(const double epsilon, const int minPoints, const ksi::metric &metric_object)
    : _metric_object(metric_object.clone())
{
   this->_epsilon = epsilon;
   this->_minPoints = minPoints;
}

ksi::partition ksi::dbscan::doPartition(const ksi::dataset &ds)
{
   try
   {
      // cluster
      int C = -1;

      std::size_t dsSize = ds.getNumberOfData();
      
      // partition matrix
      std::vector<std::vector<double>> mU;

      std::vector<bool> processed(dsSize, false);

      for (std::size_t i = 0; i < dsSize; ++i)
      {
         if (processed[i])
            continue;

         const ksi::datum *datum = ds.getDatum(i);
         processed[i] = true;

         auto neighbors = findNeighbors(datum, ds);
         auto neighborsSize = neighbors.size();

         if (neighborsSize < this->_minPoints)
            continue; // noise

         ++C;
         mU.push_back(std::vector<double>(dsSize, 0.0));
         // cluster membership
         mU[C][i] = 1.0;

         for (std::size_t j = 0; j < neighborsSize; ++j)
         {
            auto neighbor = neighbors[j].first;
            auto neighborIndex = neighbors[j].second;

            if (neighbor == datum || processed[neighborIndex])
               continue;

            mU[C][neighborIndex] = 1.0;
            processed[neighborIndex] = true;

            auto neighbors_ = findNeighbors(neighbor, ds);
            auto neighbors_Size = neighbors_.size();

            if (neighbors_Size >= this->_minPoints)
            {
               // concatenate
               neighbors.insert(neighbors.end(), neighbors_.begin(), neighbors_.end());
               neighborsSize += neighbors_Size;
            }
         }
      }

      ksi::partition part;
      part.setPartitionMatrix(mU);
      return part;
   }
   CATCH
}

std::vector<std::pair<const ksi::datum *, std::size_t>> ksi::dbscan::findNeighbors(const ksi::datum *datum, const ksi::dataset &ds)
{
   std::vector<std::pair<const ksi::datum *, std::size_t>> neighbors;
   std::size_t dsSize = ds.getNumberOfData();

   for (std::size_t i = 0; i < dsSize; i++)
   {
      auto datum_ = ds.getDatum(i);

      if (this->_metric_object->calculateDistance(*datum, *datum_) <= this->_epsilon)
         neighbors.emplace_back(datum_, i);
   }
   return neighbors;
}

ksi::partitioner *ksi::dbscan::clone() const
{
   return new dbscan(*this);
}

std::string ksi::dbscan::getAbbreviation() const
{
   return std::string("dbscan");
}

ksi::dbscan::~dbscan()
{
}
