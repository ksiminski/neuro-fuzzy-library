/** @file */ 

#ifndef FCM_T_H
#define FCM_T_H
 

#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>

#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "../common/dataset.h"
#include "../common/dataset.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../service/debug.h"
#include "../service/exception.h"
#include "../auxiliary/mathematics.h"


namespace ksi
{
   /** The class implements Fuzzy C-means clustering algorithm. */
   template<class T>
   class fcm_T : virtual public partitioner
   {
   protected:
      /** fuzzification parameter */
      double _m = 2.0;
      /** number of clusters */
      int _nClusters = -1;
      /** number of iterations */
      double _nIterations = -1;
      /** Threshold of Frobenius norm for changed in location of cluster
          centres. When the Frobenius norm of 
          differences of U matrices in two consecutive iterations
          is less than _epsilon, the clustering algorithm stops. */
      double _epsilon = -1;
      /** distance matrix pow (distance, 2 / (1 - _m)) */
      std::vector<std::vector<T>> Dm;
      /** membership matrix [_nClusters, number_of_dataitems] */
      std::vector<std::vector<T>> mU;
      
      /** @return matrix of cluster centres */
      std::vector<std::vector<T>> calculateClusterCentres (
         const std::vector<std::vector<T>> & U,
         const std::vector<std::vector<T>> & X);
      
      /** @return modified partition matrix U  */
      std::vector<std::vector<T>> modifyPartitionMatrix(
         const std::vector<std::vector<T>> & mV, 
         const std::vector<std::vector<T>> & mX);
      
      /** The method calculates fuzzification of a gaussian cluster with formula:
       * \f[ 
       *    s_{ca} = \sqrt{ \frac{ \sum_{i=1}^X \mu_{ci}^m \left( x_{ia} - v_{ca}  \right)^2 }{\sum_{i=1}^X \mu_{ci}^m } }, 
       * \f] 
       * where: <br/>
       * \f$ s_{ca} \f$ -- fuzzification of the \f$a\f$-th attribute in the \f$c\f$-th cluster;<br/>
       * \f$ \mu_{ci} \f$ -- membership of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ x_{ia} \f$ -- value of the \f$a\f$-th attribute of \f$i\f$-th data item;<br/>
       * \f$ v_{ca} \f$ -- value of the \f$a\f$-th attribute of the \f$c\f$-th cluster centre
       * @return calculates the fuzzification of cluster 
        */
      std::vector<std::vector<T>> calculateClusterFuzzification(
         const std::vector<std::vector<T>> & mU, 
         const std::vector<std::vector<T>> & mV, 
         const std::vector<std::vector<T>> & mX);  
      
      /** The method normalises each column separatedly into range [0, 1].
        @param[in,out] m the matrix to normalise, this object is modified */
      void normaliseByColumns (std::vector<std::vector<T>> & m);

      /** The method normalises each row separatedly into range [0, 1].
        @param[in,out] m the matrix to normalise, this object is modified */
      void normaliseByRows (std::vector<std::vector<T>> & m);

      /** The method fills the matrix m with random numbers from range [0, 1].
        @param[out] m the matrix to fill */
      void randomise (std::vector<std::vector<T>> & m);
      /** The method calculated an Euclidean distance between two data points 
        * represented by two vectors.
        * @param x point represented by a vector of attributes 
        * @param x point represented by a vector of attributes 
        * @return an Euclidean distance between x and y */
      virtual T calculateDistance(const std::vector<T> & x, 
                                  const std::vector<T> & y);

      /** @return Frobenius norm of differences of two matrices.
       * \f[ \|A - B\|_F \f]
       * @param A
       * @param B 
       * @throw ksi::exception if dimensions of matrices do not match          
       */
      T Frobenius_norm_of_difference
      (
         const std::vector<std::vector<T>> & A,
         const std::vector<std::vector<T>> & B 
      );
      
      /** @return Frobenius norm of differences of two vectors.
       * \f[ \|a - b\|_F \f]
       * @param a
       * @param b 
       * @throw ksi::exception if dimensions of vectors do not match          
       */
      T Frobenius_norm_of_difference 
      (
         const std::vector<T> & a,
         const std::vector<T> & b 
      );
      
      /** @param nClusters number of clusters
          @param nAttr number of attributes
          @param mV matrix of cluster centres
          @param mS matrix of cluster fuzzification
          @return a gaussian partition
          @date 2019-01-27 */
      partition elaborate_gaussian_partition (const int nClusters, const int nAttr, 
                                              const std::vector<std::vector<T>> & mV,
                                              const std::vector<std::vector<T>> & mS);
      
      /** The function elaborates gaussian prototypes of clusters and returns them as a dataset.
          @param nClusters number of clusters
          @param nAttr number of attributes
          @param mV matrix of cluster centres
          @param mS matrix of cluster fuzzification
          @return a dataset with prototypes of clusters
          @date 2019-01-27 */
      ksi::dataset elaborate_gaussian_prototypes (const int nClusters, const int nAttr, 
                                                  const std::vector<std::vector<T>> & mV,
                                                  const std::vector<std::vector<T>> & mS);
      
   public: 
      void setFuzzification (double m);
      void setNumberOfClusters (int c);
      virtual void setNumberOfIterations (int i);
      /** The method sets an epsilon. When the Frobenius norm of 
          differences of U matrices in two consecutive iterations
          is less than EPSILON, the clustering algorithm stops.
          @throw ksi::exception if EPSILON negative or zero
       */
      void setEpsilonForFrobeniusNorm (const double EPSILON);
      
      /** The method executes Fuzzy C-Means clustering algorithm.
       * @param ds dataset to cluster
       * @return partition into clusters
       * @throw ksi::exception if number of clusters not set 
       * @throw ksi::exception if neither number of iterations nor minimal epsilon set 
       */
      virtual partition doPartition(const ksi::dataset & ds);
      
      fcm_T ();
      /** @param nClusters number of clusters to cluster data into
          @param nClusteringIterations number of iterations of clutering procedure */
      fcm_T (const int number_of_clusters, const int number_of_clustering_iterations);
      fcm_T (const fcm_T & wzor); 
      fcm_T & operator = (const fcm_T & wzor); 
      
      
      virtual partitioner * clone () const;
      virtual ~fcm_T ();  
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
   };
}


 
 


template<class T>
std::string ksi::fcm_T<T>::getAbbreviation() const
{
   return std::string ("fcm");
}


template<class T>
ksi::partitioner * ksi::fcm_T<T>::clone() const
{
   auto p = new ksi::fcm_T<T>(*this);
   
   return p;
}

template<class T>
ksi::fcm_T<T>::fcm_T(const ksi::fcm_T<T> & wzor) : partitioner(wzor)
{
   _m = wzor._m;
   _nClusters = wzor._nClusters; 
   _nIterations = wzor._nIterations;
   _epsilon = wzor._epsilon;
}

template<class T>
ksi::fcm_T<T> & ksi::fcm_T<T>::operator=(const ksi::fcm_T<T> & wzor)
{
   if (this == &wzor)
      return *this;
   
   _m = wzor._m;
   _nClusters = wzor._nClusters;
   _nIterations = wzor._nIterations;   
   _epsilon = wzor._epsilon;
   
   return *this;
}

template<class T>
ksi::fcm_T<T>::fcm_T()
{
 
}

template<class T>
ksi::fcm_T<T>::fcm_T (const int nClusters, const int nClusteringIterations) : _nClusters(nClusters), _nIterations(nClusteringIterations)
{
 
}

template<class T>
ksi::fcm_T<T>::~fcm_T()
{
}

template<class T>
std::vector<std::vector<T>> ksi::fcm_T<T>::calculateClusterCentres(
   const std::vector<std::vector<T>> & U, 
   const std::vector<std::vector<T>> & X)
{
   try
   {
      std::vector<std::vector<T>> V;
      
      std::size_t nX = X.size();
      if (nX > 0)
      {
         std::size_t nAttr = X[0].size();
         for (int c = 0; c < _nClusters; c++)
         {
            std::vector<T> suma_x (nAttr, 0.0);
            T suma_u_ci_m {};
            
            for (std::size_t i = 0; i < nX; i++)
            {
               T u_ci_m = ksi::power(U[c][i], _m);
               suma_u_ci_m += u_ci_m;
               
               for (std::size_t a = 0; a < nAttr; a++)
                  suma_x[a] += (u_ci_m * X[i][a]);
            }
            
            std::vector<T> v (nAttr);
            for (std::size_t a = 0; a < nAttr; a++)
               v[a] = suma_x[a] / suma_u_ci_m;
            
            V.push_back(v);
         }
      }
      return V;
   }
   CATCH;
}

 
template<class T>
void ksi::fcm_T<T>::randomise(std::vector<std::vector<T>> & m)
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

template<class T>
void ksi::fcm_T<T>::normaliseByColumns(std::vector<std::vector<T>> & m)
{
   try
   {
      if (m.size() > 0)
      {
         std::size_t nAttr = m[0].size();
         std::size_t nRows = m.size();
         
         for (std::size_t a = 0; a < nAttr; a++)
         {
            T suma {};
            for (std::size_t r = 0; r < nRows; r++)
               suma += m[r][a];
            for (std::size_t r = 0; r < nRows; r++)
               m[r][a] /= suma;
         }
      }
   }
   CATCH;
}

template<class T>
void ksi::fcm_T<T>::normaliseByRows(std::vector<std::vector<T>> & m)
{
   try
   {
      if (m.size() > 0)
      {
         std::size_t nCols = m[0].size();
         std::size_t nRows = m.size();
         
         for (std::size_t r = 0; r < nRows; r++)
         {
            T suma {};
            for (std::size_t a = 0; a < nCols; a++)   
               suma += m[r][a];
            for (std::size_t a = 0; a < nCols; a++)
               m[r][a] /= suma;
         }
      }
   }
   CATCH;
}

template<class T>
std::vector<std::vector<T>> ksi::fcm_T<T>::modifyPartitionMatrix(
   const std::vector<std::vector<T>> & mV, 
   const std::vector<std::vector<T>> & mX)
{
   try
   {
      std::vector<std::vector<T>> U (mV.size());
      std::size_t nClusters = mV.size();
      std::size_t nX = mX.size();
      double exponent = 2.0 / (1.0 - _m);
      
      if (nX > 0)
      {
         //std::size_t nAttr = mX[0].size();
         for (auto & u : U)
            u = std::vector<T> (nX);

         // distance matrix:
         std::vector<T>   Dmsums  (nX, T{});
         std::vector<int> Dmzeros (nX, 0.0);
         Dm = std::vector<std::vector<T>> (nClusters);
         for (std::size_t c = 0; c < nClusters; c++)
         {
            Dm[c] = std::vector<T> (nX);

            for (std::size_t x = 0; x < nX; x++)
            {
                Dm[c][x] = ksi::power(calculateDistance (mV[c], mX[x]), exponent);
                if (Dm[c][x] == 0)
                  Dmzeros[x]++;
               Dmsums[x] += Dm[c][x];
            }
         }

//          for (std::size_t c = 0; c < nClusters; c++)
//          {
//             for (std::size_t x = 0; x < nX; x++)
//             {
//                if (Dm[c][x] == 0)
//                   Dmzeros[x]++;
//                Dmsums[x] += Dm[c][x];
//             }
//          }
         
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

template<class T>
T ksi::fcm_T<T>::calculateDistance(
   const std::vector<T> & x, 
   const std::vector<T> & y)
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
         T sum {};
         for (size_t i = 0; i < size; i++)
         {
            T roznica = x[i] - y[i];
            sum += (roznica * roznica);
         }
         return ksi::square_root(sum); 
      }
   }
   CATCH;
}

template<class T>
std::vector< std::vector<T>> ksi::fcm_T<T>::calculateClusterFuzzification(
   const std::vector<std::vector<T>> & mU,    
   const std::vector<std::vector<T>> & mV,
   const std::vector<std::vector<T>> & mX)
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
            T sumU {};
            std::vector<T> sumUXV (nAttr, 0.0);
            for (std::size_t x = 0; x < nX; x++)
            {
               T um = ksi::power(mU[c][x], _m);
               sumU += um;
               
               for (std::size_t a = 0; a < nAttr; a++)
               {
                  T roznica = mX[x][a] - mV[c][a];
                  sumUXV[a] += um * roznica * roznica;
               }
            }
            
            for (std::size_t a = 0; a < nAttr; a++)
               mS[c][a] = square_root (sumUXV[a] / sumU);
         }
         return mS;
      }
      return std::vector< std::vector<T>>();
   }
   CATCH;
}

template<class T>
ksi::partition ksi::fcm_T<T>::doPartition(const ksi::dataset & ds)
{
   try
   {
//       debug(_nClusters);
      if (_nClusters < 1)
         throw std::string ("unknown number of clusters");
      if (_nIterations < 1 and _epsilon < 0)
         throw std::string ("You should set a maximal number of iteration or "
         "minimal difference -- epsilon.");
      if (_nIterations > 0 and _epsilon > 0)
         throw std::string ("Both number of iterations and minimal epsilon set -- you should set either number of iterations or minimal epsilon.");
      
      T dummy;
      auto mX = ds.getMatrix(dummy);
      std::size_t nAttr = ds.getNumberOfAttributes();
      std::size_t nX    = ds.getNumberOfData();
      std::vector<std::vector<T>> mV;
      mU = std::vector<std::vector<T>> (_nClusters);
      
      for (auto & u : mU)
         u = std::vector<T> (nX);
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
         T frob {};
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
      std::vector<std::vector<T>> mS = calculateClusterFuzzification(mU, mV, mX);
      
      auto prototypes = elaborate_gaussian_prototypes (_nClusters, nAttr, mV, mS);
//       debug(prototypes);
      
      ksi::partition part = elaborate_gaussian_partition(_nClusters, nAttr, mV, mS);
      
      return part;
   }
   CATCH;
}




template<class T>
void ksi::fcm_T<T>::setFuzzification(double m)
{
   _m = m;
}

template<class T>
void ksi::fcm_T<T>::setNumberOfClusters(int c)
{
   _nClusters = c;
}

template<class T>
void ksi::fcm_T<T>::setNumberOfIterations(int i)
{
   _nIterations = i;
}

template<class T>
void ksi::fcm_T<T>::setEpsilonForFrobeniusNorm(const double EPSILON)
{
   try
   {
      if (EPSILON <= 0)
         throw std::string ("Use positive value for EPSILON!");
      
      _epsilon = EPSILON;
   }
   CATCH;
}

template<class T>
T ksi::fcm_T<T>::Frobenius_norm_of_difference(
   const std::vector<T> & a, 
   const std::vector<T> & b)
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
      
      T frob {};
      for (std::size_t i = 0; i < nA; i++)
      {
         auto diff = a[i] - b[i];
         frob += (diff * diff);
      }
      return frob;
   }
   CATCH;
}

template<class T>
T ksi::fcm_T<T>::Frobenius_norm_of_difference(
   const std::vector<std::vector<T>> & A, 
   const std::vector<std::vector<T>> & B)
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
      
      T frob {};
      for (int r = 0; r < nRowsA; r++)
      {
         for (int c = 0; c < nColsA; c++)
         {
            T diff = A[r][c] - B[r][c];
            frob += (diff * diff);
         }
      }
      return frob;
   }
   CATCH;   
}

#endif

