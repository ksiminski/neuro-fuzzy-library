/** @file */ 

#include <cmath>
#include <vector> 
#include <algorithm>
#include <numeric>
 

#include "../common/dataset.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../descriptors/descriptor-gaussian-subspace.h"
#include "partitioner.h"
#include "partition.h"
#include "fcm.h"
#include "sfcm.h"
#include "../service/debug.h"

ksi::sfcm::sfcm()
{
}

ksi::sfcm::sfcm(const int nClusters, const int nClusteringIterations) : /*fcm_T<double>(nClusters, nClusteringIterations),*/ fcm (nClusters, nClusteringIterations)  
{
}

ksi::sfcm::sfcm(const ksi::sfcm& wzor) : /*fcm_T<double>(wzor),*/ fcm (wzor)
{
    _weight_exponent = wzor._weight_exponent;
}


ksi::sfcm::sfcm(ksi::sfcm && wzor) : /*fcm_T<double>(wzor),*/ fcm (wzor)
{
    std::swap (_weight_exponent, wzor._weight_exponent);
}


ksi::sfcm & ksi::sfcm::operator=(const ksi::sfcm& wzor)
{
    if (this == &wzor)
        return *this;
    
    ksi::fcm::operator=(wzor);
    ksi::fcm_T<double>::operator=(wzor);   
    
    _weight_exponent = wzor._weight_exponent;
    
    return *this;
}

ksi::sfcm & ksi::sfcm::operator=(ksi::sfcm && wzor)
{
    if (this == &wzor)
        return *this;
    
    ksi::fcm::operator=(wzor);
    ksi::fcm_T<double>::operator=(wzor);  
    
    std::swap (_weight_exponent, wzor._weight_exponent);
    
    return *this;
}
 
 
std::string ksi::sfcm::getAbbreviation() const
{
   return std::string ("sfcm");
}

 
ksi::partitioner * ksi::sfcm::clone()  const
{
   ksi::sfcm * p = new ksi::sfcm(*this);
   
   return p;
}

ksi::sfcm::~sfcm()
{
}

std::vector<std::vector<double>> ksi::sfcm::modifyPartitionMatrix (
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX, 
         const std::vector<std::vector<double>> & mZ)
{
   try
   {
      std::size_t nX = mX.size();
      std::vector<std::vector<double>> U (mV.size());
      for (auto & u : U)
         u = std::vector<double> (nX);
      if (mV.size() > 0)
      {
         std::size_t nAttr = mV[0].size();
         
         double exponent = 1.0 / (1.0 - _m);
         
         
         for (std::size_t x = 0; x < nX; x++)
         {
            std::vector<double> distance (_nClusters, 0.0);
            for (int c = 0; c < _nClusters; c++)
            {
               double suma = 0.0;
               for (std::size_t a = 0; a < nAttr; a++)
               {
                  double roznica = mX[x][a] - mV[c][a];
                  suma += (pow(mZ[c][a], _weight_exponent) * roznica * roznica);
               }
               distance[c] = pow(suma, exponent);
            }
            double sum_distances = std::accumulate(distance.begin(), distance.end(), 0.0);
            for (int c = 0; c < _nClusters; c++)
               U[c][x] = distance[c] / sum_distances;
         }
      }
      return U; 
   }
   CATCH;
}
 
std::vector<std::vector<double>> ksi::sfcm::modifyAttributeWeights (
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX, 
         const std::vector<std::vector<double>> & mU)
{
   try
   {
      std::vector<std::vector<double>> mZ (mV);
      if (mV.size() > 0)
      {
         std::size_t nAttr = mV[0].size();
         std::size_t nX    = mX.size();
         
         double exponent = 1.0 / (1.0 - _weight_exponent);
         
         for (std::size_t c = 0; c < _nClusters; c++)
         {
            std::vector<double> distances (nAttr, 0.0);
            for (std::size_t a = 0; a < nAttr; a++)
            {
               double suma = 0.0;
               for (std::size_t x = 0; x < nX; x++)
               {
                  double u_cx_m = pow(mU[c][x], _m);
                  double roznica = mX[x][a] - mV[c][a];
                  suma += (u_cx_m * roznica * roznica);
               }
               distances[a] = pow(suma, exponent);
            }
            double sum_distances = std::accumulate(distances.begin(), distances.end(), 0.0);
            for (std::size_t a = 0; a < nAttr; a++)
               mZ[c][a] = distances[a] / sum_distances;
         }
      }
      return mZ;
   }
   CATCH;
}



ksi::partition ksi::sfcm::doPartition(const ksi::dataset & ds)
{
   try
   {
      if (_nClusters < 1)
            throw std::string ("unknown number of clusters");
         if (_nIterations < 1 and _epsilon < 0)
            throw std::string ("You should set a maximal number of iteration or "
                              "minimal difference -- epsilon.");
         if (_nIterations > 0 and _epsilon > 0)
            throw std::string ("Both number of iterations and minimal epsilon set -- you should set either number of iterations or minimal epsilon.");
      
      
      auto mX = ds.getMatrix();
      std::size_t nAttr = ds.getNumberOfAttributes();
      std::size_t nX    = ds.getNumberOfData();
      
      std::vector<std::vector<double>> mV;  // [_nClusters x nAttr]
      
      std::vector<std::vector<double>> mU (_nClusters);
      for (auto & u : mU)
         u = std::vector<double> (nX);
      randomise(mU);
      normaliseByColumns(mU);
      
      std::vector<std::vector<double>> mZ(_nClusters);
      for (auto & z : mZ)
         z = std::vector<double> (nAttr);
      
      randomise(mZ);
      normaliseByRows(mZ);
      
      if (_nIterations > 0)
      {
         for (int iter = 0; iter < _nIterations; iter++)
         {
            mV = calculateClusterCentres(mU, mX);
            mU = modifyPartitionMatrix (mV, mX, mZ);
            normaliseByColumns(mU);
            mZ = modifyAttributeWeights (mV, mX, mU);
            normaliseByRows(mZ);
         }
      }
      else if (_epsilon > 0)
      {
         double frob;
         do 
         {
            mV = calculateClusterCentres(mU, mX);
            auto mUnew = modifyPartitionMatrix (mV, mX, mZ);
            normaliseByColumns(mUnew);
            auto mZnew = modifyAttributeWeights (mV, mX, mU);
            normaliseByRows(mZnew);
            
            frob = std::max( Frobenius_norm_of_difference (mU, mUnew),
                           Frobenius_norm_of_difference (mZ, mZnew));
            mU = mUnew;
            mZ = mZnew;
            
         } while (frob > _epsilon);
      }   
         
      mV = calculateClusterCentres(mU, mX);
      std::vector<std::vector<double>> mS = calculateClusterFuzzification(mU, mV, mX);
      
      // przeksztalcenie do postaci zbiorow gaussowskich
      ksi::partition part;
      for (int c = 0; c < _nClusters; c++)
      {
         ksi::cluster cl; 
         for (std::size_t a = 0; a < nAttr; a++)
         {
            ksi::descriptor_gaussian_subspace d (mV[c][a], mS[c][a], mZ[c][a]);
            cl.addDescriptor(d);
         }
         part.addCluster(cl);
      }
      
      return part;
   }
   CATCH;
}



void ksi::sfcm::setWeigthExponent(double WeightExponent)
{
   _weight_exponent = WeightExponent;
}

 
