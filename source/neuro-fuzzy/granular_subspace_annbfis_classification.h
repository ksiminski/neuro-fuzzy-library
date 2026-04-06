
#ifndef GRANULAR_SUBSPACE_ANNBFIS_CLASSIFICATION_H
#define GRANULAR_SUBSPACE_ANNBFIS_CLASSIFICATION_H

#include "../neuro-fuzzy/granular_nfs_classification.h"
#include "../neuro-fuzzy/subspace-annbfis.h"

namespace ksi
{
   class granular_subspace_annbfis_classification : virtual public granular_nfs_classification, virtual public subspace_annbfis
   {
    public:
      granular_subspace_annbfis_classification (const int number_of_data_to_read,
    const int minimal_number_of_granules_in_set,
    const int maximal_number_of_granules_in_set,
    const int number_of_data_to_generate,
    const double dbPositiveClass, 
    const double dbNegativeClass, 
    ksi::roc_threshold threshold_type,
    const ksi::implication & imp);
      
      granular_subspace_annbfis_classification (const granular_subspace_annbfis_classification & wzor);
      granular_subspace_annbfis_classification (granular_subspace_annbfis_classification && wzor);
      granular_subspace_annbfis_classification & operator= (const granular_subspace_annbfis_classification & wzor);
      granular_subspace_annbfis_classification & operator= (granular_subspace_annbfis_classification && wzor);
      virtual ~granular_subspace_annbfis_classification ();
  
   protected:
       virtual void createFuzzyNonGranularRulebase(
//             const int nRules, 
            const int nClusteringIterations, 
            const int nTuningIterations, 
            const double dbLearningCoefficient, 
            const dataset & train, 
            const dataset & validation);
      
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
