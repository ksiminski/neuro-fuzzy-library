/** @file */  
 
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
 
#include "../service/debug.h"
#include "partitioner.h"
#include "partition.h"
#include "../common/dataset.h"
#include "../owas/owa.h"
#include "../owas/uowa.h"
#include "../descriptors/descriptor-interval-gaussian.h"
#include "../service/debug.h"
#include "rfcom.h"


std::string ksi::rfcom::getAbbreviation() const
{
   return std::string ("rfcom");
}


ksi::partitioner* ksi::rfcom::clone() const
{
   return new ksi::rfcom(*this);
}

ksi::rfcom::~rfcom()
{
    
}

ksi::rfcom::rfcom(const ksi::rfcom & wzor) : rfcm(wzor), fcom(wzor) 
{
    
}

ksi::rfcom::rfcom(ksi::rfcom && wzor) : rfcm(wzor), fcom(wzor)
{
   
}

ksi::rfcom & ksi::rfcom::operator=(const ksi::rfcom & wzor)
{
   if (& wzor == this)
      return *this;
   
   ksi::rfcm::operator=(wzor);
   ksi::fcom::operator=(wzor);
   
   return *this;
}

ksi::rfcom & ksi::rfcom::operator=(ksi::rfcom && wzor)
{
   if (& wzor == this)
      return *this;
   
   ksi::rfcm::operator=(wzor);
   ksi::fcom::operator=(wzor);
   
   return *this;
}

ksi::rfcom::rfcom(const ksi::data_modifier & imputer, 
                  const ksi::data_modifier & marginaliser, 
                  const ksi::dissimilarity & dis, 
                  const ksi::owa & owa, 
                  const bool useMarginalisedDataForCentres)
  : rfcm (imputer, marginaliser, useMarginalisedDataForCentres), fcom (dis, owa)
{
   
}

 
ksi::partition ksi::rfcom::doPartition(const ksi::dataset & ds) 
{
   try
   {
      if (not _pMarginaliser)
         throw std::string ("marginalised object not set");
      if (not _pImputer)
         throw std::string ("imputer object not set");
      if (_nClusters < 1)
         throw std::string ("unknown number of clusters");
      if (_epsilon < 0)
         throw std::string ("unknown minimal epsilon for Frobenius norm");
      if (not pDissimilarity)
         throw std::string ("no dissimilarity measure object");
      if (not pOwa)
         throw std::string ("no ordered weighted averaging object");
      
      // all seems correctly set :-)
      
      const auto pOriginalOwa = pOwa;
      ksi::uowa uniformOWA;
      
      ksi::dataset lowerDataset (ds);   // marginalised
      ksi::dataset upperDataset (ds);   // imputed
      
      _pMarginaliser->modify(lowerDataset);
      if (lowerDataset.getNumberOfData() == 0) // empty lower set 
         return ksi::partition();
      
      _pImputer->modify(upperDataset);
      
      std::size_t nAttr = ds.getNumberOfAttributes();
      std::size_t nXLower = lowerDataset.getNumberOfData();
      std::size_t nXUpper = upperDataset.getNumberOfData();
      
      auto mXLower = lowerDataset.getMatrix();
      auto mXUpper = upperDataset.getMatrix();
      
      // weights in upper data set:
      
      std::vector<double> wWeightsUpper (nXUpper);
      for (std::size_t x = 0; x < nXUpper; x++)
         wWeightsUpper[x] = upperDataset.getDatum(x)->getWeight();
      
      std::vector<std::vector<double>> mV, mVnext;
      
      mV = std::vector<std::vector<double>> (_nClusters);
      
      std::default_random_engine silnik;
      silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
      std::uniform_int_distribution<std::size_t> rozklad (0, nXLower - 1);
    
      // initialize cluster centres at random
      for (auto & r : mV)
         r = mXLower[rozklad(silnik)];
      
      typicalitiesLower = std::vector<std::vector<double>> (_nClusters);
      for (auto & row : typicalitiesLower)
         row = std::vector<double> (nXLower, 1.0);
      
      typicalitiesUpper = std::vector<std::vector<double>> (_nClusters);
      for (auto & row : typicalitiesUpper)
         row = std::vector<double> (nXUpper, 1.0);
      
      // set typicalities to 1
      globalTypicalitiesLower =  std::vector<double> (nXLower, 1.0);
      globalTypicalitiesUpper =  std::vector<double> (nXUpper, 1.0);
      
      // itinialize typicalities in data items with 1
      for (std::size_t x = 0; x < nXLower; x++)
         lowerDataset.getDatumNonConst(x)->setTypicality(1.0);
      for (std::size_t x = 0; x < nXUpper; x++)
         upperDataset.getDatumNonConst(x)->setTypicality(1.0);
      
      int iter = 0;
      double frob = 0;
      do 
      {
         // calculate partition matrices:
          
         // The method fcom::modifyPartitionMatrix modifies betas and fs, so
         // these variables has to be set to lower values here:
         mULower = fcom::modifyPartitionMatrix(mV, mXLower, typicalitiesLower, globalTypicalitiesLower); 
         
         // ... and set to upper values here.
         mUUpper = modifyPartitionMatrix(mV, mXUpper, typicalitiesUpper, globalTypicalitiesUpper, wWeightsUpper);  
         
         // calculate cluster centres:
         // If j <= 4 then use uniform weighting UOWA, else either PLOWA, SOWA, or UOWA
         if (iter < NUMBER_OF_ITERATIONS_WITHOUT_WEIGHTING)
            pOwa = & uniformOWA;
         else
            pOwa = pOriginalOwa;
         
         auto mVnextLower = fcom::calculateClusterCentres(mXLower, mULower, typicalitiesLower);
         auto mVnextUpper = calculateClusterCentres(mXUpper, mUUpper, typicalitiesUpper, wWeightsUpper); 
         
         if (_useMarginalisedDataForCentres)
            mVnext = mVnextLower;
         else 
            mVnext = mVnextUpper;
         
         // update global typicality
         for (int x = 0; x < nXLower; x++)
         {
            double f = 0.0;
            for (int c = 0; c < _nClusters; c++)
               f = std::max(f, typicalitiesLower[c][x]);
            globalTypicalitiesLower[x] = f;
         }
         for (int x = 0; x < nXUpper; x++)
         {
            double f = 0.0;
            for (int c = 0; c < _nClusters; c++)
               f = std::max(f, typicalitiesUpper[c][x]);
            globalTypicalitiesUpper[x] = f;
         }
         
         // step 5: if Frobenius norm ||V(j + 1) - V(j)|| > ksi, then j++ 
         //         and go to step 2 else stop
         frob = Frobenius_norm_of_difference(mV, mVnext);
         mV = mVnext;
         iter++;
         
         
      } while (frob > _epsilon and iter < 100); 

      // The original pointer has to be reset:
      pOwa = pOriginalOwa;
      
      // set elaborated typicalities into data set:
      for (std::size_t x = 0; x < nXLower; x++)
         lowerDataset.getDatumNonConst(x)->setTypicality(globalTypicalitiesLower[x]);
      for (std::size_t x = 0; x < nXUpper; x++)
         upperDataset.getDatumNonConst(x)->setTypicality(globalTypicalitiesUpper[x]);
      
      // elaborate descriptors of data partition:
      ksi::partition part;
      
      // fuzzyfications of clusters:
      auto mSLower = fcom::calculateClusterFuzzification(mULower, mV, typicalitiesLower, mXLower); 
      auto mSUpper = rfcom::calculateClusterFuzzification(mUUpper, mV, typicalitiesUpper, mXUpper, wWeightsUpper); 
      
      for (int c = 0; c < _nClusters; c++)
      {
         ksi::cluster cl; 
         for (std::size_t a = 0; a < nAttr; a++)
         {
            ksi::descriptor_interval_gaussian d (mV[c][a],  std::min(mSLower[c][a], mSUpper[c][a]), std::max(mSLower[c][a], mSUpper[c][a]) );
            cl.addDescriptor(d);
         }
         part.addCluster(cl);
      }
      
      // The last step: elaborate typicalities of original data items:
      auto nX = ds.getNumberOfData(); 
      for (std::size_t x = 0; x < nX; x++)
      {
         ds.getDatumNonConst(x)->setTypicality(0.0);
      }
      
      for (std::size_t x = 0; x < nXLower; x++)
      {
         auto typicality = lowerDataset.getDatum(x)->getTypicality();
         auto id         = lowerDataset.getDatum(x)->getID();
         
         auto ds_typicality = ds.getDatum(id)->getTypicality();
         ds.getDatumNonConst(id)->setTypicality(std::max(typicality, ds_typicality));
      }
      
      for (std::size_t x = 0; x < nXUpper; x++)
      {
         auto typicality = upperDataset.getDatum(x)->getTypicality();
         auto id         = upperDataset.getDatum(x)->getID();
         auto id_incomplete = upperDataset.getDatum(x)->getIDincomplete();
         
         if (id_incomplete < 0)           
         {
            auto ds_typicality = ds.getDatum(id)->getTypicality();
            ds.getDatumNonConst(id)->setTypicality(std::max(typicality, ds_typicality));
         }
         else // imputed tuple, find parent (original tuple)
         {
            auto ds_typicality = ds.getDatum(id_incomplete)->getTypicality();
            ds.getDatumNonConst(id_incomplete)->setTypicality(std::max(typicality, ds_typicality));
         }
      }
      return part;
   }
   CATCH;
}


std::vector< std::vector<double>> ksi::rfcom::calculateClusterFuzzification(
   const std::vector< std::vector< double > >& mU, 
   const std::vector< std::vector< double > >& mV, 
   const std::vector< std::vector< double > >& mB, 
   const std::vector< std::vector< double > >& mX, 
   const std::vector< double >& wW)
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
            double sumBetaUm = 0.0;
            std::vector<double> sumUXV (nAttr, 0.0);
            for (std::size_t x = 0; x < nX; x++)
            {
               double betaum = wW[x] * mB[c][x] * pow(mU[c][x], _m);
               //double um = mU[c][x];
               sumBetaUm += betaum;
               
               for (std::size_t a = 0; a < nAttr; a++)
               {
                  double diff = mX[x][a] - mV[c][a];
                  auto distance = (diff * diff * pDissimilarity->dis(diff));
                  sumUXV[a] += betaum * distance * distance;
               }
            }
            
            for (std::size_t a = 0; a < nAttr; a++)
               mS[c][a] = sqrt (sumUXV[a] / sumBetaUm);
         }
         return mS;
      }
      return std::vector< std::vector<double>>();
   }
   CATCH;
}

std::vector<std::vector<double>> ksi::rfcom::modifyPartitionMatrix(
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mX,
   const std::vector<std::vector<double>> & betas,
   const std::vector<double> & fs,
   const std::vector<double> & wW)
{
   try
   {
      auto nC = mV.size(); // number of clusters;
      auto mU = fcom::modifyPartitionMatrix(mV, mX, betas, fs);
      auto nX = wW.size(); // number of data items
      if (nX != mX.size())
      {
         std::stringstream ss;
         ss << "Number of data items (" << mX.size() << ") and number of weights ("
            << nX << ") do not match!";
         
         throw ss.str();
      }
      
      for (std::size_t x = 0; x < nX; x++)
      {
         auto weight = wW[x];
         for (std::size_t c = 0; c < nC; c++)
            mU[c][x] /= weight;
      }
      
      return mU;
   }
   CATCH;
}

/*
std::vector<std::vector<double>> ksi::rfcom::initializeClusterCentres(
   const std::vector<std::vector<double>> & mX, 
   const int nAttributes, 
   const int nClusters)
{
   try
   {
      const double MEAN = 0.0;
      const double DEV  = 0.1;
      
      
      std::vector<double> sums (nAttributes, 0.0);
      std::vector<double> maxi (mX[0]); // maximal values of attributes
      std::vector<double> mini (mX[0]); // minimal values of attributes 
      for (const auto & x : mX)
      {
         for (int a = 0; a < nAttributes; a++)
         {
            sums[a] += x[a];
            if (maxi[a] < x[a])
               maxi[a] = x[a];
            if (mini[a] > x[a])
               mini[a] = x[a];
         }
      }
      
      std::vector<double> amplitudes (nAttributes);
      for (int a = 0; a < nAttributes; a++)
         amplitudes[a] = maxi[a] - mini[a];
      
      auto means (sums);
      auto nX = mX.size();
      for (int a = 0; a < nAttributes; a++)
         means[a] /= nX;
      
      
      
      // means calculated
      // now random deviation:
      
      std::default_random_engine silnik;
      silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
      std::normal_distribution<double> rozklad (MEAN, DEV);
      
      std::vector<std::vector<double>> mV;
      for (int c = 0; c < nClusters; c++)
      {
         std::vector<double> cluster (nAttributes);
         for (int a = 0; a < nAttributes; a++)
            cluster[a] = means[a] + rozklad (silnik) * amplitudes[a];
         mV.push_back(cluster);
      }
      
//       debug("mV");
//       for (const auto & w : mV)
//       {
//          for (const auto & d : w)
//             std::cout << d << " ";
//          std::cout << std::endl;
//       }
      
      return mV;
   }
   CATCH;
}
*/


std::vector<std::vector<double>> ksi::rfcom::calculateClusterCentres(
   const std::vector<std::vector<double>> & mX,
   const std::vector<std::vector<double>> & mU,
   std::vector<std::vector<double>> & betas,
   const std::vector<double> & wWeights)
{
   try 
   {
      auto nX = mX.size();
      auto nAttr = mX[0].size();
         
      // step 1: initialize  mV
      auto mV = initializeClusterCentres(mX, nAttr, _nClusters);
      
      ksi::uowa Uowa;
      ksi::owa * pOriginalOwa = pOwa;
      
      // for each cluster:
      for (int c = 0; c < _nClusters; c++)
      {
         double frob = 0;
         std::vector<double> alphas (nX, 1.0);
         
         int iter = 0;
         do 
         {
            alphas = std::vector<double> (nX, 1.0);
            std::vector<double> newCentre (nAttr);
            for (int a = 0; a < nAttr; a++)
            {
               // step 2: calculate residuals 
               std::vector<residual> residuals; 
               for (std::size_t x = 0; x < nX; x++)
               {
                  residual r;
                  r.pre_sort_index = x;
                  r.value = fabs (mX[x][a] - mV[c][a]);
                  residuals.push_back(r);
               }
               
               // step 3: rank-order the residuals:
               // sortuje rezyduale:
               std::sort(residuals.begin(), residuals.end(),
                  [] (const residual & a, const residual & b) 
                  {
                     return a.value < b.value;
                  }
               );
               
               for (std::size_t x = 0; x < nX; x++)
                  residuals[x].post_sort_index = x;
               
               std::sort(residuals.begin(), residuals.end(),
                  [] (const residual & a, const residual & b) 
                  {
                     return a.pre_sort_index < b.pre_sort_index;
                  }
               );
               
               // step 4: calculate alphas using (18) or (19) or uniform weighting:
               if (iter < NUMBER_OF_ITERATIONS_WITHOUT_WEIGHTING)
                  pOwa = & Uowa;
               else 
                  pOwa = pOriginalOwa;
               
               // step 5: calculate alphas for all clusters:
               for (std::size_t x = 0; x < nX; x++)
                  alphas[x] *= pOwa->value(residuals[x].post_sort_index + 1);
            }
            // step 6: update the prototype for the ath attributes with (23):
            std::vector<double> licznik   (nAttr, 0.0),
                                mianownik (nAttr, 0.0);
            for (std::size_t x = 0; x < nX; x++)
            {
               auto weight = wWeights[x];
               
               auto um = pow (mU[c][x], _m);
               if (std::isnan(mU[c][x]))
                  debug(mU[c][x]);
               for (int a = 0; a < nAttr; a++)
               {
                  auto h = pDissimilarity->dis(mX[x][a] - mV[c][a]);
                  auto alfa = alphas[x];
                  
                  auto common = weight * alfa * um * h;
                  licznik[a]   += (common * mX[x][a]);
                  mianownik[a] += common;
               }
            }
            for (int a = 0; a < nAttr; a++)
               newCentre[a] = licznik[a] / mianownik[a];
            
            frob = Frobenius_norm_of_difference(mV[c], newCentre);
            mV[c] = newCentre;
            
            iter++;
         }
         //while (frob > _epsilon);
         while (frob > _epsilon and iter < 100); 
         
         betas[c] = alphas;
         
         // reset original pointer to OWA object
         pOwa = pOriginalOwa;
      }
      return mV;
   }
   CATCH;
}
