/** @file */

#include <memory>
#include <vector>

#include "../partitions/granular-dbscan.h"
#include "../partitions/partitioner.h"
#include "../partitions/fcm.h"
#include "../descriptors/descriptor.h"
#include "../descriptors/descriptor-triangular.h"
#include "../tnorms/t-norm.h"
#include "../snorms/s-norm.h"
#include "../tnorms/t-norm-lukasiewicz.h"
#include "../snorms/s-norm-lukasiewicz.h"

ksi::granular_dbscan::granular_dbscan(
    const double epsilon,
    const double minPoints,
    const double xi,
    const double psi,
    const ksi::partitioner &fuzzyficationAlgorithm,
    const ksi::s_norm &snorm,
    const ksi::t_norm &tnorm)
    : _fuzzyficationAlgorithm(fuzzyficationAlgorithm.clone()),
      _snorm(snorm.clone()),
      _tnorm(tnorm.clone())
{
   this->_epsilon = epsilon;
   this->_minPoints = minPoints;
   this->_xi = xi;
   this->_psi = psi;
}

ksi::granular_dbscan::granular_dbscan(const granular_dbscan &obj)
    : partitioner(obj),
      _fuzzyficationAlgorithm(std::shared_ptr<partitioner>(obj._fuzzyficationAlgorithm->clone())),
      _snorm(std::shared_ptr<s_norm>(obj._snorm->clone())),
      _tnorm(std::shared_ptr<t_norm>(obj._tnorm->clone()))
{
   this->_epsilon = obj._epsilon;
   this->_minPoints = obj._minPoints;
   this->_xi = obj._xi;
   this->_psi = obj._psi;
}

ksi::granular_dbscan &ksi::granular_dbscan::operator=(const ksi::granular_dbscan &obj)
{
   if (this == &obj)
      return *this;

   this->_fuzzyficationAlgorithm = obj._fuzzyficationAlgorithm;
   this->_tnorm = std::shared_ptr<t_norm>(obj._tnorm->clone());
   this->_snorm = std::shared_ptr<s_norm>(obj._snorm->clone());

   this->_epsilon = obj._epsilon;
   this->_minPoints = obj._minPoints;
   this->_xi = obj._xi;
   this->_psi = obj._psi;

   return *this;
}

std::vector<std::vector<std::shared_ptr<ksi::descriptor>>> ksi::granular_dbscan::prepareFuzzyData(const ksi::dataset &ds, std::shared_ptr<partitioner> algorithm)
{
   try
   {
      auto partition = algorithm->doPartition(ds);

      std::vector<std::vector<std::shared_ptr<ksi::descriptor>>> fuzzyData;

      const std::size_t numberOfClusters = partition.getNumberOfClusters();
      for (std::size_t i = 0; i < numberOfClusters; ++i)
      {
         ksi::cluster *cluster = partition.getCluster(i);

         std::vector<std::shared_ptr<ksi::descriptor>> granule;

         const std::size_t numberOfDescriptors = cluster->getNumberOfDescriptors();
         for (std::size_t j = 0; j < numberOfDescriptors; ++j)
         {
            granule.push_back(std::shared_ptr<ksi::descriptor>{cluster->getDescriptor(j)});
         }

         fuzzyData.push_back(granule);
      }

      return fuzzyData;
   }
   CATCH
}

ksi::partition ksi::granular_dbscan::doPartition(const ksi::dataset &ds)
{
   try
   {
      const auto fuzzyDs = prepareFuzzyData(ds, this->_fuzzyficationAlgorithm);

      std::vector<std::vector<double>> partition_matrix; // each row represents a cluster, each column -- a granule

      const std::size_t datasetSize = fuzzyDs.size();
      std::vector<bool> coreProcessed(datasetSize, false);

      // cluster
      int C = 0; 

      std::size_t minIndex = 0;
      std::vector<std::shared_ptr<ksi::descriptor>> coreGranule = fuzzyDs[minIndex];
      coreProcessed[minIndex] = true;

      while (!coreGranule.empty())
      {
         ++C;  // cluster number 

         std::vector<double> neighboursMemberships = findNeighboursMemberships(fuzzyDs, coreGranule);

         std::vector<bool> processed(datasetSize, false);
         processed[minIndex] = true;

         std::vector<std::shared_ptr<ksi::descriptor>> neighbourGranule{};
         std::size_t maxMembIndex = findMaxMembIndex(datasetSize, neighboursMemberships, this->_psi, processed);

         if (maxMembIndex != std::numeric_limits<std::size_t>::max())
         {
            neighbourGranule = fuzzyDs[maxMembIndex];
         }

         while (!neighbourGranule.empty())
         {
            const std::vector<double> expandedNeighboursMemberships = findNeighboursMemberships(fuzzyDs, neighbourGranule);

            for (std::size_t i = 0; i < datasetSize; ++i)
            {
               neighboursMemberships[i] = std::max(neighboursMemberships[i], this->_tnorm->tnorm(neighboursMemberships[maxMembIndex], expandedNeighboursMemberships[i]));
            }
            processed[maxMembIndex] = true;

            maxMembIndex = findMaxMembIndex(datasetSize, neighboursMemberships, this->_psi, processed);
            if (maxMembIndex != std::numeric_limits<std::size_t>::max())
            {
               neighbourGranule = fuzzyDs[maxMembIndex];
            }
            else
            {
               neighbourGranule = {};
            }
         }

         partition_matrix.push_back(neighboursMemberships);

         std::vector<double> aggregated(datasetSize, 0);

         for (std::size_t c = 0; c < datasetSize; ++c) // columns
         {
            for (std::size_t r = 0; r < C; ++r) // rows
            {
               aggregated[c] = this->_snorm->snorm(aggregated[c], partition_matrix[r][c]);
            }
         }

         coreGranule = {};

         double minValue = 1;
         minIndex = std::numeric_limits<std::size_t>::max();

         for (std::size_t i = 0; i < datasetSize; ++i)
         {
            auto mi = aggregated[i];
            if (mi < minValue && mi < this->_xi && coreProcessed[i] == false)
            {
               minValue = mi;
               minIndex = i;
            }
         }

         if (minIndex != std::numeric_limits<std::size_t>::max())
         {
            coreGranule = fuzzyDs[minIndex];
            coreProcessed[minIndex] = true;
         }
      }

      std::vector<std::vector<double>> mU;

      for (std::size_t r = 0; r < C; ++r) // clusters
      {
         double sum = 0;

         for (std::size_t c = 0; c < datasetSize; ++c) // granules
         {
            sum += partition_matrix[r][c];
         }

         if (sum >= this->_minPoints)
         {
            mU.push_back(partition_matrix[r]);
         }
      }

      
      ////////////////////////////
      // TODO Ekstrakcja metody!
      // KS: mU: partition matrix for granules
      // KS: 
      
      auto mClusterDatum = getClusterDatumMatrix(ds, fuzzyDs, mU);
       
     /////////////
      
      ksi::partition part;
      // part.setPartitionMatrix(mU);
      
      part.setPartitionMatrix(mClusterDatum);
      return part;
   }
   CATCH
}

std::vector<std::vector<double>> ksi::granular_dbscan::getClusterDatumMatrix(const ksi::dataset& input_dataset, const std::vector<std::vector<std::shared_ptr<descriptor>>>& granules, const std::vector<std::vector<double>>& mClusterGranule)
{
   try 
   {
      const auto ds_size = input_dataset.size();    // number of input data 
      const auto gr_size = granules.size();         // number of granules 
      const auto cl_size = mClusterGranule.size();  // number of clusters
      std::vector<std::vector<double>> mGranuleDatum (gr_size, std::vector<double> (ds_size));
    
      // We have to calculate membership of each data item to each granule. 
      
      for (std::size_t i = 0; i < ds_size; i++)
      {
         auto d = input_dataset.getDatum(i);
         for (std::size_t g = 0; g < gr_size; g++)
         {
             auto memb = getMembershipToGranule(*d, granules[g], _tnorm);
             mGranuleDatum[g][i] = memb;
         }
      }
      
      // We have just calculated memberships of all data items to granules.
      // We already have memberships of granules to clusters.
      // Now we are elaborating memberships of all data items to clusters.
      
      std::vector<std::vector<double>> mClusterDatum (cl_size, std::vector<double> (ds_size)); 
      
      for (std::size_t c = 0; c < cl_size; c++)
      {
         for (std::size_t d = 0; d < ds_size; d++)
         {
            double v { 0 };
            for (std::size_t g = 0; g < gr_size; g++)
               v = std::max(v, mClusterGranule[c][g] * mGranuleDatum[g][d]);
            mClusterDatum[c][d] = v;
         }
      }
      
      return mClusterDatum;
 
   }
   CATCH;
}


double ksi::granular_dbscan::getMembershipToGranule(const ksi::datum& d, const std::vector<std::shared_ptr<ksi::descriptor>>& gs, const std::shared_ptr<t_norm> pt)
{
   try 
   {
      if (d.getNumberOfAttributes() != gs.size())
      {
         std::stringstream ss; 
         ss << "Number of attributes (" << d.getNumberOfAttributes() << ") and number of descriptors of a granules (" << gs.size() << ") do not match!";
         
         ksi::exception ex (ss.str());
         throw ex;
         
      }
      
      double memb = 1.0;
      const auto nAttr = d.getNumberOfAttributes();
      
      for (std::size_t a = 0; a < nAttr; a++)
      {
          double m = gs[a]->getMembership(d.at(a)->getValue());   
          memb = pt->tnorm(memb, m);
      }
      return memb;
   }
   CATCH;
}


std::size_t ksi::granular_dbscan::findMaxMembIndex(const std::size_t datasetSize, const std::vector<double> &memberships, const double psi, const std::vector<bool> &processed)
{
   double maxValue = 0;
   std::size_t maxIndex = std::numeric_limits<std::size_t>::max();

   for (std::size_t i = 0; i < datasetSize; ++i)
   {
      auto mi = memberships[i];
      if (mi > maxValue && mi > psi && processed[i] == false)
      {
         maxValue = mi;
         maxIndex = i;
      }
   }

   return maxIndex;
}

std::vector<double> ksi::granular_dbscan::findNeighboursMemberships(
    const std::vector<std::vector<std::shared_ptr<ksi::descriptor>>> &fuzzyDs,
    const std::vector<std::shared_ptr<ksi::descriptor>> &granule)
{
   const std::size_t dsSize = fuzzyDs.size();
   const std::size_t numberOfDescriptors = granule.size();

   std::vector<double> memberships(dsSize, 0);

   for (std::size_t i = 0; i < dsSize; ++i)
   {
      auto granule_ = fuzzyDs[i];

      double membershipResult = 1;

      for (std::size_t j = 0; j < numberOfDescriptors; ++j)
      {
         const descriptor_triangular distance = calculateDistance(granule[j], granule_[j]);
         double membership = areaPercentageInSpace(this->_epsilon, distance);

         membershipResult = this->_tnorm->tnorm(membershipResult, membership);
      }

      memberships[i] = membershipResult;
   }
   return memberships;
}

const ksi::descriptor_triangular ksi::granular_dbscan::calculateDistance(
    const std::shared_ptr<ksi::descriptor> &firstDescriptor,
    const std::shared_ptr<ksi::descriptor> &secondDescriptor)
{
   double core = std::abs(secondDescriptor->getCoreMean() - firstDescriptor->getCoreMean());
   double supp_min = core - std::max(firstDescriptor->getFuzzification(), secondDescriptor->getFuzzification());
   double supp_max = core + std::max(firstDescriptor->getFuzzification(), secondDescriptor->getFuzzification());

   return descriptor_triangular(supp_min, core, supp_max);
}

const double ksi::granular_dbscan::areaPercentageInSpace(const double epsilon, const descriptor_triangular &triangle)
{
   if (epsilon < triangle.getSupportMin())
      return 0.0;
   else if (epsilon > triangle.getSupportMax())
      return 1.0;
   else
   {
      const double fullArea = (triangle.getSupportMax() - triangle.getSupportMin()) * 0.5;
      double area;

      if (epsilon < triangle.getCoreMean())
      {
         const double a = epsilon - triangle.getSupportMin();
         const double h = a / (triangle.getCoreMean() - triangle.getSupportMin());
         area = 0.5 * a * h;
      }
      else
      {
         const double a = triangle.getSupportMax() - epsilon;
         const double h = a / (triangle.getSupportMax() - triangle.getCoreMean());
         area = fullArea - (0.5 * a * h);
      }

      return area / fullArea;
   }
}

ksi::partitioner *ksi::granular_dbscan::clone() const
{
   return new granular_dbscan(*this);
}

std::string ksi::granular_dbscan::getAbbreviation() const
{
   return std::string("GrDBSCAN");
}

ksi::granular_dbscan::~granular_dbscan()
{
}
