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
#include "fcm-possibilistic.h"
#include "../service/debug.h"


 
ksi::partitioner * ksi::fcm_possibilistic::clone()
{
   auto p = new ksi::fcm_possibilistic(*this);
   
   return p;
}

ksi::fcm_possibilistic::fcm_possibilistic(const ksi::fcm_possibilistic& wzor) : fcm (wzor)
{
  
}

ksi::fcm_possibilistic & ksi::fcm_possibilistic::operator=(const ksi::fcm_possibilistic & wzor)
{
   if (this == &wzor)
      return *this;
   
   ksi::fcm::operator=(wzor);
   
   return *this;
}

ksi::fcm_possibilistic::fcm_possibilistic()
{

}



ksi::fcm_possibilistic::~fcm_possibilistic()
{
}

 

 

std::vector<std::vector<double>> ksi::fcm_possibilistic::modifyPartitionMatrix(
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mX)
{
   try
   {
      std::vector<std::vector<double>> U (mV.size());
      std::size_t nClusters = mV.size();
      std::size_t nX = mX.size();
      double exponent = 1.0 / (_m - 1.0);
      if (nX > 0)
      {
         std::size_t nAttr = mX[0].size();
         for (auto & u : U)
            u = std::vector<double> (nX);
         
         // distance matrix:
         //std::vector<std::vector<double>> Dm (nClusters);
         Dm = std::vector<std::vector<double>> (nClusters);
         for (std::size_t c = 0; c < nClusters; c++)
         {
            Dm[c] = std::vector<double> (nX);
            for (std::size_t x = 0; x < nX; x++)
               Dm[c][x] = pow(calculateDistance (mV[c], mX[x]), 2.0);
         }
         
         for (std::size_t c = 0; c < nClusters; c++)
         {
            for (std::size_t x = 0; x < nX; x++)
            {
               U[c][x] = 1.0 / (1 + pow (Dm[c][x] / etas[c], exponent));
            }
         }
      }
      return U;
   }
   CATCH;
}

 

void ksi::fcm_possibilistic::calculateEtas(int cluster_number, int nDataItems,
   const ksi::dataset & ds
)
{
   try
   {
      ksi::fcm::doPartition(ds);
      etas = std::vector<double> (_nClusters);
      
      for (int c = 0; c < _nClusters; c++)
      {
         double suma_ud = 0.0;
         double suma_u  = 0.0;
         
         for (std::size_t x = 0; x < nDataItems; x++)
         {
            double um = pow (mU[c][x], _m);
            double d2 = pow (Dm[c][x], 1 - _m);
            
            suma_ud += um * d2;
            suma_u  += um;
            
         }
         etas[c] = suma_ud / suma_u;
      }
   }
   CATCH;
}
 

 
ksi::partition ksi::fcm_possibilistic::doPartition(const ksi::dataset & ds)
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
      std::vector<std::vector<double>> mV;
      //std::vector<std::vector<double>> mU (_nClusters);
      mU = std::vector<std::vector<double>> (_nClusters);
      
      for (auto & u : mU)
         u = std::vector<double> (nX);
      randomise(mU);
      normaliseByColumns(mU);
      
      calculateEtas(_nClusters, nX, ds);
      
      if (_nIterations > 0)
      {
         for (int iter = 0; iter < _nIterations; iter++)
         {
            mV = calculateClusterCentres(mU, mX);
            mU = modifyPartitionMatrix (mV, mX);
         }
      }
      else if (_epsilon > 0)
      {
         double frob;
         do 
         {
            mV = calculateClusterCentres(mU, mX);
            auto mUnew = modifyPartitionMatrix (mV, mX);
            
            frob = Frobenius_norm_of_difference (mU, mUnew);
            mU = mUnew;
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
            ksi::descriptor_gaussian d (mV[c][a], mS[c][a]);
            cl.addDescriptor(d);
         }
         part.addCluster(cl);
      }
      
      return part;
   }
   CATCH;
}

 
 