/** @file */ 

#ifndef FCM_H
#define FCM_H

 
#include <vector> 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "../common/dataset.h"


namespace ksi
{
   /** The class implements Fuzzy C-means clustering algorithm. */
   class fcm : virtual public partitioner
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
      std::vector<std::vector<double>> Dm;
      /** membership matrix [_nClusters, number_of_dataitems] */
      std::vector<std::vector<double>> mU;
      
      /** @return matrix of cluster centres */
      std::vector<std::vector<double>> calculateClusterCentres (
         const std::vector<std::vector<double>> & U,
         const std::vector<std::vector<double>> & X);
      
      /** @return modified partition matrix U  */
      std::vector<std::vector<double>> modifyPartitionMatrix(
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX);
      
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
      std::vector<std::vector<double>> calculateClusterFuzzification(
         const std::vector<std::vector<double>> & mU, 
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX);

  
      
      /** The method normalises each column separatedly into range [0, 1].
        @param[in,out] m the matrix to normalise, this object is modified */
      void normaliseByColumns (std::vector<std::vector<double>> & m);

      /** The method normalises each row separatedly into range [0, 1].
        @param[in,out] m the matrix to normalise, this object is modified */
      void normaliseByRows (std::vector<std::vector<double>> & m);

      /** The method fills the matrix m with random numbers from range [0, 1].
        @param[out] m the matrix to fill */
      void randomise          (std::vector<std::vector<double>> & m);
      /** The method calculated an Euclidean distance between two data points 
        * represented by two vectors.
        * @param x point represented by a vector of attributes 
        * @param x point represented by a vector of attributes 
        * @return an Euclidean distance between x and y */
      double calculateDistance(const std::vector<double> & x, 
                               const std::vector<double> & y);

      /** @return Frobenius norm of differences of two matrices.
       * \f[ \|A - B\|_F \f]
       * @param A
       * @param B 
       * @throw ksi::exception if dimensions of matrices do not match          
       */
      double Frobenius_norm_of_difference
      (
         const std::vector<std::vector<double>> & A,
         const std::vector<std::vector<double>> & B 
         );
      
      /** @return Frobenius norm of differences of two vectors.
       * \f[ \|a - b\|_F \f]
       * @param a
       * @param b 
       * @throw ksi::exception if dimensions of vectors do not match          
       */
      double Frobenius_norm_of_difference 
      (
         const std::vector<double> & a,
         const std::vector<double> & b 
         );
      
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
      
      fcm ();
      fcm (const fcm & wzor); 
      fcm & operator = (const fcm & wzor); 
      
      
      virtual partitioner * clone ();
      virtual ~fcm ();      
   };

}

#endif

