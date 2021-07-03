/** @file */ 


#ifndef RFCOM_H
#define RFCOM_H

 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "rfcm.h"
#include "fcom.h"
#include "fcm-conditional.h"
#include "../common/data-modifier-imputer.h"
#include "../common/data-modifier-marginaliser.h"
#include "../dissimilarities/dissimilarity.h"
#include "../owas/owa.h"


namespace ksi
{
   /**
    * @date 2018-07-06 -- 2018-07-13 
    */
   class rfcom : virtual public ksi::rfcm, virtual public ksi::fcom
   {
      
   protected:
      /** Global typicalities of data items. */
      std::vector<double> globalTypicalitiesUpper, globalTypicalitiesLower;
      
      /** Typicalities of items to clusters 
          [cluster x data item]              */
      std::vector<std::vector<double>> typicalitiesUpper, typicalitiesLower;      
      
      /** distance matrix pow (distance, 2 / (1 - _m)) */
      std::vector<std::vector<double>> DmUpper, DmLower;
      /** membership matrix [_nClusters, number_of_dataitems] */
      std::vector<std::vector<double>> mUUpper, mULower;
      
      /** The method calculates values of partition matrix with formula:
        * \f[ 
       *    u_{ci} =   \frac{ f_i w_i \left[\sum_{a = 1}^A \left( x_{ia} - v_{ca}  \right)^2 h\left( x_{ia} - v_{ca}  \right)\right]^\frac{1}{1-m}
       *                             }
       *                    { \sum_{k = 1}^C  \beta_{ki} \left[\left( x_{ia} - v_{ka}  \right)^2 h\left( x_{ia} - v_{ka}  \right)\right]^\frac{1}{1-m}} 
                          , 
       * \f] 
       * where: <br/>
       * \f$ s_{ca} \f$ -- fuzzification of the \f$a\f$-th attribute in the \f$c\f$-th cluster;<br/>
       * \f$ \beta_{ci} \f$ -- typicality of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ \mu_{ci} \f$ -- membership of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ x_{ia} \f$ -- value of the \f$a\f$-th attribute of \f$i\f$-th data item;<br/>
       * \f$ v_{ca} \f$ -- value of the \f$a\f$-th attribute of the \f$c\f$-th cluster centre;<br/>
       * \f$ h \f$ -- dissimilarity function defined by the field fcom::pDissimilarity (a pointer to the ksi::dissimilarity class);<br/>
       * \f$ A \f$ -- number of attributes;<br/>
       * \f$ f_{i} \f$ -- global typicality of the \f$i\f$-th data item;<br/> 
       * \f$w_i\f$ -- weight of the \f$i\f$-th data item in the data set;<br/>
       *
       * @param mV -- matrix of cluster centres
       * @param mX -- matrix of data items
       * @param betas -- matrix of betas
       * @param fs -- vector of global typicalities
       * @param wW -- vector of weights of data items
       * @return modified partition matrix U  */
      std::vector<std::vector<double>> modifyPartitionMatrix(
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX,
         const std::vector<std::vector<double>> & betas,
         const std::vector<double> & fs,
         const std::vector<double> & wW);
      
      
      /* First the mean values of all attributes from all data items is calculated. The cluster centres are initialized with these mean values with small random deviation.
       * @param mX -- matrix of data items
       * @param nAttributes -- number of attributes
       * @param nCluster -- number of cluster to initialize
       * 
       * @return matrix of cluster centres
       * @date 2018-07-09
       */
   /*   virtual std::vector<std::vector<double>> initializeClusterCentres (
         const std::vector<std::vector<double>> & mX,
         const int nAttributes,
         const int nClusters 
      );
   */  
   
   
     /** The method calculates centres of clusters. In this method each data item
       * has its own weight. 
       * @return cluster centres    
       * @param[in] mX matrix of data items
       * @param[in] mU partition matrix
       * @param[out] betas Typicalities of items to clusters  [cluster x data item] 
       * @param[in] wW -- vector of weights of data items
       */
      std::vector<std::vector<double>> calculateClusterCentres(
         const std::vector< std::vector<double>> & mX, 
         const std::vector< std::vector<double>> & mU, 
         std::vector< std::vector<double>> & betas,
         const std::vector<double> & wW);

   public: 
      
      /** Constructor of ksi::rfcm -- constructor copies the 
       * imputer and marginaliser objects.
       * @param imputer an imputer object
       * @param marginaliser a marginaliser object
       * @param dis a dissimilarity object
       * @param owa an ordered weighting object
       * @param useMarginalisedDataForCentres if true marginalised data set is used for localisation of cluster centres, otherwise -- imputed data set
       * @date 2018-06-14
      */
      rfcom (const ksi::data_modifier & imputer, 
             const ksi::data_modifier & marginaliser, 
             const ksi::dissimilarity & dis, 
             const ksi::owa & owa,
             const bool useMarginalisedDataForCentres = true);
      
      rfcom (const rfcom & wzor);
      rfcom (rfcom && wzor);
      rfcom & operator= (const rfcom & wzor);
      rfcom & operator= (rfcom && wzor);
      virtual ~rfcom ();      
      
      /** The method elaborates a partition with the RFCOM algorithm.
       * It also elaborates typicalities of data items. 
       * The typicalities are elaborated in the following way:
       * <ol>
       *   <li>The algorithm elaborated upper and lower typicality of each data items. The final typicality is an S-norm of them.</li>
       *   <li>The lower typicality of an incomplete data item does not exists because the data item has no representation in the lower data set.</li>
       *   <li>The upper typicality of an incomplete data item is composed of several typicalities of imputed data items. These typicalities are aggregated with an S-norm.</li>
       *   <li>In our algorithm we use max S-norm.</li>
       * </ol>
       * 
       * @throw ksi::exception if _pImputer or _pMarginaliser or _nClusters 
       *                        or _epsilon or pDissimilarity or pOwa not set 
       */
      virtual partition doPartition(const ksi::dataset& ds);
      
      
      virtual partitioner * clone () const;
      
      /** The method calculates fuzzification of a gaussian cluster with formula:
       * \f[ 
       *    s_{ca} = \sqrt{ 
       *               \frac{\sum_{i=1}^X w_i\beta_{ci} \mu_{ci}^m 
       *                            \left( x_{ia} - v_{ca}  \right)^2 h\left( x_{ia} - v_{ca}  \right) }
       *                    {\sum_{i=1}^X w_i\beta_{ci} \mu_{ci}^m } 
                          }, 
       * \f] 
       * where: <br/>
       * \f$ s_{ca} \f$ -- fuzzification of the \f$a\f$-th attribute in the \f$c\f$-th cluster;<br/>
       * \f$ \beta_{ci} \f$ -- typicality of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ \mu_{ci} \f$ -- membership of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ x_{ia} \f$ -- value of the \f$a\f$-th attribute of \f$i\f$-th data item;<br/>
       * \f$ v_{ca} \f$ -- value of the \f$a\f$-th attribute of the \f$c\f$-th cluster centre;<br/>
       * \f$ w_i \f$ -- weight of \f$i\f$-th data item
       * \f$ h \f$ -- dissimilarity function defined by the field fcom::pDissimilarity (a pointer to the ksi::dissimilarity class)
       * @return calculates the fuzzification of cluster 
       * @param mU -- partition matrix
       * @param mV -- matrix of cluster centres
       * @param mB -- matrix of betas
       * @param mX -- matrix of data items
       * @param wW -- vector of weights of data items
       */
      std::vector< std::vector<double>> calculateClusterFuzzification(
         const std::vector<std::vector<double>> & mU,    
         const std::vector<std::vector<double>> & mV,
         const std::vector<std::vector<double>> & mB,
         const std::vector<std::vector<double>> & mX,
         const std::vector<double>              & wW);
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
   };
}

#endif

