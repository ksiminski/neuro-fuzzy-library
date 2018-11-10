/** @file */ 

#ifndef FCM_POSSIBILISTIC_H
#define FCM_POSSIBILISTIC_H

 
#include <vector> 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "fcm.h"
#include "../common/dataset.h"


namespace ksi
{
   /** The class implements possibilistic Fuzzy C-means clustering algorithm.
    *  R. Krishnapuram, J. M. Keller, "A possiblistic approach to clustering", Transanctions on Fuzzy Systems, 1(2), pp. 98-110, 1993
    */
   class fcm_possibilistic : virtual public fcm
   {
   protected:
      /** Eta's for possibilistic clustering */
      std::vector<double> etas;
      
      /** @return modified partition matrix U  */
      std::vector<std::vector<double>> modifyPartitionMatrix(
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX);      
      
      /** Calculates eta's for possibilistic clustering.
       * @param cluster_number number of clusters
       * @param nDataItems     number of data items in the data set
       */
      void calculateEtas (int cluster_number, int nDataItems,
         const ksi::dataset & ds
      );
      
      
   public: 

      
      /** The method executes Fuzzy C-Means clustering algorithm.
       * @param ds dataset to cluster
       * @return partition into clusters
       * @throw ksi::exception if number of clusters or number of iterations not set
       */
      virtual partition doPartition(const ksi::dataset & ds);
      
      fcm_possibilistic ();
      fcm_possibilistic (const fcm_possibilistic & wzor); 
      fcm_possibilistic & operator = (const fcm_possibilistic & wzor); 
      
      
      virtual partitioner * clone ();
      virtual ~fcm_possibilistic ();      
   };

}

#endif

