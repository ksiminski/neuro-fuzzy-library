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
#include "fcm.h"
#include "fcm-conditional.h"
#include "../service/debug.h"


 
ksi::partitioner * ksi::fcm_conditional::clone()
{
   return new ksi::fcm_conditional(*this);
}

ksi::fcm_conditional::~fcm_conditional()
{
}

ksi::fcm_conditional::fcm_conditional()
{

}

ksi::fcm_conditional::fcm_conditional(const ksi::fcm & wzor): fcm(wzor)
{

}

ksi::fcm_conditional& ksi::fcm_conditional::operator=(const ksi::fcm& wzor)
{
   if (this == & wzor)
      return *this;
   
   ksi::fcm::operator=(wzor);
   
   return *this;
}

void ksi::fcm_conditional::normaliseByColumns(
   std::vector< std::vector< double > >& m, 
   const std::vector< double >& weights)
{
   try
   {
      if (m.size() > 0)
      {
         std::size_t nCols = m[0].size();
         std::size_t nRows = m.size();
         if (weights.size() != nCols)
         {
            throw std::string ("Numbers of data items and data weights do not match!");            
         }
         
         for (std::size_t a = 0; a < nCols; a++)
         {
            double suma = 0.0;
            for (std::size_t r = 0; r < nRows; r++)
               suma += m[r][a];
            for (std::size_t r = 0; r < nRows; r++)
               m[r][a] *= weights[a] / suma;
         }
      }
   }
   CATCH;
}


 
ksi::partition ksi::fcm_conditional::doPartition(const ksi::dataset & ds)
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
      std::vector<double> wWeights (nX);
      for (std::size_t x = 0; x < nX; x++)
         wWeights[x] = ds.getDatum(x)->getWeight();
      
      for (auto & u : mU)
         u = std::vector<double> (nX);
      randomise(mU);
      normaliseByColumns(mU, wWeights);
      
      if (_nIterations > 0)
      {
         for (int iter = 0; iter < _nIterations; iter++)
         {
            mV = calculateClusterCentres(mU, mX);
            mU = modifyPartitionMatrix (mV, mX, wWeights);
            normaliseByColumns(mU, wWeights);
         }
      }
      else if (_epsilon > 0)
      {
         double frob;
         do 
         {
            mV = calculateClusterCentres(mU, mX);
            auto mUnew = modifyPartitionMatrix (mV, mX, wWeights);
            normaliseByColumns(mUnew, wWeights);
            
            frob = Frobenius_norm_of_difference (mU, mUnew);
            mU = mUnew;
         } while (frob > _epsilon);
      }
            
            
      mV = calculateClusterCentres(mU, mX);
      std::vector<std::vector<double>> mS = calculateClusterFuzzification(mU, mV, mX, wWeights);
      
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


std::vector<std::vector<double>> ksi::fcm_conditional::modifyPartitionMatrix(
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mX, 
   const std::vector< double >& weights)
{
   try
   {
      std::vector<std::vector<double>> U (mV.size());
      std::size_t nClusters = mV.size();
      std::size_t nX = mX.size();
      double exponent = 2.0 / (1.0 - _m);
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
               Dm[c][x] = pow(calculateDistance (mV[c], mX[x]), exponent);
         }

         std::vector<double> Dmsums  (nX, 0.0);
         std::vector<int>    Dmzeros (nX, 0.0);
         for (std::size_t c = 0; c < nClusters; c++)
         {
            for (std::size_t x = 0; x < nX; x++)
            {
               if (Dm[c][x] == 0)
                  Dmzeros[x]++;
               Dmsums[x] += Dm[c][x];
            }
         }
         
         for (std::size_t c = 0; c < nClusters; c++)
         {
            for (std::size_t x = 0; x < nX; x++)
            {
               if (Dmzeros[x] > 0)
               {
                  if (Dm[c][x] == 0.0)
                     U[c][x] = weights[x] / Dmzeros[x];
                  else
                     U[c][x] = 0.0;
               }
               else
               {
                  U[c][x] = weights[x] * Dm[c][x] / Dmsums[x];
               }
            }
         }
      }
      return U;
   }
   CATCH;
}


std::vector< std::vector<double>> ksi::fcm_conditional::calculateClusterFuzzification(
   const std::vector<std::vector<double>> & mU,    
   const std::vector<std::vector<double>> & mV,
   const std::vector<std::vector<double>> & mX, 
   const std::vector< double >& weights)
{
   try
   {
      auto mS (mV);
      if (mX.size() > 0)
      {
         std::size_t nX = mX.size();
         std::size_t nAttr = mX[0].size();
         
         for (int c = 0; c < _nClusters; c++)
         {
            double sumU = 0.0;
            std::vector<double> sumUXV (nAttr, 0.0);
            for (std::size_t x = 0; x < nX; x++)
            {
               double w = weights[x];
               double um = pow(mU[c][x], _m);
               //double um = mU[c][x];
               sumU += um * w;
               
               for (std::size_t a = 0; a < nAttr; a++)
               {
                  double roznica = mX[x][a] - mV[c][a];
                  sumUXV[a] += w * um * roznica * roznica;
               }
            }
            
            for (std::size_t a = 0; a < nAttr; a++)
               mS[c][a] = sqrt (sumUXV[a] / sumU);
         }
         return mS;
      }
      return std::vector< std::vector<double>>();
   }
   CATCH;
}
 
 