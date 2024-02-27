
#ifndef WEIGHTED_ANNBFIS_H
#define WEIGHTED_ANNBFIS_H

#include "../neuro-fuzzy/abstract-annbfis.h"
#include "../tnorms/t-norm.h"
#include "../common/dataset.h"


namespace ksi
{
   class weighted_annbfis : public abstract_annbfis
   {
    public:
      weighted_annbfis ();
      weighted_annbfis (const weighted_annbfis & wzor);
      weighted_annbfis (weighted_annbfis && wzor);
      weighted_annbfis & operator= (const weighted_annbfis & wzor);
      weighted_annbfis & operator= (weighted_annbfis && wzor);
      virtual ~weighted_annbfis ();
      
     public: 
         
       /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm t-norm
       * @param imp implication
       * @date  2022-05-16
       */  
       weighted_annbfis(const int nRules, 
            const int nClusteringIterations, 
            const int nTuningIterations, 
            const double dbLearningCoefficient,
            const bool bNormalisation,
            const t_norm & tnorm,
            const implication & imp);
       
       
     /** @param imp implication for logical interpretation of fuzzy rulebase
         @date 2022-05-16
         @author Krzysztof Siminski
         */    
       weighted_annbfis (const implication & imp);
      /** The method creates a fuzzy rulebase from the dataset.
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param train train dataset  
       * @date  2022-05-08
       * @author Krzysztof Siminski 
       */
      virtual void createFuzzyRulebase (
         int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient,
         const dataset & train); 
      
   public:
       /** The method sets name and abbreviation of the system */
       void set_name ();
       
   public:
       /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ;
      
   protected:
       
   public:
       /** interface polution :-) */
      virtual discriminative_model * clone_discriminant () const;
      virtual generative_model * clone_generator () const;
   };
}


#endif
