/** @file */

#ifndef ABSTRACT_MA_H
#define ABSTRACT_MA_H

#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "../common/number.h"
#include "rulebase.h"
#include "neuro-fuzzy-system.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../partitions/partitioner.h"

namespace ksi
{
   /** Mamdani-Assilan neuro-fuzzy system  */
   /** gaussian fuzzy sets in premises
    */
   class abstract_ma : virtual public neuro_fuzzy_system
   {
   
   public:
      
      abstract_ma();   
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-24
       */
      abstract_ma (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const partitioner & Partitioner, const double dbMinimalTypicality = -1);
      
       /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobeniu norm for the clustering algorithm
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param positive_class label for positive_class
       * @param negative_class label for negative_class
       * @param threshold_type threshold type for classification
       * @param dbMinimalTypicality minimal typicality for outliers 
       */
      abstract_ma (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const partitioner & Partitioner, double positive_class, double negative_class, ksi::roc_threshold threshold_type, const double dbMinimalTypicality = -1);
      
 
      /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobeniu norm for the clustering algorithm
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param Partitioner clustering object
       * @param positive_class label for positive_class
       * @param negative_class label for negative_class
       * @param threshold_type threshold type for classification
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-30
       */
      abstract_ma (int nRules, double dbFrobeniusEpsilon, int nTuningIterations,
                    double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const partitioner & Partitioner,
                    double positive_class, double negative_class, ksi::roc_threshold threshold_type, const double dbMinimalTypicality = -1
    );

      
      /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobeniu norm for the clustering algorithm
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param Partitioner clustering object
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-30
       */
      abstract_ma (int nRules, double dbFrobeniusEpsilon, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const partitioner & Partitioner, const double dbMinimalTypicality = -1);

      
      abstract_ma(const abstract_ma & a);
      abstract_ma(abstract_ma && a);
      abstract_ma & operator = (const abstract_ma & a);
      abstract_ma & operator = (abstract_ma && a);
      ~abstract_ma();
     
      
      
   protected:   
      /** The method creates a fuzzy rulebase from the dataset.
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param train train dataset  
       * @date  2018-02-16
       * @author Krzysztof Siminski 
       */
      virtual void createFuzzyRulebase ( 
         int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient,
         const dataset & train); 
        
      /** Function that partitions the data set.
       @param X dataset to partition
       @date 2019-12-24 */
      virtual partition doPartition (const dataset & X) = 0;
 
   public:  
     
      /** 
       @return rulebase's answer of a data item
       @param item data item to elaborate answer for
       */
      virtual double answer (const datum & item) const;
      
      /** A method elaborates an answer of a datum (data item). 
       * @param d datum to elaborate answer for 
       * @return The method returns a number.
       */   
      virtual number elaborate_answer (const datum & d) const; 
      
      virtual void train_discriminative_model (const dataset & ds);
      virtual void train_generative_model(const dataset & ds);

      /** The method elaborates the answer of the discriminative_model for a datum 
       @param d a datum to elaborate answer for
       @return just a value :-)
       */
      virtual double discriminate (const datum & d); 
      
      
   };
}




#endif 
