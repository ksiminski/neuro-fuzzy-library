
#ifndef GRANULAR_SUBSPACE_ANNBFIS_REGRESSION_H
#define GRANULAR_SUBSPACE_ANNBFIS_REGRESSION_H

#include "../neuro-fuzzy/granular_nfs_regression.h"
#include "../neuro-fuzzy/subspace-annbfis.h"

namespace ksi
{
   class granular_subspace_annbfis_regression : virtual public granular_nfs_regression, virtual public subspace_annbfis 
   {
    public:
      granular_subspace_annbfis_regression (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate);
      granular_subspace_annbfis_regression (const granular_subspace_annbfis_regression & wzor);
      granular_subspace_annbfis_regression (granular_subspace_annbfis_regression && wzor);
      granular_subspace_annbfis_regression & operator= (const granular_subspace_annbfis_regression & wzor);
      granular_subspace_annbfis_regression & operator= (granular_subspace_annbfis_regression && wzor);
      virtual ~granular_subspace_annbfis_regression ();
   
   protected:
       /** @todo niezaimplementowane
           @warning niezaimplementowane
           */
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
