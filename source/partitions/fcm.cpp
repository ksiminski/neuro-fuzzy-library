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
#include "../service/debug.h"


 
ksi::partitioner * ksi::fcm::clone()
{
   auto p = new ksi::fcm(*this);
   
   return p;
}

ksi::fcm::fcm(const ksi::fcm& wzor) : partitioner(wzor)
{
   _m = wzor._m;
   _nClusters = wzor._nClusters;
   _nIterations = wzor._nIterations;
   _epsilon = wzor._epsilon;
}

ksi::fcm& ksi::fcm::operator=(const ksi::fcm & wzor)
{
   if (this == &wzor)
      return *this;
   
   _m = wzor._m;
   _nClusters = wzor._nClusters;
   _nIterations = wzor._nIterations;   
   _epsilon = wzor._epsilon;
   
   return *this;
}

ksi::fcm::fcm()
{

}



ksi::fcm::~fcm()
{
}

std::vector<std::vector<double>> ksi::fcm::calculateClusterCentres(
   const std::vector<std::vector<double>> & U, 
   const std::vector<std::vector<double>> & X)
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
               double u_ci_m = pow(U[c][i], _m);
               suma_u_ci_m += u_ci_m;
               
               for (std::size_t a = 0; a < nAttr; a++)
                  suma_x[a] += (u_ci_m * X[i][a]);
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

void ksi::fcm::randomise(std::vector<std::vector<double>> & m)
{
   try
   {
      auto czas = std::chrono::system_clock::now();
      auto interwal = czas.time_since_epoch();
      std::default_random_engine silnik;
      std::uniform_real_distribution <double> rozklad(0, 1);
      silnik.seed(interwal.count());
      
      for (auto & wiersz : m)
         for (auto & liczba : wiersz)
            liczba = rozklad(silnik);
   }
   CATCH;
}

void ksi::fcm::normaliseByColumns(std::vector<std::vector<double>> & m)
{
   try
   {
      if (m.size() > 0)
      {
         std::size_t nAttr = m[0].size();
         std::size_t nRows = m.size();
         
         for (std::size_t a = 0; a < nAttr; a++)
         {
            double suma = 0.0;
            for (std::size_t r = 0; r < nRows; r++)
               suma += m[r][a];
            for (std::size_t r = 0; r < nRows; r++)
               m[r][a] /= suma;
         }
      }
   }
   CATCH;
}

void ksi::fcm::normaliseByRows(std::vector<std::vector<double>> & m)
{
   try
   {
      if (m.size() > 0)
      {
         std::size_t nCols = m[0].size();
         std::size_t nRows = m.size();
         
         for (std::size_t r = 0; r < nRows; r++)
         {
            double suma = 0.0;
            for (std::size_t a = 0; a < nCols; a++)   
               suma += m[r][a];
            for (std::size_t a = 0; a < nCols; a++)
               m[r][a] /= suma;
         }
      }
   }
   CATCH;
}

std::vector<std::vector<double>> ksi::fcm::modifyPartitionMatrix(
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mX)
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
                     U[c][x] = 1.0 / Dmzeros[x];
                  else
                     U[c][x] = 0.0;
               }
               else
               {
                  U[c][x] = Dm[c][x] / Dmsums[x];
               }
            }
         }
      }
      return U;
   }
   CATCH;
}

double ksi::fcm::calculateDistance(
   const std::vector<double> & x, 
   const std::vector<double> & y)
{
   try
   {
      if (x.size() != y.size())
      {
         try 
         {      
            std::stringstream ss;
            ss << "The lengths of vectors do not match: " 
               << x.size() << " != " << y.size() << std::endl;
            throw ss.str();
         }
         CATCH;
      }
      else
      {
         std::size_t size = x.size();
         double sum = 0.0;
         for (size_t i = 0; i < size; i++)
         {
            double roznica = x[i] - y[i];
            sum += (roznica * roznica);
         }
         return sqrt(sum);
      }
   }
   CATCH;
}


std::vector< std::vector<double>> ksi::fcm::calculateClusterFuzzification(
   const std::vector<std::vector<double>> & mU,    
   const std::vector<std::vector<double>> & mV,
   const std::vector<std::vector<double>> & mX)
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
               double um = pow(mU[c][x], _m);
               //double um = mU[c][x];
               sumU += um;
               
               for (std::size_t a = 0; a < nAttr; a++)
               {
                  double roznica = mX[x][a] - mV[c][a];
                  sumUXV[a] += um * roznica * roznica;
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

/*
std::vector< std::vector<double>> ksi::fcm::calculateClusterFuzzification(
   const std::vector<std::vector<double>> & mU,    
   const std::vector<std::vector<double>> & mV,
   const std::vector<std::vector<double>> & mX)
{
   struct el
   {
      double wartosc = 0;
      double blad = 0;
      bool policzone = false;
      
      bool operator < (const el & e)
      {
         return wartosc < e.wartosc;
      }
   };
   
   const int ITERATIONS = 100;
   debug(_m);
   auto mS (mV);
   if (mX.size() > 0)
   {
      std::size_t nX = mX.size();
      std::size_t nAttr = mX[0].size();
      
      for (int c = 0; c < _nClusters; c++)
      {
         
         for (std::size_t a = 0; a < nAttr; a++)
         {
            std::vector<el> sigmata  { {  0.1, 0, false},
                                       {  2,   0, false},
                                       { 10,   0, false},
                                       { 50,   0, false} };
            for (int iter = 0; iter < ITERATIONS; iter++)
            {
               // dla kazdej sigmy
               for (auto & element : sigmata)
               {
                  if (not element.policzone)
                  {
                     double sigma = element.wartosc;
                     double roznica = 0.0;
                     double suma = 0.0;
                     for (std::size_t x = 0; x < nX; x++)
                     {
                        suma += pow(mU[c][x] -  exp(- pow(mX[x][a] - mV[c][a], 2.0) / (2 * sigma * sigma))  , 2.0);
                     }
                     element.blad = suma;
                  }
               }
               std::sort(sigmata.begin(), sigmata.end());
               
               if (sigmata[1].blad < sigmata[2].blad)
                  // usuwam sigmata[3];
                  sigmata.pop_back();
               else
                  // usuwam pierwszy:
                  sigmata.erase(sigmata.begin());
               // sprawdzam roznice bledow:
               if (sigmata[0].blad - sigmata[1].blad > sigmata[2].blad - sigmata[1].blad)
                  sigmata.push_back ({ (sigmata[0].wartosc + sigmata[1].wartosc ) / 2.0, 0, false });
               else 
                  sigmata.push_back ({ (sigmata[1].wartosc + sigmata[2].wartosc ) / 2.0, 0, false });
               // 
               
              
            }
            double wynik = std::numeric_limits<double>::max();
            double min_wartosc;
            for (const auto & d : sigmata)
               if (wynik > d.blad)
               {
                  min_wartosc = d.wartosc;
                  wynik = d.blad;
               }
            mS[c][a] = min_wartosc;
         }         
         
         
      }   
      
      
      return mS;
   }
   return std::vector< std::vector<double>>();
}
*/


 
ksi::partition ksi::fcm::doPartition(const ksi::dataset & ds)
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
      
      if (_nIterations > 0)
      {
         for (int iter = 0; iter < _nIterations; iter++)
         {
            mV = calculateClusterCentres(mU, mX);
            mU = modifyPartitionMatrix (mV, mX);
            normaliseByColumns(mU);
         }
      }
      else if (_epsilon > 0)
      {
         double frob;
         do 
         {
            mV = calculateClusterCentres(mU, mX);
            auto mUnew = modifyPartitionMatrix (mV, mX);
            normaliseByColumns(mUnew);
            
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

void ksi::fcm::setFuzzification(double m)
{
   _m = m;
}
 
void ksi::fcm::setNumberOfClusters(int c)
{
   _nClusters = c;
}

void ksi::fcm::setNumberOfIterations(int i)
{
   _nIterations = i;
}

void ksi::fcm::setEpsilonForFrobeniusNorm(const double EPSILON)
{
   try
   {
      if (EPSILON <= 0)
         throw std::string ("Use positive value for EPSILON!");
      
      _epsilon = EPSILON;
   }
   CATCH;
}


double ksi::fcm::Frobenius_norm_of_difference(
   const std::vector<double> & a, 
   const std::vector<double> & b)
{
   try
   {
      auto nA = a.size();
      auto nB = b.size();

      if (nA == 0 and nB == 0)
         return 0.0;
      if (nA != nB)
      {
         std::stringstream ss;
         ss << "The dimensions of vectors do not match:" << std::endl
            << "A has " << nA << " items," << std::endl
            << "B has " << nB << " items.";
         throw ss.str();
      }

      double frob = 0.0;
      for (std::size_t i = 0; i < nA; i++)
      {
         auto diff = a[i] - b[i];
         frob += (diff * diff);
      }
      return frob;
   }
   CATCH;
}


double ksi::fcm::Frobenius_norm_of_difference(
   const std::vector<std::vector<double>> & A, 
   const std::vector<std::vector<double>> & B)
{
   try
   {
      auto nRowsA = A.size();
      auto nRowsB = B.size();
      
      if (nRowsA == 0 and nRowsB == 0)
         return 0.0;
      else if (nRowsA != nRowsB)
      {
         std::stringstream ss;
         ss << "The dimensions of matrices do not match:" << std::endl
            << "A has " << nRowsA << " rows," << std::endl
            << "B has " << nRowsB << " rows.";
         throw ss.str();
      }
      
      auto nColsA = A[0].size();
      auto nColsB = B[0].size();
      if (nColsA != nColsB)
      {
         std::stringstream ss;
         ss << "The dimensions of matrices do not match:" << std::endl
            << "A has dimensions [" << nRowsA << ", " << nColsA << "]," << std::endl
            << "B has dimensions [" << nRowsB << ", " << nColsB << "]," << std::endl;
         throw ss.str();
      }  
      
      double frob = 0;
      for (int r = 0; r < nRowsA; r++)
      {
         for (int c = 0; c < nColsA; c++)
         {
            double diff = A[r][c] - B[r][c];
            frob += (diff * diff);
         }
      }
      return frob;
   }
   CATCH;   
}
 
  