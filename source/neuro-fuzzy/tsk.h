/** @file */

#ifndef TSK_H
#define TSK_H


#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "../common/number.h"
#include "../common/data-modifier.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/abstract-tsk.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

namespace ksi
{
   /** Takagi-Sugeno-Kang neuro-fuzzy system  */
   /** gaussian fuzzy sets in premises
    */
   class tsk : public abstract_tsk
   {
      
   public:
      
      tsk();      
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @date  2019-07-15
       */
      tsk (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm);
      
      tsk (int nRules, int nClusteringIterations);

      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param modifier data modifier one or a chain of modifiers
       * @date  2021-01-08
       */
      tsk (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm,
          const ksi::data_modifier & modifier);



      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @date  2019-12-22
       */
      tsk (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, double positive_class, double negative_class, ksi::roc_threshold threshold_type);


      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @param modifier data modifier one or a chain of modifiers
       * @date  2021-01-09
       */
      tsk (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, double positive_class, double negative_class, ksi::roc_threshold threshold_type,
          const ksi::data_modifier & modifier);

      
      
      /** 
       * @param trainDataFile 
       * @param testDataDile
       * @param resultsFile
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param bNormalisation normalisation of data
       * @date 2020-04-27 */
      tsk(const std::string & trainDataFile,
          const std::string & testDataFile,
          const std::string & resultsFile,
          const int nRules,
          const int nClusteringIterations,
          const int nTuningIterations,
          const double dbLearningCoefficient,
          const t_norm & tnorm,
          const bool bNormalisation);

      /** 
       * @param trainDataFile 
       * @param testDataDile
       * @param resultsFile
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param bNormalisation normalisation of data
       * @param modifier data modifier one or a chain of modifiers
       * @date 2021-01-18 */
      tsk(const std::string & trainDataFile,
          const std::string & testDataFile,
          const std::string & resultsFile,
          const int nRules,
          const int nClusteringIterations,
          const int nTuningIterations,
          const double dbLearningCoefficient,
          const t_norm & tnorm,
          const bool bNormalisation,
          const ksi::data_modifier & modifier 
         );
      
      
      tsk(const tsk & a);
      tsk(tsk && a);
      tsk & operator = (const tsk & a);
      tsk & operator = (tsk && a);
      ~tsk();
      
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ;
      
      virtual discriminative_model * clone_discriminant () const;
      virtual generative_model * clone_generator () const;
      
      
      
   protected:
      void set_name ();
       
      virtual partition doPartition (const dataset & X);
  
   public:   
    
      
      
   };
}




#endif 
