/** @file */ 

#ifndef FCM_CONDITIONAL_H
#define FCM_CONDITIONAL_H

 
#include <vector> 
#include "../auxiliary/definitions.h"
#include "fcm.h"
#include "partition.h"
#include "../common/dataset.h"


namespace ksi
{
   /** The class implements Conditional Fuzzy C-means clustering algorithm. 
    The algorithm is described in:
    Witold Pedrycz, Conditional Fuzzy C-Means, Pattern Recognition Letters 17 (1996), p. 625-631  
    */
   class fcm_conditional : virtual public fcm
   {
   protected: 
  
      
      /** The method normalises each column separatedly, so that sum of all
        * values in a column equals datum's weight.
        @param[in,out] m the matrix to normalise, this object is modified
        @param[in]     weights a vector of weights of data
        */
      void normaliseByColumns (std::vector<std::vector<double>> & m,
                               const std::vector<double> & weights
      );
      /** The method calculates fuzzification of a gaussian cluster with formula:
       * \f[ 
       *    s_{ca} = \sqrt{ \frac{ \sum_{i=1}^X w_i\mu_{ic}^m \left( x_{ia} - v_{ca}  \right)^2 }{\sum_{i=1}^X w_i\mu_{ic}^m } }, 
       * \f] 
       * where: <br/>
       * \f$ s_{ca} \f$ -- fuzzification of the \f$a\f$-th attribute in the \f$c\f$-th cluster;<br/>
       * \f$ \mu_{ic} \f$ -- membership of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ x_{ia} \f$ -- value of the \f$a\f$-th attribute of \f$i\f$-th data item;<br/>
       * \f$ v_{ca} \f$ -- value of the \f$a\f$-th attribute of the \f$c\f$-th cluster centre<br/>
       * \f$ w_{i} \f$ -- weight of \f$i\f$-th data item
       * @return calculates the fuzzification of cluster 
       * @param mU matrix of memberships
       * @param mV cluster centres
       * @param mX data items
       * @param weights weights of data items
        */

      std::vector< std::vector<double>> calculateClusterFuzzification(
         const std::vector<std::vector<double>> & mU,    
         const std::vector<std::vector<double>> & mV,
         const std::vector<std::vector<double>> & mX, 
         const std::vector< double >& weights);
      
      std::vector<std::vector<double>> modifyPartitionMatrix(
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX, 
         const std::vector< double >& weights);
      
   public: 
 
      
      /** The method executes Conditional Fuzzy C-Means clustering algorithm.
       * @param ds dataset to cluster
       * @return partition into clusters
       * @throw ksi::exception if number of clusters or number of iterations not set
       */
      virtual partition doPartition(const ksi::dataset & ds);
      virtual partitioner * clone ();
      virtual ~fcm_conditional();
      
      fcm_conditional();
      fcm_conditional(const fcm& wzor);
      fcm_conditional & operator = (const fcm& wzor);
      
   };

}

#endif

