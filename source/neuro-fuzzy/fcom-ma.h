/** @file */

#ifndef FCOM_MA_H
#define FCOM_MA_H


#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "../common/number.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/abstract-ma.h"
#include "../neuro-fuzzy/abstract_fcom.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../owas/owa.h"
#include "../dissimilarities/dissimilarity.h"


namespace ksi
{
   /** Takagi-Sugeno-Kang neuro-fuzzy system  */
   /** gaussian fuzzy sets in premises
    */
   class fcom_ma : virtual public abstract_ma, virtual public abstract_fcom
   {       
   public:
      fcom_ma();      
      
      /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobeniu norm for the clustering algorithm
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param Dissimilarity object for dissimilarity
       * @param Owa owa object 
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-20
       */
      fcom_ma (int nRules, double dbFrobeniusEpsilon, int nTuningIterations,
          double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm,
          const ksi::dissimilarity & Dissimilarity, const ksi::owa & Owa, const double dbMinimalTypicality);
  
      /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobeniu norm for the clustering algorithm
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param Dissimilarity object for dissimilarity
       * @param Owa owa object 
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2019-12-22
       */
      fcom_ma (int nRules, double dbFrobeniusEpsilon, int nTuningIterations,
                double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm,
                const ksi::dissimilarity & Dissimilarity, const ksi::owa & Owa, double positive_class, double negative_class, const ksi::roc_threshold threshold_type, const double dbMinimalTypicality);
      

      
      /** constructor
       * @param nRules number of rules
       * @param dbFrobeniusEpsilon epsilon for Frobeniu norm for the clustering algorithm
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param Dissimilarity object for dissimilarity
       * @param Owa owa object 
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_value classification threshold value 
       * @param dbMinimalTypicality minimal typicality for outliers 
       * @date  2024-05-10
       */
      fcom_ma (int nRules, double dbFrobeniusEpsilon, int nTuningIterations,
               double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm,
               const ksi::dissimilarity & Dissimilarity, const ksi::owa & Owa, double positive_class, double negative_class, const double threshold_value, const double dbMinimalTypicality);
      
      fcom_ma(const fcom_ma & a);
      fcom_ma(fcom_ma && a);
      fcom_ma & operator = (const fcom_ma & a);
      fcom_ma & operator = (fcom_ma && a);
      ~fcom_ma();
      
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ;
      
      virtual discriminative_model * clone_discriminant () const;
      virtual generative_model * clone_generator () const;
      
   protected:
      void set_name ();
      virtual partition doPartition (const dataset & X);
            /** Prints extra report from abstract fcom plus add information on
          minimal typicality */
      virtual std::string extra_report() const;
      
   };
}

#endif 
