/** @file */

#ifndef ABSTRACT_ANNBFIS_H
#define ABSTRACT_ANNBFIS_H


#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "../common/number.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

namespace ksi 
{
   /** Abstract annbfis neuro-fuzzy system  */
   /** abstract annbfis 
    */
   class abstract_annbfis : virtual public neuro_fuzzy_system
   {
   protected: 
      /** fuzzy implication */
      implication * _pImplication = nullptr;
  
   public:
      
      abstract_annbfis();   
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param Partitioner partition method object
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-24
       */
      abstract_annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, const partitioner & Partitioner, const double dbMinimalTypicality = -1);

      /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobenius norm in clustering
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param Partitioner partition method object
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-30
       */
      abstract_annbfis (int nRules, double dbFrobeniusEpsilon, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, const partitioner & Partitioner, const double dbMinimalTypicality = -1);
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param Partitioner partition method object
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-24
       */
      abstract_annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, const partitioner & Partitioner, double positive_class, double negative_class, ksi::roc_threshold threshold_type, const double dbMinimalTypicality = -1);

      /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobenius norm in clustering
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param Partitioner partition method object
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-30
       */
      abstract_annbfis (int nRules, double dbFrobeniusEpsilon, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, const partitioner & Partitioner, double positive_class, double negative_class, ksi::roc_threshold threshold_type, const double dbMinimalTypicality = -1);

      
      abstract_annbfis(const abstract_annbfis & a);
      abstract_annbfis(abstract_annbfis && a);
      
      /** A constructor with implication.
       @param imp implication
       @date 2018-03-29
       */
      abstract_annbfis (const implication & imp, const partitioner & Partitioner);
      
      abstract_annbfis & operator = (const abstract_annbfis & a);
      abstract_annbfis & operator = (abstract_annbfis && a);
      ~abstract_annbfis();
      
      
      
 
      
   protected:     
      /** The method creates a fuzzy rulebase from the dataset.
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param train train dataset 
       * @date  2018-12-24
       * @author Krzysztof Siminski
       * 
       */
      virtual void createFuzzyRulebase (
         int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient,
         const dataset & train); 
   public:   
      /** 
       @return rulebase's answer of a data item
       @param item data item to elaborate answer for
       */
      double answer (const datum & item) const ;

      /** A method elaborates an answer of a datum (data item). 
       * @param d datum to elaborate answer for 
       * @return The method returns a number.
       */   
      virtual number elaborate_answer (const datum & d) const; 
      
      virtual void train_discriminative_model (const dataset & ds);
      /** The method elaborates the answer of the discriminative_model for a datum 
       @param d a datum to elaborate answer for
       @return just a value :-)
       */
      virtual double discriminate (const datum & d); 
      
       /** Function that partitions the data set.
       @param X dataset to partition
       @date 2019-12-24 */
      virtual partition doPartition (const dataset & X) = 0;
       
   };
}

#endif 

