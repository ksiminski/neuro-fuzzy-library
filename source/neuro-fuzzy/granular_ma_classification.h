
#ifndef GRANULAR_MA_CLASSIFICATION_H
#define GRANULAR_MA_CLASSIFICATION_H

#include "../neuro-fuzzy/granular_nfs_classification.h"
#include "../neuro-fuzzy/ma.h"

namespace ksi
{
   class granular_ma_classification : virtual public granular_nfs_classification, virtual public ma 
   {
       
    public:
      granular_ma_classification (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate,
            const double dbPositiveClass, 
            const double dbNegativeClass, 
            ksi::roc_threshold threshold_type);
      granular_ma_classification (
          const int number_of_rules,
          const int number_of_clustering_iterations,
          const int number_of_tuning_iterations,
          double dbLearningCoefficient, 
          bool bNormalisation, 
          const t_norm & tnorm,
          const int number_of_data_to_read,
          const int minimal_number_of_granules_in_set,
          const int maximal_number_of_granules_in_set,
          const int number_of_data_to_generate,
          const double dbPositiveClass, 
          const double dbNegativeClass, 
          ksi::roc_threshold threshold_type);
      
      granular_ma_classification (const granular_ma_classification & wzor);
      granular_ma_classification (granular_ma_classification && wzor);
      granular_ma_classification & operator= (const granular_ma_classification & wzor);
      granular_ma_classification & operator= (granular_ma_classification && wzor);
      virtual ~granular_ma_classification ();
      
   protected:
       void initializeName ();
      
   
   protected:
       virtual void createFuzzyNonGranularRulebase(
//             const int nRules, 
            const int nClusteringIterations, 
            const int nTuningIterations, 
            const double dbLearningCoefficient, 
            const dataset & train);
      
    public:
      virtual ksi::neuro_fuzzy_system * clone() const;
       
      /** 
       @return rulebase's answer of a data item
       @param item data item to elaborate answer for
       */
      virtual double answer (const datum & item) const;
      
      
    
        
    

        
   };
}


#endif
