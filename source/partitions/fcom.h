/** @file */ 

#ifndef FCOM_H
#define FCOM_H

 
#include <vector> 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "fcm.h"
#include "../common/dataset.h"
#include "../dissimilarities/dissimilarity.h"
#include "../owas/owa.h"


namespace ksi
{
   /** The class implements Fuzzy C-ordered-means clustering algorithm.
    * Jacek Leski, Fuzzy c-ordered-means clustering, Fuzzy Sets and Systems, 286 (2016), pp. 114-133 
    * @date 2018-05-24
    */
   class fcom : virtual public fcm
   {
   protected:
      
      /** A structure to hold a value of a residual, its index before 
           sorting, and its index after sorting.*/
      struct residual
      {
         double value;   ///< value of the residual
         std::size_t pre_sort_index;  ///< index before sorting
         std::size_t post_sort_index; ///< index after sorting
      };
      
      /** number of iterations without weighting, default value: 4  */
      const int NUMBER_OF_ITERATIONS_WITHOUT_WEIGHTING = 4;
      
      
      /** Global typicalities of data items. */
      std::vector<double> fs;
   
      /** Typicalities of items to clusters 
          [cluster x data item]              */
      std::vector<std::vector<double>> betas;
    
      /** a pointer to a dissimilarity measure object */
      ksi::dissimilarity * pDissimilarity = nullptr;
      
      /** a pointer to an OWA object */
      ksi::owa * pOwa = nullptr;
      
       
      
      
      /** The method calculates values of partition matrix with formula:
        * \f[ 
       *    u_{ci} =   \frac{ f_i \left[\sum_{a = 1}^A \left( x_{ia} - v_{ca}  \right)^2 h\left( x_{ia} - v_{ca}  \right)\right]^\frac{1}{1-m}
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
       * @return modified partition matrix U  */
      std::vector<std::vector<double>> modifyPartitionMatrix(
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX,
         const std::vector<std::vector<double>> & betas,
         const std::vector<double> & fs);      
 
      /** 
       * @return cluster centres mV  
       * @param[in] mX matrix of data items
       * @param[in] mU partition matrix
       * @param[out] betas Typicalities of items to clusters  [cluster x data item] 
       */
      std::vector<std::vector<double>> calculateClusterCentres(
         const std::vector< std::vector<double>> & mX, 
         const std::vector< std::vector<double>> & mU, 
         std::vector< std::vector<double>> & betas );
      
      
      /** The method calculates fuzzification of a gaussian cluster with formula:
       * \f[ 
       *    s_{ca} = \sqrt{ 
       *               \frac{\sum_{i=1}^X \beta_{ci} \mu_{ci}^m 
       *                            \left( x_{ia} - v_{ca}  \right)^2 h\left( x_{ia} - v_{ca}  \right) }
       *                    {\sum_{i=1}^X \beta_{ci} \mu_{ci}^m } 
                          }, 
       * \f] 
       * where: <br/>
       * \f$ s_{ca} \f$ -- fuzzification of the \f$a\f$-th attribute in the \f$c\f$-th cluster;<br/>
       * \f$ \beta_{ci} \f$ -- typicality of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ \mu_{ci} \f$ -- membership of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ x_{ia} \f$ -- value of the \f$a\f$-th attribute of \f$i\f$-th data item;<br/>
       * \f$ v_{ca} \f$ -- value of the \f$a\f$-th attribute of the \f$c\f$-th cluster centre;<br/>
       * \f$ h \f$ -- dissimilarity function defined by the field fcom::pDissimilarity (a pointer to the ksi::dissimilarity class)
       * @return calculates the fuzzification of cluster 
       * @param mU -- partition matrix
       * @param mV -- matrix of cluster centres
       * @param betas Typicalities of items to clusters  [cluster x data item]  
       * @param mX -- matrix of data items
       */
      std::vector<std::vector<double>> calculateClusterFuzzification(
         const std::vector< std::vector<double>> & mU,
         const std::vector< std::vector<double>> & mV, 
         const std::vector< std::vector<double>> & betas,
         const std::vector< std::vector<double>> & mX);

       /** The method calculates fuzzification of a gaussian cluster with formula:
       * \f[ 
       *    s_{ca} = \sqrt{ \frac{ \sum_{i=1}^X t_{i}\mu_{ci}^m \left( x_{ia} - v_{ca}  \right)^2 }{\sum_{i=1}^X t_{i}\mu_{ci}^m } }, 
       * \f] 
       * where: <br/>
       * \f$ s_{ca} \f$ -- fuzzification of the \f$a\f$-th attribute in the \f$c\f$-th cluster;<br/>
       * \f$ \mu_{ci} \f$ -- membership of \f$i\f$-th data item to the \f$c\f$-th cluster;<br/>
       * \f$ x_{ia} \f$ -- value of the \f$a\f$-th attribute of \f$i\f$-th data item;<br/>
       * \f$ v_{ca} \f$ -- value of the \f$a\f$-th attribute of the \f$c\f$-th cluster centre
       * \f$ t_{i} \f$ -- typicality  of the \f$i\f$-th data item 
       * @return calculates the fuzzification of cluster 
        */
      std::vector<std::vector<double>> calculateClusterFuzzification(
         const std::vector< std::vector<double>> & mU,
         const std::vector< std::vector<double>> & mV, 
         const std::vector< double> & typicalities,
         const std::vector< std::vector<double>> & mX);

      
      
      /** The method uses the original Leski's initialization. All values are initialized with zeros.
       * @param mX -- matrix of data items
       * @param nAttributes -- number of attributes
       * @param nCluster -- number of cluster to initialize
       * 
       * @return matrix of cluster centres
       * @date 2018-07-09
       */
      virtual std::vector<std::vector<double>> initializeClusterCentres (
         const std::vector<std::vector<double>> & mX,
         const int nAttributes,
         const int nClusters 
      );
      
   public: 
      
      /** The method executes fuzzy c-ordered-means clustering algorithm.
       * @param ds dataset to cluster
       * @return partition into clusters
       * @throw ksi::exception if number of clusters or minimal epsilon for Frobenius norm not set
       */
      virtual partition doPartition(const ksi::dataset & ds);
      
      /** Do not use this method. Set epsilon for Frobenius norm.
       @throw ksi::exception The method throws an exception with a short message.
       */
      virtual void setNumberOfIterations (int i);
      
      fcom ();
      fcom (const ksi::dissimilarity & dis, const ksi::owa & owa);
      
      /** @param number_of_clusters number of clusters 
          @param frobenius_epsilon epsilon for Frobenius norm 
          @param dis dissimilarity object
          @param owa ordered weighting averaging object */
      fcom (const int number_of_clusters, double frobenius_epsilon, const ksi::dissimilarity & dis, const ksi::owa & owa);
      
      fcom (const fcom & wzor); 
      fcom (fcom && wzor);
      fcom & operator = (const fcom & wzor); 
      fcom & operator = (fcom && wzor);
      
      virtual partitioner * clone () const;
      virtual ~fcom ();  
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
   };

}

#endif

