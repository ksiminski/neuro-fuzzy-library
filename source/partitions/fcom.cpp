/** @file */ 

#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>

#include "../common/dataset.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../owas/owa.h"
#include "../owas/uowa.h"
#include "partitioner.h"
#include "partition.h"
#include "fcom.h"
#include "../service/debug.h"
#include "../service/exception.h"

std::string ksi::fcom::getAbbreviation() const
{
    return std::string ("fcom");   
}

 
ksi::partitioner * ksi::fcom::clone() const
{
   auto p = new ksi::fcom(*this);
   
   return p;
}

ksi::fcom::fcom(const int number_of_clusters, double frobenius_epsilon, const ksi::dissimilarity& dis, const ksi::owa& owa)  
{
    _nClusters = number_of_clusters;
//     debug(_nClusters);
    _epsilon = frobenius_epsilon;
    pDissimilarity = dis.clone();
    pOwa = owa.clone();
}


ksi::fcom::fcom(const ksi::fcom& wzor) : /*fcm_T<double>(wzor),*/ fcm (wzor)
{
   if (wzor.pDissimilarity)
      pDissimilarity = wzor.pDissimilarity->clone();
   else
      pDissimilarity = nullptr;
   
   if (wzor.pOwa)
      pOwa = wzor.pOwa->clone();
   else 
      pOwa = nullptr; 
   
   this->betas = wzor.betas;
   this->fs = wzor.fs;  
   
}

ksi::fcom::fcom (ksi::fcom && wzor) : fcm (wzor)
{
   std::swap (pDissimilarity, wzor.pDissimilarity);
   std::swap (pOwa, wzor.pOwa);
   std::swap(this->betas, wzor.betas);
   std::swap(this->fs, wzor.fs);  

}

ksi::fcom & ksi::fcom::operator=(const ksi::fcom & wzor) 
{
   if (this == &wzor)
      return *this;
   
   ksi::fcm::operator=(wzor);
   
   if (pDissimilarity)
      delete pDissimilarity;
   if (wzor.pDissimilarity)
      pDissimilarity = wzor.pDissimilarity->clone();
   else
      pDissimilarity = nullptr;
   
   
   if (pOwa)
      delete pOwa;
   if (wzor.pOwa)
      pOwa = wzor.pOwa->clone();
   else 
      pOwa = nullptr; 
   
   
   this->betas = wzor.betas;
   this->fs = wzor.fs;   
   
   return *this;
}

ksi::fcom & ksi::fcom::operator=(ksi::fcom && wzor)
{
   if (this == &wzor)
      return *this;
   
   ksi::fcm::operator=(wzor);
   
   std::swap (pDissimilarity, wzor.pDissimilarity);
   std::swap (pOwa, wzor.pOwa);
   std::swap(this->betas, wzor.betas);
   std::swap(this->fs, wzor.fs);  
   
   return *this;
}


ksi::fcom::fcom()
{
   pDissimilarity = nullptr;
   pOwa = nullptr; 
   _epsilon = -1;

}

ksi::fcom::~fcom()
{
   if (pDissimilarity)
      delete pDissimilarity;
   pDissimilarity = nullptr;
   
   if (pOwa)
      delete pOwa;
   pOwa = nullptr;
}


ksi::fcom::fcom (const ksi::dissimilarity & dis, const ksi::owa & Owa) : fcom ()
{
   pDissimilarity = dis.clone();
   pOwa = Owa.clone();
}


std::vector< std::vector<double>> ksi::fcom::initializeClusterCentres(
   const std::vector< std::vector<double>> & mX, 
   const int nAttributes,
   const int nClusters)
{
   try
   {
      std::vector<std::vector<double>> mV (_nClusters);
   
      for (auto & r : mV)
         r = std::vector<double> (nAttributes, 0.0);
      
      return mV;
   }
   CATCH;
}


std::vector<std::vector<double>> ksi::fcom::calculateClusterCentres(
   const std::vector<std::vector<double>> & mX,
   const std::vector<std::vector<double>> & mU,
   std::vector<std::vector<double>> & betas)
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
               
               /*
               // step 4: calculate alphas using (18) or (19) or uniform weighting:
               if (iter < NUMBER_OF_ITERATIONS_WITHOUT_WEIGHTING)
                  pOwa = & Uowa;
               else 
                  pOwa = pOriginalOwa;
               */
               // step 5: calculate alphas for all clusters:
               for (std::size_t x = 0; x < nX; x++)
               {
                   alphas[x] *= pOwa->value(residuals[x].post_sort_index + 1);
                   
//                    if (pOwa == pOriginalOwa)
//                    {
//                       debug(pOwa->print_owa_parameters());
//                       debug(alphas[x]);
//                       debug(pOwa->value(residuals[x].post_sort_index + 1));
//                    }
                   
                  // debug(residuals[x].post_sort_index + 1);
                  // debug(pOwa->value(residuals[x].post_sort_index + 1));
               }
            }
            // step 6: update the prototype for the ath attributes with (23):
            std::vector<double> licznik   (nAttr, 0.0),
                                mianownik (nAttr, 0.0);

            std::vector<bool> modifikowane (nAttr, false);  
                                
            for (std::size_t x = 0; x < nX; x++)
            {
               auto um = pow (mU[c][x], _m);
               
               if (std::isnan(mU[c][x]))
                  debug(mU[c][x]);   
               
               for (int a = 0; a < nAttr; a++)
               {
                  auto h = pDissimilarity->dis(mX[x][a] - mV[c][a]);
                  auto alfa = alphas[x];
                  auto common = alfa * um * h;

                  licznik[a]   += (common * mX[x][a]);
                  mianownik[a] +=  common;
               }
            }
            
            
            for (int a = 0; a < nAttr; a++)
            {
               if (mianownik[a] == 0)
               {
                   std::stringstream ss;
                   ss << mianownik << std::endl;
                   ss << modifikowane << std::endl;
                   throw ksi::exception (ss.str());
               }
               newCentre[a] = licznik[a] / mianownik[a];
            }
            frob = Frobenius_norm_of_difference(mV[c], newCentre);
            mV[c] = newCentre;
            
            iter++;
            
         }
         while (frob > _epsilon and iter < 100); 
         
         betas[c] = alphas;
         
         // reset original pointer to OWA object
         pOwa = pOriginalOwa;
      }
      return mV;
   }
   CATCH;
}
 

std::vector<std::vector<double>> ksi::fcom::modifyPartitionMatrix(
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mX,
   const std::vector<std::vector<double>> & betas,
   const std::vector<double> & fs)
{
   try
   {
      const double EPSILON = 1e-9;
      
      auto nX = mX.size();
      auto nAttr = mX[0].size();
      double expo = 1.0 / (1.0 - _m);
         
      mU = std::vector<std::vector<double>> (_nClusters);
      for (auto & u : mU)
         u = std::vector<double> (nX);
      
      // wzor (14) 
      for (int x = 0; x < nX; x++)
      {
         double suma = 0.0;
         std::vector<double> distances (_nClusters);
         for (int k = 0; k < _nClusters; k++)
         {
            double distance = 0;
            for (int a = 0; a < nAttr; a++)
            {
               double diff = mX[x][a] - mV[k][a];
               distance += (diff * diff * pDissimilarity->dis(diff));
            }
         
            // Jezeli przyklad lezy dokladnie (z dokladnoscia do epsilona)
            // w srodku klastra, to jest problem numeryczny.
            if (fabs(distance) < EPSILON)
            {
               //distances.push_back(-1.0); // oznaczam, ze przyklad lezy w srodku klastra
                distances[k] = -1.0;
                suma = -1.0;  // suma nie bedzie potrzebna
            }
            else if (suma != -1.0) // zaden z przykladow nie lezy w srodku klastra
            {         
               double potega = pow(distance, expo);
               //distances.push_back(potega);
               distances[k] = potega;
               suma += (betas[k][x] * potega);
            }
         } 
         
         int ileZer = 0;
         for (int k = 0; k < _nClusters; k++)
            if (distances[k] == -1.0)
               ileZer++;
            
         for (int k = 0; k < _nClusters; k++)
         {
            if (suma == 0.0)
               mU[k][x] = 0.0;  
            else if (suma == -1.0) // ktorys z przykladow lezy w srodku klastra
            {
               if (distances[k] == -1.0) // ... ten wlasnie!
                  mU[k][x] = 1.0 / ileZer;
               else                      // ... a ten nie!
                  mU[k][x] = 0;
            }
            else 
            {
               mU[k][x] = fs[x] * distances[k] / suma;
//                if (suma == 0.0)
//                    throw ksi::exception ("suma == " + std::to_string(suma));
            }
         }
      }
      return mU;
   }
   CATCH;
}

 
void ksi::fcom::setNumberOfIterations(int i)
{
   try
   {
      throw std::string ("For this clustering algorithm do not use the method "
                         "ksi::fcom::setNumberOfIterations.");
   }
   CATCH;
}
 

 
ksi::partition ksi::fcom::doPartition(const ksi::dataset & ds)
{
   try
   {
//       debug(_nClusters); 
       
      const int MAXITER = 100; 
      
      if (_nClusters < 1)
         throw std::string ("unknown number of clusters");
      //if (_nIterations < 1)
      //   throw std::string ("unknown number of clustering iterations");
      if (_epsilon < 0)
         throw std::string ("unknown minimal epsilon for Frobenius norm");
      if (pDissimilarity == nullptr)
         throw std::string ("no dissimilarity measure object");
      if (pOwa == nullptr)
         throw std::string ("no ordered weighted averaging object");
      
      if (not pOwa->are_parameters_valid())
      {
          std::stringstream ss;
          ss << "invalid OWA parameters: " << pOwa->print_owa_parameters();
          throw ksi::exception(ss.str());
      }
      
      auto mX = ds.getMatrix();
      std::size_t nAttr = ds.getNumberOfAttributes();
      std::size_t nX    = ds.getNumberOfData();
      
      pOwa->set_number_of_data_items(nX);
      const auto pOriginalOwa = pOwa;
      ksi::uowa uniformOWA;
      uniformOWA.set_number_of_data_items(nX);
      
      
      std::vector<std::vector<double>> mV, mVnext;
      
      // Leski's algorithm 4:
      
      // step 1: fix c (number of clusters), m
      //         Choose dissimilarity measure.
      //         Initialize mV
      
      mV = std::vector<std::vector<double>> (_nClusters);
      //for (auto & row : mV)
      //   row = std::vector<double> (nAttr, 0.0);
      
      std::default_random_engine silnik;
      silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
      std::uniform_int_distribution<std::size_t> rozklad (0, nX - 1);
      
      // initialize cluster centres at random
      for (auto & r : mV)
         r = mX[rozklad(silnik)];
      
      mVnext = mV;
      
      //         beta_ik = 1
      betas = std::vector<std::vector<double>> (_nClusters);
      for (auto & row : betas)
         row = std::vector<double> (nX, 1.0);
      
      //         f_k = 1
      fs =  std::vector<double> (nX, 1.0);
         
      // itinialize typicalities with 1
      for (std::size_t x = 0; x < nX; x++)
         ds.getDatumNonConst(x)->setTypicality(1.0);

      //         set iteration index j = 1
      int iter = 0;
      double frob = 0;
      do 
      {
         // step 2: Calculate the fuzzy partition matrix U(j) 
         //         for j-th iteration using (14)
         mU = modifyPartitionMatrix(mV, mX, betas, fs);
         
         // step 3: Update the centres for j_th iteration V(j) using 
         //         U(j) and Algorithm 3
         
         // If j <= 4 then use uniform weighting UOWA, else either (18) or (19) or UOWA
         if (iter < NUMBER_OF_ITERATIONS_WITHOUT_WEIGHTING)
            pOwa = & uniformOWA;
         else
            pOwa = pOriginalOwa;
      
         mVnext = calculateClusterCentres(mX, mU, betas);
      
         // step 4: Update overall typicality parameters f_k using (13):
         for (int x = 0; x < nX; x++)
         {
            double f = 0.0;
            for (int c = 0; c < _nClusters; c++)
               f = std::max(f, betas[c][x]);
            fs[x] = f;
         }
         
      
         // step 5: if Frobenius norm ||V(j + 1) - V(j)|| > ksi, then j++ 
         //         and go to step 2 else stop
         frob = Frobenius_norm_of_difference(mV, mVnext);
         
         mV = mVnext;
         iter++; 
//          debug(iter);
         
      } while ( ( frob > _epsilon or iter < NUMBER_OF_ITERATIONS_WITHOUT_WEIGHTING)  and iter < MAXITER);
//       debug(iter);
//       debug(frob);
//       debug(_epsilon);
      
      if (iter >= MAXITER)
          debug("max iteration number reached");
      
      // The original pointer has to be reset:
      pOwa = pOriginalOwa;
      
      // trzeba jeszcze wpisac typowosci do danych:
      for (std::size_t x = 0; x < nX; x++)
      {
         ds.getDatumNonConst(x)->setTypicality(fs[x]);
      }
      
      // przeksztalcenie do postaci zbiorow gaussowskich
      ksi::partition part;
      
      // wyznaczenie rozmycia klastra
     // auto mS = calculateClusterFuzzification(mU, mV, betas, mX);
      auto mS = calculateClusterFuzzification(mU, mV, fs, mX);
      
      
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

std::vector< std::vector<double>> ksi::fcom::calculateClusterFuzzification(
   const std::vector<std::vector<double>> & mU,    
   const std::vector<std::vector<double>> & mV,
   const std::vector<std::vector<double>> & betas,
   const std::vector<std::vector<double>> & mX)
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
            double betaum = betas[c][x] * pow(mU[c][x], _m);
            sumBetaUm += betaum;
            
            for (std::size_t a = 0; a < nAttr; a++)
            {
               double diff = mX[x][a] - mV[c][a];
               auto distance = (diff * diff * pDissimilarity->dis(diff));
               sumUXV[a] += betaum * distance;
            }
         }
         
         for (std::size_t a = 0; a < nAttr; a++)
            mS[c][a] = sqrt (sumUXV[a] / sumBetaUm);
      }
      return mS;
   }
   return std::vector< std::vector<double>>();
}


std::vector<std::vector<double>> ksi::fcom::calculateClusterFuzzification(
         const std::vector< std::vector<double>> & mU,
         const std::vector< std::vector<double>> & mV, 
         const std::vector< double> & typicalities,
         const std::vector< std::vector<double>> & mX)
{
   auto mS (mV);
   if (mX.size() > 0)
   {
      std::size_t nX = mX.size();
      std::size_t nAttr = mX[0].size();
      
      for (int c = 0; c < _nClusters; c++)
      {
         double sumTypicalityUm = 0.0;
         std::vector<double> sumUXV (nAttr, 0.0);
         for (std::size_t x = 0; x < nX; x++)
         {
            double typicality_um = typicalities[x] * pow(mU[c][x], _m);
            sumTypicalityUm += typicality_um;
            
            for (std::size_t a = 0; a < nAttr; a++)
            {
               double diff = mX[x][a] - mV[c][a];
               auto distance = (diff * diff);
               sumUXV[a] += typicality_um * distance;
            }
         }
         
         for (std::size_t a = 0; a < nAttr; a++)
            mS[c][a] = sqrt (sumUXV[a] / sumTypicalityUm);
      }
      return mS;
   }
   return std::vector< std::vector<double>>();
}
