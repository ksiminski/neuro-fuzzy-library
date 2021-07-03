/** @file */

#ifndef MA_H
#define MA_H

#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "../common/number.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/abstract-ma.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

namespace ksi
{
   /** Mamdani-Assilan neuro-fuzzy system  */
   /** gaussian fuzzy sets in premises
    */
   class ma : virtual public abstract_ma
   {
   protected:  
 
   public:
      
      ma();   
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @date  2019-07-15
       */
      ma (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm);
      ma (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, double positive_class, double negative_class, ksi::roc_threshold threshold_type);
      
      ma(const ma & a);
      ma(ma && a);
      ma & operator = (const ma & a);
      ma & operator = (ma && a);
      ~ma();
     
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ; 
      
      virtual discriminative_model * clone_discriminant () const;
      virtual generative_model * clone_generator () const; 
      
      void set_name ();
       
      virtual partition doPartition (const dataset & X);
      
   };
}




#endif 
