/** @file */ 


#ifndef RFCM_H
#define RFCM_H

 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "fcm.h"
#include "fcm-conditional.h"
#include "../common/data-modifier-imputer.h"
#include "../common/data-modifier-marginaliser.h"


namespace ksi
{
   /** Partitioner for rough fuzzy c-means clustering for incomplete data.
   
   * CITATION REQUEST
    * This implementation is an extention of the algorithm published in
    * Krzysztof Simiński, Clustering with missing values, [in] Fundamenta Informaticae, 2013, volume 123, number 3, pp. 331-350.
    * If you use this algorithm, please cite the paper:
    * <pre>
    @ARTICLE{id:Siminski2013Clustering,
      author = {Krzysztof Siminski},
      title = {Clustering with missing values},
      journal = {Fundamenta Informaticae},
      year = {2013},
      volume = {123},
      pages = {331-350},
      number = {3},
      abstract = {The paper presents the clustering algorithm for data with missing
                  values. In this approach both marginalisation and imputation are
                  applied. The result of the clustering is the type-2 fuzzy set 
                  / rough fuzzy set. This approach enables the distinction between
                  original and imputed data. The method can be applied to the data
                  sets with all attributes lacking some values. The paper is
                  accompanied by the numerical examples of clustering of synthetic 
                  and real-life data sets.},
     }
    * </pre>
    * @date 2018-06-15 
    */
   class rfcm : virtual public ksi::fcm_conditional
   {
   protected:
      ksi::data_modifier * _pImputer = nullptr;
      ksi::data_modifier * _pMarginaliser = nullptr;
      
      /** Flag for calculation of localisation of clusters with lower (marginalised)
          data set, otherwise upper (imputed) data set is used.
        */
      bool _useMarginalisedDataForCentres = true;
      
      
       /** The method calculates cluster centres of weighted data items
        * @param U partition matrix
        * @param X matrix of data items
        * @param w vector of weights of data items
        * @return matrix of cluster centres 
        */
      std::vector<std::vector<double>> calculateClusterCentres (
         const std::vector<std::vector<double>> & U,
         const std::vector<std::vector<double>> & X,
         const std::vector<double>              & w);
   public: 
      
      /** Constructor of ksi::rfcm -- constructor copies the 
       * imputer and marginaliser objects.
       * @param imputer an imputer object
       * @param marginaliser a marginaliser object
       * @param useLowerDataForCentres set true, otherwise set false to calculate cluster centres with imputed data
       * @date 2018-06-14
      */
      rfcm (const ksi::data_modifier & imputer, 
            const ksi::data_modifier & marginaliser,
            const bool useLowerDataForCentres = true
           );
      rfcm (const rfcm & wzor);
      rfcm (rfcm && wzor);
      rfcm & operator= (const rfcm & wzor);
      rfcm & operator= (rfcm && wzor);
      virtual ~rfcm ();      
      
      /** @throw ksi::exception if _pImputer or _pMarginaliser not set */
      virtual partition doPartition(const ksi::dataset& ds);
      virtual partitioner * clone ();
      
      /** The method sets bLowersetBasedLocalisation flag.
       * The cluster centres will be calculated with marginalised (lower) data.
       */
      void setCalculateClusterCentresWithMarginalisedData() ;
      
      /** The method resets bLowersetBasedLocalisation flag.
       * The cluster centres will be calculated with imputed (upper) data.
       */
      void setCalculateClusterCentresWithImputedData();
      
      /** @return true  if cluster centres are calculated with marginalised
       *                (lower) data set 
       *  @return false if cluster centres are calculated with imputed
       *                (upper) data set 
       */
      bool areClustersCalculatedWithMarginalisedData() const ;
   };
}

#endif

