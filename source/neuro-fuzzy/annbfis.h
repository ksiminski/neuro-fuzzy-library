/** @file */

#ifndef ANNBFIS_H
#define ANNBFIS_H


#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "../common/number.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/abstract-annbfis.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

namespace ksi 
{
   /** Annbfis neuro-fuzzy system  */
   /** annbfis 
    */
   class annbfis : virtual public abstract_annbfis
   {
   protected: 
      
 
      
   public:
      
      annbfis();   
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @date  2019-07-16
       */
      annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp);
      
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param modifier data modifier one or a chain of modifiers
       * @date  2021-01-08
       */
      annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, const ksi::data_modifier & modifier);

   protected:     
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @date  2019-07-16
       */
      annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, const partitioner & par);
      
   public:   
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @date  2019-12-22
       */
      annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, double positive_class, double negative_class, const ksi::roc_threshold threshold_type);

      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @param modifier data modifier one or a chain of modifiers
       * @date  2021-01-09
       */
      annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, double positive_class, double negative_class, const ksi::roc_threshold threshold_type, const ksi::data_modifier & modifier); 
      
      annbfis(const annbfis & a);
      annbfis(annbfis && a);
      
      /** A constructor with implication.
       @param imp implication
       @date 2018-03-29
       */
      annbfis (const implication & imp);
      
      annbfis & operator = (const annbfis & a);
      annbfis & operator = (annbfis && a);
      ~annbfis();
      
      
      
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ;
      
   protected:     
  
      
      
      virtual discriminative_model * clone_discriminant () const;
      virtual generative_model * clone_generator () const;
      
      void set_name ();
      virtual partition doPartition (const dataset & X);
      
    
      
   };
}




#endif 
