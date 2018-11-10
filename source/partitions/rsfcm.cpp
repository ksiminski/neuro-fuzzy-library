/** @file */  
 
#include <cmath>
 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "../common/dataset.h"
#include "../descriptors/descriptor-interval-gaussian-subspace.h"
#include "../service/debug.h"
#include "rsfcm.h"
#include "rfcm.h"
#include "sfcm.h"

ksi::partitioner * ksi::rsfcm::clone()
{
   return new ksi::rsfcm(*this);
}

ksi::rsfcm::~rsfcm()
{
}

ksi::rsfcm::rsfcm(const ksi::rsfcm & wzor) : sfcm(wzor), rfcm(wzor)
{
}

ksi::rsfcm::rsfcm(ksi::rsfcm && wzor) : sfcm(wzor), rfcm(wzor)
{
}

ksi::rsfcm & ksi::rsfcm::operator=(const ksi::rsfcm & wzor)
{
   if (& wzor == this)
      return *this;
   
   ksi::sfcm::operator=(wzor);
   ksi::rfcm::operator=(wzor);
   
   return *this;
}

ksi::rsfcm & ksi::rsfcm::operator=(ksi::rsfcm && wzor)
{
   if (& wzor == this)
      return *this;
   
   ksi::sfcm::operator=(wzor);
   ksi::rfcm::operator=(wzor);
   
   return *this;
}

ksi::rsfcm::rsfcm(const ksi::data_modifier & imputer, 
                  const ksi::data_modifier & marginaliser,
                  const bool useMarginalisedDataForCentres
               ) : rfcm (imputer, marginaliser, useMarginalisedDataForCentres)
{
}
 
ksi::partition ksi::rsfcm::doPartition(const ksi::dataset & ds) 
{
   try
   {
      if (not _pMarginaliser)
         throw std::string ("marginalised object not set");
      if (not _pImputer)
         throw std::string ("imputer object not set");
      if (_nClusters < 1)
         throw std::string ("number of clusters not set");
      if (_nIterations < 1 and _epsilon < 0)
         throw std::string ("You should set a maximal number of iteration or "
                            "minimal difference -- epsilon.");
      if (_nIterations > 0 and _epsilon > 0)
         throw std::string ("Both number of iterations and minimal epsilon set -- you should set either number of iterations or minimal epsilon.");
      
      ksi::dataset lowerDataset (ds);   // marginalised
      ksi::dataset upperDataset (ds);   // imputed
      
      _pMarginaliser->modify(lowerDataset);
      _pImputer->modify(upperDataset);
      
      std::size_t nAttr = ds.getNumberOfAttributes();
      std::vector<std::vector<double>> mV;
      
      // dla lower
      auto mXlower = lowerDataset.getMatrix();
      
      std::size_t nXlower = lowerDataset.getNumberOfData();
      auto mUlower = std::vector<std::vector<double>> (_nClusters);
      
      for (auto & u : mUlower)
         u = std::vector<double> (nXlower);
      randomise(mUlower);
      fcm::normaliseByColumns(mUlower);
      
      // dla upper 
      auto mXupper = upperDataset.getMatrix();
      std::size_t nXupper = upperDataset.getNumberOfData();
      //std::vector<std::vector<double>> mU (_nClusters);
      auto mUupper = std::vector<std::vector<double>> (_nClusters);
      std::vector<double> wWeights (nXupper);
      for (std::size_t x = 0; x < nXupper; x++)
         wWeights[x] = upperDataset.getDatum(x)->getWeight();
      
      for (auto & u : mUupper)
         u = std::vector<double> (nXupper);
      randomise(mUupper);
      fcm_conditional::normaliseByColumns(mUupper, wWeights);
      
      // attribute weights
      std::vector<std::vector<double>> mZ(_nClusters);
      for (auto & z : mZ)
         z = std::vector<double> (nAttr);
      randomise(mZ);
      fcm::normaliseByRows(mZ);
      ////////////////////
            
      
      if (_nIterations > 0)
      {
         for (int iter = 0; iter < _nIterations; iter++)
         {
            if (_useMarginalisedDataForCentres) 
               mV = fcm::calculateClusterCentres(mUlower, mXlower);
            else
               mV = rfcm::calculateClusterCentres(mUupper, mXupper, wWeights);  
            
            // zbior zmarginalizowany klastruje FCM  
            mUlower = sfcm::modifyPartitionMatrix (mV, mXlower, mZ);
            sfcm::normaliseByColumns(mUlower);
            
            // zbior gorny za pomoca FCM conditional:
            mUupper = modifyPartitionMatrix (mV, mXupper, mZ, wWeights); 
            fcm_conditional::normaliseByColumns(mUupper, wWeights);
            
            // modification of attribute weights:
            mZ = modifyAttributeWeights(mV, mXlower, mUlower);
            sfcm::normaliseByRows(mZ);
         }
      }
      else if (_epsilon > 0)
      {
         double frobUpper, frobLower, frobZ;
         do 
         {
            if (_useMarginalisedDataForCentres) 
               mV = fcm::calculateClusterCentres(mUlower, mXlower);
            else
               mV = rfcm::calculateClusterCentres(mUupper, mXupper, wWeights);  
            
            // zbior zmarginalizowany klastruje FCM  
            auto mUlowerNew = sfcm::modifyPartitionMatrix (mV, mXlower, mZ);
            sfcm::normaliseByColumns(mUlower);
            
            // zbior gorny za pomoca FCM conditional:
            auto mUupperNew = modifyPartitionMatrix (mV, mXupper, mZ, wWeights);
            fcm_conditional::normaliseByColumns(mUupper, wWeights);
            
            // modification of attribute weights:
            auto mZnew = modifyAttributeWeights(mV, mXlower, mUlower);
            sfcm::normaliseByRows(mZnew);
            
            frobUpper = Frobenius_norm_of_difference (mUupper, mUupperNew);
            frobLower = Frobenius_norm_of_difference (mUlower, mUlowerNew);
            frobZ     = Frobenius_norm_of_difference (mZ,      mZnew);
            
            mUupper = mUupperNew;
            mUlower = mUlowerNew;
            mZ      = mZnew;
            
         } while (frobUpper > _epsilon or 
                  frobLower > _epsilon or
                  frobZ > _epsilon);
      }     
       
      if (_useMarginalisedDataForCentres) 
         mV = fcm::calculateClusterCentres(mUlower, mXlower);
      else
         mV = rfcm::calculateClusterCentres(mUupper, mXupper, wWeights);  
         
      auto mSupper = fcm_conditional::calculateClusterFuzzification(mUupper, mV, mXupper, wWeights);
      auto mSlower = fcm::calculateClusterFuzzification(mUlower, mV, mXlower);
      
      // przeksztalcenie do postaci zbiorow gaussowskich
      
      ksi::partition part;
      for (int c = 0; c < _nClusters; c++)
      {
         ksi::cluster cl; 
         for (std::size_t a = 0; a < nAttr; a++)
         {
            auto smin = std::min (mSlower[c][a], mSupper[c][a]);
            auto smax = std::max (mSlower[c][a], mSupper[c][a]);
            ksi::descriptor_interval_gaussian_subspace d (mV[c][a], smin, smax, mZ[c][a]);
            cl.addDescriptor(d);
         }
         part.addCluster(cl);
      }
       
      return part;
   }
   CATCH;
}

std::vector<std::vector<double>> ksi::rsfcm::modifyPartitionMatrix(
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mX, 
   const std::vector<std::vector<double>> & mZ, 
   const std::vector<double> & mW)
{
   try
   {  
      std::size_t nX = mX.size();
      std::vector<std::vector<double>> U (mV.size());
      
      if (nX > 0)
      {
         double exponent = 1.0 / (1.0 - _m);   
         
         std::size_t nAttr = mX[0].size();
         for (auto & u : U)
            u = std::vector<double> (nX);
         
         // distance matrix:
         Dm = std::vector<std::vector<double>> (_nClusters);
         for (int c = 0; c < _nClusters; c++)
            Dm[c] = std::vector<double> (nX);
      
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
               Dm[c][x] = distance[c] = pow(suma, exponent);
            }
         }
         
         std::vector<double> Dmsums  (nX, 0.0);
         std::vector<int>    Dmzeros (nX, 0.0);
         for (std::size_t c = 0; c < _nClusters; c++)
         {
            for (std::size_t x = 0; x < nX; x++)
            {
               if (Dm[c][x] == 0)
                  Dmzeros[x]++;
               Dmsums[x] += Dm[c][x];
            }
         }
         
         for (std::size_t c = 0; c < _nClusters; c++)
         {
            for (std::size_t x = 0; x < nX; x++)
            {
               if (Dmzeros[x] > 0)
               {
                  if (Dm[c][x] == 0.0)
                     U[c][x] = mW[x] / Dmzeros[x];
                  else
                     U[c][x] = 0.0;
               }
               else
               {
                  U[c][x] = mW[x] * Dm[c][x] / Dmsums[x];
               }
            }
         }
      }
      return U;
   }
   CATCH;
}
 
