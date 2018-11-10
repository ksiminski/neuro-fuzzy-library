/** @file */  
 
#include <cmath>
 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "../common/dataset.h"
#include "../descriptors/descriptor-interval-gaussian.h"
#include "../service/debug.h"
#include "rfcm.h"

ksi::partitioner* ksi::rfcm::clone()
{
   return new ksi::rfcm(*this);
}

ksi::rfcm::~rfcm()
{
   delete _pImputer;
   _pImputer = nullptr;
   delete _pMarginaliser;
   _pMarginaliser = nullptr;
}

ksi::rfcm::rfcm(const ksi::rfcm & wzor) : fcm_conditional(wzor)
{
   if (wzor._pImputer)
      _pImputer = wzor._pImputer->clone();
   if (wzor._pMarginaliser)
      _pMarginaliser = wzor._pMarginaliser->clone();
   
   _useMarginalisedDataForCentres = wzor._useMarginalisedDataForCentres;
}

ksi::rfcm::rfcm(ksi::rfcm && wzor) : fcm_conditional(wzor)
{
   std::swap (wzor._pImputer, _pImputer);
   std::swap (wzor._pMarginaliser, _pMarginaliser);
   std::swap (wzor._useMarginalisedDataForCentres, _useMarginalisedDataForCentres);
}

ksi::rfcm & ksi::rfcm::operator=(const ksi::rfcm & wzor)
{
   if (& wzor == this)
      return *this;
   
   ksi::fcm_conditional::operator=(wzor);
   
   if (wzor._pImputer)
      delete _pImputer;
   _pImputer = wzor._pImputer->clone();
   
   if (wzor._pMarginaliser)
      delete _pMarginaliser;
   _pMarginaliser = wzor._pMarginaliser->clone();
   
   _useMarginalisedDataForCentres = wzor._useMarginalisedDataForCentres;
      
   return *this;
}

ksi::rfcm & ksi::rfcm::operator=(ksi::rfcm && wzor)
{
   if (& wzor == this)
      return *this;
   
   ksi::fcm_conditional::operator=(wzor);
   
   std::swap (wzor._pImputer, _pImputer);
   std::swap (wzor._pMarginaliser, _pMarginaliser);
   
   std::swap (wzor._useMarginalisedDataForCentres, _useMarginalisedDataForCentres);
   
   return *this;
}

ksi::rfcm::rfcm(const ksi::data_modifier & imputer, 
                const ksi::data_modifier & marginaliser,
                const bool useMarginalisedDataForCentres
               )
{
   _pImputer = imputer.clone();
   _pMarginaliser = marginaliser.clone();
   _useMarginalisedDataForCentres = useMarginalisedDataForCentres;
}
 
ksi::partition ksi::rfcm::doPartition(const ksi::dataset & ds) 
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
      
      if (_nIterations > 0)
      {
         for (int iter = 0; iter < _nIterations; iter++)
         {
            if (_useMarginalisedDataForCentres) 
               mV = fcm::calculateClusterCentres(mUlower, mXlower);
            else
               mV = rfcm::calculateClusterCentres(mUupper, mXupper, wWeights);  
            
            // zbior zmarginalizowany klastruje FCM  
            mUlower = fcm::modifyPartitionMatrix (mV, mXlower);
            fcm::normaliseByColumns(mUlower);
            
            // zbior gorny za pomoca FCM conditional:
            mUupper = fcm_conditional::modifyPartitionMatrix (mV, mXupper, wWeights);
            fcm_conditional::normaliseByColumns(mUupper, wWeights);
         }
      }
      else if (_epsilon > 0)
      {
         double frobUpper, frobLower;
         do 
         {
            if (_useMarginalisedDataForCentres) 
               mV = fcm::calculateClusterCentres(mUlower, mXlower);
            else
               mV = rfcm::calculateClusterCentres(mUupper, mXupper, wWeights);  
            
            // zbior zmarginalizowany klastruje FCM  
            auto mUlowerNew = fcm::modifyPartitionMatrix (mV, mXlower);
            fcm::normaliseByColumns(mUlower);
            
            // zbior gorny za pomoca FCM conditional:
            auto mUupperNew = fcm_conditional::modifyPartitionMatrix (mV, mXupper, wWeights);
            fcm_conditional::normaliseByColumns(mUupper, wWeights);
            frobUpper = Frobenius_norm_of_difference (mUupper, mUupperNew);
            frobLower = Frobenius_norm_of_difference (mUlower, mUlowerNew);
            mUupper = mUupperNew;
            mUlower = mUlowerNew;
         } while (frobUpper > _epsilon or frobLower > _epsilon);
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
            ksi::descriptor_interval_gaussian d (mV[c][a], 
                                        mSlower[c][a], 
                                        mSupper[c][a]);
            cl.addDescriptor(d);
         }
         part.addCluster(cl);
      }
      
       
      return part;
   }
   CATCH;
}

bool ksi::rfcm::areClustersCalculatedWithMarginalisedData() const
{
   return _useMarginalisedDataForCentres;
}

void ksi::rfcm::setCalculateClusterCentresWithImputedData()
{
   _useMarginalisedDataForCentres = false;
}

void ksi::rfcm::setCalculateClusterCentresWithMarginalisedData()
{
   _useMarginalisedDataForCentres = true;
}


std::vector<std::vector<double>> ksi::rfcm::calculateClusterCentres(
   const std::vector<std::vector<double>> & U, 
   const std::vector<std::vector<double>> & X,
   const std::vector<double>              & w)
{
   try
   {
      std::vector<std::vector<double>> V;
      
      std::size_t nX = X.size();
      if (nX > 0)
      {
         std::size_t nAttr = X[0].size();
         for (int c = 0; c < _nClusters; c++)
         {
            std::vector<double> suma_x (nAttr, 0.0);
            double suma_u_ci_m = 0.0;
            
            for (std::size_t i = 0; i < nX; i++)
            {
               double u_ci_m_w = pow(U[c][i], _m) * w[i];
               suma_u_ci_m += u_ci_m_w;
               
               for (std::size_t a = 0; a < nAttr; a++)
                  suma_x[a] += (u_ci_m_w * X[i][a]);
            }
            
            std::vector<double> v (nAttr);
            for (std::size_t a = 0; a < nAttr; a++)
               v[a] = suma_x[a] / suma_u_ci_m;
            
            V.push_back(v);
         }
      }
      return V;
   }
   CATCH;
}
