/** @file */ 


#ifndef RSFCM_H
#define RSFCM_H

 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "rfcm.h"
#include "sfcm.h"
#include "../common/data-modifier-imputer.h"
#include "../common/data-modifier-marginaliser.h"


namespace ksi
{
   /** Partitioner for rough subspace fuzzy c-means clustering.
    * This implementation is an extention of the algorithm published in
    * 
    * CITATION REQUEST
    * If you use this algorithm, please cite the paper:
    * Krzysztof Simiński, Rough fuzzy subspace clustering for data with missing values, Computing & Informatics, 2014, volume 33, number 1, pp. 131-153. 
    * <pre>
      @article{id:Siminski2014Rough,
  title={Rough fuzzy subspace clustering for data with missing values},
  author={Simi{\'n}ski, Krzysztof},
  journal={Computing \& Informatics},
  volume={33},
  number={1},
  year={2014},
  pages={131--153},
  abstract = {The paper presents rough fuzzy subspace clustering algorithm and 
  experimental results of clustering. In this algorithm three approaches for 
  handling missing values are used: marginalisation, imputation and rough sets. 
  The algorithm also assigns weights to attributes in each cluster; this leads 
  to subspace clustering. The parameters of clusters are elaborated in the 
  iterative procedure based on minimising of criterion function. The crucial 
  parameter of the proposed algorithm is the parameter having the influence on 
  the sharpness of elaborated subspace cluster. The lower values of the 
  parameter lead to selection of the most important attribute. The higher values
  create clusters in the global space, not in subspaces. The paper is 
  accompanied by results of clustering of synthetic and real life data sets.},
} 
    * </pre>
    * @date 2018-07-14 
    * 
    * @author Krzysztof Siminski
    *
    */
   class rsfcm : virtual public ksi::sfcm, virtual public ksi::rfcm
   {
   public:
      rsfcm (const ksi::data_modifier & imputer, 
            const ksi::data_modifier & marginaliser,
            const bool useLowerDataForCentres = true
           );
      rsfcm (const rsfcm & wzor);
      rsfcm (rsfcm && wzor);
      rsfcm & operator= (const rsfcm & wzor);
      rsfcm & operator= (rsfcm && wzor);
      virtual ~rsfcm ();      
      
      /** @throw ksi::exception if _pImputer or _pMarginaliser not set
       */
      virtual partition doPartition(const ksi::dataset & ds);
      virtual partitioner * clone ();
      
      
      /** The method elaborates partition matrix.
       @return return a new partition matrix 
       @param mV a set of cluster centers
       @param mX data set
       @param mZ matrix of attribute weights in clusters
       @param wW vector of weights of data items
       @date 2018-07-21
       */      
      std::vector<std::vector<double>> modifyPartitionMatrix(
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX, 
         const std::vector<std::vector<double>> & mZ, 
         const std::vector< double >& wW);
   };   
}

#endif

